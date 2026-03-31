#### Compilación

```bash
$ cd src/
$ flex++ lexer.ll
$ g++ Lexer.cpp Parser.cpp main.cpp -o analyzer
```

#### Ejecución

```bash
$ ./analyzer prueba
```

#### Definición de gramática G.
Para la gramática G = ( N, Σ, P, S), descrita por las siguientes producciones:
> P = {
>> programa → declaraciones sentencias <br>
>> declaraciones → declaraciones declaración | declaración <br>
>> declaración → tipo lista-var **;** <br>
>> tipo → **int** | **float** <br>
>> lista_var → lista_var **,** _**identificador**_ | _**identificador**_ <br>
>> sentencias → sentencias sentencia | sentencia <br>
>> sentencia → _**identificador**_ **=** expresión **;** | **if** **(** expresion **)** sentencias **else** sentencias | **while** **(** expresión **)** sentencias <br>
>> expresion → expresion **+** expresión | expresión **-** expresión | expresión __\*__ expresión | expresion **\/** expresión | _**identificador**_ | **_numero_** <br>
>> expresion → **(** expresion **)** <br>
}

## Preguntas
---
1. Definimos las entradas de la terna como siguen: 
 - __N__ := { programa, declaraciones, sentencias, declaración, tipo, lista-var, , sentencia, expresion}
 - __Σ__ := { int, float, **=** , **,** , **;**, **(**, **)**, if, else, while, +, -, \*, \/ , __identificador__, __numero__}
 - __S__ := programa

---
2. Con fin de que el compilador sea estable es necesario eliminar la ambigüedad en las reglas de producción siguientes:
> expresion → expresion **+** expresión | expresión **-** expresión | expresión __\*__ expresión | expresion **\/** expresión | _**identificador**_ | **_numero_** <br>
> expresion → **(** expresion **)** <br>

### Eliminación de ambigüedad

Primero identificaremos la precedencia de los operadores.

**Precedencia de operadores de forma decreciente**
- ()
- \/, \* 
- +, -

Y siguiendo las reglas de inferencia vistas en clase.
Podemos re-definir el conjunto **P** con las nuevas reglas de producción:

> P = {
>> programa → declaraciones sentencias <br>
>> declaraciones → declaraciones declaración | declaración <br>
>> declaración → tipo lista-var **;** <br>
>> tipo → **int** | **float** <br>
>> lista_var → lista_var **,** _**identificador**_ | _**identificador**_ <br>
>> sentencias → sentencias sentencia | sentencia <br>
>> sentencia → _**identificador**_ **=** expresión **;** | **if** **(** expresion **)** sentencias **else** sentencias | **while** **(** expresión **)** sentencias <br>
>> expresion → e_add 
>> e_add → e_add + e_mult | e_add - e_mult | e_mult <br>
>> e_mult → e_mult * e_sym | e_mult \ e_sym | e_sym <br>
>> e_sym → (expresion) | **identificador** | **numero** <br>
> }

Asi, removemos la ambigüedad de la gramática. Como mencionaba al inicio, esto nos ayuda a que el
compilador identifique la diferencia entre las cadenas 
- (a + b) * c
- a + (b * c)
- (a + (b * c))
Y asi actúe conforme nos convenga.

---
3. Notemos que tanto las nuevas producciones como en las anteriores, existe la recursion izquierda. 
Por lo tanto reescribimos las reglas de producción usando la regla de inferencia presentada en clase 

A → Aα | β 
    A → βA' y A' → αA' | ε

Veamos las producciones que cumplen con la estructura de esta recursion izquierda:

> {
>> declaraciones → declaraciones declaración | declaración <br>
>> declaración → tipo lista-var **;** <br>
>> lista_var → lista_var **,** _**identificador**_ | _**identificador**_ <br>
>> sentencias → sentencias sentencia | sentencia <br>
>> sentencia → _**identificador**_ **=** expresión **;** | **if** **(** expresion **)** sentencias **else** sentencias | **while** **(** expresión **)** sentencias <br>
>> expresion → e_add 
>> e_add → e_add + e_mult | e_add - e_mult | e_mult <br>
>> e_mult → e_mult * e_sym | e_mult \ e_sym | e_sym <br>
>> e_sym → (expresion) | **identificador** | **numero** <br>
> } 

Por ejemplo, en la primera regla de producción a modificar, los valores serian los siguientes: 

a = declaraciones 
α = β = declaración
Asi, definimos el siguiente conjunto de producciones: 

> P_1 = {
>> declaraciones → declaración declaraciones_p 
>> declaraciones_p → declaración declaraciones_p | ε
>> declaración → tipo lista-var **;** <br>
> }

Siguiendo con el algoritmo definimos los siguientes conjuntos:

A = lista_var
α = **,** _**identificador**_
β = _**identificador**_

> P_2 = {
>> lista_var → _**identificador**_ lista_var_p <br>
>> lista_var_p → **,** _**identificador**_ lista_var_p | ε <br>
>}

> P_3 = {
>> sentencias → sentencia sentencias_p <br>
>> sentencias_p → sentencia sentencias_p | ε <br>
>> sentencia → _**identificador**_ **=** expresión **;** | **if** **(** expresion **)** sentencias **else** sentencias | **while** **(** expresión **)** sentencias <br>
>}

> P_3 = {
>> sentencias → sentencia sentencias_p <br>
>> sentencias_p → sentencia sentencias_p | ε <br>
>> sentencia → _**identificador**_ **=** expresión **;** | **if** **(** expresion **)** sentencias **else** sentencias | **while** **(** expresión **)** sentencias <br>
>}

Para este caso, tendremos multiples alphas,

A_1 =  expresion <br>
α = + e_mult, - e_mult <br>
β = e_mult <br>

A_2 = e_mult <br>
α = * e_sym, \ e_sym <br>
β = e_sym <br>

> P_4 = {
>> expresion → e_mult expresion_p <br>
>> expresion_p → + e_mult expresion_p | - e_mult expresion_p | ε <br>
>> e_mult → e_sym e_mult_p <br>
>> e_mult_p →  * e_sym e_mult_p  | \ e_sym e_mult_p | ε <br>
>> e_sym → (expresion) | **identificador** | **numero** <br>
> } 

Asi, re-definimos el conjunto de producciones, de nuevo, como sigue:

> P = {
>> programa → declaraciones sentencias <br>
>> declaraciones → declaración declaraciones_p 
>> declaraciones_p → declaración declaraciones_p | ε
>> declaración → tipo lista-var **;** <br>
>> tipo → **int** | **float** <br>
>> lista_var → _**identificador**_ lista_var_p <br>
>> lista_var_p → **,** _**identificador**_ lista_var_p | ε <br>
>> sentencias → sentencia sentencias_p <br>
>> sentencias_p → sentencia sentencias_p | ε <br>
>> sentencia → _**identificador**_ **=** expresión **;** | **if** **(** expresion **)** sentencias **else** sentencias | **while** **(** expresión **)** sentencias <br>
>> expresion → e_mult expresion_p <br>
>> expresion_p → + e_mult expresion_p | - e_mult expresion_p | ε <br>
>> e_mult → e_sym e_mult_p <br>
>> e_mult_p →  * e_sym e_mult_p  | \ e_sym e_mult_p | ε <br>
>> e_sym → (expresion) | **identificador** | **numero** <br>
> }

4. 

Debido a que no hay una regla de producción con estructura A → αβ1 | αβ2 | αβ3 | .. | φ , no es necesario el realizar 
el proceso de factorizacion izquierda.

5. 
Asi, los conjuntos modificados quedan como :
__N__ := { programa, declaraciones, declaraciones_p, declaración, tipo, lista_var, lista_var_p, sentencias, sentencias_p, sentencia, expresion, expresion_p, e_mult, e_mult_p, e_sym}

__P__ = {
> programa        → declaraciones sentencias <br>
> declaraciones   → declaración declaraciones_p 
> declaraciones_p → declaración declaraciones_p | ε
> declaración     → tipo lista-var **;** <br>
> tipo            → **int** | **float** <br>
> lista_var       → _**identificador**_ lista_var_p <br>
> lista_var_p     → **,** _**identificador**_ lista_var_p | ε <br>
> sentencias      → sentencia sentencias_p <br>
> sentencias_p    → sentencia sentencias_p | ε <br>
> sentencia       → _**identificador**_ **=** expresión **;** | **if** **(** expresion **)** sentencias **else** sentencias | **while** **(** expresión **)** sentencias <br>
> expresion       → e_mult expresion_p <br>
> expresion_p     → + e_mult expresion_p | - e_mult expresion_p | ε <br>
> e_mult          → e_sym e_mult_p <br>
> e_mult_p        →  * e_sym e_mult_p  | \ e_sym e_mult_p | ε <br>
> e_sym           → (expresion) | **identificador** | **numero** <br>
}

6. Definir el Analizador Léxico (lexer.ll) con las acciones léxicas correspondientes. (2 pts.)

7. Implementar el Analizador Sintáctico (Parser.cpp) de descenso recursivo, documentando las funciones de cada No-Terminal, de forma que el programa descrito en el archivo _prueba_ sea reconocido y aceptado por el analizador resultante. (4 pts.)

---
#### Extras

8. Documentar el código. (0.25pts)
9. Proponer 4 archivos de prueba nuevos, 2 válidos y 2 inválidos. (0.25pts)
10. Modificar el Makefile para poder simplificar el proceso de compilación de la práctica. (1pt)

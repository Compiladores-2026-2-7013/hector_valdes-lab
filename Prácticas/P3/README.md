<p  align="center">
  <img  width="200"  src="https://www.fciencias.unam.mx/sites/default/files/logoFC_2.png"  alt="">  <br>Compiladores  2026-2 <br>
  Práctica 3: Analizador sintáctico de descenso predictivo <br> Profesora: Ariel Adara Mercado Martínez
</p>

# Análisis sintáctico descendente predictivo

## Objetivo:
Que el alumno conozca e implemente los principios del análisis sintáctico descendente predictivo, aplicando la construcción de los conjuntos FIRST y FOLLOW, así como la tabla de análisis sintáctico predictivo, para construir un analizador sintáctico LL(1) que, junto con el analizador léxico desarrollado con Flex, permita reconocer programas válidos del lenguaje C_1.


### Estructura del directorio
```c++
p4
├── README.md
└── src //carpeta de código
    ├── prueba //archivo para I/O test
    ├── lib //carpeta para bibliotecas
    │   └── FlexLexer.h //archivo de cabecera (ignorar)
    ├── Makefile //archivo de reglas de compilación
    ├── main.cpp //contiene la función principal del programa
    ├── Production.cpp //archivo para la clase producción
    ├── lexer.ll //archivo de Flex para generación de `scanner`
    ├── Symbol.cpp //archivo para la clase de símbolo
    ├── Grammar.cpp //archivo para la clase de gramática
    ├── ParserLL.cpp //archivo para parser LL(1)
    └── headers //carpeta de archivos de código
        ├── Lexer.hpp //archivo de cabecera para el scanner
        ├── Symbol.h //archivo de cabecera de símbolo
        ├── Production.h //archivo de cabecera de producción
        ├── Symbols.hpp //archivo de cabecera definición de los conjuntos N y Σ
        ├── Grammar.h //archivo de cabecera de gramática
        └── ParserLL.hpp //archivo de cabecera del parser LL(1)

```

### Uso

#### Compilacion

```bash
$ cd src/
$ make
```

#### Ejecucion

```bash
$ ./compiler prueba
```

#### Ejercicios
Para la gramática G = ( N, Σ, P, S), descrita por las siguientes producciones: 
> P = {
>> programa → declaraciones sentencias <br>
>> declaraciones → declaraciones declaracion | declaracion <br>
>> declaracion → tipo lista-var **;** <br>
>> tipo → **int** | **float** <br>
>> lista_var → lista_var **,** _**identificador**_ | _**identificador**_ <br>
>> sentencias → sentencias sentencia | sentencia <br>
>> sentencia → _**identificador**_ **=** expresion **;** | **if** **(** expresion **)** sentencias **else** sentencias | **while** **(** expresión **)** sentencias <br>
>> expresion → expresion **+** expresion | expresion **-** expresion | expresion __\*__ expresion | expresion **/** expresión | _**identificador**_ | **_numero_** <br>
>> expresion → **(** expresion **)** <br>
}


1. Determinar en un archivo Readme, en formato Markdown (.md) o LaTeX (.tex) - con su respectivo PDF, para este último - , los conjuntos _N_, _Σ_ y el símbolo inicial _S_.  (0.5 pts.) <br>
    a. Mostrar en el archivo el proceso de eliminación de ambigüedad o justificar, en caso de no ser necesario. (0.25 pts.) <br>
    b. Mostrar en el archivo el proceso de eliminación de la recursividad izquierda o justificar, en caso de no ser necesario. (0.25 pts.) <br>
    c. Mostrar en el archivo el proceso de factorización izquierda o justificar, en caso de no ser necesario. (0.25 pts.) <br>
    d. Mostrar en el archivo los nuevos conjuntos _N'_ y _P'_, que definen _G'_. (0.25 pts.) <br>
2. Mostrar en el archivo la construcción de los conjuntos FIRST de la gramática _G'_. (1 pt.)
3. Mostrar en el archivo la construcción de los conjuntos FOLLOW de la gramática _G'_. (1 pt.)
4. Mostrar en el archivo la construcción de la tabla de análisis sintáctico predictivo para _G'_. (1 pt.)
5. Sustituir el contenido del Analizador Léxico (lexer.ll) con el implementado en la segunda práctica. (0.5 pts.)
6. Definir en un comentario de _Symbols.hpp_ la gramática _G'_. (0.05 pts.)
7. Definir _Σ_ en un _**enum**_ de _Symbols.hpp_. (0.10 pts.)
8. Definir _N'_ en un _**enum**_ de _Symbols.hpp_. (0.10 pts.)
9. Cargar _N' ∪ Σ_ en _ParserLL.cpp_. (0.25 pts.) 
10. Cargar _P'_ en _ParserLL.cpp_. (0.25 pts.)
11. Cargar la tabla de análisis sintáctico predictivo en _ParserLL.cpp_. (0.25 pts.)
12. Implementar el algoritmo de análisis sintáctico de descenso predictivo en _ParserLL.cpp_ de modo que el programa acepte el archivo _prueba_. (4 pts.)
---
#### Extras

13. Documentar el código. (0.25pts)
14. Proponer 4 archivos de prueba nuevos, 2 válidos y 2 inválidos. (0.25pts)

## Respuestas (Actividades Teóricas)

### 1. Conjuntos $N$, $Σ$ y símbolo inicial $S$ (Gramática Original $G$)
- **Símbolo inicial ($S$)**: `programa`
- **Conjunto de No Terminales ($N$)**: `{ programa, declaraciones, declaracion, tipo, lista_var, sentencias, sentencia, expresion }`
- **Conjunto de Terminales ($Σ$)**: `{ int, float, ;, ,, identificador, =, if, (, ), else, while, +, -, *, /, numero }`

#### a. Eliminación de ambigüedad
La gramática original es ambigua en las producciones de `expresion` puesto que no define precedencia ni asociatividad para los operadores aritméticos (`+`, `-`, `*`, `/`). Para solucionarlo, reestructuramos `expresion` introduciendo nuevos no terminales (`termino` y `factor`) respetando la precedencia tradicional (multiplicativas `*`, `/` sobre aditivas `+`, `-`):
```text
expresion → expresion + termino | expresion - termino | termino
termino → termino * factor | termino / factor | factor
factor → ( expresion ) | identificador | numero
```
Nota: La producción de la estructura *dangling-else* en `sentencia` no presenta ambigüedad en su estado actual, ya que sólo provee la forma `if ( expresion ) sentencias else sentencias` (que requiere el bloque `else` forzosamente, de acuerdo a `P`).

#### b. Eliminación de recursividad izquierda
Identificamos recursividad izquierda directa en `declaraciones`, `lista_var`, `sentencias`, `expresion` y `termino`.
Aplicando la transformación general $A \rightarrow A\alpha \mid \beta \implies A \rightarrow \beta A', A' \rightarrow \alpha A' \mid \epsilon$:

- Para `declaraciones`:
  ```text
  declaraciones → declaracion declaraciones'
  declaraciones' → declaracion declaraciones' | ε
  ```
- Para `lista_var`:
  ```text
  lista_var → identificador lista_var'
  lista_var' → , identificador lista_var' | ε
  ```
- Para `sentencias`:
  ```text
  sentencias → sentencia sentencias'
  sentencias' → sentencia sentencias' | ε
  ```
- Para `expresion` (ya contemplando la de ambigüedad):
  ```text
  expresion → termino expresion'
  expresion' → + termino expresion' | - termino expresion' | ε
  ```
- Para `termino`:
  ```text
  termino → factor termino'
  termino' → * factor termino' | / factor termino' | ε
  ```

#### c. Factorización izquierda
No tenemos producciones en conflicto para aplicar factorización izquierda en esta gramática modificada, pues las producciones de cada terminal no comparten prefijos directos. Específicamente, en `sentencia`, los terminales iniciales son `identificador`, `if` y `while`, los cuales difieren entre sí.

#### d. Conjuntos $N'$ y $P'$ para la gramática $G'$
- $N' = \{$ `programa`, `declaraciones`, `declaraciones'`, `declaracion`, `tipo`, `lista_var`, `lista_var'`, `sentencias`, `sentencias'`, `sentencia`, `expresion`, `expresion'`, `termino`, `termino'`, `factor` $\}$
- $P' = \{$
  1. `programa → declaraciones sentencias`
  2. `declaraciones → declaracion declaraciones'`
  3. `declaraciones' → declaracion declaraciones' | ε`
  4. `declaracion → tipo lista_var ;`
  5. `tipo → int | float`
  6. `lista_var → identificador lista_var'`
  7. `lista_var' → , identificador lista_var' | ε`
  8. `sentencias → sentencia sentencias'`
  9. `sentencias' → sentencia sentencias' | ε`
  10. `sentencia → identificador = expresion ;`
  11. `sentencia → if ( expresion ) sentencias else sentencias`
  12. `sentencia → while ( expresion ) sentencias`
  13. `expresion → termino expresion'`
  14. `expresion' → + termino expresion' | - termino expresion' | ε`
  15. `termino → factor termino'`
  16. `termino' → * factor termino' | / factor termino' | ε`
  17. `factor → ( expresion ) | identificador | numero`
$\}$


### 2. Conjuntos FIRST de la gramática $G'$

- FIRST(factor) = `{ (, identificador, numero }`
- FIRST(termino') = `{ *, /, ε }`
- FIRST(termino) = `{ (, identificador, numero }`
- FIRST(expresion') = `{ +, -, ε }`
- FIRST(expresion) = `{ (, identificador, numero }`
- FIRST(sentencia) = `{ identificador, if, while }`
- FIRST(sentencias') = `{ identificador, if, while, ε }`
- FIRST(sentencias) = `{ identificador, if, while }`
- FIRST(lista_var') = `{ ,, ε }`
- FIRST(lista_var) = `{ identificador }`
- FIRST(tipo) = `{ int, float }`
- FIRST(declaracion) = `{ int, float }`
- FIRST(declaraciones') = `{ int, float, ε }`
- FIRST(declaraciones) = `{ int, float }`
- FIRST(programa) = `{ int, float }`


### 3. Conjuntos FOLLOW de la gramática $G'$

- FOLLOW(programa) = `{ $ }`
- FOLLOW(declaraciones) = `{ identificador, if, while }`
- FOLLOW(declaraciones') = `{ identificador, if, while }`
- FOLLOW(declaracion) = `{ int, float, identificador, if, while }`
- FOLLOW(tipo) = `{ identificador }`
- FOLLOW(lista_var) = `{ ; }`
- FOLLOW(lista_var') = `{ ; }`
- FOLLOW(sentencias) = `{ $, else }`
- FOLLOW(sentencias') = `{ $, else }`
- FOLLOW(sentencia) = `{ identificador, if, while, $, else }`
- FOLLOW(expresion) = `{ ;, ) }`
- FOLLOW(expresion') = `{ ;, ) }`
- FOLLOW(termino) = `{ +, -, ;, ) }`
- FOLLOW(termino') = `{ +, -, ;, ) }`
- FOLLOW(factor) = `{ *, /, +, -, ;, ) }`

### 4. Tabla de Análisis Sintáctico Predictivo $M[A, a]$

> **Notación**: Las celdas muestran la parte derecha de la producción elegida para el símbolo No Terminal $A$ (renglones) y Terminal $a$ (columnas).

| No Terminal \ Terminal | int | float | ; | , | identificador | = | if | ( | ) | else | while | + | - | * | / | numero | $ |
| ---------------------- | :-: | :---: | :-: | :-: | :---: | :-: | :-: | :-: | :-: | :--: | :---: | :-: | :-: | :-: | :-: | :----: | :-: |
| **programa** | `declaraciones sentencias` | `declaraciones sentencias` | | | | | | | | | | | | | | | |
| **declaraciones** | `declaracion declaraciones'` | `declaracion declaraciones'` | | | | | | | | | | | | | | | |
| **declaraciones'** | `declaracion declaraciones'` | `declaracion declaraciones'` | | | `ε` | | `ε` | | | | `ε` | | | | | | |
| **declaracion** | `tipo lista_var ;` | `tipo lista_var ;` | | | | | | | | | | | | | | | |
| **tipo** | `int` | `float` | | | | | | | | | | | | | | | |
| **lista_var** | | | | | `identificador lista_var'` | | | | | | | | | | | | |
| **lista_var'** | | | `ε` | `, identificador lista_var'` | | | | | | | | | | | | | |
| **sentencias** | | | | | `sentencia sentencias'` | | `sentencia sentencias'` | | | | `sentencia sentencias'` | | | | | | |
| **sentencias'** | | | | | `sentencia sentencias'` | | `sentencia sentencias'` | | | `ε` | `sentencia sentencias'` | | | | | | `ε` |
| **sentencia** | | | | | `identificador = expresion ;`| | `if ( expresion ) sentencias else sentencias` | | | | `while ( expresion ) sentencias` | | | | | | |
| **expresion** | | | | | `termino expresion'` | | | `termino expresion'` | | | | | | | | `termino expresion'` | |
| **expresion'** | | | `ε` | | | | | | `ε` | | | `+ termino expresion'` | `- termino expresion'` | | | | |
| **termino** | | | | | `factor termino'` | | | `factor termino'` | | | | | | | | `factor termino'` | |
| **termino'** | | | `ε` | | | | | | `ε` | | | `ε` | `ε` | `* factor termino'` | `/ factor termino'` | | |
| **factor** | | | | | `identificador` | | | `( expresion )` | | | | | | | | `numero` | |

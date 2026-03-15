#### Ejercicios
1. ¿Qué ocurre si en la primera sección se quitan las llaves al nombre de la macro letra? (0.5 pts)
# Resultado:
1. Si quitamos la llaves a la declaracion del uso de la biblioteca __iostream__, ocurre un error de compilacion, ya que estas son necesarias para diferenciar entre el codigo de el lenguaje cpp y el codigo lex.
2. Si quitamos la llaves a la definicion de la expresión regular, __palabra__ igual causaria un error de compilacion, ya que son necesarias para declarar el inicio de una cerradura.

2. ¿Qué ocurre si en la segunda sección se quitan las llaves a las macros? (0.5 pts)
# Resultado:
Si quitamos las llaves a la definicion de los macros, por ejemplo, escribimos **espacio** en lugar de **{espacio}**, el lexer buscara lexemas identicas a "espacio" en lugar de remplazar la definicion de la regex llamada espacio.

3. ¿Cómo se escribe un comentario en flex? (0.5 pts)
# Resultado:
Usando /* text */, pero tiene que ser indentadas las lineas del comentario.

4. ¿Qué se guarda en yytext? (0.5 pts)
# Resultado:
La cadena de texto que esta siendo actualmente evaluada, por el lexer.

5. ¿Qué pasa al ejecutar el programa e introducir cadenas de caracteres y de dígitos por la consola? (0.5 pts)
# Resultado:
Identifica si son palabras o numeros, y ejecuta la accion lexica dependiendo de que regex sea el que genera la palabra siendo evaluada.

6. ¿Qué ocurre si introducimos caracteres como "\*" en la consola? (0.5 pts)
# Resultado:
Solo los imprime de vuelta. Lo cual es la accion lexica default.

7. Modificar al código anterior en un archivo nuevo, de tal manera que reconozca lo siguiente: (2 pts)
    1. La expresión regular para los hexadecimales en lenguaje C++.
    2. 5 palabras reservadas del lenguaje C++.
    3. Los identificadores válidos del lenguaje C++, con longitud máxima de 32 caracteres (**Sugerencia**: use el operador {m,n}).
    4. Los espacios en blanco.
# Observaciones 
1234hola no seria un identificador valido, pero mi programa lo identifica como una cadena de numeros y una cadena generada por mi regex id. 



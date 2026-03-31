#include "headers/Parser.hpp"
#include <iostream>

namespace C_1
{
  Parser::Parser(/* args */)
  {
  }

  Parser::Parser(Lexer *lexer)
  {
    this->lexer = lexer;
  }
    
  Parser::~Parser()
  {
  }

  /**
   * programa → declaraciones sentencias
   *
   * Función del símbolo inicial. Analiza el programa completo exigiendo
   * primero un bloque de declaraciones y luego uno de sentencias.
   */
  void Parser::programa(){
    declaraciones();
    sentencias();
  }

  /**
   * declaraciones → declaración declaraciones_p
   *
   * Punto de entrada del bloque de declaraciones. Siempre requiere al
   * menos una declaración antes de procesar las opcionales.
   */
  void Parser::declaraciones(){
    declaracion();
    declaraciones_p();
  }

  /**
   * declaraciones_p → declaración declaraciones_p | ε
   *
   * Parte auxiliar para eliminar la recursión izquierda de declaraciones.
   * Si el token actual es un tipo (int/float) continúa; de lo contrario
   * produce ε.
   */
  void Parser::declaraciones_p(){
    if (token == t_int || token == t_float) {
        declaracion();
        declaraciones_p();
    }
    // else epsilon
  }

  /**
   * declaración → tipo lista_var ;
   *
   * Una declaración consiste en un tipo de dato, seguido de una lista de
   * variables separadas por comas, y terminada con punto y coma.
   */
  void Parser::declaracion(){
    tipo();
    lista_var();
    if (token == t_semicolon) {
        token = eat();
    } else {
        error("Se esperaba ';' despues de la declaracion de variables");
    }
  }

  /**
   * tipo → int | float
   *
   * Consume el token de tipo de dato (int o float).
   */
  void Parser::tipo(){
    if (token == t_int || token == t_float) {
        token = eat();
    } else {
        error("Se esperaba un tipo de dato (int o float)");
    }
  }

  /**
   * lista_var → identificador lista_var_p
   *
   * Inicia la lista de variables con al menos un identificador.
   */
  void Parser::lista_var(){
    if (token == t_id) {
        token = eat();
        lista_var_p();
    } else {
        error("Se esperaba un identificador en la lista de variables");
    }
  }

  /**
   * lista_var_p → , identificador lista_var_p | ε
   *
   * Parte auxiliar para eliminar la recursión izquierda de lista_var.
   * Mientras haya comas continúa consumiendo identificadores.
   */
  void Parser::lista_var_p(){
    if (token == t_comma) {
        token = eat();
        if (token == t_id) {
            token = eat();
            lista_var_p();
        } else {
            error("Se esperaba un identificador despues de ','");
        }
    }
    // else epsilon
  }

  /**
   * sentencias → sentencia sentencias_p
   *
   * Punto de entrada del bloque de sentencias. Exige al menos una
   * sentencia antes de procesar las opcionales.
   */
  void Parser::sentencias(){
    sentencia();
    sentencias_p();
  }

  /**
   * sentencias_p → sentencia sentencias_p | ε
   *
   * Parte auxiliar para eliminar la recursión izquierda de sentencias.
   * El FIRST(sentencia) = { identificador, if, while }.
   */
  void Parser::sentencias_p(){
    if (token == t_id || token == t_if || token == t_while) {
        sentencia();
        sentencias_p();
    }
    // else epsilon
  }

  /**
   * sentencia → identificador = expresion ;
   *           | if ( expresion ) sentencias else sentencias
   *           | while ( expresion ) sentencias
   *
   * Analiza una sentencia completa según su primer token.
   * - Asignación: identificador seguido de '=', expresión y ';'.
   * - Condicional: if-else con su condición entre paréntesis.
   * - Bucle:       while con su condición entre paréntesis.
   */
  void Parser::sentencia(){
    if (token == t_id) {
        token = eat();
        if (token == t_assign) {
            token = eat();
            expresion();
            if (token == t_semicolon) {
                token = eat();
            } else {
                error("Se esperaba ';' al final de la sentencia");
            }
        } else {
            error("Se esperaba '=' en la asignacion");
        }
    } else if (token == t_if) {
        token = eat();
        if (token == t_lpar) {
            token = eat();
            expresion();
            if (token == t_rpar) {
                token = eat();
                sentencias();
                if (token == t_else) {
                    token = eat();
                    sentencias();
                } else {
                    error("Se esperaba 'else' despues del 'if'");
                }
            } else {
                error("Se esperaba ')' despues de la condicion del 'if'");
            }
        } else {
            error("Se esperaba '(' antes de la condicion del 'if'");
        }
    } else if (token == t_while) {
        token = eat();
        if (token == t_lpar) {
            token = eat();
            expresion();
            if (token == t_rpar) {
                token = eat();
                sentencias();
            } else {
                error("Se esperaba ')' despues de la condicion del 'while'");
            }
        } else {
            error("Se esperaba '(' antes de la condicion del 'while'");
        }
    } else {
        error("Sentencia no reconocida");
    }
  }

  /**
   * expresion → e_mult expresion_p
   *
   * Nivel de menor precedencia (suma/resta). Delega primero en e_mult
   * y luego en la parte recursiva para encadenar sumas/restas.
   */
  void Parser::expresion(){
    e_mult();
    expresion_p();
  }

  /**
   * expresion_p → + e_mult expresion_p | - e_mult expresion_p | ε
   *
   * Parte auxiliar para eliminar la recursión izquierda de expresion.
   * Maneja los operadores aditivos con asociatividad izquierda.
   */
  void Parser::expresion_p(){
    if (token == t_add || token == t_sub) {
        token = eat();
        e_mult();
        expresion_p();
    }
    // else epsilon
  }

  /**
   * e_mult → e_sym e_mult_p
   *
   * Nivel de precedencia media (multiplicación/división). Delega en
   * e_sym y luego en la parte recursiva para encadenar productos.
   */
  void Parser::e_mult(){
    e_sym();
    e_mult_p();
  }

  /**
   * e_mult_p → * e_sym e_mult_p | / e_sym e_mult_p | ε
   *
   * Parte auxiliar para eliminar la recursión izquierda de e_mult.
   * Maneja los operadores multiplicativos con asociatividad izquierda.
   */
  void Parser::e_mult_p(){
    if (token == t_mult || token == t_div) {
        token = eat();
        e_sym();
        e_mult_p();
    }
    // else epsilon
  }

  /**
   * e_sym → ( expresion ) | identificador | numero
   *
   * Nivel de mayor precedencia. Maneja los factores atómicos:
   * expresiones parentizadas, identificadores y literales numéricos.
   */
  void Parser::e_sym(){
    if (token == t_lpar) {
        token = eat();
        expresion();
        if (token == t_rpar) {
            token = eat();
        } else {
            error("Se esperaba ')' cerrando la expresion");
        }
    } else if (token == t_id) {
        token = eat();
    } else if (token == t_num) {
        token = eat();
    } else {
        error("Factor no reconocido");
    }
  }

  /************************************************************************/
  /**                                                                    **/
  /**                       Funciones auxiliares                         **/
  /**                                                                    **/
  /************************************************************************/

  /**
   * Solicita el siguiente token al lexer.
   * @return  el token leído como valor enum Token.
   */
  Token Parser::eat(){
    return (Token) lexer->yylex();
  }

  /**
   * Imprime un mensaje de error sintáctico con la línea donde ocurrió.
   * @param msg  descripción del error encontrado.
   */
  void Parser::error(string msg){
    cout << "ERROR DE SINTAXIS: " << msg
         << " en la linea " << lexer->getLine() << endl;
  }   

  /**
   * Inicia el análisis sintáctico completo del archivo de entrada.
   * Lee el primer token y llama al símbolo inicial (programa).
   * Reporta si la cadena es aceptada o rechazada por la gramática.
   */
  void Parser::parse(){
    token = eat();
    programa();
    if(token == t_eof)
      cout << "La cadena es aceptada" << endl;
    else 
      cout << "La cadena no pertenece al lenguaje generado por la gramatica" << endl;
  }

}

%{
  #include <iostream>
%}

%option c++
%option noyywrap

hexa_digit {digito}|[A-F]|[a-f]
digito [0-9]
letra [a-zA-Z]
espacio [ \t\n]
  /* ----- MODIFICACIONES PREGUNTA 7 -----
   
  1. To model the hexadecimal numbers in cpp. 
  The biggest number we can storage with primitive types is 0xfffffffffffffff using a long. 
  2. Removed regex palabra, bc it caused trouble doing the id regex
  */
hexa 0x{hexa_digit}{1,15}
reservadas "if"|"switch"|"case"|"for"|"else"
blanks [ |\t|\n]
mix {digito}|{letra}
id {letra}+{mix}*

  
  /* -------------------------------------- */

%%
{espacio} {/* Para ignorar retorno de carro*/}
{reservadas} { std::cout << "Encontré una palabra reservada: " << yytext << std::endl; }
{hexa} { std::cout << "Encontré un hexadecimal: " << yytext << std::endl; }
{digito}+ { std::cout << "Encontré un número: " << yytext << std::endl; }
  /* Considero multiples retornos de carros como espacio blanco pero no solo uno */
{blanks}+ { std::cout << "Encontré espacios blancos ->" << yytext << "<-"<< std::endl; }
{id} { std::cout << "Encontré un identificador: " << yytext << std::endl; }

%%

int main() {
  FlexLexer* lexer = new yyFlexLexer;
  lexer->yylex();
}

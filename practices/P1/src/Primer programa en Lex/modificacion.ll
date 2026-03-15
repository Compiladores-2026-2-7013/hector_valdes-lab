%{
  #include <iostream>
%}

%option c++
%option noyywrap

digito [0-9]
letra [a-zA-Z]
espacio [ \t\n]
single_spaces [ |\t|\n]
reservadas ["if"|"switch"|"case"|"for"|"else"]
blanks {single_spaces}+|{espacio}
hexa_digit {digito}|[A-F]
hexa {hexa_digit}{2}
id {letra}{1,32}

  /* ----- MODIFICACIONES PREGUNTA 7 ------*/
  /* Removed regex palabra, bc it caused trouble doing the id regex
  /* -------------------------------------- */

%%

{hexa} { std::cout << "Encontré un hexadecimal: " << yytext << std::endl; }
{espacio} { /* La acción léxica puede ir vacía si queremos que el escáner ignore la regla*/}
{digito}+ { std::cout << "Encontré un número: " << yytext << std::endl; }
{reservadas} { std::cout << "Encontré una palabra reservada: " << yytext << std::endl; }
{id} { std::cout << "Encontré un identificador: " << yytext << std::endl; }
{blanks} { std::cout << "Encontré espacios blancos ->" << yytext << "<-"<< std::endl; }

%%

int main() {
  FlexLexer* lexer = new yyFlexLexer;
  lexer->yylex();
}

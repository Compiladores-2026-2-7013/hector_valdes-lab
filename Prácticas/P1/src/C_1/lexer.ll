%{
#include <iostream>
#include <string>
using namespace std;

#include "tokens.hpp"
#include "Lexer.hpp"

%}

%option c++
%option outfile="Lexer.cpp"
%option yyclass="C_1::Lexer"
%option case-insensitive

 /* ---- CONSTANT REGEX ---- */
MAS "+"
MENOS "-"
MUL "*"
DIV "\\"
ASIG "="
LPAR "("
RPAR ")"
COMA ","
PYC ";"

  /* ---- RESERVED WORDS ---- */
IF "if"
INT "int"
WHILE "while"
ELSE "else"
FLOAT "float"

 /* ----- NUMBERS ----- */
DIG [0-9]
HEX_DIG {DIG}|[A-F]|[a-f]

  /*
  The limits of the digits is because I am planning to 
  just implement the analysis of the primitive types. Thus, 
  the largest number we can represent is 2^64(using ufloat), 
  which is equivalent to 0xFFFFFFFFFFFFFFF.
  */
HEX 0x{HEX_DIG}{1,15}
  /* DEC_P := Decimal Point */
DEC_P .{DIG}+
  /* SCNOT := Scientific Notation */
SCNOT .?[Ee]{DIG}+
NUM {DIG}*{DEC_P}?|{HEX}|{DIG}+{SCNOT}

  /* Identifiers */
LETT [a-zA-Z_]
MIXED {DIG}|{LETT}
ID {LETT}{MIXED}*

  /* some here */
ESP [ |\t|\n]*

%%


{MAS} { cout << MAS << "," << yytext << endl; }

{MENOS} { cout << MENOS << "," << yytext << endl; }

{MUL} { cout << MUL << "," << yytext << endl; }

{DIV} { cout << DIV << "," << yytext << endl; }

{ASIG} { cout << ASIG << "," << yytext << endl; }

{LPAR} { cout << LPAR << "," << yytext << endl; }

{RPAR} { cout << RPAR << "," << yytext << endl; }

{COMA} { cout << COMA << "," << yytext << endl; }

{PYC} { cout << PYC << "," << yytext << endl; }

{IF} { cout << IF << "," << yytext << endl; }

{INT} { cout << INT << "," << yytext << endl; }

{WHILE} { cout << WHILE << "," << yytext << endl; }

{ELSE} { cout << ELSE << "," << yytext << endl; }

{FLOAT} { cout << FLOAT << "," << yytext << endl; }

{NUM} { cout << NUMERO << "," << yytext << endl; }

{ESP} {/* We'll ignore the blanks characters */}

{ID} { cout << ID << "," << yytext << endl; }

.   { cout << "ERROR LEXICO" << yytext << endl;}

%%

int yyFlexLexer::yywrap(){
    return 1;
}


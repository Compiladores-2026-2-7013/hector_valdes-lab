%{
#include <iostream>
#include <string>
using namespace std;

#include "headers/Symbols.hpp"
#include "headers/Lexer.hpp"

int line = 1;
%}

%option c++
%option yyclass="Lexer"

 /* ---- Operators ---- */
MAS   "+"
MENOS "-"
MUL   "*"
DIV   "/"
ASIG  "="
LPAR  "("
RPAR  ")"
COMA  ","
PYC   ";"

 /* ---- Reserved words ---- */
IF    "if"
ELSE  "else"
WHILE "while"
INT   "int"
FLOAT "float"

 /* ---- Numbers ---- */
DIGIT  [0-9]
DEC_P  \.{DIGIT}+
NUM    {DIGIT}+{DEC_P}?

 /* ---- Identifiers ---- */
LETTER [a-zA-Z_]
MIXED  [a-zA-Z0-9_]
ID     {LETTER}{MIXED}*

%%

{INT}    { return t_int;       }
{FLOAT}  { return t_float;     }
{IF}     { return t_if;        }
{ELSE}   { return t_else;      }
{WHILE}  { return t_while;     }

{ID}     { return t_id;        }
{NUM}    { return t_num;       }

{ASIG}   { return t_assign;    }
{COMA}   { return t_comma;     }
{PYC}    { return t_semicolon; }
{LPAR}   { return t_lpar;      }
{RPAR}   { return t_rpar;      }
{MAS}    { return t_add;       }
{MENOS}  { return t_sub;       }
{MUL}    { return t_mult;      }
{DIV}    { return t_div;       }

[ \t\r]+ { /* skip whitespace */    }
"\n"     { line++;                  }

<<EOF>>  { return t_eof;       }

.        { cout << "ERROR LEXICO '" << yytext
                << "' en la linea " << line << endl; }

%%

int yyFlexLexer::yywrap() {
    return 1;
}

int Lexer::getLine() {
    return line;
}

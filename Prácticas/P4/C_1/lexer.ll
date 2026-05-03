%{
#include <sstream>
#include <cstdlib>

#include "Parser.hpp"
#include "Lexer.hpp"

using namespace std;

#undef YY_DECL 
#define YY_DECL int c_1::Lexer::lex(c_1::Parser::semantic_type *yylval) 
%}

%option c++
%option noyywrap
%option outfile="Lexer.cpp"
%option yyclass="Lexer"


DIGIT  [0-9]
DEC_P  \.[0-9]+
NUM    {DIGIT}+{DEC_P}?

LETTER [a-zA-Z_]
MIXED  [a-zA-Z0-9_]
ID     {LETTER}{MIXED}*

WSPC [ \t\n\r]+

%%

"int"   { return Parser::token::INT; }
"float" { return Parser::token::FLOAT; }
"if"    { return Parser::token::IF; }
"else"  { return Parser::token::ELSE; }
"while" { return Parser::token::WHILE; }

"+"	{ return Parser::token::MAS; }
"-"	{ return Parser::token::MENOS; }
"*"	{ return Parser::token::MUL; }
"/"	{ return Parser::token::DIV; }
"=" { return Parser::token::ASIG; }
";" { return Parser::token::PYC; }
"," { return Parser::token::COMA; }

"("	{ return Parser::token::LPAR; }
")"	{ return Parser::token::RPAR; }
"{" { return Parser::token::LKEY; }
"}" { return Parser::token::RKEY; }

{NUM}	{
	 yylval->sval = strdup(yytext);
	 return Parser::token::NUM;
	}

{ID} {
    yylval->sval = strdup(yytext);
    return Parser::token::ID;
}

{WSPC}  { /* Ignoramos espacios en blanco */ }

.	{
	  cout << "Error léxico en la línea: " << yylineno << " -> '" << yytext << "'" << endl;
	}


<<EOF>> {	
         yyterminate();
        }

%%

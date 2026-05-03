%{
#include <sstream>
#include <cstdlib>

#include "Parser.hpp"
#include "Lexer.hpp"

using namespace std;

#undef YY_DECL // Buena práctica
#define YY_DECL int calc::Lexer::lex(calc::Parser::semantic_type *yylval) // Referencia a 1 en Lexer.hpp
%}

%option c++
%option noyywrap
%option outfile="Lexer.cpp"
%option yyclass="Lexer"


DIG [0-9]
WSPC [ \t]+
FLT {DIG}+\.{DIG}+

%%


"+"	{
	 cout << "Terminal + detectado" << endl;	
	 return Parser::token::MAS;
	}

"-"	{
	 cout << "Terminal - detectado" << endl;	
	 return Parser::token::MENOS;
	}

"/"	{
	 cout << "Terminal / detectado" << endl;	
	 return Parser::token::DIV;
	}

"*"	{
	 cout << "Terminal * detectado" << endl;	
	 return Parser::token::MUL;
	}

"("	{
	 cout << "Terminal ( detectado" << endl;	
	 return Parser::token::PARIZQ;
	}

")"	{
	 cout << "Terminal ) detectado" << endl;	
	 return Parser::token::PARDER;
	}

{FLT}	{
	 cout << "Terminal numérico flotante " << yytext << " detectado" << endl;
	 yylval->numero.val = atof(yytext);
	 yylval->numero.tipo = 2; /* 2: Flotante */
	 return Parser::token::NUM;
	}

{DIG}+	{
	 cout << "Terminal numérico entero " << yytext << " detectado" << endl;
	 yylval->numero.val = atof(yytext);
	 yylval->numero.tipo = 1; /* 1: Entero */
	 return Parser::token::NUM;
	}

{WSPC}  { /* Ignoramos espacios en blanco */ }

"\n"    {  return Parser::token::ENDL; }

.	{
	  cout << "Error léxico en la línea: " << yylineno << " -> " << yytext << endl;
	}


<<EOF>> {	
         yyterminate();
        }


%%


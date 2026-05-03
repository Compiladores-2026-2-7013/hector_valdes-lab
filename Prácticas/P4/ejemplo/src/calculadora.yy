%{
#include <iostream>
#include <fstream>
#include <string>
#include <FlexLexer.h>
using namespace std;
%}

%language "C++"
%require "3.2"
%defines "Parser.hpp"
%output "Parser.cpp"
 
%define api.parser.class {Parser}
%define api.namespace {calc}
%parse-param {Lexer* lexer}

%code requires
{
    namespace calc {
        class Lexer;
    } // namespace calc
} // %code requires
 
%code
{
 #include "Lexer.hpp"
 #define yylex(x) lexer->lex(x) // Referencia a 1 en Lexer.hpp
}

%union {
  struct { 
    double val; //valor unificado
    int tipo; //1: entero, 2: flotante
  } numero;
}

%token<numero> NUM
%token ENDL

%left MAS MENOS
%left MUL DIV

%precedence UMINUS

%nonassoc PARIZQ
%nonassoc PARDER

%type<numero> expresion

%start lines

%%

lines:
    lines line
  | line
  ;

line: 
    expresion ENDL { 
        cout << "Evaluación correcta: " << $1.val;
        if($1.tipo == 2) cout << " (flotante)";
        else cout << " (entero)";
        cout << endl; 
    }
  | ENDL { }
  ;

expresion : expresion MAS expresion   { $$.val = $1.val + $3.val; $$.tipo = ($1.tipo == 2 || $3.tipo == 2) ? 2 : 1; }
	  | expresion MENOS expresion { $$.val = $1.val - $3.val; $$.tipo = ($1.tipo == 2 || $3.tipo == 2) ? 2 : 1; }
	  | expresion MUL expresion   { $$.val = $1.val * $3.val; $$.tipo = ($1.tipo == 2 || $3.tipo == 2) ? 2 : 1; }
	  | expresion DIV expresion   { $$.val = $1.val / $3.val; $$.tipo = ($1.tipo == 2 || $3.tipo == 2) ? 2 : 1; }
	  | MENOS expresion %prec UMINUS { $$.val = -$2.val; $$.tipo = $2.tipo; }
	  | PARIZQ expresion PARDER   { $$ = $2; }
	  | NUM                       { $$ = $1; }
	  ;

%%

void calc::Parser::error(const std::string& msg) {
    std::cerr << msg << '\n';
}


#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char *argv[]){
    if(argc < 2){
        cout<<"Faltan argumentos "<<endl;
        return EXIT_FAILURE;
    }
    filebuf fb;
    fb.open(string(argv[1]), ios::in);
    istream in(&fb);
    calc::Lexer lexer(&in);
    calc::Parser parser(&lexer);
    parser.parse();
    fb.close();
    return 0;
    /*
    calc::Lexer scanner{ std::cin, std::cerr };
    calc::Parser parser{ &scanner };
    //std::cout.precision(10);
    parser.parse();*/
}

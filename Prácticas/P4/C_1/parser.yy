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
%define api.namespace {c_1}
%parse-param {Lexer* lexer}

%code requires
{
    namespace c_1 {
        class Lexer;
    } 
} 
 
%code
{
 #include "Lexer.hpp"
 #define yylex(x) lexer->lex(x) 
}

%union {
  char *sval;
}

%token<sval> ID
%token<sval> NUM
%token INT FLOAT 
%token IF ELSE WHILE
%token ASIG PYC COMA 
%token LPAR RPAR LKEY RKEY

%left MAS MENOS
%left MUL DIV

%nonassoc IFX
%nonassoc ELSE

%start programa

%%

programa: declaraciones sentencias { cout << "✔ Programa analizado correctamente." << endl; };

declaraciones: 
      declaraciones declaracion 
    | declaracion 
    ;

declaracion: 
      tipo lista_var PYC 
    ;

tipo: 
      INT 
    | FLOAT 
    ;

lista_var: 
      lista_var COMA ID 
    | ID 
    ;

sentencias: 
      sentencias sentencia 
    | sentencia 
    ;

sentencia: 
      ID ASIG expresion PYC 
    | IF LPAR expresion RPAR LKEY sentencias RKEY ELSE LKEY sentencias RKEY
    | WHILE LPAR expresion RPAR LKEY sentencias RKEY 
    | error PYC { cout << ">> Error en la sentencia. Intentando recuperar..." << endl; }
    ;

expresion: 
      expresion MAS expresion 
    | expresion MENOS expresion 
    | expresion MUL expresion 
    | expresion DIV expresion 
    | LPAR expresion RPAR 
    | ID 
    | NUM 
    ;

%%

void c_1::Parser::error(const std::string& msg) {
    std::cerr << "❌ Error Sintáctico: " << msg << '\n';
}

#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char *argv[]){
    if(argc < 2){
        cout<<"Faltan argumentos. Uso: ./c1_parser <archivo_prueba> "<<endl;
        return EXIT_FAILURE;
    }
    filebuf fb;
    fb.open(string(argv[1]), ios::in);
    if (!fb.is_open()) {
        cout << "No se pudo abrir el archivo " << argv[1] << endl;
        return EXIT_FAILURE;
    }
    istream in(&fb);
    c_1::Lexer lexer(&in);
    c_1::Parser parser(&lexer);
    
    int result = parser.parse();
    
    fb.close();
    return result;
}

#include "headers/ParserLL.hpp"


ParserLL::ParserLL(Lexer *lexer)
{
    this->lexer = lexer;
    loadSyms();
    loadProds();
    loadTable();
}

ParserLL::~ParserLL()
{
}


void ParserLL::loadSyms()
{
  grammar.setNum(17, 16);
  grammar.start = PROGRAMA;
  
  grammar.addSymbol(t_eof, Symbol(t_eof));
  grammar.addSymbol(t_int, Symbol(t_int));
  grammar.addSymbol(t_float, Symbol(t_float));
  grammar.addSymbol(t_semicolon, Symbol(t_semicolon));
  grammar.addSymbol(t_comma, Symbol(t_comma));
  grammar.addSymbol(t_id, Symbol(t_id));
  grammar.addSymbol(t_assign, Symbol(t_assign));
  grammar.addSymbol(t_if, Symbol(t_if));
  grammar.addSymbol(t_lpar, Symbol(t_lpar));
  grammar.addSymbol(t_rpar, Symbol(t_rpar));
  grammar.addSymbol(t_else, Symbol(t_else));
  grammar.addSymbol(t_while, Symbol(t_while));
  grammar.addSymbol(t_add, Symbol(t_add));
  grammar.addSymbol(t_sub, Symbol(t_sub));
  grammar.addSymbol(t_mult, Symbol(t_mult));
  grammar.addSymbol(t_div, Symbol(t_div));
  grammar.addSymbol(t_num, Symbol(t_num));

  grammar.addSymbol(strEmpty, Symbol(strEmpty));
  grammar.addSymbol(PROGRAMA, Symbol(PROGRAMA));
  grammar.addSymbol(DECLARACIONES, Symbol(DECLARACIONES));
  grammar.addSymbol(DECLARACIONES_PRIMA, Symbol(DECLARACIONES_PRIMA));
  grammar.addSymbol(DECLARACION, Symbol(DECLARACION));
  grammar.addSymbol(TIPO, Symbol(TIPO));
  grammar.addSymbol(LISTA_VAR, Symbol(LISTA_VAR));
  grammar.addSymbol(LISTA_VAR_PRIMA, Symbol(LISTA_VAR_PRIMA));
  grammar.addSymbol(SENTENCIAS, Symbol(SENTENCIAS));
  grammar.addSymbol(SENTENCIAS_PRIMA, Symbol(SENTENCIAS_PRIMA));
  grammar.addSymbol(SENTENCIA, Symbol(SENTENCIA));
  grammar.addSymbol(EXPRESION, Symbol(EXPRESION));
  grammar.addSymbol(EXPRESION_PRIMA, Symbol(EXPRESION_PRIMA));
  grammar.addSymbol(TERMINO, Symbol(TERMINO));
  grammar.addSymbol(TERMINO_PRIMA, Symbol(TERMINO_PRIMA));
  grammar.addSymbol(FACTOR, Symbol(FACTOR));
}

void ParserLL::loadProds()
{
  grammar.addProd(1, Production(PROGRAMA, {DECLARACIONES, SENTENCIAS}));
  grammar.addProd(2, Production(DECLARACIONES, {DECLARACION, DECLARACIONES_PRIMA}));
  grammar.addProd(3, Production(DECLARACIONES_PRIMA, {DECLARACION, DECLARACIONES_PRIMA}));
  grammar.addProd(4, Production(DECLARACIONES_PRIMA, {strEmpty}));
  grammar.addProd(5, Production(DECLARACION, {TIPO, LISTA_VAR, t_semicolon}));
  grammar.addProd(6, Production(TIPO, {t_int}));
  grammar.addProd(7, Production(TIPO, {t_float}));
  grammar.addProd(8, Production(LISTA_VAR, {t_id, LISTA_VAR_PRIMA}));
  grammar.addProd(9, Production(LISTA_VAR_PRIMA, {t_comma, t_id, LISTA_VAR_PRIMA}));
  grammar.addProd(10, Production(LISTA_VAR_PRIMA, {strEmpty}));
  grammar.addProd(11, Production(SENTENCIAS, {SENTENCIA, SENTENCIAS_PRIMA}));
  grammar.addProd(12, Production(SENTENCIAS_PRIMA, {SENTENCIA, SENTENCIAS_PRIMA}));
  grammar.addProd(13, Production(SENTENCIAS_PRIMA, {strEmpty}));
  grammar.addProd(14, Production(SENTENCIA, {t_id, t_assign, EXPRESION, t_semicolon}));
  grammar.addProd(15, Production(SENTENCIA, {t_if, t_lpar, EXPRESION, t_rpar, SENTENCIAS, t_else, SENTENCIAS}));
  grammar.addProd(16, Production(SENTENCIA, {t_while, t_lpar, EXPRESION, t_rpar, SENTENCIAS}));
  grammar.addProd(17, Production(EXPRESION, {TERMINO, EXPRESION_PRIMA}));
  grammar.addProd(18, Production(EXPRESION_PRIMA, {t_add, TERMINO, EXPRESION_PRIMA}));
  grammar.addProd(19, Production(EXPRESION_PRIMA, {t_sub, TERMINO, EXPRESION_PRIMA}));
  grammar.addProd(20, Production(EXPRESION_PRIMA, {strEmpty}));
  grammar.addProd(21, Production(TERMINO, {FACTOR, TERMINO_PRIMA}));
  grammar.addProd(22, Production(TERMINO_PRIMA, {t_mult, FACTOR, TERMINO_PRIMA}));
  grammar.addProd(23, Production(TERMINO_PRIMA, {t_div, FACTOR, TERMINO_PRIMA}));
  grammar.addProd(24, Production(TERMINO_PRIMA, {strEmpty}));
  grammar.addProd(25, Production(FACTOR, {t_lpar, EXPRESION, t_rpar}));
  grammar.addProd(26, Production(FACTOR, {t_id}));
  grammar.addProd(27, Production(FACTOR, {t_num}));
}

void ParserLL::loadTable()
{
  table[PROGRAMA][t_int] = 1;
  table[PROGRAMA][t_float] = 1;

  table[DECLARACIONES][t_int] = 2;
  table[DECLARACIONES][t_float] = 2;

  table[DECLARACIONES_PRIMA][t_int] = 3;
  table[DECLARACIONES_PRIMA][t_float] = 3;
  table[DECLARACIONES_PRIMA][t_id] = 4;
  table[DECLARACIONES_PRIMA][t_if] = 4;
  table[DECLARACIONES_PRIMA][t_while] = 4;

  table[DECLARACION][t_int] = 5;
  table[DECLARACION][t_float] = 5;

  table[TIPO][t_int] = 6;
  table[TIPO][t_float] = 7;

  table[LISTA_VAR][t_id] = 8;

  table[LISTA_VAR_PRIMA][t_comma] = 9;
  table[LISTA_VAR_PRIMA][t_semicolon] = 10;

  table[SENTENCIAS][t_id] = 11;
  table[SENTENCIAS][t_if] = 11;
  table[SENTENCIAS][t_while] = 11;

  table[SENTENCIAS_PRIMA][t_id] = 12;
  table[SENTENCIAS_PRIMA][t_if] = 12;
  table[SENTENCIAS_PRIMA][t_while] = 12;
  table[SENTENCIAS_PRIMA][t_else] = 13;
  table[SENTENCIAS_PRIMA][t_eof] = 13;

  table[SENTENCIA][t_id] = 14;
  table[SENTENCIA][t_if] = 15;
  table[SENTENCIA][t_while] = 16;

  table[EXPRESION][t_lpar] = 17;
  table[EXPRESION][t_id] = 17;
  table[EXPRESION][t_num] = 17;

  table[EXPRESION_PRIMA][t_add] = 18;
  table[EXPRESION_PRIMA][t_sub] = 19;
  table[EXPRESION_PRIMA][t_semicolon] = 20;
  table[EXPRESION_PRIMA][t_rpar] = 20;

  table[TERMINO][t_lpar] = 21;
  table[TERMINO][t_id] = 21;
  table[TERMINO][t_num] = 21;

  table[TERMINO_PRIMA][t_mult] = 22;
  table[TERMINO_PRIMA][t_div] = 23;
  table[TERMINO_PRIMA][t_add] = 24;
  table[TERMINO_PRIMA][t_sub] = 24;
  table[TERMINO_PRIMA][t_semicolon] = 24;
  table[TERMINO_PRIMA][t_rpar] = 24;

  table[FACTOR][t_lpar] = 25;
  table[FACTOR][t_id] = 26;
  table[FACTOR][t_num] = 27;
}

int ParserLL::parse()
{
  stack<int> pila;
  pila.push(t_eof);
  pila.push(PROGRAMA);

  token = eat();

  while (!pila.empty())
  {
    int topIndex = pila.top();
    pila.pop();

    Symbol X = grammar.getSym(topIndex);

    if (X.getType() == terminal)
    {
      if (X.getToken() == token)
      {
        if (token == t_eof)
        {
          aceptar("Programa válido :)");
          return 0; // Accept
        }
        token = eat();
      }
      else
      {
        error("Error sintáctico: se esperaba un token específico");
        return -1;
      }
    }
    else
    {
      NoTerm currentNoTerm = X.getNoTerm();
      if (table[currentNoTerm].find(token) != table[currentNoTerm].end())
      {
        int prodId = table[currentNoTerm][token];
        Production p = grammar.getProd(prodId);
        vector<int> body = p.getBody();

        if (body.size() > 0 && body[0] != strEmpty)
        {
          for (int i = body.size() - 1; i >= 0; i--)
          {
            pila.push(body[i]);
          }
        }
      }
      else
      {
        error("Error sintáctico: no hay producción en la tabla predictiva");
        return -1;
      }
    }
  }
  return -1;
}

void ParserLL::error(string msg)
{
    cout<<msg<<endl;
    exit(EXIT_FAILURE);
}

Token ParserLL::eat()
{
    return (Token) lexer->yylex();    
}

void ParserLL::aceptar(string msg)
{
    cout<<msg<<endl;
}

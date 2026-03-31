#ifndef __SYMBOLS_HPP__
#define __SYMBOLS_HPP__

/** 
 * 1. Definir en un comentario la gramática G(N, T, P, S)
 *
 */


/**
 * 2. Determinar la enumeración para el conjunto T
 */
enum Token { 
    primero, 
    t_eof, 
    t_int, 
    t_float, 
    t_id, 
    t_num, 
    t_if, 
    t_else, 
    t_while, 
    t_assign, 
    t_comma, 
    t_semicolon, 
    t_lpar, 
    t_rpar, 
    t_add, 
    t_sub, 
    t_mult, 
    t_div
};

/**
 * 3. Determinar la enumeración para el conjunto N
 */
enum NoTerm { 
    strEmpty,
    nt_programa,
    nt_declaraciones,
    nt_declaraciones_p,
    nt_declaracion,
    nt_tipo,
    nt_lista_var,
    nt_lista_var_p,
    nt_sentencias,
    nt_sentencias_p,
    nt_sentencia,
    nt_expresion,
    nt_expresion_p,
    nt_e_mult,
    nt_e_mult_p,
    nt_e_sym
};

#endif // !__SYMBOLS_HPP__

#define CONS 7

// #define CONS2 4

#ifndef CONS
#error "We need a cons"
#endif

#ifndef CONS2
#warning "We dont have a constant number 2"
#endif

#pragma GCC warning "You looking good today, be careful"

#ifdef CONS2
#define mult CONS * CONS2
#else 
#define mult CONS * 2
#endif

#include <stdio.h>


/**
* Compiladores 2025-2
*
*/
int main ( void ) {
  printf ("Hola Mundo !\n");
  int cons_times_cons2 = mult;
  printf ("Resultado : %d\n", cons_times_cons2);
  return 0;
}

#include <stdio.h>
#include "symrec.h"
#include "coisas.h"

int yyparse();
symrec* init_table();


int main()
{
  /* Monta o mundo */
  sym_table = init_table(sym_table);
  struct tick * t = init_animation();

  /* Descrição inicial */
  printf("Então você acorda em um quarto... 'Examine' para olhar ao seu redor\n");

  /* Que comece o jogo */
  while (yyparse()) {
    puts("processing stuff...");
animation_loop:
    for(struct tick * q = t; q != NULL; q = q->next) {
      q->function(q->self, q->ctx);
    }
  }

  return 0; 
}







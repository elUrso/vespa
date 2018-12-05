#include <stdio.h>
#include <stdlib.h>
#include "symrec.h"
#include "coisas.h"
#include "avent.tab.h"

/* Variáveis globais */
symrec *sym_table  = NULL; /* Tabela de símbolos global */
symrec *inventario = NULL; /* material com o aventureiro */
Elemento *Posic    = NULL; /* Posição atual */

/* Objetos  */
#include "objetos.c"

/* Lugares */
#include "lugares.c"

//
// Funções auxiliares
//

/* verifica se um objeto está presente e visível */
/* retorna 1 se no local, 2 se no inventário, 0 se não existir*/
int presente(char *nome) {
  /* inventário? */
  if (getsym(inventario, nome)) return 2;
  if (getsym(Posic->cont, nome)) return 1;
  return 0;
}

/* Implementações dos verbos */

/* Macros para testar propriedades comuns */
#define Ativo(x) (x)->Det.obj.ativo
#define Visivel(x) (x)->Det.obj.visivel

/* Transfere um elemento para o inventário */
void Pegar(Elemento *o1, Elemento *o2) {
  if (o1 == NULL || o1->tipo == LUGAR) {
	puts("Não dá para pegar um lugar!");
	return;
  }

  if (o1 == &zumbi) {
    puts("Cê ta louco?!");
    return;
  }
  if (o1->pegavel == 0) {
    puts("Isso não vai sair daí não...");
    return;
  }
  if (Ativo(o1)) {
	if (Visivel(o1)) {
	  int r = presente(o1->nome);
	  switch (r) {
	  case 2:
		printf("Você já está com %s!\n", o1->nome);
		  return;
	  case 1:
		/* retira do local */
		Posic->cont = popsym(Posic->cont, o1->nome);
		/* insere no inventário */
		inventario = putsym(inventario, o1->nome, OBJ,o1);
		printf("Peguei %s\n", o1->nome);
		return;
	  default:
		printf("Não há %s aqui!\n", o1->nome);
		return;
	  }
	}
	printf("Não consigo ver nenhum %s!\n", o1->nome);
  }
  else
	printf("Não existe %s!!!!\n", o1->nome);
}

/* Transfere do inventário para o local atual */
void Largar(Elemento *o1, Elemento *o2) {
  if (o1->tipo == LUGAR) {
	puts("Largue a mão de ser besta!");
	return;
  }
  if (getsym(inventario, o1->nome)) {
	/* retira do inventario */
	inventario = popsym(inventario, o1->nome);

	/* insere no local */
	Posic->cont = putsym(Posic->cont, o1->nome, OBJ,o1);
	return;
  }
  else {
	/* Em inglês for fun */
	puts("You don't have it");
  }
}

/* Descreve um Elemento em detalhes */
void Examinar(Elemento *o1, Elemento *o2) {
  symrec *ptr;

  /* o default é descrever o local atual */
  if (o1 == NULL || o1 == Posic) {
	Olhar(NULL, NULL);
	puts("Aqui tem:");
  int i = 0;
	for (ptr = Posic->cont; ptr != (symrec *) 0;
		 ptr = (symrec *)ptr->next) {
    i++;
	  /* como a lista contém tods os nomes, precisamos filtrar */
	  if (ptr->tipo == OBJ) {
		Elemento *oo = (Elemento *)ptr->value;
		if (Visivel(oo)  && Ativo(oo))
		  printf("\t%s\n", oo->nome);
	  }
	}
  if(i == 0) puts("nada...");
	return;
  }
  if (o1->tipo == OBJ)
	if (Ativo(o1) && Visivel(o1))
	  Olhar(o1, NULL);
	else puts("Oi?");
  else
	puts("Não tenho como responder neste momento");
}

void Olhar(Elemento *o1, Elemento *o2) {
  if (o1) 
	puts((o1->visto == 0)?o1->visto = 1, o1->longa:o1->curta);
  else
	puts((Posic->visto == 0)?Posic->visto = 1, Posic->longa:Posic->curta);
}

void Gritar(Elemento *o1, Elemento *o2){
  puts("YEEAAAAAOOOOOWWWGRRUWL");
}

void HoraRelogio(Elemento *o1, Elemento *o2) {
  if(o1 == &relogio || getsym(inventario, "relogio"))
    printf("São %d:00 em ponto!\n", relogio.Det.obj.estado);
  else
    puts("catorze pras vinte e oito");
}

struct initfunc {
  char *fname;
  Fptr fnct;
};

/* Lista de verbos */
struct initfunc lfunc[] = {
  {"pegue", Pegar},
  {"cate", Pegar},
  {"largue", Largar },
  {"solte", Largar },
  {"jogue", Largar },
  {"examine", Examinar },
  {"olhe", Olhar },
  {"veja", Olhar },
  {"grite", Gritar },
  {"berre", Gritar },
  {"hora", HoraRelogio},
  {0, 0}
};

/* Para objetos */
struct initobj {
  char *name;
  Elemento *obj;
};

/* Lista de objetos */
struct initobj lobjs[] = {
  {"relogio", &relogio},
  {"zumbi", &zumbi},
  { 0, 0}
};

/* Para lugares */
struct initlug {
  char *name;
  Elemento *lug;
};

/* Lista de lugares */
struct initlug llugs[] = {
  {"quarto",  &quarto},
  {"sala",    &sala},
  {"sotao",   &sotao},
  { 0, 0}
};

/* Inicializa a tabela de símbolos passada como argumento */
symrec*  init_table(symrec *sym_table)
{
  /*fix exits*/
  sala.Det.lug.Saidas[4] = &sotao;
  sotao.Det.lug.Saidas[5] = &sala;
  sala.Det.lug.Saidas[3] = &quarto;

  int i;
  symrec *ptr = sym_table;		/* cabeça da lista */
  /* Lista de verbos */
  for (i = 0; lfunc[i].fname != 0; i++) {
	/* insere */
    ptr = putsym(ptr, lfunc[i].fname, VERBO, lfunc[i].fnct);
	/* completa os dados */
    ptr->value = lfunc[i].fnct;
  }
  /* Lista de objetos */
  for (i = 0; lobjs[i].name != 0; i++) {
	Elemento * oo = lobjs[i].obj;
	/* insere */
    ptr = putsym(ptr, lobjs[i].name, OBJ, oo);
	oo->cont = NULL;
  }

  /* Lista de lugares */
  for (i = 0; llugs[i].name != 0; i++) 
	/* insere */
    ptr = putsym(ptr, llugs[i].name, LUGAR,llugs[i].lug);

  /* Coloca os objetos nos lugares */
  
  sotao.cont = putsym(sotao.cont, "relogio", 	  OBJ, &relogio);
  

  /* Ajustes finais */
  relogio.cont=   putsym(relogio.cont,   "hora", VERBO, HoraRelogio);

  Posic = &quarto;
  /* retorna a nova cabeça da lista */
  return ptr;
}

struct tick * init_animation() {
  animation_init:
  evento_tick.next = &evento_zumbi;
  return &evento_tick;
}


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

  if(Posic == &quarto) {
    if(folheto.Det.obj.estado < 3) {
      folheto.Det.obj.estado++;
    } else {
      folheto.Det.obj.ativo = 1;
      puts("Parece que não está tão vazio assim :P");
    }
  }
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

void AbrirPorta(Elemento *o1, Elemento *o2) {
  if(relogio.Det.obj.estado == 0) {
    puts("A porta se abriu, corra livre e feliz! Você escapou.\nCongratulations, you´re a WINNER! (^o^)");
    exit(EXIT_SUCCESS);
  } else
    puts("Ela não quis abrir");
}

void Atirar(Elemento *o1, Elemento *o2) {
  static int life = 2;
  if(getsym(inventario, "municao") != NULL & zumbi.pos == Posic) {
    life--;
    inventario = popsym(inventario, "municao");
    if(life < 0) {
      puts("Hahahahah, agora ele morreu! Acho que tu ganhou mermão!\nOmedetô \\(>.<)/");
      exit(EXIT_SUCCESS);
    }
    puts("Você acertou o bixão, mas ele continua em pé");
    switch(relogio.Det.obj.estado % 4){
      case 0:
        quarto.cont = putsym(quarto.cont, "municao", OBJ, &municao);
      break;
      case 1:
        sotao.cont = putsym(sotao.cont, "municao", OBJ, &municao);
      break;
      case 2:
        porao.cont = putsym(porao.cont, "municao", OBJ, &municao);
      break;
      case 3:
        telhado.cont = putsym(telhado.cont, "municao", OBJ, &municao);
      break;
    }
  } else {
    puts("Ta querendo atirar em quem?!");
  }
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
  {"abra", AbrirPorta},
  {"destranque", AbrirPorta},
  {"atire", Atirar},
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
  {"porta", &porta},
  {"municao", &municao},
  {"arma", &arma},
  {"mapa", &mapa},
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
  {"porao",   &porao},
  {"cozinha",   &cozinha},
  {"telhado",   &telhado},
  {"folheto",   &folheto},
  { 0, 0}
};

/* Inicializa a tabela de símbolos passada como argumento */
symrec*  init_table(symrec *sym_table)
{
  /*fix exits*/
  sala.Det.lug.Saidas[4] = &sotao;
  sala.Det.lug.Saidas[5] = &porao;
  sala.Det.lug.Saidas[2] = &cozinha;
  sala.Det.lug.Saidas[3] = &quarto;
  porao.Det.lug.Saidas[4] = &sala;
  cozinha.Det.lug.Saidas[3] = &sala;
  quarto.Det.lug.Saidas[2] = &sala;
  sotao.Det.lug.Saidas[5] = &sala;
  sotao.Det.lug.Saidas[4] = &telhado;
  telhado.Det.lug.Saidas[5] = &sotao;


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
  cozinha.cont = putsym(cozinha.cont, "porta", OBJ, &porta);
  porao.cont = putsym(porao.cont, "arma", OBJ, &arma);
  cozinha.cont = putsym(cozinha.cont, "municao", OBJ, &municao);
  sala.cont = putsym(sala.cont, "mapa", OBJ, &mapa);
  quarto.cont = putsym(quarto.cont, "folheto", OBJ, &folheto);
  
  

  /* Ajustes finais */
  relogio.cont=   putsym(relogio.cont, "hora", VERBO, HoraRelogio);
  porta.cont=   putsym(relogio.cont, "abra", VERBO, AbrirPorta);
  arma.cont=  putsym(relogio.cont, "atire", VERBO, Atirar);

  Posic = &quarto;
  /* retorna a nova cabeça da lista */
  return ptr;
}

struct tick * init_animation() {
  animation_init:
  evento_jump2.next = &evento_zumbi;
  evento_jump.next = &evento_jump2;
  evento_tick.next = &evento_jump;
  return &evento_tick;
}


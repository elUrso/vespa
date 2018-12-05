/* Parte específica de Objeto */
typedef struct objeto {
  short int ativo;
  short int visivel;
  short int estado;
} Objeto;


/* Parte específica de lugar */
typedef struct lugar {
  struct elemento  *Saidas[6];		/* N,S,L,O,C,B */
} Lugar;

/* Estrutura geral para Elementos */
typedef struct elemento {
  char *nome;
  char *longa;
  char *curta;
  symrec *cont;
  int tipo;
  union {
	Objeto obj;
	Lugar lug;
  } Det;						/* detalhe */
  void (*animacao) (struct elemento *, struct elemento *);
  char genero;
  int visto;
  struct elemento * pos;
  int pegavel;
} Elemento;


/* Ponteiro para função */
typedef void (*Fptr)(Elemento *, Elemento *);

/* Examinar é usada em mais de um lugar. As outras funções não precisam
   de protótipos aqui, mas poderiam ser colocados
*/
void Examinar(Elemento *, Elemento *);

extern Elemento* Posic;			/* Posição atual */

extern symrec *inventario;		/* O que está com o aventureiro */

struct tick {
  Fptr function;
  Elemento * self;
  Elemento * ctx;
  struct tick * next;
};

struct tick * init_animation();
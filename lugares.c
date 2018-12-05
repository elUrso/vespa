Elemento sala = {
  .nome = "sala",
  .genero = 'F',
  .longa = "Rustica e aconchegante, mas há marcas de sangue pelo chão",
  .curta = "Aquele sangue não é meu...",
  .cont = NULL,
  .tipo = LUGAR,
  .Det.lug = {
      .Saidas = {
          /*N*/NULL,
          /*S*/NULL,
          /*L*/NULL,
          /*O*/NULL,
          /*C*/NULL,
          /*B*/NULL}
  },
  .animacao = NULL
};

Elemento quarto = {
  .nome = "quarto",
  .genero = 'M',
  .longa = "Até que o quarto é grande, mas está bem vazio",
  .curta = "mm quarto",
  .cont = NULL,
  .tipo = LUGAR,
  .Det.lug = {
      .Saidas = {
          /*N*/NULL,
          /*S*/NULL,
          /*L*/NULL,
          /*O*/NULL,
          /*C*/NULL,
          /*B*/NULL}
  },
  .animacao = NULL
};

Elemento sotao = {
  .nome = "sotao",
  .genero = 'M',
  .longa = "Parece um lugar bem vazio, mas deve ter algo de útil",
  .curta = "Quanta caixa?! tudo vazia...",
  .cont = NULL,
  .tipo = LUGAR,
  .Det.lug = {
      .Saidas = {
          /*N*/NULL,
          /*S*/NULL,
          /*L*/NULL,
          /*O*/NULL,
          /*C*/NULL,
          /*B*/NULL}
  },
  .animacao = NULL
};

static void jump_scare (Elemento * self , Elemento * ctx) {
    static int lock = 1;
    if(Posic == self && lock) {
      lock = 0;
      zumbi.Det.obj.estado = 1000;
    }
}

static void jump_scare2 (Elemento * self , Elemento * ctx) {
    static int lock = 1;
    if(Posic == self && lock) {
      lock = 0;
      zumbi.Det.obj.estado = 1000;
    }
}

Elemento porao = {
  .nome = "porao",
  .genero = 'M',
  .longa = "um arrepio sobe pela espinha a cada segundo",
  .curta = "aqui da medo",
  .cont = NULL,
  .tipo = LUGAR,
  .Det.lug = {
      .Saidas = {
          /*N*/NULL,
          /*S*/NULL,
          /*L*/NULL,
          /*O*/NULL,
          /*C*/NULL,
          /*B*/NULL}
  },
  /*add trigger to spawn the zombie*/
  .animacao = jump_scare
};

struct tick evento_jump = {
    .function = jump_scare,
    .self = &porao,
    .ctx = NULL,
    .next = NULL
};



Elemento telhado = {
  .nome = "telhado",
  .genero = 'M',
  .longa = "Rapaz, ta frio aqui fora, além de ser muito alto pra pular",
  .curta = "Não rola pular...",
  .cont = NULL,
  .tipo = LUGAR,
  .Det.lug = {
      .Saidas = {
          /*N*/NULL,
          /*S*/NULL,
          /*L*/NULL,
          /*O*/NULL,
          /*C*/NULL,
          /*B*/NULL}
  },
  .animacao = NULL
};

struct tick evento_jump2 = {
    .function = jump_scare,
    .self = &telhado,
    .ctx = NULL,
    .next = NULL
};

Elemento cozinha = {
  .nome = "cozinha",
  .genero = 'M',
  .longa = "Agora sangue vai rolar, tem muita faca aqui! (Você tem medo de faca)",
  .curta = "É uma faca ali?!",
  .cont = NULL,
  .tipo = LUGAR,
  .Det.lug = {
      .Saidas = {
          /*N*/NULL,
          /*S*/NULL,
          /*L*/NULL,
          /*O*/NULL,
          /*C*/NULL,
          /*B*/NULL}
  },
  .animacao = NULL
};


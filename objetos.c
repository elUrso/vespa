Elemento arma    = {
  .nome = "arma",
  .genero = 'F',
  .longa = "Um dispositivo muito efetivo, mas requer balas",
  .curta = "♪ bang bang, you´re dead! ♪",
  .cont = NULL,
  .tipo = OBJ,
  .Det.obj = {
    .ativo = 1,
    .visivel = 1,
    .estado = 0
  },
  .animacao = NULL,
  .pegavel = 1
};

static void tock (Elemento * self , Elemento * ctx) {
    self->Det.obj.estado = self->Det.obj.estado + 1 % 24;
}

Elemento relogio    = {
  .nome = "relogio",
  .genero = 'M',
  .longa = "Tick, tack, ele conta o tempo de forma estranha",
  .curta = "♪ TiK ToK! ♪",
  .cont = NULL,
  .tipo = OBJ,
  .Det.obj = {
    .ativo = 1,
    .visivel = 1,
    .estado = 0
  },
  .animacao = tock,
  .pegavel = 1
};

struct tick evento_tick = {
    .function = tock,
    .self = &relogio,
    .ctx = NULL,
    .next = NULL
};

static void zumbi_move (Elemento * self , Elemento * ctx) {
    static int limit = 8;
    if(Posic == self->pos)
      self->Det.obj.estado -= 1;
    else
      self->Det.obj.estado += 1;
    if(self->Det.obj.estado > limit) {
        if(self->pos != NULL)
          self->pos->cont = popsym(self->pos->cont, "zumbi");
        Posic->cont = putsym(Posic->cont, "zumbi", OBJ, self);
        self->pos = Posic;
        self->Det.obj.estado = 0;
        limit--;
        printf("Ahhhh! Um zumbi está em %s!!!\n", self->pos->nome);
    }
    if(self->Det.obj.estado < 0) {
      puts("Ele vai te pegar!");
    }
    if(self->Det.obj.estado < -2) {
      puts("Ele te pegou e comeu você vivo! Que cena terrível! Você perdeu. LOSER :O");
      exit(EXIT_FAILURE);
    }
}

Elemento zumbi    = {
  .nome = "zumbi",
  .genero = 'M',
  .longa = "Tick, tack, ele conta o tempo de forma estranha",
  .curta = "♪ TiK ToK! ♪",
  .cont = NULL,
  .tipo = OBJ,
  .Det.obj = {
    .ativo = 1,
    .visivel = 1,
    .estado = 0
  },
  .animacao = zumbi_move,
  .pos = NULL,
  .pegavel = 0
};

struct tick evento_zumbi = {
    .function = zumbi_move,
    .self = &zumbi,
    .ctx = NULL,
    .next = NULL
};
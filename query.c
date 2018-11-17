#include "query.h"
#include "player.h"
#include "element.h"
#include "place.h"
#include "str.h"

#include <stdio.h>
#include <stdlib.h>

/* Internal data structures */

struct state {
    char _auto;
    MObj * player;
    MObj * intro;
    struct {
        MObj * locked_room;
    } rooms;
    int state;
};

/* Define methods names */

static char * methods[2] = {
    "eval", NULL
};

/* Define methods itselves */

static void * _eval (void * _self, void * _arg) {
    MObj * self = _self;
    MObj * place;
    struct state * state = self->_state;
    switch(state->state) {
        case 1:
            printf("%s\n\n", Mcall(state->intro, "get name", NULL));
            printf("%s\n\n", Mcall(state->intro, "get Desc", NULL));
        break;
        case 2:
            place = Mcall(state->player, "get location", NULL);
            printf("Local: %s\nDescrição: %s\n", (char *) Mcall(place, "get name", NULL), (char *) Mcall(place, "get Desc", NULL));
            /*Listar objetos das sala na primeira visita*/
        break;
        default:
        break;
    }
    state->state = state->state + 1;

    return NULL;
}

static void * (* action[1]) (void * self, void * arg) = {
    _eval
};

static char * class = "Query";

static void _free (void * _self) {
    MObj * self = (MObj *) _self;
    struct state * state = self->_state;

    free(state);
    free(self);
}

MObj * MQuery (MObj * self, MPack * arg) {
    struct state * state = malloc(sizeof(struct state));
    if(state == NULL) {
        puts("Err MElement");
        exit(EXIT_FAILURE);
    }

    state->_auto = Mpack_bool(arg);
    state->state = 0;

    /* This is a big bit, but is the bit that contains the game story itself*/
    state->intro = Mnew(MElement, Mpack("Introdução", "str", Mpack("F", "str", Mpack("", "str", Mpack("– Droga Katie, você tinha mesmo the tentar roubar a droga da fórmula?! Você deve saber o que vai acontecer com você agora…\nLogo depois, João olhou bem nos olhos dela com uma expressão triste, deu-lhe um abraço e receitou algumas palavras em seu ouvido. Já deixando a sala ele ordenou:\n– Limpem a memória dela… Me desculpe.\n– João! Não, não fui eu! Não foi minha culpa, acredita em mim! Por favor, não me faça esquecer tudo…\nMas ele já havia deixado a sala. Katie foi levada ao complexo de controle de memória e teve suas memórias apagadas por uma droga. Isso foi tudo o que ele conseguia se lembrar.", "str", NULL)))));
    state->player = Mnew(MPlayer, Mpack("Katie", "str", Mpack("F", "str", Mpack("...", "str", Mpack("Não me lembro de muita coisa...", "str", NULL)))));

    state->rooms.locked_room = Mnew(MPlace, Mpack("Quarto fechado", "str", Mpack("M", "str", Mpack("apenas um quarto", "str", Mpack("Apenas um quarto, não há muita coisa além da cama e um botão", "str", NULL)))));
    Mcall(state->player, "set location", Mpack(state->rooms.locked_room, "Obj", NULL));
    /*convetion*/
    Mpack_free(arg);

    self->_methods = methods;
    self->_action = action;

    self->_state = (void *) state;

    self->_class = class;

    self->_Super = NULL;
    self->_Self = self;
    self->_Child = NULL;

    self->_free = _free;

    return self;
}
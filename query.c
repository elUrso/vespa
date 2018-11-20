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
        MObj * patient_2;
        MObj * patient_3;
        MObj * corridor;
        MObj * recovery;
        MObj * elevator;
        MObj * control;
        MObj * preparation;
        MObj * staff;
        MObj * deposit;
        MObj * memory_management;
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
        case 200:
            return &false;
        default:
        break;
    }
    state->state = state->state + 1;

    return &true;
}

static void * (* action[1]) (void * self, void * arg) = {
    _eval
};

static char * class = "Query";

static void _free (void * _self) {
    MObj * self = (MObj *) _self;
    struct state * state = self->_state;

    /*Add Mfree for the objects inside Query*/
    
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

    state->rooms.patient_2 = Mnew(MPlace, Mpack("Quarto 1", "str", Mpack("M", "str", Mpack("apenas um quarto de descanso", "str", Mpack("Apenas um quarto, não há muita coisa além da cama e um botão", "str", NULL)))));
    state->rooms.patient_3 = Mnew(MPlace, Mpack("Quarto 3", "str", Mpack("M", "str", Mpack("apenas um quarto de descanso", "str", Mpack("Apenas um quarto, não há muita coisa além da cama e um botão", "str", NULL)))));
    state->rooms.corridor = Mnew(MPlace, Mpack("Corredor", "str", Mpack("M", "str", Mpack("um corredor bem grande", "str", Mpack("Um corredor bem grande, com várias portas trancadas e duas saídas", "str", NULL)))));
    state->rooms.recovery = Mnew(MPlace, Mpack("Sala de recuperação", "str", Mpack("F", "str", Mpack("com algumas macas e equipamentos estranhos", "str", Mpack("Contém algumas macas e equipamentos estranhos, pode ter alguma coisa escondida nela", "str", NULL)))));
    state->rooms.elevator = Mnew(MPlace, Mpack("Sala de elevadores", "str", Mpack("F", "str", Mpack("tem dois elevadores", "str", Mpack("Uma sala com dois elevadores, porém uma das portas está suja de sangue", "str", NULL)))));
    state->rooms.control = Mnew(MPlace, Mpack("Sala de controle", "str", Mpack("F", "str", Mpack("tem vários botões", "str", Mpack("Tem vários botões na sala, alguns monitores quebrados e um barulho de computador", "str", NULL)))));
    state->rooms.preparation = Mnew(MPlace, Mpack("Sala de preparação", "str", Mpack("F", "str", Mpack("tem vários cabos saindo do teto", "str", Mpack("Vários cabos saem do teto, todos em volta de uma mesa bem grande", "str", NULL)))));
    state->rooms.staff = Mnew(MPlace, Mpack("Sala dos funcionários", "str", Mpack("F", "str", Mpack("uma mesinha de reunião e alguns armários", "str", Mpack("Com vários armários e uma mesa de runião, não tem muito o que falar", "str", NULL)))));
    state->rooms.deposit = Mnew(MPlace, Mpack("Depósito", "str", Mpack("M", "str", Mpack("várias caixas", "str", Mpack("Várias caixas, mas a maioria parece estar vazia", "str", NULL)))));
    state->rooms.memory_management = Mnew(MPlace, Mpack("Sala de operação", "str", Mpack("F", "str", Mpack("tem duas capsulas", "str", Mpack("Não dá pra descrever muito bem, mas tem duas capsulas e é um local bem frio", "str", NULL)))));
    Mcall(state->player, "set location", Mpack(state->rooms.patient_3, "Obj", NULL));
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
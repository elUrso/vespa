#include "query.h"
#include "player.h"
#include "element.h"
#include "out.h"
#include "button.h"
#include "place.h"
#include "list.h"
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

MObj * helper[200];

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
            printf("%s\n\n", (char *) Mcall(state->intro, "get name", NULL));
            printf("%s\n\n", (char *) Mcall(state->intro, "get Desc", NULL));
        break;
        case 2:
            place = Mcall(state->player, "get location", NULL);
            printf("Local: %s\nDescrição: %s\n", (char *) Mcall(place, "get name", NULL), (char *) Mcall(place, "get Desc", NULL));
            MObj * list = Mcall(place, "get List", NULL);
            puts("Lista de objetos:");
            int i = 0;
            for(struct MList_node * p = Mcall(list, "get head", NULL); p != NULL; p = p->next) {
                MObj * element = p->value;
                if(Mcall(element, "get visibility", NULL) == &true) {
                    i++;
                    printf("%d\t%s %s\n", i, (char *) Mcall(element, "get ai", NULL), (char *) Mcall(element, "get name", NULL));
                }
            }
            if(i == 0) puts("Não há objetos");
            puts("");
        break;
        case 3:
        case 5:
            puts("% saídas");
            place = Mcall(state->player, "get location", NULL);
            printf("Local: %s\nDescrição: %s\n", (char *) Mcall(place, "get name", NULL), (char *) Mcall(place, "get Desc", NULL));
            list = Mcall(place, "get paths", NULL);
            puts("Lista de saídas:");
            i = 0;
            for(struct MList_node * p = Mcall(list, "get head", NULL); p != NULL; p = p->next) {
                MObj * element = p->value;
                if(Mcall(element, "get enabled", NULL) == &true) {
                    i++;
                    printf("%d\t%s %s\n", i, (char *) Mcall(element, "get ai", NULL), (char *) Mcall(element, "get name", NULL));
                }
            }
            if(i == 0) puts("Não há saídas");
            puts("");
        break;
        case 4:
            puts("% apertar o botão");
            place = Mcall(state->player, "get location", NULL);
            printf("Local: %s\nDescrição: %s\n", (char *) Mcall(place, "get name", NULL), (char *) Mcall(place, "get Desc", NULL));
            /*later replace it with: get object: botao*/
            Mcall(helper[0], "set state", Mpack(&i_true, "int", NULL));
            puts("");
        break;
        case 6:

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
    
    /*patient_3 outs*/
    MObj * outs = Mcall(state->rooms.patient_3, "get paths", NULL);
    MObj * out = Mnew(MOut, Mpack(state->rooms.corridor, "Obj", Mpack("porta", "str", Mpack("F", "str", Mpack("vai para o corredor", "str", Mpack("vai para o corredor", "str", NULL))))));
    Mcall(out, "set enabled", Mpack(&i_false, "int", NULL));
    Mcall(outs, "insert", Mpack(out, "MObj", Mpack("door", "str", NULL)));
    /*patient_3 objects*/
    MObj * list = Mcall(state->rooms.patient_3, "get List", NULL);
    MObj * button = Mnew(MButton, Mpack("botão", "str", Mpack("M", "str", Mpack("é um botão", "str", Mpack("É um botão, talvez de pra apertar", "str", NULL)))));
    Mcall(button, "set trigger", Mpack("Uma porta se abriu", "str", Mpack(out, "Obj", Mpack("set enabled", "str", Mpack(&i_true, "int", NULL)))));
    Mcall(button, "set state", Mpack(&i_false, "int", NULL));
    Mcall(button, "set visibility", Mpack(&i_true, "int", NULL));
    Mcall(list, "insert", Mpack(button, "MObj", Mpack("button", "str", NULL)));
    helper[0] = button;



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
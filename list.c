#include "list.h"
#include "str.h"

#include <stdio.h>
#include <stdlib.h>

struct node {
    MObj * value;
    char * id;
    struct node * next;
};

struct state {
    int size;
    struct node * head;
};

static char * methods[3] = {
    "insert",
    "query",
    "remove"
};

static void * insert (void * _self, void * _arg) {
    MObj * self = (MObj *) _self;
    MPack * arg = (MPack *) _arg;
    if(arg == NULL) {
        puts("Err MList insert");
        exit(EXIT_FAILURE);
    }
    char * str = Mpack_str(arg->next);
    struct state * state = self->_state;
    struct node * node = malloc(sizeof(struct node));
    if(node == NULL) {
        puts("Err MList insert");
        exit(EXIT_FAILURE);
    }
    node->value = arg->value;
    node->next = state->head;
    node->id = str;
    state->head = node;
    return NULL;
}

static void * query (void * _self, void * _arg) {
    void * q = NULL;
    MObj * self = (MObj *) _self;
    MPack * arg = (MPack *) _arg;
    if(arg == NULL) {
        puts("Err MList query");
        exit(EXIT_FAILURE);
    }
    char * target = Mpack_str(arg);
    struct state * state = self->_state;
    struct node * n = state->head;
    while(n != NULL) {
        if(STRcmp(target, n->id)) {
            q = n->value;
            break;
        }
        n = n->next;
    }
    return q;
}

/*Continue, needs to define free*/
static void * _remove (void * _self, void * arg) {
    return NULL;
}

static void * (* action[3]) (void * self, void * arg) = {
    insert, query, _remove
};

static char * class = "List";



MObj * MList (MObj * self, MPack * arg) {
    struct state * p = malloc(sizeof(struct state));
    if(p == NULL) {
        puts("Err MList");
        exit(EXIT_FAILURE);
    }
    p->size = 0;
    /*convetion*/
    Mpack_free(arg);

    self->_methods = methods;
    self->_action = action;

    self->_state = (void *) p;

    self->_class = class;

    self->_Super = NULL;
    self->_Self = self;
    self->_Child = NULL;

    self->_free = NULL;

    return self;
}

/*
insere(TabSim t, char *n, Elemento *val)
busca(TabSim t, char *n)
int retira(TabSim t, char *n)
*/
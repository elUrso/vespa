#include "list.h"
#include "str.h"

#include <stdio.h>
#include <stdlib.h>

/* Internal data structures */
struct node {
    MObj * value;
    char * id;
    struct node * next;
};

struct state {
    int size;
    struct node * head;
};

/* Define methods names */

static char * methods[3] = {
    "insert",
    "query",
    "remove"
};

/* Define methods itselves */
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
    Mpack_free(_arg);
    if(node == NULL) {
        puts("Err MList insert");
        exit(EXIT_FAILURE);
    }
    node->value = arg->value;
    node->next = state->head;
    node->id = str;
    state->head = node;
    state->size = state->size + 1;
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
    Mpack_free(_arg);
    while(n != NULL) {
        if(STRcmp(target, n->id)) {
            q = n->value;
            break;
        }
        n = n->next;
    }
    return q;
}

static void * _remove (void * _self, void * _arg) {
    void * q = NULL;
    MObj * self = (MObj *) _self;
    MPack * arg = (MPack *) _arg;
    if(arg == NULL) {
        puts("Err MList remove");
        exit(EXIT_FAILURE);
    }
    char * target = Mpack_str(arg);
    struct state * state = self->_state;
    struct node * prev = NULL;
    struct node * n = state->head;
    struct node * next = n->next;
    Mpack_free(_arg);
    while(n != NULL) {
        if(STRcmp(target, n->id)) {
            q = n->value;
            break;
        }
        prev = n;
        n = next;
        next = n->next;
    }
    if(n == NULL) return q; /*Item was not found*/
    if(prev == NULL) {
        state->head = next;
    } else {
        prev->next = next;
    }
    free(n);
    state->size = state->size - 1;
    return q;
}

static void * (* action[3]) (void * self, void * arg) = {
    insert, query, _remove
};

static char * class = "List";

static void _free (void * _self) {
    MObj * self = (MObj *) _self;
    struct state * state = self->_state;
    struct node * q = state->head;
    struct node * p;
    while(q != NULL) {
        p = q->next;
        free(q);
        q = p;
    }
    free(state);
    free(_self);
}


MObj * MList (MObj * self, MPack * arg) {
    struct state * p = malloc(sizeof(struct state));
    if(p == NULL) {
        puts("Err MList");
        exit(EXIT_FAILURE);
    }
    p->size = 0;
    p->head = NULL;
    /*convetion*/
    Mpack_free(arg);

    self->_methods = methods;
    self->_action = action;

    self->_state = (void *) p;

    self->_class = class;

    self->_Super = NULL;
    self->_Self = self;
    self->_Child = NULL;

    self->_free = _free;

    return self;
}

/*
insere(TabSim t, char *n, Elemento *val)
busca(TabSim t, char *n)
int retira(TabSim t, char *n)
*/
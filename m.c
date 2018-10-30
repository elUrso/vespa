#include "m.h"
#include "str.h"

#include <stdio.h>
#include <stdlib.h>

struct MSolve_t {
    MObj * s;
    Mfactory f;
};

static struct MSolve_t Msolve(MObj * object, char * method) {
    if(object == NULL) {
        return (struct MSolve_t) {.s = NULL, .f = NULL};
    }
    int p = STRquery(object->_methods, method);
    if(p == -1) return Msolve(object->_Super, method);
    return (struct MSolve_t) {.s = object, .f = (Mfactory) object->_action[p]};
}

MObj * Mnew(Mfactory type, MPack * arg) {
    MObj * obj = malloc(sizeof(MObj));
    if(obj == NULL) return NULL;
    return type(obj, arg);
}

void * Mcall(MObj * object, char * method, MPack * arg) {
    struct MSolve_t p = Msolve(object, method);
    if(p.f == NULL) return NULL;
    return p.f(p.s, arg);
}

void Mfree(MObj * object) {
    if(object == NULL) return;
    Mfree((MObj *) object->_Super);
    object->_free(object);
}

MPack * Mpack(void * value, char * type, void * next) {
    MPack * p = malloc(sizeof(MPack));
    if(p == NULL) {
        puts("Err Mpack");
        exit(EXIT_FAILURE);
        return NULL;
    }
    p->next = next;
    p->type = type;
    p->value = value;
    return p;
}

void Mpack_free(MPack * pack) {
    if(pack == NULL) return;
    Mpack_free(pack->next);
    free(pack);
}


int Mpack_int(MPack * arg) {
    if(STRcmp(arg->type, "int")) return *((int *)(arg->value));
    puts("Err Mpack_int");
    exit(EXIT_FAILURE);
    return 0;
}

char * Mpack_str(MPack * arg) {
    if(STRcmp(arg->type, "str")) return (char *) (arg->value);
    puts("Err Mpack_char");
    exit(EXIT_FAILURE);
    return 0;
}
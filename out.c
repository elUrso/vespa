#include "element.h"
#include "place.h"
#include "list.h"
#include "str.h"

#include <stdio.h>
#include <stdlib.h>

/* Internal data structures */

struct state {
    MObj * out;
    char enabled;
};
/* Define methods names */

static char * methods[4] = {
    "get out", "get enabled", "set enabled", NULL
};

/* Define methods itselves */

static void * _get_out (void * _self, void * _arg) {
    MObj * self = (MObj *) _self;
    struct state * state = self->_state;
    return state->out;
}

static void * _get_enable (void * _self, void * _arg) {
    MObj * self = (MObj *) _self;
    struct state * state = self->_state;
    return state->enabled ? &true : &false;
}

static void * _set_enable (void * _self, void * _arg) {
    MObj * self = (MObj *) _self;
    MPack * arg = _arg;
    int t = Mpack_int(arg);
    Mpack_free(arg);
    struct state * state = self->_state;
    state->enabled = t;
    return state->enabled ? &true : &false;
}


static void * (* action[3]) (void * self, void * arg) = {
    _get_out, _get_enable, _set_enable
};

static char * class = "Out";

static void _free (void * _self) {
    MObj * self = (MObj *) _self;
    struct state * state = self->_state;
    free(state);
    free(self);
}

/* To create such a behemoth, you need to pass: name, gender M ou F, shortDescription, longDescription */
MObj * MOut (MObj * self, MPack * arg) {
    struct state * state = malloc(sizeof(struct state));

    state->out = Mpack_Obj(arg);
    state->enabled = 1;


    self->_methods = methods;
    self->_action = action;

    self->_state = (void *) state;

    self->_class = class;

    self->_Super = Mnew(MElement, arg->next);
    self->_Self = self;
    self->_Child = NULL;

    self->_free = _free;

    ((MObj *)self->_Super)->_Child = self;

    arg->next = NULL;
    Mpack_free(arg);

    return self;
}
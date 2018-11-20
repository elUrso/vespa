#include "element.h"
#include "object.h"
#include "list.h"
#include "str.h"

#include <stdio.h>
#include <stdlib.h>

/* Internal data structures */

struct state {
    char * adj;
    char bool_visible;
};
/* Define methods names */

static char * methods[3] = {
    "get visibility", "set visibility", NULL
};

/* Define methods itselves */

static void * _get_visibility (void * _self, void * _arg) {
    MObj * self = (MObj *) _self;
    struct state * state = self->_state;
    return (state->bool_visible)? &true: &false;
}

static void * _set_visibility (void * _self, void * _arg) {
    MObj * self = (MObj *) _self;
    struct state * state = self->_state;
    MPack * arg = _arg;
    char i = Mpack_int(arg);
    state->bool_visible = i;
    return (state->bool_visible)? &true: &false;
}


static void * (* action[2]) (void * self, void * arg) = {
    _get_visibility, _set_visibility, 
};

static char * class = "Object";

static void _free (void * _self) {
    MObj * self = (MObj *) _self;
    struct state * state = self->_state;
    free(state);
    free(self);
}

/* To create such a behemoth, you need to pass: name, gender M ou F, shortDescription, longDescription */
MObj * MObject (MObj * self, MPack * arg) {
    struct state * state = malloc(sizeof(struct state));

    state->bool_visible = 1;


    self->_methods = methods;
    self->_action = action;

    self->_state = (void *) state;

    self->_class = class;

    self->_Super = Mnew(MElement, arg);
    self->_Self = self;
    self->_Child = NULL;

    self->_free = _free;

    ((MObj *)self->_Super)->_Child = self;

    return self;
}
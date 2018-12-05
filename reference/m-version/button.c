#include "object.h"
#include "button.h"
#include "list.h"
#include "str.h"

#include <stdio.h>
#include <stdlib.h>

/* Internal data structures */

struct state {
    char bool_active;
    char * message;
    MObj * target;
    char * method;
    MPack * arg;
};
/* Define methods names */

static char * methods[4] = {
    "get state", "set state", "set trigger", NULL
};

/* Define methods itselves */

static void * _get_state (void * _self, void * _arg) {
    MObj * self = (MObj *) _self;
    struct state * state = self->_state;
    return (state->bool_active)? &true: &false;
}

static void * _set_state (void * _self, void * _arg) {
    MObj * self = (MObj *) _self;
    struct state * state = self->_state;
    MPack * arg = _arg;
    char i = Mpack_int(arg);
    Mpack_free(arg);
    state->bool_active = i;
    if(state->bool_active) {
        puts(state->message);
        Mcall(state->target, state->method, state->arg);
    }
    return (state->bool_active)? &true: &false;
}

static void * _set_trigger (void * _self, void * _arg) {
    MObj * self = (MObj *) _self;
    struct state * state = self->_state;
    MPack * arg = _arg;
    state->message = Mpack_str(arg); arg = arg->next;
    state->target = Mpack_Obj(arg); arg = arg->next;
    state->method = Mpack_str(arg);
    state->arg = arg->next;
    arg->next = NULL;
    Mpack_free(_arg);
    return (state->bool_active)? &true: &false;
}


static void * (* action[3]) (void * self, void * arg) = {
    _get_state, _set_state, _set_trigger
};

static char * class = "Button";

static void _free (void * _self) {
    MObj * self = (MObj *) _self;
    struct state * state = self->_state;
    free(state);
    free(self);
}

/* To create such a behemoth, you need to pass: name, gender M ou F, shortDescription, longDescription */
MObj * MButton (MObj * self, MPack * arg) {
    struct state * state = malloc(sizeof(struct state));

    state->bool_active = 1;
    state->message = NULL;
    state->target = NULL;
    state->method = NULL;
    state->arg = NULL;


    self->_methods = methods;
    self->_action = action;

    self->_state = (void *) state;

    self->_class = class;

    self->_Super = Mnew(MObject, arg);
    ((MObj *)self->_Super)->_Child = self;
    self->_Self = self;
    self->_Child = NULL;

    self->_free = _free;

    ((MObj *)self->_Super)->_Child = self;

    return self;
}
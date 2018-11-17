#include "player.h"
#include "element.h"

#include <stdio.h>
#include <stdlib.h>

/* Internal data structures */

struct state {
    MObj * location;
};
/* Define methods names */

static char * methods[3] = {
    "get location", "set location", NULL
};

/* Define methods itselves */
static void * _get_location (void * _self, void * arg) {
    struct state * state = ((MObj *)_self)->_state;
    return state->location;
}

static void * _set_location (void * _self, void * _arg) {
    struct state * state = ((MObj *)_self)->_state;
    MPack * arg = _arg;
    state->location = Mpack_Obj(arg);
    Mpack_free(arg);
    return state->location;
}

static void * (* action[2]) (void * self, void * arg) = {
    _get_location, _set_location    
};

static char * class = "Player";

static void _free (void * _self) {
    MObj * self = (MObj *) _self;
    struct state * state = self->_state;
    free(state);
    free(self);
}

/* To create such a behemoth, you need to pass: name, gender M ou F, shortDescription, longDescription */
MObj * MPlayer (MObj * self, MPack * arg) {
    struct state * state = malloc(sizeof(struct state));

    state->location = NULL;

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
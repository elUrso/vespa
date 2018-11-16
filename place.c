#include "element.h"
#include "place.h"
#include "list.h"
#include "str.h"

#include <stdio.h>
#include <stdlib.h>

/* Internal data structures */

struct state {
    MObj * paths;
};
/* Define methods names */

static char * methods[2] = {
    "get paths", NULL
};

/* Define methods itselves */

static void * _get_paths (void * _self, void * _arg) {
    MObj * self = (MObj *) _self;
    struct state * state = self->_state;
    return state->paths;
}

static void * (* action[1]) (void * self, void * arg) = {
    _get_paths
};

static char * class = "Place";

static void _free (void * _self) {
    MObj * self = (MObj *) _self;
    struct state * state = self->_state;
    Mfree(state->paths);
    free(state);
    free(self);
}

/* To create such a behemoth, you need to pass: name, gender M ou F, shortDescription, longDescription */
MObj * MPlace (MObj * self, MPack * arg) {
    struct state * state = malloc(sizeof(struct state));

    state->paths = Mnew(MList, NULL);


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
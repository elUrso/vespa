#include "element.h"
#include "list.h"
#include "str.h"

#include <stdio.h>
#include <stdlib.h>

/* Internal data structures */

struct state {
    char * name;
    char ** articles;
    char * shortDesc;
    char * longDesc;
    MObj * objList;
    char bool_long_;
};

static char * male[4] = {
    "o", "do", "um", "de um"
};

static char * female[4] = {
    "a", "da", "uma", "de uma"
};

/* Define methods names */

static char * methods[6] = {
    "get name", "get shortDesc", "get longDesc", "get Desc", "get List", NULL
};

/* Define methods itselves */

static void * _get_name (void * _self, void * _arg) {
    MObj * self = (MObj *) _self;
    struct state * state = self->_state;
    return state->name;
}

static void * _get_short (void * _self, void * _arg) {
    MObj * self = (MObj *) _self;
    struct state * state = self->_state;
    return state->shortDesc;
}

static void * _get_long (void * _self, void * _arg) {
    MObj * self = (MObj *) _self;
    struct state * state = self->_state;
    return state->longDesc;
}
static void * _get_desc (void * _self, void * _arg) {
    MObj * self = (MObj *) _self;
    struct state * state = self->_state;
    if(state->bool_long_) return state->shortDesc;
    state->bool_long_ = 1;
    return state->longDesc;
}

static void * _get_list (void * _self, void * _arg) {
    MObj * self = (MObj *) _self;
    struct state * state = self->_state;
    return state->objList;
}

static void * (* action[5]) (void * self, void * arg) = {
    _get_name, _get_short, _get_long, _get_desc, _get_list
};

static char * class = "Element";

static void _free (void * _self) {
    MObj * self = (MObj *) _self;
    struct state * state = self->_state;
    free(state->name);
    free(state->shortDesc);
    free(state->longDesc);
    Mfree(state->objList);
    free(state);
    free(self);
}

/* To create such a behemoth, you need to pass: name, gender M ou F, shortDescription, longDescription */
MObj * MElement (MObj * self, MPack * _arg) {
    struct state * state = malloc(sizeof(struct state));
    MPack * arg = _arg;
    if(arg == NULL) {puts("Err MElement name");exit(EXIT_FAILURE);}
    char * name = Mpack_str(arg); arg = arg->next; if(arg == NULL) {puts("Err MElement gender");exit(EXIT_FAILURE);}
    char * gender = Mpack_str(arg); arg = arg->next; if(arg == NULL) {puts("Err MElement shortDesc");exit(EXIT_FAILURE);}
    char * shortDesc = Mpack_str(arg); arg = arg->next; if(arg == NULL) {puts("Err MElement longDesc");exit(EXIT_FAILURE);}
    char * longDesc = Mpack_str(arg);

    if(state == NULL) {
        puts("Err MElement");
        exit(EXIT_FAILURE);
    }

    state->name = name;
    state->articles = gender[0] == 'M' ? male: female; free(gender);
    state->shortDesc = shortDesc;
    state->longDesc = longDesc;
    state->objList = Mnew(MList, NULL);
    state->bool_long_  = 0;
    /*convetion*/
    Mpack_free(_arg);

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
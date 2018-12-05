#include <stdio.h>
#include <stdlib.h>

#include "str.h"
#include "m.h"
#include "element.h"
#include "object.h"
#include "place.h"
#include "out.h"
#include "query.h"

struct {
    char autoquery;
} game_state;

static void set_state() {
    game_state.autoquery = 1;
}

int main(int argc, char **argv) {
    set_state();
    for(int i = 0; i < argc; i++) {
        if(STRcmp("-q", argv[i])) game_state.autoquery = (game_state.autoquery + 1) % 2;
    }
    
    if(game_state.autoquery) puts("AutoQuery Mode is Set");
    
    MObj * query = Mnew(MQuery, Mpack(&false, "bool", NULL));

    game:
        if(Mcall(query, "eval", NULL) == &false) goto end;
    goto game;
    end:
    return 0;
}
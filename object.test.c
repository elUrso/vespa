#include "m.h"
#include "str.h"
#include "object.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    MObj * l = Mnew(MObject, Mpack("cabo de vassoura", "str", Mpack("M", "str", Mpack("serve parar limpa coisas", "str", Mpack("este belo cabo de vassoura limpa até a sua mãe!", "str", NULL)))));
    int t = 0;
    Mcall(l, "set visibility", Mpack(&t, "int", NULL));
    if(* (char *) Mcall(l, "get visibility", NULL)) puts("Object is visible");
    else puts("Out is invisible");
    Mfree(l);
    return 0;
}
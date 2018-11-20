#include "m.h"
#include "str.h"
#include "button.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    MObj * l = Mnew(MButton, Mpack("cabo de vassoura", "str", Mpack("M", "str", Mpack("serve parar limpa coisas", "str", Mpack("este belo cabo de vassoura limpa até a sua mãe!", "str", NULL)))));
    int t = 1;
    Mcall(l, "set state", Mpack(&t, "int", NULL));
    if(* (char *) Mcall(l, "get state", NULL)) puts("Button is active");
    else puts("Button is inactive");
    Mfree(l);
    return 0;
}
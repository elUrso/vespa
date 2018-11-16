#include "m.h"
#include "str.h"
#include "element.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    MObj * l = Mnew(MElement, Mpack("cabo de vassoura", "str", Mpack("M", "str", Mpack("serve parar limpa coisas", "str", Mpack("este belo cabo de vassoura limpa até a sua mãe!", "str", NULL)))));
    printf("name: %s\n", (char *) Mcall(l, "get name", NULL));
    printf("short: %s\n", (char *) Mcall(l, "get shortDesc", NULL));
    printf("long: %s\n", (char *) Mcall(l, "get longDesc", NULL));
    printf("desc: %s\n", (char *) Mcall(l, "get Desc", NULL));
    printf("desc: %s\n", (char *) Mcall(l, "get Desc", NULL));
    MObj * list = (MObj *) Mcall(l, "get List", NULL);
    if(!STRcmp("List", list->_class)) exit(EXIT_FAILURE);
    Mfree(l);
    return 0;
}
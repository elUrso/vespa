#include "m.h"
#include "str.h"
#include "place.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    MObj * l = Mnew(MPlace, Mpack("Matagal", "str", Mpack("M", "str", Mpack("É um local bem zoado", "str", Mpack("Tem mosquitos demais e você não vai querer ficar aqui", "str", NULL)))));
    printf("name: %s\n", (char *) Mcall(l, "get name", NULL));
    printf("short: %s\n", (char *) Mcall(l, "get shortDesc", NULL));
    printf("long: %s\n", (char *) Mcall(l, "get longDesc", NULL));
    printf("desc: %s\n", (char *) Mcall(l, "get Desc", NULL));
    printf("desc: %s\n", (char *) Mcall(l, "get Desc", NULL));
    MObj * list = (MObj *) Mcall(l, "get paths", NULL);
    if(!STRcmp("List", list->_class)) exit(EXIT_FAILURE);
    Mfree(l);
    return 0;
}
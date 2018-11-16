#include "m.h"
#include "str.h"
#include "place.h"
#include "out.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    MObj * p = Mnew(MPlace, Mpack("Matagal", "str", Mpack("M", "str", Mpack("É um local bem zoado", "str", Mpack("Tem mosquitos demais e você não vai querer ficar aqui", "str", NULL)))));
    MObj * out = Mnew(MOut, Mpack(p, "Obj", Mpack("Ponte", "str", Mpack("M", "str", Mpack("Vai pro matagal", "str", Mpack("Apesar de estar meio desgastada, dá pra usar, ela vai pro matagal", "str", NULL))))));
    /*MObj * l = Mcall(out, "get out", NULL);
    printf("name: %s\n", (char *) Mcall(l, "get name", NULL));
    printf("short: %s\n", (char *) Mcall(l, "get shortDesc", NULL));
    printf("long: %s\n", (char *) Mcall(l, "get longDesc", NULL));
    printf("desc: %s\n", (char *) Mcall(l, "get Desc", NULL));
    printf("desc: %s\n", (char *) Mcall(l, "get Desc", NULL));
    */
    int t = 0;
    Mcall(out, "set enabled", Mpack(&t, "int", NULL));
    if(* ((char *) Mcall(out, "get enabled", NULL))) puts("Out is available");
    else puts("Out is unavailable");
    Mfree(out);
    return 0;
}
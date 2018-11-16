#include "m.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    MObj * l = Mnew(MList, NULL);
    MObj * t = 0;
    /*printf("%lld\n", (long long int) l);*/
    Mcall(l, "insert", Mpack(l, "MObj", Mpack("self", "str", NULL)));
    t = Mcall(l, "query", Mpack("self", "str", NULL));
    /*printf("%lld\n", (long long int) t);*/
    if(t != l) exit(EXIT_FAILURE);
    return 0;
}
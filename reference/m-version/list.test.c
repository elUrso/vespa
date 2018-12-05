#include "m.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    MObj * l = Mnew(MList, NULL);
    MObj * t = NULL;
    MObj * q = NULL;
    /*printf("%lld\n", (long long int) l);*/
    Mcall(l, "insert", Mpack(l, "MObj", Mpack("self", "str", NULL)));
    t = Mcall(l, "query", Mpack("self", "str", NULL));
    /*printf("%lld\n", (long long int) t);*/
    if(t != l) exit(EXIT_FAILURE);
    q = Mcall(l, "remove", Mpack("self", "str", NULL));
    if(q != l) exit(EXIT_FAILURE);
    Mfree(q);
    return 0;
}
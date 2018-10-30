#include "m.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    MObj * l = Mnew(MList, NULL);
    printf("%lld\n", (long long int) l);
    Mcall(l, "insert", Mpack(l, "MObj", Mpack("self", "str", NULL)));
    printf("%lld\n", (long long int) Mcall(l, "query", Mpack("self", "str", NULL)));
    return 0;
}
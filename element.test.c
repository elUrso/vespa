#include "m.h"
#include "element.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    MObj * l = Mnew(MElement, NULL);
    Mfree(l);
    return 0;
}
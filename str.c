#include "str.h"

#include <stdlib.h>

int STRcmp(char * a, char * b) {
    int same = 1;
    for(int i = 0; same; i++) {
        if(a[i] != b[i]) same = 0;
        if(a[i] == '\0' || b[i] == '\0') break;
    }
    return same;
}

int STRquery(char ** source, char * str) {
    int q = -1;
    for(int i = 0; source[i] != NULL; i++) {
        if(STRcmp(str, source[i])) {
            q = i;
            break;
        }
    }
    return q;
}
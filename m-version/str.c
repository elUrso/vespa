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

char * STRcp(char * a) {
    int i;
    for(i = 0; a[i] != 0; i++);
    i++;
    char * str = malloc(sizeof(char) * i);
    if(str == NULL) exit(EXIT_FAILURE);
    for(i = 0; a[i] != 0; i++)
        str[i] = a[i];
    str[i] = a[i];
    return str;
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
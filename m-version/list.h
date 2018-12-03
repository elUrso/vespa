#ifndef LIST_H
#define LIST_H

#include "m.h"

MObj * MList (MObj * self, MPack * arg);

struct MList_node {
    MObj * value;
    char * id;
    struct MList_node * next;
};

#endif
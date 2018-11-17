/* Meta Library - Written by Vitor Silva
 */

#ifndef M_H
#define M_H

typedef struct {
    char **  _methods;
    void * (** _action) (void * self, void * arg);
    
    void * _state;

    char * _class;

    void * _Super;
    void * _Self;
    void * _Child;
    void (* _free) (void * t);
} MObj;

typedef struct {
    void * value;
    char * type;
    void * next;
} MPack;

typedef MObj * (* Mfactory) (MObj * self, MPack * arg);
typedef void * (* Mfunction) (MObj * self, MPack arg);

MObj * Mnew(Mfactory type, MPack * arg);
void * Mcall(MObj * object, char * method, MPack * arg);
void Mfree(MObj * object);

/*MPack functions*/
MPack * Mpack(void * value, char * type, void * next);
void Mpack_free(MPack * pack);
int Mpack_int(MPack * arg);
char * Mpack_str(MPack * arg);
char Mpack_bool(MPack * arg);
MObj * Mpack_Obj(MPack * arg);

extern char true;
extern char false;

#endif
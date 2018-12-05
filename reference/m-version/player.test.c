#include "m.h"
#include "place.h"
#include "player.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    MObj * cabo_canaveral = Mnew(MPlace, Mpack("Cabo canaveral", "str", Mpack("M", "str", Mpack("olha, um foguete!", "str", Mpack("Um local de lançamentos de foguete, levemente abandonado", "str", NULL)))));
    MObj * marte = Mnew(MPlace, Mpack("Marte", "str", Mpack("M", "str", Mpack("ta meio quente hein", "str", Mpack("Vermelho já está, só falta pegar fogo", "str", NULL)))));
    MObj * jogador = Mnew(MPlayer, Mpack("Manoel", "str", Mpack("M", "str", Mpack("um tanto burro", "str", Mpack("Não é dos mais inteligentes", "str", NULL)))));
    MObj * place;
    printf("%s\n", (char *) Mcall(cabo_canaveral, "get name", NULL));
    printf("%s\n", (char *) Mcall(marte, "get name", NULL));
    Mcall(jogador, "set location", Mpack(cabo_canaveral, "Obj", NULL));
    place = Mcall(jogador, "get location", NULL);
    printf("%s\n", (char *) Mcall(place, "get name", NULL));
    Mcall(jogador, "set location", Mpack(marte, "Obj", NULL));
    place = Mcall(jogador, "get location", NULL);
    printf("%s\n", (char *) Mcall(place, "get name", NULL));
    return 0;
}
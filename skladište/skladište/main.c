#define _CRT_SECURE_NO_WARNINGS

#include "functions.h"
#include <stdio.h>

int main(void) {
    inicijalizacija("skladiste.bin");

    int opcija = 1;

    while (opcija) {
        opcija = izbornik("skladiste.bin");
    }

    printf("Kraj programa\n");

    return 0;
}

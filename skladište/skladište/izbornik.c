#define _CRT_SECURE_NO_WARNINGS

#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

ARTIKL* poljeArtikala = NULL;
ARTIKL* pronadeniArtikl = NULL;

int izbornik(const char* const ime) {
    printf("\t\t\n\n");
    printf("\t\tOdaberite jednu od ponudenih opcija: \n\n");
    printf("\t\t****************************************************\n\n");
    printf("\t\tOpcija 1: Dodavanje artikla:\n\n");
    printf("\t\tOpcija 2: Sortiranje artikala po cijeni od najvece\n\n");
    printf("\t\tOpcija 3: Sortiranje artikala po cijeni od najmanje\n\n");
    printf("\t\tOpcija 4: Ispis svih artikala\n\n");
    printf("\t\tOpcija 5: Pretrazivanje artikla po ID-u\n\n");
    printf("\t\tOpcija 6: Brisanje artikla\n\n");
    printf("\t\tOpcija 7: Brisanje datoteke\n\n");
    printf("\t\tOpcija 8: Zavrsetak programa\n\n");
    printf("\t\t****************************************************\n\n");

    int opcija = 0;

    if (scanf("%d", &opcija) != 1) {
        printf("Neispravan unos.\n");
        while (getchar() != '\n'); 
        return 1;
    }
    system("cls");

    switch ((enum Opcije)opcija) {
    case DODAVANJE_ARTIKLA:
        dodajArtikl(ime);
        break;

    case SORTIRANJE_NAJVECA_CIJENA:
        free(poljeArtikala);
        poljeArtikala = (ARTIKL*)ucitajArtikl(ime);
        if (poljeArtikala != NULL) {
            quickSortCijenaMax(poljeArtikala, 0, brojArtikala - 1);
            ispisiArtikl(poljeArtikala);
        }
        break;

    case SORTIRANJE_NAJMANJA_CIJENA:
        free(poljeArtikala);
        poljeArtikala = (ARTIKL*)ucitajArtikl(ime);
        if (poljeArtikala != NULL) {
            quickSortCijenaMin(poljeArtikala, 0, brojArtikala - 1);
            ispisiArtikl(poljeArtikala);
        }
        break;

    case ISPIS_SVIH_ARTIKALA:
        free(poljeArtikala);
        poljeArtikala = (ARTIKL*)ucitajArtikl(ime);
        if (poljeArtikala != NULL) {
            ispisiArtikl(poljeArtikala);
        }
        break;

    case PRETRAZIVANJE_PO_ID:
        free(poljeArtikala);
        poljeArtikala = (ARTIKL*)ucitajArtikl(ime);
        if (poljeArtikala != NULL) {
            int idZaPretragu;
            printf("Unesite ID za pretragu: ");
            if (scanf("%d", &idZaPretragu) != 1) {
                printf("Neispravan unos.\n");
                while (getchar() != '\n'); 
                return 1;
            }
            pronadeniArtikl = pretrazivanje(poljeArtikala, brojArtikala, idZaPretragu);
            if (pronadeniArtikl != NULL) {
                printf("ID: %d\n", pronadeniArtikl->id);
                printf("Ime: %s\n", pronadeniArtikl->ime);
                printf("Proizvodac: %s\n", pronadeniArtikl->proizvodac);
                printf("Vrsta: %s\n", pronadeniArtikl->vrsta);
                printf("Cijena: %.2f eura\n", pronadeniArtikl->cijena);
                printf("Kolicina: %d\n", pronadeniArtikl->kolicina);
            }
            else {
                printf("Ne postoji artikl s tim ID-om");
            }
        }
        break;

    case BRISANJE_ARTIKLA:
        free(poljeArtikala);
        printf("Unesite ID artikla za brisanje: ");
        int idZaBrisanje;
        if (scanf("%d", &idZaBrisanje) != 1) {
            printf("Neispravan unos.\n");
            while (getchar() != '\n'); 
            return 1;
        }
        poljeArtikala = (ARTIKL*)ucitajArtikl(ime);
        if (poljeArtikala != NULL) {
            brisanjeArtikala(poljeArtikala, ime, idZaBrisanje);
        }
        break;

    case BRISANJE_DATOTEKE:
        brisanjeDatoteke(ime);
        break;

    case ZAVRSETAK_PROGRAMA:
        izlaz(poljeArtikala);
        opcija = 0;
        break;

    default:
        printf("Unesite ispravnu opciju\n");
        opcija = 4;
    }

    return opcija;
}

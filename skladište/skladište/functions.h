#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "datatype.h"
#include <stdio.h>

extern ARTIKL* poljeArtikala;
extern ARTIKL* pronadeniArtikl;
extern int brojArtikala;

enum Opcije {
    DODAVANJE_ARTIKLA = 1,
    SORTIRANJE_NAJVECA_CIJENA,
    SORTIRANJE_NAJMANJA_CIJENA,
    ISPIS_SVIH_ARTIKALA,
    PRETRAZIVANJE_PO_ID,
    BRISANJE_ARTIKLA,
    BRISANJE_DATOTEKE,
    ZAVRSETAK_PROGRAMA
};

int izbornik(const char* const ime);
void inicijalizacija(const char* const ime);
void dodajArtikl(const char* const ime);
void* ucitajArtikl(const char* const ime);
void ispisiArtikl(const ARTIKL* const polje);
void brisanjeArtikala(ARTIKL* const polje, const char* const ime, int id);
ARTIKL* pretrazivanje(const ARTIKL* const polje, int brojArtikala, int id);
int usporediID(const void* a, const void* b);
void zamjena(ARTIKL* const veci, ARTIKL* const manji);
void quickSortCijenaMax(ARTIKL* polje, int low, int high);
void quickSortCijenaMin(ARTIKL* polje, int low, int high);
int brisanjeDatoteke(const char* ime);
int izlaz(ARTIKL* polje);

#endif

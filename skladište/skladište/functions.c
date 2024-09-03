#define _CRT_SECURE_NO_WARNINGS

#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int brojArtikala = 0;

void inicijalizacija(const char* const ime) {
    if (ime == NULL) {
        fprintf(stderr, "Ime datoteke nije valjano\n");
        return;
    }

    FILE* fp = fopen(ime, "rb");
    if (fp == NULL) {
        fp = fopen(ime, "wb");
        if (fp == NULL) {
            perror("Otvaranje datoteke za inicijalizaciju");
            exit(EXIT_FAILURE);
        }
        fwrite(&brojArtikala, sizeof(int), 1, fp);
        fclose(fp);
        printf("Kreirana datoteka %s\n", ime);
    }
    else {
        fclose(fp);
    }
}

void dodajArtikl(const char* const ime) {
    if (ime == NULL) {
        fprintf(stderr, "Ime datoteke nije valjano\n");
        return;
    }

    FILE* fp = fopen(ime, "rb+");
    if (fp == NULL) {
        perror("Otvaranje datoteke za dodavanje artikala");
        exit(EXIT_FAILURE);
    }

    fread(&brojArtikala, sizeof(int), 1, fp);
    printf("Broj artikala: %d\n", brojArtikala);

    ARTIKL temp = { 0 };
    temp.id = brojArtikala + 1;

    (void)getchar();

    printf("Unesite ime artikla: ");
    if (scanf("%19[^\n]", temp.ime) != 1) {
        fprintf(stderr, "Neuspjesan unos imena artikla\n");
        fclose(fp);
        return;
    }

    (void)getchar();

    printf("Unesite vrstu artikla: ");
    if (scanf("%19[^\n]", temp.vrsta) != 1) {
        fprintf(stderr, "Neuspjesan unos vrste artikla\n");
        fclose(fp);
        return;
    }

    (void)getchar();

    printf("Unesite ime proizvodaca: ");
    if (scanf("%19[^\n]", temp.proizvodac) != 1) {
        fprintf(stderr, "Neuspjesan unos imena proizvodaca\n");
        fclose(fp);
        return;
    }

    (void)getchar();

    printf("Unesite cijenu artikla: ");
    if (scanf("%f", &temp.cijena) != 1) {
        fprintf(stderr, "Neuspjesan unos cijene artikla\n");
        fclose(fp);
        return;
    }

    (void)getchar();

    printf("Unesite kolicinu artikla: ");
    if (scanf("%d", &temp.kolicina) != 1) {
        fprintf(stderr, "Neuspjesan unos kolicine artikla\n");
        fclose(fp);
        return;
    }

    fseek(fp, sizeof(ARTIKL) * brojArtikala, SEEK_CUR);
    fwrite(&temp, sizeof(ARTIKL), 1, fp);
    printf("Novi artikl dodan\n");

    rewind(fp);
    brojArtikala++;
    fwrite(&brojArtikala, sizeof(int), 1, fp);
    fclose(fp);
}

void* ucitajArtikl(const char* const ime) {
    if (ime == NULL) {
        fprintf(stderr, "Ime datoteke nije valjano\n");
        return NULL;
    }

    FILE* fp = fopen(ime, "rb");
    if (fp == NULL) {
        perror("Otvaranje datoteke za ucitavanje artikala");
        return NULL;
    }

    fread(&brojArtikala, sizeof(int), 1, fp);
    printf("Broj artikala: %d\n", brojArtikala);

    ARTIKL* poljeArtikala = (ARTIKL*)calloc(brojArtikala, sizeof(ARTIKL));
    if (poljeArtikala == NULL) {
        perror("Alokacija memorije za polje artikala");
        fclose(fp);
        return NULL;
    }

    fread(poljeArtikala, sizeof(ARTIKL), brojArtikala, fp);
    printf("Svi artikli su uspjesno ucitani\n");
    fclose(fp);

    return poljeArtikala;
}

void ispisiArtikl(const ARTIKL* const polje) {
    if (polje == NULL) {
        fprintf(stderr, "Polje artikala je prazno\n");
        return;
    }

    for (int i = 0; i < brojArtikala; i++) {
        printf("ID: %-5d Ime: %-15s Proizvodac: %-15s Vrsta: %-10s Cijena:%-10.2feura Kolicina: %-5d\n",
            (polje + i)->id,
            (polje + i)->ime,
            (polje + i)->proizvodac,
            (polje + i)->vrsta,
            (polje + i)->cijena,
            (polje + i)->kolicina);
    }
}

void brisanjeArtikala(ARTIKL* const polje, const char* const ime, int id) {
    if (polje == NULL) {
        fprintf(stderr, "Polje artikala je prazno\n");
        return;
    }

    FILE* fp = fopen(ime, "rb+");
    if (fp == NULL) {
        perror("Otvaranje datoteke skladiste.dat");
        return;
    }

    fseek(fp, 0, SEEK_SET);
    int brojArtikala;
    fread(&brojArtikala, sizeof(int), 1, fp);

    ARTIKL* poljeArtikala = (ARTIKL*)malloc(brojArtikala * sizeof(ARTIKL));
    if (poljeArtikala == NULL) {
        perror("Alokacija memorije za polje artikala");
        fclose(fp);
        return;
    }

    fread(poljeArtikala, sizeof(ARTIKL), brojArtikala, fp);
    fclose(fp);

    int index = -1;
    for (int i = 0; i < brojArtikala; i++) {
        if ((poljeArtikala + i)->id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        fprintf(stderr, "Artikl s ID-om %d nije pronaden\n", id);
        free(poljeArtikala);
        return;
    }

    for (int i = index; i < brojArtikala - 1; i++) {
        *(poljeArtikala + i) = *(poljeArtikala + i + 1);
    }

    brojArtikala--;

    fp = fopen(ime, "wb");
    if (fp == NULL) {
        perror("Otvaranje datoteke skladiste.dat za pisanje");
        free(poljeArtikala);
        return;
    }

    fwrite(&brojArtikala, sizeof(int), 1, fp);
    fwrite(poljeArtikala, sizeof(ARTIKL), brojArtikala, fp);
    printf("Artikl s ID-om %d je uspjesno obrisan\n", id);

    fclose(fp);
    free(poljeArtikala);
}

ARTIKL* pretrazivanje(const ARTIKL* const polje, int brojArtikala, int id) {
    ARTIKL kljuc;
    kljuc.id = id;

    ARTIKL* pronadeniArtikl = (ARTIKL*)bsearch(&kljuc, polje, brojArtikala, sizeof(ARTIKL), usporediID);

    return pronadeniArtikl;
}

int usporediID(const void* a, const void* b) {
    const ARTIKL* aa = (const ARTIKL*)a;
    const ARTIKL* bb = (const ARTIKL*)b;

    if (aa->id < bb->id) return -1;
    else if (aa->id > bb->id) return 1;
    else return 0;
}

void zamjena(ARTIKL* const veci, ARTIKL* const manji) {
    ARTIKL temp;
    temp = *manji;
    *manji = *veci;
    *veci = temp;
}

void quickSortCijenaMax(ARTIKL* polje, int low, int high) {
    if (low < high) {
        int pi = partitionMax(polje, low, high);

        quickSortCijenaMax(polje, low, pi - 1);
        quickSortCijenaMax(polje, pi + 1, high);
    }
}

static int partitionMax(ARTIKL* polje, int low, int high) {
    float pivot = (polje + high)->cijena;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if ((polje + j)->cijena >= pivot) {
            i++;
            zamjena(polje + i, polje + j);
        }
    }
    zamjena(polje + i + 1, polje + high);
    return (i + 1);
}

void quickSortCijenaMin(ARTIKL* polje, int low, int high) {
    if (low < high) {
        int pi = partitionMin(polje, low, high);

        quickSortCijenaMin(polje, low, pi - 1);
        quickSortCijenaMin(polje, pi + 1, high);
    }
}

static int partitionMin(ARTIKL* polje, int low, int high) {
    float pivot = (polje + high)->cijena;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if ((polje + j)->cijena <= pivot) {
            i++;
            zamjena(polje + i, polje + j);
        }
    }
    zamjena(polje + i + 1, polje + high);
    return (i + 1);
}

int brisanjeDatoteke(const char* ime) {
    if (remove(ime) == 0) {
        printf("Datoteka uspjesno izbrisana\n");
        return 1;
    }
    else {
        fprintf(stderr, "Brisanje datoteke nije uspjelo\n");
        return 0;
    }
}

int izlaz(ARTIKL* polje) {
    free(polje);
    return 0;
}

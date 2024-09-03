#ifndef DATATYPE_H
#define DATATYPE_H
#define MAX_ARTIKLI 100

typedef struct artikl {
	int id;
	char ime[20];
	char vrsta[20];
	float cijena;
	int kolicina;
	char proizvodac[20];
}ARTIKL;

#endif
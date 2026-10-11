/*1. Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamički alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_bodovi 50

typedef struct _Student{
char ime[30];
char prezime[30];
int bodovi;
} stud;


int main() {
	int br;
	stud* studenti = NULL;
	FILE* dat;
	dat=fopen("dat.txt", "r");

	if (dat==NULL) {
		printf("Greska pri otvaraju datoteke");
		return -1;
	}

	char buffer[50] = { 0 };
	int brojac = 0;

	while (fgets(buffer, 50, dat) != NULL) {
		brojac++;
	}

	rewind(dat);

	studenti = (stud*)malloc(brojac * sizeof(stud));
	if (studenti==NULL) {
		printf("Greska pri alokaciji memorije");
		fclose(dat);
		return -1;
	}

	for (br = 0; br < brojac; br++) {
		fscanf(dat, "%s %s %d", studenti[br].ime, studenti[br].prezime,&studenti[br].bodovi);
	}

	fclose(dat);

	for (int i = 0; i < br; i++) {
		double relativni = (double)studenti[i].bodovi / MAX_bodovi * 100;
		printf("%s %s  Apsolutni broj bodova:%d  Relativni broj bodova:%.2f%% \n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, relativni);
	}
	
	free(studenti);
	return 0;
}
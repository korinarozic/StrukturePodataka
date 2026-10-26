#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Person* Position;

typedef struct _Person {
	char ime[20];
	char prezime[20];
	int god;
	Position next;
}Person;

//A. dodavanje na pocetak
int insertBegin(char* name, char* last_name, int year, Position p) {
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));
	if (newPerson == NULL)
		return 0;

	strcpy(newPerson->ime, name);
	strcpy(newPerson->prezime, last_name);
	newPerson->god = year;

	newPerson->next = p->next;
	p->next = newPerson;
	return 1;
}

//B. printanje
int printList(Position p) {
	if (p == NULL)
		return 0;
	Position temp = p->next;

	while (temp != NULL) {
		printf("%s %s %d\n", temp->ime, temp->prezime, temp->god);
		temp = temp->next;
	}
	return 1;
}

//C. dodavanje na kraj
int insertEnd(char* name, char* last_name, int year, Position p) {
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));
	if (newPerson == NULL)
		return 0;

	//pozicionirati se na kraj liste
	while (p->next != NULL) {
		p = p->next;
	}

	strcpy(newPerson->ime, name);
	strcpy(newPerson->prezime, last_name);
	newPerson->god = year;

	newPerson->next = NULL;
	p->next = newPerson;

	return 1;
}

//D. pretrazivanje
Position findLastname(char* Last_name, Position p) {
	Position q = NULL;
	for (q = p->next; q != NULL; q = q->next) {
		if (strcmp(q->prezime, Last_name) == 0)
			return q;
	}
	return NULL;
}

//E. brisnje
int deleteP(char* LastName, Position p) {
	Position curr = NULL;
	Position prev = p;
	curr = prev->next;
	while (curr != NULL) {
		if (strcmp(curr->prezime, LastName) == 0) {
			prev->next = curr->next;
			free(curr);

			return 1;
		}
		prev = curr;
		curr = curr->next;
	}
	return 0;
}

//dodavanje iza odredenog elementa
int insertAfter(char* LastName, Position p)
{
	Position temp = findLastname(LastName, p);

	if (temp == NULL)
		return 0;

	Position newPerson = malloc(sizeof(Person));

	if (newPerson == NULL)
		return 0;

	printf("Unesi ime, prezime i godinu rodenja: ");
	scanf("%19s %19s %d", newPerson->ime, newPerson->prezime, &newPerson->god);

	newPerson->next = temp->next;
	temp->next = newPerson;

	return 1;
}

//dodavanje ispred odredenog elementa
int insertBefore(char* LastName, Position p)
{
	Position temp = findLastname(LastName, p);

	if (temp == NULL)
		return 0;

	Position prev = p;

	while (prev->next != temp) {
		prev = prev->next;
	}

	Position newPerson = (Position)malloc(sizeof(Person));

	if (newPerson == NULL)
		return 0;

	printf("Unesi ime, prezime i godinu rodenja: ");
	scanf("%19s %19s %d", newPerson->ime, newPerson->prezime, &newPerson->god);

	newPerson->next = temp;
	prev->next = newPerson;

	return 1;
}

//upis liste u datoteku
int writeList(Position p)
{
	FILE* fp = fopen("lista.txt", "w");

	if (fp == NULL)
		return 0;

	Position temp = p->next;

	while (temp != NULL) {
		fprintf(fp, "%s %s %d\n", temp->ime, temp->prezime, temp->god);

		temp = temp->next;
	}

	fclose(fp);
	return 1;
}

//citanje liste iz datoteke
int readList(Position p)
{
	FILE* fp = fopen("lista.txt", "r");

	if (fp == NULL)
		return 0;

	char name[20];
	char last_name[20];
	int year;

	while (fscanf(fp, "%19s %19s %d", name, last_name, &year) == 3) {

		if (!insertEnd(name, last_name, year, p)) {
			fclose(fp);
			return 0;
		}
	}

	fclose(fp);
	return 1;
}

//sortiranje liste po prezimenima
int sortList(Position p)
{
	Position j, prev_j, temp, end;

	end = NULL;

	while (p->next != end)
	{
		prev_j = p;
		j = p->next;

		while (j->next != end)
		{
			if (strcmp(j->prezime, j->next->prezime) > 0)
			{
				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}

			prev_j = j;
			j = j->next;
		}

		end = j;
	}

	return 1;
}

int main() {
	Person Head = { .ime = {0}, .prezime = {0}, .god = 0, .next = NULL };
	Position p = &Head;
	int izbor;
	char prezime[20];
	char ime[20];
	int god;

	do {

		printf("\n1. Dodaj osobu na pocetak\n");
		printf("2. Dodaj osobu na kraj\n");
		printf("3. Ispisi listu\n");
		printf("4. Pretrazi osobu po prezimenu\n");
		printf("5. Obrisi osobu po prezimenu\n");
		printf("6. Dodaj osobu iza odredene osobe\n");
		printf("7. Dodaj osobu ispred odredene osobe\n");
		printf("8. Zapisi listu u datoteku\n");
		printf("9. Procitaj listu iz datoteke\n");
		printf("10. Sortiraj listu po prezimenima\n");
		printf("0. Izlaz\n");
		printf("Odaberi opciju: ");
		scanf("%d", &izbor);

		switch (izbor) {
		case 1:
			printf("Unesi ime, prezime i godinu rodenja: ");
			scanf("%19s %19s %d", ime, prezime, &god);

			if (!insertBegin(ime, prezime, god, p))
				printf("Greska pri dodavanju.\n");
			break;

		case 2:
			printf("Unesi ime, prezime i godinu rodenja: ");
			scanf("%19s %19s %d", ime, prezime, &god);

			if (!insertEnd(ime, prezime, god, p))
				printf("Greska pri dodavanju.\n");
			break;
		
		case 3:
			printList(p);
			break;

		case 4:
			printf("Unesi prezime za pretragu: ");
			scanf("%19s", prezime);

			if (findLastname(prezime, p) != NULL)
				printf("Osoba je pronadena.\n");
			else
				printf("Osoba nije pronadena.\n");
			break;

		case 5:
			printf("Unesi prezime osobe za brisanje: ");
			scanf("%19s", prezime);

			if (deleteP(prezime, p))
				printf("Osoba je obrisana.\n");
			else
				printf("Osoba nije pronadena.\n");
			break;

		case 6:
			printf("Iza koje osobe zelis dodati novu osobu? ");
			scanf("%19s", prezime);

			if (insertAfter(prezime, p))
				printf("Osoba je dodana.\n");
			else
				printf("Osoba nije pronadena ili je doslo do greske.\n");
			break;

		case 7:
			printf("Ispred koje osobe zelis dodati novu osobu? ");
			scanf("%19s", prezime);

			if (insertBefore(prezime, p))
				printf("Osoba je dodana.\n");
			else
				printf("Osoba nije pronadena ili je doslo do greske.\n");
			break;

		case 8:
			if (writeList(p))
				printf("Lista je zapisana u datoteku.\n");
			else
				printf("Greska pri pisanju.\n");
			break;

		case 9:
			if (readList(p))
				printf("Lista je procitana iz datoteke.\n");
			else
				printf("Greska pri citanju.\n");
			break;

		case 10:
			sortList(p);
			printf("Lista je sortirana po prezimenima.\n");
			break;

		case 0:
			printf("Izlaz iz programa.\n");
			break;

		default:
			printf("Neispravan izbor.\n");
		}
	} while (izbor != 0);

	while (p->next != NULL) {
		Position temp = p->next;
		p->next = temp->next;
		free(temp);
	}

	return 0;
}
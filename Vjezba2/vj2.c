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
int findLastname(char* Last_name, Position p) {
	Position q = NULL;
	for (q = p->next; q != NULL; q = q->next) {
		if (strcmp(q->prezime, Last_name) == 0)
			return 1;
	}
	return 0;
}

//E. brisnje
 int deleteP(char* LastName, Position p) {
	Position curr = NULL;
	Position prev = p;
	curr = prev->next;
	while(curr != NULL){
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

int main() {
	Person Head = { .ime = {0}, .prezime = {0}, .god = 0, .next = NULL };
	Position p = &Head;
	//A. Dodavanje na pocetak
	if (!insertBegin("Ana", "Anic", 2005, p)) {
		printf("Greska pri dodavanju osobe.\n");
		return 1;
	}

	if (!insertBegin("Ivo", "Ivic", 2004, p)) {
		printf("Greska pri dodavanju osobe.\n");
		return 1;
	}

	// B. Ispis liste 
	printf("Lista nakon dodavanja na pocetak:\n");
	if (!printList(p))
		return 1;

	// C. Dodavanje na kraj
	if (!insertEnd("Marko", "Matic", 2003, p)) {
		printf("Greska pri dodavanju osobe.\n");
		return 1;
	}

	printf("\nLista nakon dodavanja na kraj:\n");
	if (!printList(p))
		return 1;

	// D. Pretrazivanje
	if (findLastname("Ivic", p))
		printf("\nOsoba je pronadena.\n");
	else
		printf("\nOsoba nije pronadena.\n");

	// E. Brisanje
	if (deleteP("Anic", p))
		printf("\nOsoba je obrisana.\n");
	else
		printf("\nOsoba nije pronadena.\n");

	printf("\nLista nakon brisanja:\n");
	if (!printList(p))
		return 1;

	while (p->next != NULL) {
		Position temp = p->next;
		p->next = temp->next;
		free(temp);
	}

	return 0;
}
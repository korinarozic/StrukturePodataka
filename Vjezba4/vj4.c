
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Poly* Position;

typedef struct Poly {
	int coef;
	int pow;
	Position next;
}polynom;

int insertBegin(Position p, Position newPoly) {
	
	newPoly->next = p->next;
	p->next = newPoly;

	return 0;
}

int insertSorted(Position q, Position newPoly) {

	while (1) {
	
		if (q->next == NULL) {
			insertBegin(q, newPoly);
			return 0;
		}

		if(q->next != NULL && newPoly->pow > q->next->pow){
			insertBegin(q, newPoly);
			return 0;
		}

		if (newPoly->pow == q->next->pow) {
			q->next->coef += newPoly->coef;
			free(newPoly);


			if (q->next->coef == 0) {
				Position temp = q->next;
				q->next = temp->next;
				free(temp);
			}
			return 0;
		}

		if (newPoly->pow < q->next->pow)
			q = q->next;

	}
}

int readPoly(FILE* fp, Position p) {

	int n, coef, pow, i;
	Position newPoly = NULL;

	if (fscanf(fp, "%d", &n) != 1)
		return -1;

	for (i = 0; i < n; i++) {

		if (fscanf(fp, "%d %d", &coef, &pow) != 2)
			return -1;

		newPoly = (Position)malloc(sizeof(polynom));

		if (newPoly == NULL)
			return -1;

		newPoly->coef = coef;
		newPoly->pow = pow;
		newPoly->next = NULL;

		if (insertSorted(p, newPoly) != 0)
			return -1;
	}
	return 0;
}

int addPoly(Position first, Position second, Position result) {

	Position temp = first->next;
	Position newPoly = NULL;

	// prolazim kroz prvi polinom
	while (temp != NULL) {

		newPoly = (Position)malloc(sizeof(polynom));

		if (newPoly == NULL)
			return -1;

		newPoly->coef = temp->coef;
		newPoly->pow = temp->pow;
		newPoly->next = NULL;

		if (insertSorted(result, newPoly) != 0)
			return -1;

		temp = temp->next;
	}

	// prolazim kroz drugi polinom
	temp = second->next;

	while (temp != NULL) {

		newPoly = (Position)malloc(sizeof(polynom));

		if (newPoly == NULL)
			return -1;

		newPoly->coef = temp->coef;
		newPoly->pow = temp->pow;
		newPoly->next = NULL;

		if (insertSorted(result, newPoly) != 0)
			return -1;

		temp = temp->next;
	}

	return 0;
}

int multiplyPoly(Position first, Position second, Position result) {

	Position tempFirst = first->next;
	Position tempSecond = NULL;
	Position newPoly = NULL;

	//svaki element prvog polinoma mnozim sa svakim elementom drugog polinoma
	while (tempFirst != NULL) {

		tempSecond = second->next;

		while (tempSecond != NULL) {

			newPoly = (Position)malloc(sizeof(polynom));

			if (newPoly == NULL)
				return -1;

			newPoly->coef = tempFirst->coef * tempSecond->coef;
			newPoly->pow = tempFirst->pow + tempSecond->pow;
			newPoly->next = NULL;

			if (insertSorted(result, newPoly) != 0)
				return -1;

			tempSecond = tempSecond->next;
		}

		tempFirst = tempFirst->next;
	}

	return 0;
}

void printPoly(Position p) {

	Position temp = p->next;

	if (temp == NULL) {
		printf("0");
	}

	while (temp != NULL) {

		printf("%dx^%d", temp->coef, temp->pow);

		if (temp->next != NULL)
			printf(" + ");

		temp = temp->next;
	}

	printf("\n");
}

void deleteList(Position p) {

	Position temp = NULL;

	while (p->next != NULL) {

		temp = p->next;
		p->next = temp->next;
		free(temp);
	}
}

int main() {
	polynom head = { .coef = 0,.pow = 0, .next = NULL };
	polynom headFirst = head;
	polynom headSecond = head;

	Position q = &headFirst;

	polynom headSum = { .coef = 0, .pow = 0, .next = NULL };
	polynom headProduct = { .coef = 0, .pow = 0, .next = NULL };

	FILE* fp = NULL;

	fp = fopen("data.txt", "r");

	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke!\n");
		return -1;
	}


	if (readPoly(fp, &headFirst) != 0 ||
		readPoly(fp, &headSecond) != 0) {

		printf("Greska pri citanju datoteke!\n");
		fclose(fp);

		deleteList(&headFirst);
		deleteList(&headSecond);

		return -1;
	}

	fclose(fp);


	if (addPoly(&headFirst, &headSecond, &headSum) != 0 ||
		multiplyPoly(&headFirst, &headSecond, &headProduct) != 0) {

		printf("Greska pri obradi polinoma!\n");

		deleteList(&headFirst);
		deleteList(&headSecond);
		deleteList(&headSum);
		deleteList(&headProduct);

		return -1;
	}

	printf("Prvi polinom: ");
	printPoly(&headFirst);

	printf("Drugi polinom: ");
	printPoly(&headSecond);

	printf("Zbroj: ");
	printPoly(&headSum);

	printf("Umnozak: ");
	printPoly(&headProduct);


	deleteList(&headFirst);
	deleteList(&headSecond);
	deleteList(&headSum);
	deleteList(&headProduct);

	return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Stack* Position;
typedef struct Stack {
	int number;
	Position next;
}stack;

int Push(Position p, int num) {
	Position new = NULL;
	new = (Position)malloc(sizeof(stack));
	
	if (new == NULL) {
		printf("Greska pri alokaciji memorije.\n");
		return -1;
	}

	new->number = num;
	new->next = p->next;
	p->next = new;

	return 0;
}

int Pop(Position p, int* num) {   //pokazivac zato sto zelimo vratiti skinuti broj 
	Position temp = p->next;
	
	if (temp == NULL) {
		printf("Stog je prazan.\n");
		return -1;
	}

	*num = temp->number;
	p->next = temp->next;
	free(temp);

	return 0;
}

int Calculate(Position p, FILE* fp, int* result) {
	char znak;
	int num, num1, num2, r;

	while (fscanf(fp, "%c", &znak) == 1) {
	
		if (isspace((unsigned char)znak))
			continue;

		if (isdigit((unsigned char)znak)) {
			num = znak - '0';

			if (Push(p, num))
				return -1;
		}

		else if (znak == '+' || znak=='-' || znak=='*' || znak=='/') {

			if (Pop(p, &num1) || Pop(p, &num2))
				return -1;

			switch (znak) {
			case '+':
				r = num2 + num1;
				break;
			case '-':
				r = num2 - num1;
				break;
			case '*':
				r = num2 * num1;
				break;
			case '/':
				if (num1 == 0) {
					printf("Greska, djeljenje sa nulom.\n");
					return -1;
				}
				r = num2 / num1;
				break;
			default:
				return -1;
			}

			if (Push(p, r))
				return -1;
		}

		else {
			printf("Neispravan znak.\n");
			return -1;
		}
	}

	//provjera je li na stogu samo jedan element nakon racunanja
	if (p->next == NULL || p->next->next != NULL) {
		printf("Neispravan izraz.\n");
		return -1;
	}

	if (Pop(p, result))
		return -1;


	return 0;
}

void DeleteAll(Position p) {

	Position temp = NULL;

	while (p->next != NULL) {

		temp = p->next;
		p->next = temp->next;
		free(temp);
	}
}

int main() {
	stack Head = { .number = 0, .next = NULL };
	Position p = &Head;
	FILE* fp;
	int result;

	fp = fopen("dat.txt", "r");

	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	}

	if (Calculate(p, fp, &result)){
		printf("Greska pri racunanju.\n");
		DeleteAll(p);
		fclose(fp);
		return -1;
	}
	
	printf("Rezlutat je: %d\n", result);

	DeleteAll(p);
	fclose(fp);

	return 0;
}
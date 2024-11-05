#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char Name[MAX];
	char Surname[MAX];
	int BirthYear;
	Position next;
}Person;

int PrependList(Position head, char *Name, char *Surnaame, int BirthYear);
int PrintList(Position first);
Position CreatePerson(char* Name, char* Surname, int BirthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position Head);
int AppendList(Position Head, char* Name, char* Surname, int BirthYear);
Position FindByLastName(Position first, char* Surname);
Position FindBefore(Position Head, Position first);
int Delete(Position Head, char* Surname);


int main() {
	Person Head = { .next = NULL, .Name = {0},.Surname = {0},.BirthYear = 0 };
	Position p = &Head;
	int o,year;
	char name[MAX], surname[MAX];

	printf("ODABERITE SLJEDECE:\n1. DODAJ ELEMENT NA POCETAK LISTE\n2. DODAJ ELEMENT NA KRAJ LISTE\n3. NADI ELEMENT PO PREZIMENU\n4. OBRIŠI ELEMENT\n5. ISPIŠI LISTU\n6. IZLAZ");
	while (1) {
		printf("Unesite opciju: ");
		scanf("%d", &o);

		switch (o) {
		case 1:
			printf("Unesite ime: ");
			scanf("%s", name);
			printf("Unesite prezime: ");
			scanf("%s", surname);
			printf("Unesite godinu roðenja: ");
			scanf("%d", &year);
			PrependList(p, name, surname, year);
			break;

		case 2:
			printf("Unesite ime: ");
			scanf("%s", name);
			printf("Unesite prezime: ");
			scanf("%s", surname);
			printf("Unesite godinu roðenja: ");
			scanf("%d", &year);
			AppendList(p, name, surname, year);
			break;

		case 3:
			printf("Unesite prezime za pretragu: ");
			scanf("%s", surname);
			Position found = FindByLastName(p->next, surname);
			if (found) {
				printf("Osoba pronaðena: %s %s, Godina roðenja: %d\n", found->Name, found->Surname, found->year);
			}
			else {
				printf("Osoba s prezimenom %s nije pronaðena.\n", surname);
			}
			break;

		case 4:
			printf("Unesite prezime osobe koju želite obrisati: ");
			scanf("%s", surname);
			if (Delete(p, surname) == EXIT_SUCCESS) {
				printf("Osoba s prezimenom %s je obrisana iz liste.\n", surname);
			}
			else {
				printf("Osoba s prezimenom %s nije pronaðena.\n", surname);
			}
			break;

		case 5:
			printf("Lista osoba:\n");
			PrintList(p->next);
			break;

		case 6:
			printf("Izlaz iz programa.\n");
			return EXIT_SUCCESS;

		default:
			printf("Nepoznata opcija! Pokušajte ponovo.\n");
			break;
		}
	}

	return 0;
}
Position CreatePerson(char *Name, char *Surname, int BirthYear){
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		perror("GREŠKA PRI ALOKACIJI!");
		return NULL;
	}
	strcpy(newPerson->Name,Name);
	strcpy(newPerson->Surname, Surname);
	newPerson->BirthYear=BirthYear;
	newPerson->next = NULL;
	return newPerson;
}

int InsertAfter(Position position, Position newPerson){
	newPerson->next = position->next;
	position->next = newPerson;
	return EXIT_SUCCESS;
}

int PrependList(Position Head, char* Name, char* Surname, int BirthYear) {
	Position newPerson = NULL;
	newPerson = CreatePerson(Name,Surname,BirthYear);
	if (!newPerson) {
		return -1;
	}
	InsertAfter(Head, newPerson);
	return EXIT_SUCCESS;
}

int PrintList(Position first) {
	Position temp = first;
	while (temp) {
		printf("IME: %s\tPREZIME: %s\tDATUM RODENJA: %d\n", temp->Name, temp->Surname, temp->BirthYear);
		temp = temp->next;
	}
	printf("\n");
	return EXIT_SUCCESS;
}

Position FindLast(Position Head){
	Position temp = Head;
	while (temp->next) {
		temp = temp->next;
	}
	return temp;
}

int AppendList(Position Head, char* Name, char* Surname, int BirthYear) {
	Position newPerson = NULL;
	Position last = NULL;
	newPerson = CreatePerson(Name, Surname, BirthYear);
	if (!newPerson) {
		return -1;
	}
	last = FindLast(Head);
	InsertAfter(last, newPerson);
	return EXIT_SUCCESS;
}

Position FindByLastName(Position first, char* Surname) {
	Position temp = first;
	while (temp) {
		if (strcmp(temp->Surname, Surname) == 0) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}


Position FindBefore(Position Head,Position first) {
	Position temp = Head;
	Position temp1 = first;
	while (temp) {
		if (temp->next == temp1) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

int Delete(Position p, char* Surname) {
	Position curr = FindByLastName(p, Surname);
	Position prev = FindBefore(p, curr);
	if (prev == NULL)
		return -1;
	prev->next = curr->next;
	free(curr);
	return 0;
}
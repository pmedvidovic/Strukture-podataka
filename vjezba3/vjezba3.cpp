#define _CRT_SECURE_NO_WARNINGS
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

int PrependList(Position head, char* Name, char* Surnaame, int BirthYear);
int PrintList(Position first);
Position CreatePerson(char* Name, char* Surname, int BirthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position Head);
int AppendList(Position Head, char* Name, char* Surname, int BirthYear);
Position FindByLastName(Position first, char* Surname);
Position FindBefore(Position Head, Position first);
int Delete(Position Head, char* Surname);
int AddAfter(Position head, char* surname);
int AddBefore(Position head, char* surname);
int Sort(Position head);
int FileEntry(Position head, char* vezaneliste);
int ReadFile(Position head, char* vezaneliste);


int main() {
	Person Head = { .next = NULL, .Name = {0},.Surname = {0},.BirthYear = 0 };
	Position p = &Head;
	int o, year;
	char name[MAX], surname[MAX];

	printf("ODABERITE SLJEDECE:\n1. DODAJ ELEMENT NA POCETAK LISTE\n2. DODAJ ELEMENT NA KRAJ LISTE\n3. NADI ELEMENT PO PREZIMENU\n4. OBRISI ELEMENT\n5. ISPISI LISTU\n6. DODAJ ELEMENT IZA ODREDENOG \n7. DODAJ ELEMENT ISPRED ODREDENOG\n8. SORTIRAJ \n9. UPISI U DATOTEKU\n10. UCITAJ IZ DATOTEKE\n11.IZLAZ\n");
	while (1) {
		printf("Unesite opciju: ");
		scanf("%d", &o);
		char dat[50] = { 0 };

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
			printf("Unesite godinu rodenja: ");
			scanf("%d", &year);
			AppendList(p, name, surname, year);
			break;

		case 3:
			printf("Unesite prezime za pretragu: ");
			scanf("%s", surname);
			Position found = FindByLastName(p->next, surname);
			if (found) {
				printf("Osoba pronaðena: %s %s, Godina rodenja: %d\n", found->Name, found->Surname, found->BirthYear);
			}
			else {
				printf("Osoba s prezimenom %s nije pronadena.\n", surname);
			}
			break;

		case 4:
			printf("Unesite prezime osobe koju zelite obrisati: ");
			scanf("%s", surname);
			if (Delete(p, surname) == EXIT_SUCCESS) {
				printf("Osoba s prezimenom %s je obrisana iz liste.\n", surname);
			}
			else {
				printf("Osoba s prezimenom %s nije pronadena.\n", surname);
			}
			break;

		case 5:
			printf("Lista osoba:\n");
			PrintList(p->next);
			break;

		case 6:
			printf("Unesite prezime osobe iza koje zelite dodati novi elemnt: ");
			scanf("%s", surname);
			AddAfter(p, surname);
			break;
		case 7:
			printf("Unesite prezime osobe ispred koje zelite dodati novi elemnt: ");
			scanf("%s", surname);
			AddBefore(p, surname);
			break;
		case 8:
			Sort(p);
			printf("Odaberi opciju 5. za ispis liste!");
			break;
		case 9:
			printf("upisite ime datoteke u koju zelite pohraniti svoju listu: ");
			scanf("%s", dat);
			FileEntry(p, dat);
			break;
		case 10:
			printf("Upisite ime datoteke koju zelite ucitati u svoju listu: ");
			scanf("%s", dat);
			ReadFile(p, dat);
			break;
		case 11:
			printf("Izlaz iz programa.\n");
			return EXIT_SUCCESS;

		default:
			printf("Nepoznata opcija! Pokusajte ponovo.\n");
			break;
		}
	}

	return 0;
}
Position CreatePerson(char* Name, char* Surname, int BirthYear) {
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		perror("GRESKA PRI ALOKACIJI!");
		return NULL;
	}
	strcpy(newPerson->Name, Name);
	strcpy(newPerson->Surname, Surname);
	newPerson->BirthYear = BirthYear;
	newPerson->next = NULL;
	return newPerson;
}

int InsertAfter(Position position, Position newPerson) {
	newPerson->next = position->next;
	position->next = newPerson;
	return EXIT_SUCCESS;
}

int PrependList(Position Head, char* Name, char* Surname, int BirthYear) {
	Position newPerson = NULL;
	newPerson = CreatePerson(Name, Surname, BirthYear);
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

Position FindLast(Position Head) {
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


Position FindBefore(Position Head, Position first) {
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

int AddAfter(Position Head, char* Surname) {
	Position newPerson = NULL;
	Position temp = NULL;

	char tname[MAX] = { 0 }, tsurname[MAX] = { 0 };
	int tyear = 0;
	printf("Unesite ime novog elementa: "); scanf("%s", tname);
	printf("Unesite prezime novog elementa: "); scanf("%s", tsurname);
	printf("Unesite godinu novog elementa: "); scanf("%d", &tyear);


	temp = FindByLastName(Head->next, Surname);
	newPerson = CreatePerson(tname, tsurname[MAX], tyear);
	if (!newPerson)
		return -1;
	InsertAfter(temp, newPerson);
	return EXIT_SUCCESS;
}

int AddBefore(Position Head, char* Surname) {
	Position newPerson = NULL;
	Position prev = NULL;

	char tname[MAX] = { 0 }, tsurname[MAX] = { 0 };
	int tyear = 0;
	printf("Unesite ime novog elementa: "); scanf("%s", tname);
	printf("Unesite prezime novog elementa: "); scanf("%s", tsurname);
	printf("Unesite godinu novog elementa: "); scanf("%d", &tyear);

	prev = FindBefore(Head, FindByLastName(Head->next, Surname));
	newPerson = CreatePerson(tname, tsurname, tyear);
	if (!newPerson)
		return -1;
	InsertAfter(prev, newPerson);
	return EXIT_SUCCESS;
}

int Sort(Position Head) {
	Position first = NULL;
	Position prev = NULL;
	Position curr = NULL;
	Position temp = NULL;
	Position empty = NULL;

	if (Head->next == NULL) {
		printf("Lista je prazna!");
		return -1;
	}

	while (Head->next != empty) {
		prev = Head;
		curr = Head->next;

		while (curr->next != empty) {
			if (strcmp(curr->Surname, curr->next->Surname) > 0) {
				temp = curr->next;
				prev->next = temp;
				curr->next = temp->next;
				temp->next = curr;
				curr = temp;
			}
			prev = curr;
			curr = curr->next;
		}
		empty = curr;
	}
	return EXIT_SUCCESS;
}

int FileEntry(Position Head, char* datoteka) {

	FILE* f = fopen(datoteka, "w");
	Position p = Head->next;

	if (!f) {
		printf("GRESKA PRI OTVARANJU DATOTEKE!");
		return -1;
	}
	fprintf(f, "IME\tPREZIME\tDATUM\n");
	while (p != NULL) {
		fprintf(f, "%s %s %d\n", p->Name, p->Surname, p->BirthYear);
		p = p->next;
	}
	printf("Upis je uspjesno obavljen!");
	fclose(f);
	return EXIT_SUCCESS;
}

int ReadFile(Position Head, char* datoteka) {
	FILE* f = fopen(datoteka, "r");
	char name[MAX] = { 0 }, surname[MAX] = { 0 };
	int year = 0;

	if (!f) {
		printf("GRESKA PRI OTVARANJU DATOTEKE!");
		return -1;
	}

	while (!feof(f)) {
		fscanf(f, "%s %s %d\n", name, surname, &year);
		AppendList(Head, name, surname, year);
	}
	printf("datoteka je ucitana na kraj liste!\n");

	fclose(f);
	return EXIT_SUCCESS;
}

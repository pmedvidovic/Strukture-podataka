#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define MAX_LINE 1024
#define OPEN_ERROR -1
#define MALLOC_ERROR -2
#define MAX_BODODVI 20
typedef struct{
	char ime[30];
	char prezime[30];
	float bodovi;
} Student;

int Broji_redove() {
	int br=0;
	char buffer[MAX_LINE] = { 0 };
	FILE* file = NULL;
	file = fopen("studenti.txt","r");
	if (!file) {
		printf("GREŠKA PRI OTVARANJU!");
		return OPEN_ERROR;
	}
	while (!feof(file)) {
		fgets(buffer, MAX_LINE, file);
		br++;
	}
	fclose(file);
	return br;
}

int main() {
	/*Napisati program koji prvo proèita koliko redaka ima datoteka, tj.koliko ima studenata
	zapisanih u datoteci.Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
		studenata(ime, prezime, bodovi) i uèitati iz datoteke sve zapise.Na ekran ispisati ime,
		prezime, apsolutni i relativni broj bodova.
		Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
		relatvan_br_bodova = br_bodova / max_br_bodova * 100*/
	int Broj_redaka = 0;
	Broj_redaka = Broji_redove();
	if (Broj_redaka > 0) {
		FILE* file = NULL;
		file = fopen("studenti.txt", "r");
		if (!file) {
			printf("GREŠKA PRI OTVARANJU!\n");
			return OPEN_ERROR;
		}
		Student* stud=NULL;
		stud = (Student*)malloc(Broj_redaka * sizeof(Student));
		if (stud == NULL) {
			printf("MALLOC ERROR!\n");
			return MALLOC_ERROR;
		}
		for (int i = 0;i < Broj_redaka;i++) {
			printf("%s %s %.2lf %.2lf\n", stud[i].ime, stud[i].prezime, stud[i].bodovi, stud[i].bodovi / MAX_BODOVI * 100);
		}
		fclose(file);
		free(stud);
	}
	return 0;
}











#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct polinom* PolinomPozicija;
typedef struct polinom {
    int eksponent;
    int koeficijent;
    PolinomPozicija sljedeci;
} Polinom;

void sortiraj_i_unesi(PolinomPozicija, int, int);
void iscitaj_i_unesi(PolinomPozicija, char*);
void ispis(PolinomPozicija);
PolinomPozicija zbroji_polinnome(PolinomPozicija, PolinomPozicija);
PolinomPozicija pomnozi_polinnome(PolinomPozicija, PolinomPozicija);

int main() {
    PolinomPozicija pocetak1 = malloc(sizeof(Polinom));
    if (pocetak1 == NULL) {
        exit(1);
    }
    pocetak1->sljedeci = NULL;

    iscitaj_i_unesi(pocetak1, "polinomi1.txt");
    ispis(pocetak1);
    printf("\n");

    PolinomPozicija pocetak2 = malloc(sizeof(Polinom));
    if (pocetak2 == NULL) {
        exit(1);
    }
    pocetak2->sljedeci = NULL;

    iscitaj_i_unesi(pocetak2, "polinomi2.txt");
    ispis(pocetak2);
    printf("\n");

    PolinomPozicija zbrojeni = zbroji_polinnome(pocetak1, pocetak2);
    ispis(zbrojeni);
    printf("\n");

    PolinomPozicija pomnozeni = pomnozi_polinnome(pocetak1, pocetak2);
    ispis(pomnozeni);
    printf("\n");

    return 0;
}

void sortiraj_i_unesi(PolinomPozicija pocetak, int koeficijent, int eksponent) {
    PolinomPozicija novi = malloc(sizeof(Polinom));
    if (novi == NULL) {
        exit(1);
    }
    novi->eksponent = eksponent;
    novi->koeficijent = koeficijent;
    novi->sljedeci = NULL;
    PolinomPozicija temp = pocetak;

    while (temp->sljedeci != NULL && temp->sljedeci->eksponent < eksponent) {
        temp = temp->sljedeci;
    }

    if (temp->sljedeci != NULL && temp->sljedeci->eksponent == eksponent) {
        temp->sljedeci->koeficijent += koeficijent;
        free(novi); // Osiguranje da se ne duplira èlan
    }
    else {
        novi->sljedeci = temp->sljedeci;
        temp->sljedeci = novi;
    }
}

void iscitaj_i_unesi(PolinomPozicija pocetak, char* dat) {
    FILE* f = fopen(dat, "r");
    if (f == NULL) {
        return;
    }

    int eksponent, koeficijent;
    while (fscanf(f, "%d %d", &koeficijent, &eksponent) == 2) {
        sortiraj_i_unesi(pocetak, koeficijent, eksponent);
    }
    fclose(f);
}

void ispis(PolinomPozicija pocetak) {
    PolinomPozicija temp = pocetak->sljedeci;
    if (temp == NULL) {
        printf("Polinoma nema!!\n");
        return;
    }

    if (temp->koeficijent > 0) {
        printf("%dx^%d", temp->koeficijent, temp->eksponent);
        temp = temp->sljedeci;
    }

    while (temp != NULL) {
        if (temp->koeficijent > 0) {
            printf(" + %dx^%d", temp->koeficijent, temp->eksponent);
        }
        else {
            printf(" - %dx^%d", -temp->koeficijent, temp->eksponent);  // Ovdje je dodano ispravno ispisivanje negativnih koeficijenata
        }
        temp = temp->sljedeci;
    }
    printf("\n");
}

PolinomPozicija zbroji_polinnome(PolinomPozicija pocetak1, PolinomPozicija pocetak2) {
    PolinomPozicija novi = malloc(sizeof(Polinom));
    if (novi == NULL) {
        exit(1);
    }
    novi->sljedeci = NULL;

    PolinomPozicija temp1 = pocetak1->sljedeci;
    PolinomPozicija temp2 = pocetak2->sljedeci;

    while (temp1 != NULL) {
        sortiraj_i_unesi(novi, temp1->koeficijent, temp1->eksponent);
        temp1 = temp1->sljedeci;
    }

    while (temp2 != NULL) {
        sortiraj_i_unesi(novi, temp2->koeficijent, temp2->eksponent);
        temp2 = temp2->sljedeci;
    }

    return novi;
}

PolinomPozicija pomnozi_polinnome(PolinomPozicija pocetak1, PolinomPozicija pocetak2) {
    PolinomPozicija novi = malloc(sizeof(Polinom));
    if (novi == NULL) {
        return NULL;
    }
    novi->sljedeci = NULL;

    PolinomPozicija temp1 = pocetak1->sljedeci;
    while (temp1 != NULL) {
        PolinomPozicija temp2 = pocetak2->sljedeci;
        while (temp2 != NULL) {
            int eksponent = temp1->eksponent + temp2->eksponent;
            int koeficijent = temp1->koeficijent * temp2->koeficijent;
            sortiraj_i_unesi(novi, koeficijent, eksponent);
            temp2 = temp2->sljedeci;
        }
        temp1 = temp1->sljedeci;
    }

    return novi;
}

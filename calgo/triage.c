#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"


int passagerUnique(int numero_siege, Passager tableau[], int size) {
	for (int i = 0; i < size; i++) {
    	if (tableau[i].numero_siege == numero_siege) {
        	return 1; // Le numero de passager existe deja
    	}
	}
	return 0; // Le numéro de passager n'existe pas encore
}

int main() {
	srand(time(NULL));
	int i, k = 0;
	Passager tableau_passager[NB_ELEMENT];
	float tableau_prix_billet[NB_ELEMENT];
	Passager tableau_final[NB_ELEMENT];

	printf("Tableau des passagers : ");
	for (i = 0; i < NB_ELEMENT; i++) {
    	int numero_siege;
    	do {
        	numero_siege = rand() % 100; // Générer un numéro de passager aléatoire
    	} while (passagerUnique(numero_siege, tableau_passager, i));

    	tableau_passager[i].numero_siege = i+1;

    	printf("%d ", numero_siege);
	}

	printf("\n\n");
	printf("Tableau prix billet : ");
	for (i = 0; i < NB_ELEMENT; i++) {
    	tableau_prix_billet[i] = rand() % 100;
    	printf("%.0f ",  tableau_prix_billet[i]);
	}

	printf("\n\n");

	// Tri croissants des passagers
	for (i = 0; i < NB_ELEMENT - 1; i++) {
    	for (int j = 0; j < NB_ELEMENT - 1 - i; j++) {
        	if (tableau_passager[j].numero_siege > tableau_passager[j + 1].numero_siege) {
            	Passager temp = tableau_passager[j];
            	tableau_passager[j] = tableau_passager[j + 1];
            	tableau_passager[j + 1] = temp;
        	}
    	}
	}

	// Attribution des billets aux passagers dans le tableau final
	for (i = 0; i < NB_ELEMENT; i++) {
    	tableau_final[i] = tableau_passager[i];
    	tableau_final[i].prix_billet = tableau_prix_billet[i];
	}

	// Tri décroissant des billets dans le tableau final
	for (i = 0; i < NB_ELEMENT - 1; i++) {
    	for (int j = 0; j < NB_ELEMENT - 1 - i; j++) {
        	if (tableau_final[j].prix_billet < tableau_final[j + 1].prix_billet) {
            	Passager temp = tableau_final[j];
            	tableau_final[j] = tableau_final[j + 1];
            	tableau_final[j + 1] = temp;
        	}
    	}
	}

	// Affichage du tableau final
	printf("\n\nTableau final (valeurs triees par prix decroissant) :\n");
	for (i = 0; i < NB_ELEMENT; i++) {
    	printf("Passager %d - Prix du billet : %.2f euros\n", tableau_final[i].numero_siege, tableau_final[i].prix_billet);
	}

	return 0;
}

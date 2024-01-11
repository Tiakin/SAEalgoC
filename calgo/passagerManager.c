#include "main.h"

/**
 * @brief fichier passagerManager contenant les fonctions liées au passager
 * @author Killian
 * @author Martin
 *
 */


void tri_passager(Passager tableau_passagers[])
{

    // Tri décroissant des billets dans le tableau
	for (int i = 0; i < MAX_PASSAGERS - 1 && tableau_passagers[i].numero_siege != '\0'; i++) {
    	for (int j = 0; j < MAX_PASSAGERS - 1 - i && tableau_passagers[j].numero_siege != '\0'; j++) {
    	    int age1 = calculer_age(tableau_passagers[j].date_naissance);
            int age2 = calculer_age(tableau_passagers[j + 1].date_naissance);
        	if (((tableau_passagers[j].prix_billet < tableau_passagers[j + 1].prix_billet) && ( (age1 >= 12 && age2 >= 12) || (age1 < 12 && age2 < 12) )) || (age1 >= 12 && age2 < 12)) {
            	Passager temp = tableau_passagers[j];
            	tableau_passagers[j] = tableau_passagers[j + 1];
            	tableau_passagers[j + 1] = temp;
        	}
    	}
	}
}

void afficher_passager(Passager passager)
{
    printf("%s | ", passager.nom);
    printf("%s | ", passager.prenom);
    printf("%s | ", passager.date_naissance);
    printf("%d | ", passager.numero_siege);
    printf("%.2f\n", passager.prix_billet);
}

int calculer_age(char date_naissance[])
{
    int jour, mois, annee;
    int age;
    time_t t = time(NULL);
    struct tm date = *localtime(&t);

    sscanf(date_naissance, "%d/%d/%d", &jour, &mois, &annee);

    // Calculer l'âge du passager
    age = date.tm_year + 1900 - annee; // Soustraire l'année de naissance à l'année actuelle
    if (date.tm_mon + 1 < mois || // Si mois inférieur
        (date.tm_mon + 1 == mois && date.tm_mday < jour)) // Si jour inférieur
    {
        age--; // Décrémenter l'âge de 1
    }

    // Retourner l'âge du passager
    return age;
}

void embarquement(Vol vols[])
{
    Passager tab_passager[MAX_PASSAGERS];
    int num_embarquement;
    printf("Entrez la salle d'embarquement : ");
    scanf("%d", &num_embarquement);
    int num = 0;
    for (int i = 0; i < MAX_VOLS && vols[i].salle_embarquement != '\0'; i++) {
        if (vols[i].salle_embarquement == num_embarquement) {
                for(int j = 0; j < MAX_PASSAGERS && vols[i].liste_passagers[j].numero_siege != '\0'; j++)
                {
                 tab_passager[num] = vols[i].liste_passagers[j];
                 num++;
                }
        }
    }


    tri_passager(tab_passager);
    printf("Liste des passagers dans la salle d'embarquement %d:\n", num_embarquement);
    printf("Nom | Prenom | Date de naissance | Numero de siege | Prix du billet\n");
    printf("------------------------------------------------------------------\n");
    for (int i = 0; i < num; i++) {
        afficher_passager(tab_passager[i]);
    }
    if (num == 0)
    {
        printf("Aucun resultat.\n");
    }

}

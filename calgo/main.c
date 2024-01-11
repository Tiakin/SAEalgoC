#include "main.h"


int main()
{
    //initialisation des tableaux et lecture du fichier
    Vol tableau_vols[MAX_VOLS];

    char nom_fichier[MAX_NOM];

    printf("Entrez le nom du fichier csv contenant les donnees des vols (0=data_vols.csv): ");
    scanf("%s", nom_fichier);
    if(nom_fichier[0] == '0') // mis en place du fichier par défaut
    {
        printf("Nom par defaut (data_vols.csv)...\n");
        strcpy(nom_fichier, "data_vols.csv");
    }
    printf("Lecture du fichier...\n");

    if(creer_tableau_vols(tableau_vols, nom_fichier)) // création du tableau
    {
        printf("Lecture termine\n");

        // partie utilisateur
        char choix;
        do
        {
            printf("\e[0;32m0 ou invalide : Quitter le programme\n1: affichage des vols (h+3) \n2: Rechercher vol par critere\n3: Afficher embarquement\n\e[0;33mSaisissez un choix : \e[0;37m");
            scanf(" %[^\n]", &choix);
            switch (choix)
            {
                case '1': // affichage
                    afficher_vols(tableau_vols);
                    break;
                case '2': // Recherche
                    rechercher_vol(tableau_vols);
                    break;
                case '3':
                    embarquement(tableau_vols);
                    break;
                default:
                    choix = '0';
                    printf("choix invalide.\n");
                    break;
            }
        } while (choix != '0');
        return 0;
    }
    return 1;
}



int creer_tableau_vols(Vol tableau_vols[], char nom_fichier[]) // int
{
    FILE *fichier;
    char passagers[MAX_LIGNE];

    fichier = fopen(nom_fichier, "r");

    if (fichier == NULL)
    {
        printf("Erreur : impossible d'ouvrir le fichier %s.\n", nom_fichier);
        return 0;
    }

    int nb_vols = 0;

    fscanf(fichier, "%*[^\n]\n"); // skip de la premiere ligne

    while (!feof(fichier))
    {
        if (nb_vols >= MAX_VOLS)
        {
            printf("nombre maximal de vols atteint.\n");
            break;
        }

        fscanf(fichier, "%d,%[^,],%[^,],%d,%d,%d,%d,%d,%d,%d,%[^,],\"%[^\"]\"\n",
               &tableau_vols[nb_vols].numero_vol,
               tableau_vols[nb_vols].compagnie,
               tableau_vols[nb_vols].destination,
               &tableau_vols[nb_vols].numero_comptoir,
               &tableau_vols[nb_vols].heure_debut_enregistrement,
               &tableau_vols[nb_vols].heure_fin_enregistrement,
               &tableau_vols[nb_vols].salle_embarquement,
               &tableau_vols[nb_vols].heure_debut_embarquement,
               &tableau_vols[nb_vols].heure_fin_embarquement,
               &tableau_vols[nb_vols].heure_decollage,
               tableau_vols[nb_vols].etat_vol,
               passagers);


        creer_tableau_passagers(tableau_vols[nb_vols].liste_passagers, passagers);

        nb_vols++;
    }

    fclose(fichier);
    return 1;
}

void creer_tableau_passagers(Passager tableau_passagers[], char liste[])
{
    char *pt_tab;

    int nb_passagers = 0;

    // Extraire le premier passager de la liste
    pt_tab = strtok(liste, ";");

    while (pt_tab != NULL)
    {
        if (nb_passagers >= MAX_PASSAGERS)
        {
            printf("limite de passagers atteint.\n");
            break;
        }

        sscanf(pt_tab, "%[^,],%[^,],%[^,],%d,%f",
               tableau_passagers[nb_passagers].nom,
               tableau_passagers[nb_passagers].prenom,
               tableau_passagers[nb_passagers].date_naissance,
               &tableau_passagers[nb_passagers].numero_siege,
               &tableau_passagers[nb_passagers].prix_billet);


        nb_passagers++;
        // Extraire le passager suivant de la liste
        pt_tab = strtok(NULL, ";");
    }
}

void afficher_vols(Vol vols[])
{
    time_t t = time(NULL);
    struct tm date = *localtime(&t);
    int heure_actuelle = date.tm_hour * 100 + date.tm_min;

    printf("Liste des vols dans les 3 heures a venir :\n");
    printf("Heure | Numero | Compagnie | Destination | Comptoir | Salle | Etat\n");
    printf("------------------------------------------------------------------\n");
    for (int i = 0; i < MAX_VOLS && vols[i].numero_vol != '\0'; i++) {
        // On vérifie si le vol est dans les 3 heures à venir
        if (vols[i].heure_decollage >= heure_actuelle && vols[i].heure_decollage <= heure_actuelle + 300) {
            afficher_vol(vols[i], heure_actuelle);
        }
    }
}

void afficher_vol(Vol vol, int heure)
{
        // On affiche l'heure de décollage
        printf("%02d:%02d | ", vol.heure_decollage / 100, vol.heure_decollage % 100);
        // On affiche le numéro de vol
        printf("%d | ", vol.numero_vol);
        // On affiche la compagnie
        printf("%s | ", vol.compagnie);
        // On affiche la destination
        printf("%s | ", vol.destination);
        // On affiche le comptoir d'enregistrement et les heures si c'est d'actualité
        if (vol.heure_debut_enregistrement <= heure + 30 && vol.heure_fin_enregistrement >= heure - 10) {
            printf("%d (%02d:%02d - %02d:%02d) | ", vol.numero_comptoir, vol.heure_debut_enregistrement / 100, vol.heure_debut_enregistrement % 100, vol.heure_fin_enregistrement / 100, vol.heure_fin_enregistrement % 100);
        }
        else {
            printf("%d | ", vol.numero_comptoir);
        }
        // On affiche la salle d'embarquement et les heures si c'est d'actualité
        if (vol.heure_debut_embarquement <= heure + 30 && vol.heure_fin_embarquement >= heure - 10) {
            printf("%d (%02d:%02d - %02d:%02d) | ", vol.salle_embarquement, vol.heure_debut_embarquement / 100, vol.heure_debut_embarquement % 100, vol.heure_fin_embarquement / 100, vol.heure_fin_embarquement % 100);
        }
        else {
            printf("%d | ", vol.salle_embarquement);
        }
        // On affiche l'état du vol
        printf("%s\n", vol.etat_vol);
}

void rechercher_vol(Vol tableau_vols[])
{
    char choix;
    char compagnie[MAX_NOM] = "";
    char destination[MAX_DESTINATION] = "";
    int heure_decollage = -1;
    int i;
    int trouve;

    do
    {
        printf("\e[0;32m0 ou invalide: Quitter la recherche\n1: Rechercher par compagnie aerienne\n2: Rechercher par destination\n3: Rechercher par heure de decollage\n4: Afficher les resultats de la recherche\n\e[0;33mSaisissez un choix : \e[0;37m");
        scanf(" %[^\n]", &choix);
        switch (choix)
        {
        case '1': // Rechercher par compagnie aérienne
            printf("Entrez le nom de la compagnie aerienne : ");
            scanf(" %[^\n]", compagnie);
            break;
        case '2': // Rechercher par destination
            printf("Entrez la destination du vol : ");
            scanf(" %[^\n]", destination);
            break;
        case '3': // Rechercher par heure de décollage
            printf("Entrez l'heure de decollage du vol au format HHMM (-1 pour enlever la recherche): ");
            scanf("%d", &heure_decollage);
            break;
        case '4': // Afficher les résultats de la recherche
            printf("Resultats de la recherche :\n");
            trouve = 0;
            printf("Heure | Numéro | Compagnie | Destination | Comptoir | Salle | Etat\n");
            printf("---------------------------------------------------------------\n");
            for (i = 0; i < MAX_VOLS && tableau_vols[i].numero_vol != '\0'; i++)
            {
                if ((compagnie[0] == '\0' || strstr(tableau_vols[i].compagnie, compagnie) != NULL) &&
                    (destination[0] == '\0' || strstr(tableau_vols[i].destination, destination) != NULL) &&
                    (heure_decollage == -1 || heure_decollage == tableau_vols[i].heure_decollage))
                {
                    afficher_vol(tableau_vols[i], -31);
                    trouve = 1;
                }
            }
            if (trouve == 0)
            {
                printf("Aucun vol ne correspond aux criteres de recherche.\n");
            }
            break;
        default:
            printf("Choix invalide.\n");
            choix = '0';
            break;
        }
    } while (choix != '0');
}

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

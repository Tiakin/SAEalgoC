#include "../Headers/main.h"


int main()
{

    Vol tableau_vols[MAX_VOLS];


    char nom_fichier[MAX_NOM];

    printf("Entrez le nom du fichier csv contenant les donnees des vols (0=data_vols.csv): ");
    scanf("%s", nom_fichier);
    if(nom_fichier[0] == '0')
    {
        printf("Nom par defaut (data_vols.csv)...\n");
        strcpy(nom_fichier, "data_vols.csv");
    }
    printf("Lecture du fichier...\n");
    creer_tableau_vols(tableau_vols, nom_fichier);
    printf("Lecture termine\n");

    rechercher_vol(tableau_vols);

    return 0;
}



void creer_tableau_vols(Vol tableau_vols[], char nom_fichier[])
{
    FILE *fichier;
    char passagers[MAX_LIGNE];

    fichier = fopen(nom_fichier, "r");

    if (fichier == NULL)
    {
        printf("Erreur : impossible d'ouvrir le fichier %s.\n", nom_fichier);
        return;
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

void rechercher_vol(Vol tableau_vols[])
{
    char choix;
    char compagnie[MAX_NOM] = "";
    char destination[MAX_DESTINATION] = "";
    int heure_decollage = 0;
    int i; // Indice pour parcourir le tableau des vols
    int trouve; // Variable booléenne pour indiquer si un vol a été trouvé

    do
    {
        printf("\e[0;32m0: Quitter la recherche\n1: Rechercher par compagnie aerienne\n2: Rechercher par destination\n3: Rechercher par heure de decollage\n4: Afficher les resultats de la recherche\n\e[0;33mSaisissez un choix : \e[0;37m");
        scanf("%d", &choix);

        switch (choix)
        {
        case 0:
            break;
        case 1: // Rechercher par compagnie aérienne
            printf("Entrez le nom de la compagnie aerienne : ");
            scanf("%s", compagnie);
            break;
        case 2: // Rechercher par destination
            printf("Entrez la destination du vol : ");
            scanf("%s", destination);
            break;
        case 3: // Rechercher par heure de décollage
            printf("Entrez l'heure de decollage du vol au format HHMM : ");
            scanf("%d", heure_decollage);
            break;
        case 4: // Afficher les résultats de la recherche
            printf("Resultats de la recherche :\n");
            trouve = 0;
            for (i = 0; i < MAX_VOLS && tableau_vols[i].numero_vol != '\0'; i++)
            {
                if ((compagnie[0] == '\0' || strcmp(compagnie, tableau_vols[i].compagnie) == 0) &&
                    (destination[0] == '\0' || strcmp(destination, tableau_vols[i].destination) == 0) &&
                    (heure_decollage == 0 || strcmp(heure_decollage, tableau_vols[i].heure_decollage) == 0))
                {
                    // ici faut afficher le vol, faut attendre la fonction...

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
            break;
        }
    } while (choix != 0);
}

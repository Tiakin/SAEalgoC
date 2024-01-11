#include "main.h"

/**
 * @brief fichier volManager contenant les fonctions liées au vol
 * @author Killian
 * @author Axel
 *
 */


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
        printf("\e[0;31mMenu de recherche :\n\e[0;32m0 ou invalide: Quitter la recherche\n1: Rechercher par compagnie aerienne\n2: Rechercher par destination\n3: Rechercher par heure de decollage\n4: Afficher les resultats de la recherche\n\e[0;33mSaisissez un choix : \e[0;37m");
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
            printf("Heure | Numero | Compagnie | Destination | Comptoir | Salle | Etat\n");
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

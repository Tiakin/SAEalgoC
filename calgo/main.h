#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_VOLS 100
#define MAX_PASSAGERS 150

#define MAX_LIGNE 1000

#define MAX_NOM 50
#define MAX_DESTINATION 100
#define MAX_ETAT 20


/**
 * @brief Structure passager
 * @author Killian
 * @author Martin
 * @author Axel
 *
 */
typedef struct {
    char nom[MAX_NOM];
    char prenom[MAX_NOM];
    char date_naissance[11];
    int numero_siege;
    float prix_billet;
} Passager;


/**
 * @brief Structure vol
 * @author Killian
 * @author Martin
 * @author Axel
 *
 */
typedef struct {
    int numero_vol;
    char compagnie[MAX_NOM];
    char destination[MAX_DESTINATION];
    int numero_comptoir;
    int heure_debut_enregistrement;
    int heure_fin_enregistrement;
    int salle_embarquement;
    int heure_debut_embarquement;
    int heure_fin_embarquement;
    int heure_decollage;
    char etat_vol[MAX_ETAT];
    Passager liste_passagers[MAX_PASSAGERS];
} Vol;


/**
 * @brief Creation du tableau des vols
 * @author Killian
 * @param tableau_vols[] tableau des vols
 */
int creer_tableau_vols(Vol tableau_vols[], char nom_fichier[]);


/**
 * @brief Creation d'un tableau passager
 * @author Killian
 * @param tableau_passagers[] tableau passager (vide)
 * @param liste[] la liste des passagers
 */
void creer_tableau_passagers(Passager tableau_passagers[], char liste[]);


/**
 * @brief Affiche les vols (h+3)
 * @author Killian
 * @author Martin
 * @param vols[] tableau des vols
 */
void afficher_vols(Vol vols[]);


/**
 * @brief Affiche un vol (une heure proche affichera des details)
 * @author Killian
 * @author Martin
 * @param vol vol
 * @param heure
 */
void afficher_vol(Vol vol, int heure);


/**
 * @brief Recherche de vol
 * @author Killian
 * @param tableau_vols[] tableau des vols
 */
void rechercher_vol(Vol tableau_vols[]);


/**
 * @brief Trie les passagers dans la liste donné
 * @author Killian
 * @author Axel
 * @param tableau_passagers[] tableau des passagers
 */
void tri_passager(Passager tableau_passagers[]);


/**
 * @brief affiche un passager
 * @author Killian
 * @author Axel
 * @param passager passager
 */
void afficher_passager(Passager passager);


/**
 * @brief Fonction pour calculer l'age
 * @author Killian
 * @author Axel
 * @param date_naissance[] la date de naissance au format JJ/MM/AAAA
 * @return l'age calculé
 */
int calculer_age(char date_naissance[]);


/**
 * @brief Fonction pour afficher les embarquements
 * @author Killian
 * @author Axel
 * @param vols[] les vols
 */
void embarquement(Vol vols[]);

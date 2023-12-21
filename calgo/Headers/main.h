#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VOLS 100
#define MAX_PASSAGERS 150

#define MAX_LIGNE 1000

#define MAX_NOM 50
#define MAX_DESTINATION 100
#define MAX_ETAT 20


typedef struct {
    char nom[MAX_NOM];
    char prenom[MAX_NOM];
    char date_naissance[11];
    int numero_siege;
    float prix_billet;
} Passager;

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

void creer_tableau_vols(Vol tableau_vols[], char nom_fichier[]);

void creer_tableau_passagers(Passager tableau_passagers[], char liste[]);

void rechercher_vol(Vol tableau_vols[]);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VOLS 50
#define MAX_PASSAGERS 200

#define MAX_LIGNE 1000

#define MAX_NOM 50
#define MAX_DESTINATION 100
#define MAX_ETAT 20
#define MAX_HEURE 4

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
    int heure_debut_enregistrement[MAX_HEURE];
    int heure_fin_enregistrement[MAX_HEURE];
    int salle_embarquement;
    int heure_debut_embarquement[MAX_HEURE];
    int heure_fin_embarquement[MAX_HEURE];
    int heure_decollage[MAX_HEURE];
    char etat_vol[MAX_ETAT];
    Passager liste_passagers[MAX_PASSAGERS];
} Vol;

void creer_tableau_vols(Vol tableau_vols[], char nom_fichier[]);

void creer_tableau_passagers(Passager tableau_passagers[], char liste[]);

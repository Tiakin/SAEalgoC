#include "main.h"

typedef struct {
    char nom[MAX_NOM];
    char prenom[MAX_NOM];
    char date_naissance[11];
    int numero_siege;
    float prix_billet;
} Passager;

void afficher_vols(Vol vols[]);

void afficher_vol(Vol vol, int heure);

void rechercher_vol(Vol tableau_vols[]);

#include "main.h"

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

void tri_passager(Passager tableau_passagers[]);

int calculer_age(char date_naissance[]);

void afficher_passager(Passager passager);

void embarquement(Vol vols[]);

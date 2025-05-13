#ifndef ING1_ALLEGRO_2025_3_4_PROJECTILE_H
#define ING1_ALLEGRO_2025_3_4_PROJECTILE_H

//Inclusion Bibliothèque / .H nécessaires aux déclarations
#include "../Initialisation_jeu.h"

//Déclaration constantes

//Definition Structure
typedef struct{
    int tir_alliee;
    t_mouv mouv;
    t_hitbox hitbox;
    tab_bitmap sprite;
}t_projectile;

typedef struct noeud_p{
    t_projectile proj;
    struct noeud_p* next;
    struct noeud_p* prev;
}noeud_p;

typedef struct{
    noeud_p* debut;
    t_projectile* modele;
    int nombre_modele;
}liste_projectile;

//Déclaration sous programmes
t_projectile initialiser_projectile(int tir_allie, t_mouv tireur);
void creer_projectile(liste_projectile * liste_p, int tir_allie, t_mouv objet);
void detruire_projectile(liste_projectile* liste_p, noeud_p * noeudE);
void liberation_liste_projectile(liste_projectile* liste_p);
#endif //ING1_ALLEGRO_2025_3_4_PROJECTILE_H

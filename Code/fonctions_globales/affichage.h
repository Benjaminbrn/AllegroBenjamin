#ifndef PROJETJEU_AFFICHAGE_H
#define PROJETJEU_AFFICHAGE_H

//Inclusion Bibliothèque / .H nécessaires aux déclarations
#include <allegro.h>
#include <stdbool.h>

//Déclaration constantes
#define LARGEUR_ECRAN 1440
#define HAUTEUR_ECRAN 810

//Definition Structure
typedef struct{ //Structure pour les tableaux de bitmap
    BITMAP **sprite; //Tableau de sprite
    int taille; //Taille du tableau de sprite
    float animation; //Variable d'animation, en float car sera additionée par vitesse animatio
}tab_bitmap;

//Déclaration sous programmes :
void afficherJeu(BITMAP* page);  //Affiche le jeu
void animation(BITMAP* page, tab_bitmap* element, int x, int y); //Anime objet
BITMAP* initialiser_bitmap(const char* chemin); // Initialise et test bitmaps
tab_bitmap initialiser_tableau_bitmap(const char* chemin, int nombre_sprites); //Initialise un tableau de bitmap
void destruction_tableau_bitmap(tab_bitmap* tab, bool statique); //Supprime les bitmaps d'un tableau
void destruction_bitmaps(tab_bitmap *liste_bitmaps, int nombre_tableaux, bool premier_tab_statique); //Supprime toute bitmaps

#endif //PROJETJEU_AFFICHAGE_H

#ifndef ING1_ALLEGRO_2025_3_4_MAP_H
#define ING1_ALLEGRO_2025_3_4_MAP_H

//Inclusion Bibliothèque / .H
#include "../Initialisation_jeu.h"
#include "../fonctions_globales/affichage.h"

//Definition Structure
typedef struct{ // Structure pour le décor
    t_mouv mouv;         // Position et déplacement de l'écran par rapport au décor total
    tab_bitmap sprite;   // Sprites du décor
    BITMAP* Hitbox;      // Carte des obstacles du décor
    BITMAP* virtual_screen; // Écran virtuel pour le scrolling
    int largeur_totale;  // Largeur totale du niveau
    int hauteur_totale;  // Hauteur totale du niveau
    int scroll_x;        // Position actuelle du scrolling horizontal
    int scroll_y;        // Position actuelle du scrolling vertical
}t_map;

//Déclaration sous programmes
t_map initialiser_map(const char* chemin_background);  // Initialise la map avec l'image de fond
void detruire_map(t_map* map);                         // Libère la mémoire allouée pour la map
void actualiser_scrolling(t_map* map);                 // Met à jour la position de scrolling
void dessiner_map(t_map* map, BITMAP* page);           // Dessine la portion visible de la map sur l'écran

#endif //ING1_ALLEGRO_2025_3_4_MAP_H
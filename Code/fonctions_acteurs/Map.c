//Inclusion Bibliothèque / .H
#include "Map.h"
#include "../fonctions_globales/affichage.h"
#include <stdio.h>

//Fonction qui initialise une map à partir d'une image de fond
t_map initialiser_map(const char* chemin_background) {
    t_map map;
    map.mouv.x = 0;
    map.mouv.y = 0;
    map.mouv.dx = 1;
    map.mouv.dy = 0;
    map.mouv.vitesse = 1;
    map.scroll_x = 0;
    map.scroll_y = 0;

    // Chargement du fond
    BITMAP* background_original = load_bitmap(chemin_background, NULL);
    if (!background_original) {
        allegro_message("Erreur lors du chargement de l'image: %s", chemin_background);
        map.virtual_screen = NULL;
        return map;
    }

    // Création d'une version redimensionnée à SCREEN_W x SCREEN_H
    BITMAP* background = create_bitmap(SCREEN_W, SCREEN_H);
    stretch_blit(background_original, background, 0, 0, background_original->w, background_original->h,
                 0, 0, SCREEN_W, SCREEN_H);
    destroy_bitmap(background_original);

    // Taille virtuelle = 3 fois la largeur écran
    map.largeur_totale = SCREEN_W * 3;
    map.hauteur_totale = SCREEN_H;

    map.virtual_screen = create_bitmap(map.largeur_totale, map.hauteur_totale);
    if (!map.virtual_screen) {
        allegro_message("Erreur création écran virtuel");
        destroy_bitmap(background);
        return map;
    }

    // Répéter le fond 3 fois dans la largeur
    blit(background, map.virtual_screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);        // Première répétition (0 à SCREEN_W)
    blit(background, map.virtual_screen, 0, 0, SCREEN_W, 0, SCREEN_W, SCREEN_H); // Deuxième répétition (SCREEN_W à 2 * SCREEN_W)
    blit(background, map.virtual_screen, 0, 0, 2 * SCREEN_W, 0, SCREEN_W, SCREEN_H); // Troisième répétition (2 * SCREEN_W à 3 * SCREEN_W)

    // Hitbox
    map.Hitbox = create_bitmap(map.largeur_totale, map.hauteur_totale);
    if (!map.Hitbox) {
        allegro_message("Erreur creation hitbox");
        destroy_bitmap(map.virtual_screen);
        destroy_bitmap(background);
        map.virtual_screen = NULL;
        return map;
    }

    clear_to_color(map.Hitbox, makecol(255, 0, 255));
    destroy_bitmap(background);
    return map;
}

//Fonction qui libère la mémoire allouée pour la map
void detruire_map(t_map* map) {
    if(map->virtual_screen) {
        destroy_bitmap(map->virtual_screen);
        map->virtual_screen = NULL;
    }

    if(map->Hitbox) {
        destroy_bitmap(map->Hitbox);
        map->Hitbox = NULL;
    }
}

//Fonction qui met à jour la position de scrolling
void actualiser_scrolling(t_map* map) {
    //Mise à jour du scrolling en fonction du vecteur de déplacement
    map->scroll_x += map->mouv.vitesse * map->mouv.dx;

    //Gestion de la boucle du scrolling (pour un niveau infini)
    if (map->scroll_x < 0) {
        map->scroll_x = map->largeur_totale - SCREEN_W;
    }

    if (map->scroll_x > map->largeur_totale - SCREEN_W) {
        map->scroll_x = 0;
    }
}

//Fonction qui dessine la portion visible de la map sur l'écran
void dessiner_map(t_map* map, BITMAP* page) {
    if (!map->virtual_screen) return;

    clear_to_color(page, makecol(0, 0, 0));

    // Afficher la portion visible
    blit(map->virtual_screen, page, map->scroll_x, 0, 0, 0, SCREEN_W, SCREEN_H);
}



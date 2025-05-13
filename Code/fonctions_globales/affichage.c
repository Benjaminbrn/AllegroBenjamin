//Inclusion Bibliothèque / .H
#include "affichage.h"
#include <stdio.h>

//Constantes
const float vitesse_animation = 0.5; // Vitesse d'animation : 1 (max) -> normal, 0,5 -> ralenti de moitié, ect ...

//Dans un programme on fait toujours vsync (synchronisation verticale) avant d'afficher un élément
//Fonction qui affiche le jeu
void afficherJeu(BITMAP* page){  //Affiche le jeu
    show_mouse(page); //affiche la souris sur le double buffer
    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); //Affiche élément double buffer à écran
    clear(page); //supprime les éléments du double buffer
}

//Fonction qui effectue une animation
void animation(BITMAP* page, tab_bitmap* element, int x, int y){
    draw_sprite(page, element->sprite[(int)element->animation], x, y); //Dessine le sprite
    element->animation += vitesse_animation; //Met à jour la variable animation en fonction de la vitesse
    if(element->animation >= element->taille){ //Si l'animation est fini ...
        element->animation = 0;                //On remet la variable animation à 0
    }
}

//Fonction qui initialise une bitmap et vérifie qu'elle est bien initialisé
BITMAP* initialiser_bitmap(const char* fichier){
    BITMAP* test = load_bitmap(fichier, NULL); //Initialise ...
    if(test !=NULL){ //test si la bitmap est bien initialisé
        return test; //Si oui on retourne
    }
    printf("Impossible d'initialiser %s", fichier); // Sinon on met un message d'erreur ...
    allegro_exit(); //On quitte allegro ...
    exit(EXIT_FAILURE); // Et on quitte le programme
}

//Fonction qui initialise un tableau de bitmap (pour animation) (Attention à ne pas mettre .bpm à la fin !)
tab_bitmap initialiser_tableau_bitmap(const char* chemin, int nombre_sprites){
    //Initialisation
    tab_bitmap nouveau = {malloc(sizeof(BITMAP*) * nombre_sprites), nombre_sprites, 0}; //On initialise le tableau de bitmap
    //Code
    if(nouveau.sprite != NULL){ //On test si on peut initialiser la mémoire ..1:
        char fichier[100]; //Initialise fichier où on stock chemin finale
        for (int i = 0; i < nombre_sprites; i++) { // On charge les images du tableau
            snprintf(fichier, sizeof(fichier), "%s%d.bmp", chemin, i); //stock chemin et numéro sprite dans fichier
            nouveau.sprite[i] = initialiser_bitmap(fichier); // On charge les sprites de manière sécurisé
        }
        return nouveau; //On retourne le tableau crée
    }
    printf("Impossible d'allouer mémoire pour %s", chemin); // Sinon on met un message d'erreur ...
    allegro_exit(); //On quitte allegro ...
    exit(EXIT_FAILURE); // Et on quitte le programme
}

//Fonction pour détruire toutes bitmaps dans un tableau.
void destruction_tableau_bitmap(tab_bitmap* tab, bool statique){
    for(int i = 0; i<tab->taille; i++){ //On supprime toutes les bitmaps jusqu'à atteindre la taille max
        destroy_bitmap(tab->sprite[i]);
    }
    if(!statique){ //Si le tableau à été déclaré dynamiquement ...
        free(tab->sprite); //On libère le tableau déclaré dynamiquement, (Crash avec tableau statique)
    }
}

//Fonction pour détruire toutes bitmaps. (On met toujours dans liste bitmaps le tableau statique au début)
void destruction_bitmaps(tab_bitmap *liste_bitmaps, int nombre_tableaux, bool premier_tab_statique){
    for(int i = 0; i<nombre_tableaux; i++){ //On regarde dans tout les tableaux ...
        //On détruit (en faisant attention de spécifier que le premier tableau est statique s'il y en a un)
        //De plus &(*liste_bitmaps)[i] est dû au fait qu'on a un pointeur vers un tableau statique, d'où cette forme
        destruction_tableau_bitmap(&liste_bitmaps[i], (i == 0 && premier_tab_statique));

    }
}
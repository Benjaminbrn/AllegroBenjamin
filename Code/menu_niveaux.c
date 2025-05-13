//Inclusion Bibliothèque / .H
#include "menu_niveaux.h"
#include "../Code/fonctions_globales/boutons.h"

//Constantes pour la sélection des niveaux
    //États de retour - alignés avec Menu.c
#define Quitter 0
#define Ecran_titre 3      // Pour revenir à l'écran titre
#define Lancer_niveau_1 10 // Valeurs distinctes pour ne pas confondre avec les états du menu principal
#define Lancer_niveau_2 11
#define Lancer_niveau_3 12

// Configuration de l'affichage des niveaux - disposition horizontale
const int NOMBRE_NIVEAUX = 3;
const int NIVEAUX_Y = 120;                // Position y commune pour tous les niveaux
const int NIVEAUX_X[] = {200, 500, 800};  // Positions x pour chaque niveau
const int NIVEAU_IMG_H = 240;             // Hauteur des images des mondes
const int NIVEAU_IMG_W = 240;             // Largeur des images des mondes
const int BOUTON_Y = 380;                 // Position y des boutons
const int BOUTON_H = 80;                  // Hauteur des boutons
const int BOUTON_W = 200;                 // Largeur des boutons

// Constantes pour l'animation du curseur de sélection
const int POSITION_CURSEUR_Y = 390;        // Position y du curseur
const int POSITION_CURSEUR_X[] = {135, 435, 735}; // Positions x du curseur pour chaque niveau

//Fonction qui gère la sélection des niveaux
int MenuNiveaux(BITMAP* page){
    //Bitmaps
        //Bitmap Arrière-Plan
    BITMAP *fond = initialiser_bitmap("../Sprites/Menu/MenuPrincipale/fond_ecran.bmp");
        //Bitmaps des mondes (niveaux)
    BITMAP *monde_tropical = initialiser_bitmap("../Sprites/Menu/MenuSelection/niveau1.bmp");
    BITMAP *monde_glacial = initialiser_bitmap("../Sprites/Menu/MenuSelection/niveau2.bmp");
    BITMAP *monde_autre = initialiser_bitmap("../Sprites/Menu/MenuSelection/niveau1.bmp"); // Réutilisation temporaire
    BITMAP *mondes[] = {monde_tropical, monde_glacial, monde_autre};
        //Bitmaps des boutons
    BITMAP *bouton_niveau_1 = initialiser_bitmap("../Sprites/Menu/MenuSelection/Case/casejouerbmp");
    BITMAP *bouton_niveau_2 = initialiser_bitmap("../Sprites/Menu/MenuSelection/Case/caseoptions");
    BITMAP *bouton_niveau_3 = initialiser_bitmap("../Sprites/Menu/MenuSelection/Case/casequitter");
    BITMAP *boutons[] = {bouton_niveau_1, bouton_niveau_2, bouton_niveau_3};
        //Curseur animé
    tab_bitmap curseur = initialiser_tableau_bitmap("../Sprites/Menu/MenuSelection/Curseur/curseur", 16);

    //Variables
    int choix = Ecran_titre;          // Par défaut, on revient à l'écran titre
    static int niveau_select = 0;     // Niveau actuellement sélectionné (0, 1 ou 2)
    bool bounce_menu = true;          // Pour gérer le rebond des touches de sélection
    bool bounce_fleches = true;       // Pour gérer le rebond des flèches
    bool bounce_souris = true;        // Pour gérer le rebond de la souris

    //Execution
    while(1){
        //Dessiner fond
        stretch_blit(fond, page, 0, 0, fond->w, fond->h, 0, 0, SCREEN_W, SCREEN_H);

        //Afficher les images de niveaux et les boutons
        for(int i = 0; i < NOMBRE_NIVEAUX; i++){
            // Afficher l'image du monde/niveau
            stretch_blit(mondes[i], page, 0, 0, mondes[i]->w, mondes[i]->h,
                        NIVEAUX_X[i] - NIVEAU_IMG_W/2, NIVEAUX_Y, NIVEAU_IMG_W, NIVEAU_IMG_H);

            // Afficher le bouton correspondant
            stretch_blit(boutons[i], page, 0, 0, boutons[i]->w, boutons[i]->h,
                        NIVEAUX_X[i] - BOUTON_W/2, BOUTON_Y, BOUTON_W, BOUTON_H);
        }

        //Gestion des inputs
            //Navigation avec flèches gauche/droite
        if(bounce(key[KEY_RIGHT] || key[KEY_LEFT], &bounce_fleches)) {
            if (key[KEY_RIGHT]) {
                niveau_select = (niveau_select + 1) % NOMBRE_NIVEAUX;
            } else {
                niveau_select = (niveau_select - 1 + NOMBRE_NIVEAUX) % NOMBRE_NIVEAUX;
            }
        }
            //Navigation avec souris
        if(mouse_y > BOUTON_Y && mouse_y < BOUTON_Y + BOUTON_H) {
            for(int i = 0; i < NOMBRE_NIVEAUX; i++) {
                if(mouse_x > NIVEAUX_X[i] - BOUTON_W/2 && mouse_x < NIVEAUX_X[i] + BOUTON_W/2) {
                    if(bounce(1, &bounce_souris)) {
                        niveau_select = i;
                    }

                    // Sélection avec clic
                    if(mouse_b & 1 && bounce(1, &bounce_menu)) {
                        choix = Lancer_niveau_1 + i; // Lancer le niveau correspondant
                        goto fin_menu_niveaux;       // Sortir des boucles
                    }
                }
            }
        } else {
            bounce_souris = false; // Réinitialiser le bounce quand la souris quitte la zone
        }

            //Sélection avec entrée/espace ou échap
        if(bounce(key[KEY_ENTER] || key[KEY_SPACE] || key[KEY_ESC], &bounce_menu)) {
            if(key[KEY_ESC]) {
                choix = Ecran_titre;
                goto fin_menu_niveaux;
            } else if(key[KEY_ENTER] || key[KEY_SPACE]) {
                choix = Lancer_niveau_1 + niveau_select;
                goto fin_menu_niveaux;
            }
        }

        //Afficher le curseur sur le niveau sélectionné
        animation(page, &curseur, POSITION_CURSEUR_X[niveau_select], POSITION_CURSEUR_Y);

        //Affichage
        vsync();
        afficherJeu(page);
    }

fin_menu_niveaux:
    //Destruction des bitmaps
    BITMAP* statique[] = {fond, monde_tropical, monde_glacial, monde_autre};
    tab_bitmap liste[] = {{statique, 4}, curseur};
    destruction_bitmaps(liste, 2, true);

    // On ne détruit pas la musique ici pour permettre la continuité
    // Elle sera détruite lors de la sortie du menu principal

    return choix;
}
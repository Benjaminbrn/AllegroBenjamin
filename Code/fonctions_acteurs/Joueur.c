//Inclusion Bibliothèque / .H
#include "Joueur.h"
#include <stdbool.h>

    //Fonctions d'actions

//Fonction qui gère les actions des joueurs, déplacement, tirer, pause
void action_joueur(t_joueur* j, liste_projectile* liste_p, bool* pause, TOUCHES* touches){
    deplacement_joueur(j);                                          //Fonction qui fait le déplacement du joueur
    if(bounce(key[KEY_SPACE], &touches->espace)){  //On vérifie que la touche espace est appuyée...
        tirer_joueur(liste_p, j->mouv);                       //Fonction qui génère un projectile alliée
    }
    action_pause(pause, &touches->bounceP);                //Fonction pour activer le menu pause
}

//Fonction qui gère le déplacement du joueur, c'est à dire l'actualisation de son vecteur déplacement et vitesse
void deplacement_joueur(t_joueur* j){
    bool droite = key[KEY_RIGHT];       //Vérifie que le joueur se déplace à droite
    bool gauche = key[KEY_LEFT];        //Vérifie que le joueur se déplace à gauche
    bool haut = key[KEY_UP];            //Vérifie que le joueur se déplace en haut
    bool bas = key[KEY_DOWN];           //Vérifie que le joueur se déplace à gauche
    bool acceleration = key[KEY_LSHIFT];//Vérifie que le joueur se déplace à gauche
    j->mouv.vitesse = vitesse_j + vitesse_j*acceleration; //Change la vitesse du joueur
    j->mouv.dx = droite - gauche; //Change le vecteur déplacemenet en x du joueur
    j->mouv.dy = bas - haut;      //Change le vecteur déplacemenet en y du joueur
}

//Fonction qui créer un projectile alliée aux coordonnées du joueur
void tirer_joueur(liste_projectile * liste_p, t_mouv tireur){
    creer_projectile(liste_p, 1, tireur); //Créer un projectile alliée
}

//Fonction qui permet au joueur de mettre le jeu en pause ou continuer la partie
void action_pause(bool*pause, bool* bounce_P){
    if(bounce(key[KEY_P], bounce_P)){ //On vérifie si la touche P est touché avec rebond
        (*pause) =!(*pause); // Met la pause à l'inverse afin de lancer / mettre en pause
    }
}

//Fonction gestion de la mémoire

    //Fonction qui initialise et renvoie les données du vaisseau du joueur
t_joueur initialisation_joueur(char* pseudo){
    t_joueur nv = {{0}}; // Initialise
    nv.pseudo = pseudo;
    nv.sprite = initialiser_tableau_bitmap("../Sprites/Jeu/Joueur/vaisseau", 1);
    nv.mouv.vitesse = vitesse_j;
    // Hitbox
    nv.hitbox.x1 = nv.mouv.x;
    nv.hitbox.y1 = nv.mouv.y;
    nv.hitbox.w = 50; // Temporaire, tant que le joueur est un carré, à modifier plus tard
    nv.hitbox.h = 50; // Temporaire, tant que le joueur est un carré, à modifier plus tard
    // Propriétés
    nv.prop.pv = 3;
    nv.prop.pv_initial = 5;
    nv.prop.vie = nv.prop.pv_initial;
    nv.prop.degat = 50; // Le joueur fait 50 dégats à chaque tir. A modifier plus tard selon les armes etc
    return nv;
}

    //Fonction qui libère les données dynamique du joueur
void liberation_joueur(t_joueur* j){
    destruction_tableau_bitmap(&j->sprite, 0); //On détruit les sprites du joueur
    free(j->pseudo);                                       //On libère dynamiquement le pseudo
}


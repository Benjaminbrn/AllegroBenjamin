//Inclusion Bibliothèque / .H
#include "Initialisation_jeu.h"
#include "../Code/fonctions_acteurs/Joueur.h"
#include "../Code/fonctions_acteurs/Ennemi.h"
#include "../Code/fonctions_acteurs/Projectile.h"
#include "Jeu.h"
#include "../Code/fonctions_acteurs/Map.h"
#include <stdio.h>

//Constantes
#define max_pseudo 15 //Nombe de caractère max du pseudo
const int valeur_majuscule = 'A' - 'a'; //Valeur en ASCII d'une majuscule pour convertir une min en maj

//Fonction qui initialise et charge les différents éléments du jeu (Map, ennemis, joueur, projectils, bonus) avant de le lancer
void lancer_jeu(BITMAP* page, MUSIC* musique){
    //Code
        //Initialisation
    char* pseudo = initialiser_pseudo(page, musique); //Ouvre le menu pour rentrer le pseudo et le renvoie

    //Fonction pour charger partie si pseudo existe déjà
    //Fonction pour charger map
    t_map map = initialiser_map("../Sprites/Jeu/bg.bmp");
    //Fonction pour charger en fonction de la map : modeles ennemies / éléments / Bitmaps / Musiques

    musique->morceau = initialiser_musique("../Musique/niveau_1.wav"); //Initialise la musique
    t_joueur j = initialisation_joueur(pseudo);         //Initialise le joueur
    data_ennemi data_e = initialiser_data_ennemi();     //Initialise les données des ennemies (liste chaînée + tableau)
    liste_projectile liste_p = {NULL};                  //Initialise la liste chaînée de projectiles

        //Lancement du jeu
    jeu(page, &j, &data_e, &liste_p, musique, &map); //Fonction pour lancer jeu

        //Fin du jeu (libération des éléments dynamique, Bitmaps, musique)
    destroy_sample(musique->morceau);    //Destruction musique
    liberation_liste_projectile(&liste_p);   //Libération liste chaînée projectile
    liberation_data_ennemi(&data_e);         //Libération liste chaînée ennemi
    liberation_joueur(&j);                   //Libération joueur
    detruire_map(&map);                      //Libération map
}

//Fonction qui demande le pseudo, laisse l'utilisateur rentrer le pseudo et le renvoie.
char* initialiser_pseudo(BITMAP* page, MUSIC* musique){
    //Bitmaps
    BITMAP* fond_pseudo = initialiser_bitmap("../Sprites/Ecran_pseudo/fond_pseudo.bmp"); //Fond écran pseudo

    //Musique
    musique->morceau = initialiser_musique("../Musique/menu_pseudo.wav"); //Initialisation musique
    play_sample(musique->morceau, musique->volume, pan, 1000, true); //On joue le son

    //Variables
    char pseudo[max_pseudo + 1] = {'\0'}; //Chaîne de caractère qui contient le pseudo
    int position_pseudo = 0; //Position du curseur lors de l'écriture
    bool bounce_pseudo = true; //Bounce pour l'écriture du pseudo
    bool verouille_maj = false; //Vérifie que la verouille maj soit activé

    //Code
        //Boucle
    while(!key[KEY_ENTER]){ //Tant que la touche ENTREE n'est pas préssée ...
        //Taper pseudo
        int touche = touche_pressee(); //On récupère la touche convertie
        //On vérifie que : la touche est une lettre (KEY : 1 à 26 dans l'ordre de l'alphabet), ou on tape espace, ou retour, ou verouille maj ...
        if(bounce((touche >= KEY_A && touche <= KEY_Z)||key[KEY_BACKSPACE]||key[KEY_SPACE]||key[KEY_CAPSLOCK], &bounce_pseudo)){
            if(key[KEY_CAPSLOCK]){                 //Si verouille maj touché ...
                verouille_maj = (!verouille_maj);  //Alors on active vouille_maj ou le désactive s'il est activé
            }else if(key[KEY_BACKSPACE]){          //Sinon si retour touché ...
                if(position_pseudo > 0){           //Si le pseudo n'est pas vide ...
                    position_pseudo --;            //On recule le curseur
                    pseudo[position_pseudo] = '\0';//et on efface la lettre
                }
            }
            // (C'est donc maintenant forcément une lettre ou un espace)
            else if(position_pseudo < max_pseudo){//Sinon si le curseur ne dépasse pas la taille max
                char lettre = 'a' - 1; //On déclare une variable qui va stocker la lettre (on intialise à cette valeur pour commencer aux lettres de l'alphabet en ASCII)
                if(key[KEY_SPACE]){    //Si la touche espace est pressée...
                    lettre = ' ';      //On met un espace
                }else{                 //Sinon ...
                    lettre += touche;  //On additionne la valeur de la touche (1 à 26) à lettre (pour avoir la valeur de la lettre qu'on veut en ASCII)
                    if((key[KEY_LSHIFT]||key[KEY_RSHIFT])||verouille_maj){ //Si maj est pressée ou si verouille maj est activé ...
                        lettre += valeur_majuscule; //On addition la lettre avec la valeur qui permet de la passer en majuscule en ASCII
                    }
                }
                pseudo[position_pseudo] = lettre; //Enfin on ajoute la lettre dans le pseudo
                position_pseudo ++;               //Et on augmente la position du curseur
            }
        }

        //Affichage
        vsync(); //Rafraîchissement verticale
        stretch_blit(fond_pseudo, page, 0, 0, fond_pseudo->w, fond_pseudo->h, 0, 0, SCREEN_W, SCREEN_H); //On affiche le fond du menu pseudo
        textout_centre_ex(page, font, pseudo, 500, 350, makecol(255,255,255), -1); //On affiche le pseudo
        afficherJeu(page); //On affiche le jeu
    }
    //Destruction des bitmaps
    destroy_bitmap(fond_pseudo); //On détruit la bitmap pour le fond pseudo

    //Destruction de la musique et des sound effect
    destroy_sample(musique->morceau);

    char* pseudo_final = malloc(strlen(pseudo)); //On initialise pseudo final avec la taille (jusqu'au premier \0) de pseudo
    strcpy(pseudo_final, pseudo);                //On attribue à pseudo final le contenu (jusqu'au premier \0) de pseudo
    return pseudo_final;                         //On renvoie le pseudo finalement choisit par le joueur
}
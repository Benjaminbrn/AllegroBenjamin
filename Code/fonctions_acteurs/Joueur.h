#ifndef ING1_ALLEGRO_2025_3_4_JOUEUR_H
#define ING1_ALLEGRO_2025_3_4_JOUEUR_H

//Inclusion Bibliothèque / .H nécessaires aux déclarations
#include "../Initialisation_jeu.h"
#include "Projectile.h"

//Déclaration constantes

//Definition Structure
typedef struct{
    t_mouv mouv; //Variables mouvement
    t_prop prop; //Variables mouvement
    t_hitbox hitbox; //Variables hitbox
    tab_bitmap sprite; //Variables sprite / animation
    char* pseudo; //pseudo
}t_joueur;

//Déclaration sous programmes
void action_joueur(t_joueur* j, liste_projectile* liste_p, bool* pause, TOUCHES* touches); //Fonction qui gère les actions des joueurs, déplacement, tirer, pause
void tirer_joueur(liste_projectile * liste_p, t_mouv tireur); //Fonction qui créer un projectile alliée aux coordonnées du joueur
void deplacement_joueur(t_joueur* j); //Fonction qui gère le déplacement du joueur, (actualisation de son vecteur déplacement et vitesse)
void action_pause(bool*pause, bool* bounce_P); //Fonction qui permet au joueur de mettre le jeu en pause ou continuer la partie
t_joueur initialisation_joueur(char* pseudo); //Fonction qui initialise et renvoie les données du vaisseau du joueur
void liberation_joueur(t_joueur* j); //Fonction qui libère les données dynamique du joueur
#endif //ING1_ALLEGRO_2025_3_4_JOUEUR_H

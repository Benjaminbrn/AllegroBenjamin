#ifndef ING1_ALLEGRO_2025_3_4_JEU_H
#define ING1_ALLEGRO_2025_3_4_JEU_H

//Inclusion Bibliothèque / .H nécessaires aux déclarations
#include "../Code/Initialisation_jeu.h"
#include "../Code/fonctions_acteurs/Map.h"
#include "../Code/fonctions_acteurs/Joueur.h"
#include "../Code/fonctions_acteurs/Ennemi.h"
#include "../Code/fonctions_globales/musique.h"
#include "../Code/fonctions_globales/affichage.h"

//Déclaration constantes

//Definition Structure

//Déclaration sous programmes
void jeu(BITMAP* page, t_joueur* j, data_ennemi * data_e, liste_projectile* liste_p, MUSIC* musique, t_map* map);//Fonction qui execute la boucle de jeu avec les différents acteurs
void mouvement_acteurs(t_joueur* j, liste_ennemi *liste_e, liste_projectile* liste_p);//Fonction qui effectue le déplacement de tous les acteurs du jeu
void mouvement(t_mouv* mouv, t_hitbox* hb); //Fonction qui effecte le deplacement d'un objet selon son vecteur déplacement et actualise sa hitbox
#endif //ING1_ALLEGRO_2025_3_4_JEU_H

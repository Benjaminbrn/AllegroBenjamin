#ifndef MENU_NIVEAUX_H
#define MENU_NIVEAUX_H

//Inclusion Bibliothèque standard
#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Code/fonctions_globales/affichage.h"

//Constantes d'état de retour du menu
#define QUITTER 0
#define RETOUR_MENU 1
#define LANCER_NIVEAU_1 2
#define LANCER_NIVEAU_2 3
#define LANCER_NIVEAU_3 4

// Prototype de fonction
/**
 * @brief Affiche et gère le menu de sélection des niveaux
 * 
 * @param page La bitmap sur laquelle dessiner
 * @param musique Structure contenant les informations sur la musique
 * @return int Le choix effectué par l'utilisateur:
 *             - QUITTER (0): quitter le jeu
 *             - RETOUR_MENU (1): retourner au menu principal
 *             - LANCER_NIVEAU_1 (2): lancer le niveau 1 (monde tropical)
 *             - LANCER_NIVEAU_2 (3): lancer le niveau 2 (monde glacial)
 *             - LANCER_NIVEAU_3 (4): lancer le niveau 3 (autre monde)
 */
int MenuNiveaux(BITMAP* page);

#endif // MENU_NIVEAUX_H
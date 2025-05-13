#ifndef PROJETJEU_MENU_H
#define PROJETJEU_MENU_H

//Inclusion Bibliothèque / .H nécessaires aux déclarations
#include <allegro.h>
#include <stdbool.h>
#include "../Code/fonctions_globales/musique.h"
#include "../Code/fonctions_globales/affichage.h"

//Déclaration constantes

//Definition Structure

//Déclaration sous programmes
bool MenuPrincipale(BITMAP* page, MUSIC* musique); //Gère les différents menues
int ecranTitre(BITMAP* page, BITMAP* ecran_titre, bool* bounce_menu); //Gère l'écran titre
int ecranSelection(BITMAP* page, tab_bitmap* curseur, BITMAP* cases[], bool* bounce_menu); //Gère la selection des menues
int case_souris(); //Vérifie si une case à été touché par la souris
#endif //PROJETJEU_MENU_H

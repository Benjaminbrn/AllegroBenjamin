#ifndef PROJETJEU_BOUTONS_H
#define PROJETJEU_BOUTONS_H

//Inclusion Bibliothèque / .H nécessaires aux déclarations
#include <stdbool.h>

//Definition Structure
typedef struct toucheBounces{ //Structure qui gère les rebonds de touche pour le joueur
    bool bounceESC;   //rebond echap
    bool espace;      //rebond espace
    bool bounceP;     //rebond 'p'
}TOUCHES;

//Déclaration sous programmes
bool bounce(bool etatBouton, bool* bounce); //évite les rebonds des boutons
int touche_pressee(); //Vérifie qu'une touche soit pressée et l'a renvoie
int conversion_azerty(int touche); //Fonction qui fait la conversion AZERTY -> QWERTY

#endif //PROJETJEU_BOUTONS_H

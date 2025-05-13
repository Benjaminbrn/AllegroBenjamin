#ifndef PROJETJEU_JEU_H
#define PROJETJEU_JEU_H

//Inclusion Bibliothèque / .H
#include "../Code/fonctions_globales/affichage.h"
#include "../Code/fonctions_globales/boutons.h"
#include "../Code/fonctions_globales/musique.h"

//Déclaration constantes
#define vitesse_j 4 //Vitesse normal du joueur

//Definition Structure
    //Structure générales (utilisé par plusieurs acteurs)
typedef struct{ //Structure pour les variables de position et déplacement
    int x, y;   //position x et y
    int dx, dy; //vecteur dx et dy
    int vitesse;//vitesse
}t_mouv;

typedef struct{ //Structure pour les propriétés des objet (pv, vie et dégats)
    int vie; // Nombre d'essaie du niveau
    int pv; // composant d'une vie, nombre de hit qu'il peut prendre
    int pv_initial; //Variable qui stock pv initiale objet mort et qu'on veut avoir accès on son nombre de pv de base
    int degat;
}t_prop;

typedef struct{ //Structure pour la position des hitbox
    int x1, y1;//position x1, y1
    int w, h;  //largeur, hauteur
}t_hitbox;

//Déclaration sous programmes
void lancer_jeu(BITMAP* page, MUSIC* musique); //Fonction qui initialise les différents élément du jeu et le lance
char* initialiser_pseudo(BITMAP* page, MUSIC* musique); //Fonction qui ouvre le menu pseudo, initialise et renvoie le pseudo

#endif //PROJETJEU_JEU_H

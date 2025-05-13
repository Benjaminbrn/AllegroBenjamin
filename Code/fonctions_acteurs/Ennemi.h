#ifndef ING1_ALLEGRO_2025_3_4_ENNEMI_H
#define ING1_ALLEGRO_2025_3_4_ENNEMI_H

//Inclusion Bibliothèque / .H nécessaires aux déclarations
#include "../Initialisation_jeu.h"

//Déclaration constantes
#define vaisseau_simple 0
#define ennemi_statique 1

//Definition Structure
typedef struct{
    int* deplacement[2]; //Matrice avec tableau de dx et dy
    int taille;          //Taille de la matrice, soit nombre de déplacement pour la trajectoire
}t_trajectoire;

typedef struct{
    t_trajectoire* tab_traj;
    int* debut_trajectoire; //Contient le moment où la trajectoire de l'ennemi change
    int indice_traj; //Correspond à l'indice de la trajectoire
}tab_trajectoire;
//Inclure étape trajectoire, condition trajectoire (jeu proche ou non, ect) pour changer la trajectoire

typedef struct{
    t_mouv mouv;
    t_prop prop;
    t_hitbox hitbox;
    tab_bitmap sprite;
}t_ennemi;

typedef struct noeud_e{
    t_ennemi enn;
    struct noeud_e* next;
    struct noeud_e* prev;
}noeud_e;

typedef struct{
    noeud_e* debut;
    t_ennemi* modele; // Tableau qui va enregistrer les différents types d'ennemis avec leurs caractéristiques afin de les copier facilement
    int nombre_modele; // Nombre d'ennemis différents
}liste_ennemi;

typedef struct{                     //Structure qui va contenir les informations relatif à l'apparition d'un ennemi
    int x_map, y_map;               //Position dans la map (au cours du scrolling) à partir de laquelle l'ennemi doit apparaître
    int x_ecran, y_ecran;           //Position sur l'écran où l'ennemi apparaît
    int type;                       //Type d'ennemi
}spawn_ennemi;

typedef struct {
    spawn_ennemi* ennemi;          //Tableau contenant toutes les apparitions d'ennemis
    int indice;                      //indice du tableau
    int taille;                      //Type d'ennemi
}tab_ennemi;

typedef struct{
    liste_ennemi liste;    //Liste chaînée des ennemies actuellement dans le jeu + modele des ennemies
    tab_ennemi tab;        //Tableau dynamqiue d'ennemies à faire apparaître dans le jeu
}data_ennemi;

//Déclaration sous programmes
t_ennemi initialisation_modele_ennemi();
t_ennemi initialisation_ennemi(t_ennemi modele, spawn_ennemi enn);
liste_ennemi initialiser_liste_ennemis();
spawn_ennemi initialiser_spawn_ennemi(int y_ecran, int x_ecran, int x_map, int y_map, int type);
tab_ennemi initialiser_tab_ennemi();
data_ennemi initialiser_data_ennemi();
void creer_ennemi(liste_ennemi* liste_e, spawn_ennemi enn);
void detruire_ennemie(liste_ennemi* liste_e, noeud_e * noeudE);
void liberation_liste_ennemi(liste_ennemi * liste_e);
void liberation_tab_ennemi(tab_ennemi* tab_e);
void liberation_data_ennemi(data_ennemi* data_e);
#endif //ING1_ALLEGRO_2025_3_4_ENNEMI_H

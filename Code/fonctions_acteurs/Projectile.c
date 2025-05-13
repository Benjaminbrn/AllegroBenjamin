//Inclusion Bibliothèque / .H
#include "Projectile.h"
#include "Collisions.h"
#include <stdio.h>


//Fonction qui initialise et renvoie les données d'un projecctile
t_projectile initialiser_projectile(int tir_allie, t_mouv tireur){ // tir_allie : booléen (1 : tir allie ; 0 : tir ennemi)
    t_projectile nv;
    nv.mouv.dy = 0;
    nv.mouv.y = tireur.y + 20;
    nv.tir_alliee = tir_allie;
    nv.sprite = initialiser_tableau_bitmap("../Sprites/Jeu/Projectile/Proj", 1);
    if(tir_allie){
        nv.mouv.dx = 1;
        nv.mouv.x = tireur.x + 51;
    }else{
        nv.mouv.dx = -1;
        nv.mouv.x = tireur.x - 51;
    }
    nv.mouv.vitesse = 7;
    // Hitbox
    nv.hitbox.x1 = nv.mouv.x;
    nv.hitbox.y1 = nv.mouv.y;
    nv.hitbox.w = 50; // Temporaire, tant que les projectiles sont des carrés, à modifier plus tard
    nv.hitbox.h = 50; // Temporaire, tant que les projectiles sont des carrés, à modifier plus tard
    return nv;
}

//Fonction qui créer un projectile et le met dans liste chaînée
void creer_projectile(liste_projectile * liste_p, int tir_allie, t_mouv objet){ // tir_allie : booléen (1 : tir allie ; 0 : tir ennemi)
    noeud_p *nv = malloc(sizeof(noeud_p)); //Aloue de la mémoire pour un nouveau maillon
    if(nv == NULL){            //SI le maillon est null dû à une erreur ..
        printf("Erreur d'allocution mémoire modele"); //On affiche qu'il y a une erreur ...
        allegro_exit();                               //On quitte Allegro ...
        exit(EXIT_FAILURE);                           //On ferme le programme
    }
    nv->proj = initialiser_projectile(tir_allie, objet); //On initialise les données du projectile
    nv->next = liste_p->debut; //On l'inclut au début de la liste
    nv->prev = NULL;           //Comme il est au début, il n'a pas de précédent
    if(liste_p->debut !=NULL){ //Si il y avait déjà un maillon au début ...
        liste_p->debut->prev = nv; //On dit que le précédent de l'ancien premier maillon et le maillon créée
    }
    liste_p->debut = nv; //on met le maillon créant que début
}

void detruire_projectile(liste_projectile* liste_p, noeud_p * noeudP){
    destruction_tableau_bitmap(&noeudP->proj.sprite, 0);

    if(noeudP->next != NULL){
        noeudP->next->prev = noeudP -> prev;
    }
    if(noeudP->prev !=NULL){
        noeudP->prev->next = noeudP -> next;
    }else{
        liste_p->debut = noeudP->next;
    }
    free(noeudP);
}

//Fonction qui libère de la liste chaînée de projectiles
void liberation_liste_projectile(liste_projectile* liste_p){
    while(liste_p->debut != NULL){ //On parcourt l'entierté de la liste
        noeud_p* temp = liste_p->debut->next;
        detruire_projectile(liste_p, liste_p->debut);
        liste_p->debut = temp;
    }
}
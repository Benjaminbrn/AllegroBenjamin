//Inclusion Bibliothèque / .H
#include "Ennemi.h"
#include <stdio.h>

void deplacement_ennemi(t_mouv* mouv, int type_ennemi){

}

t_ennemi initialisation_modele_ennemi(){ //Temporaire, à charger depuis fichier données
    t_ennemi nv;
    nv.sprite = initialiser_tableau_bitmap("../Sprites/Jeu/Ennemi1/vaisseau", 1);
    //Vitesse
    nv.mouv.vitesse = 3;
    //Dimensions Hitbox
    nv.hitbox.w = 50; //largeur
    nv.hitbox.h = 50; //hauteur
    // Propriétés
    nv.prop.pv_initial = 100;
    nv.prop.pv = nv.prop.pv_initial;   //point de vie
    nv.prop.vie = 1;  //vie
    nv.prop.degat = 1;  //vie
    return nv;
}

t_ennemi initialisation_ennemi(t_ennemi modele, spawn_ennemi enn) {
    t_ennemi nv = modele;
    // Position
    nv.mouv.x = enn.x_ecran;         //Position en x
    nv.mouv.y = enn.y_ecran;         //Position en y
    nv.mouv.dx = -1;              //Vecteur déplacement en x //Temporaire
    nv.mouv.dy = 0;               //Vecteur déplacement en y
    // Hitbox
    nv.hitbox.x1 = nv.mouv.x;
    nv.hitbox.y1 = nv.mouv.y;
    return nv;
}

liste_ennemi initialiser_liste_ennemis(){
    liste_ennemi nv = {NULL};
    nv.nombre_modele = 1; //Temporaire, à charger depuis données de la map
    nv.modele = malloc(sizeof(t_ennemi) * nv.nombre_modele);
    if(nv.modele == NULL){
        printf("Erreur d'allocution mémoire modele ennemi");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i<nv.nombre_modele; i++){
        nv.modele[i] = initialisation_modele_ennemi(); //Temporaire, à charger depuis donnés map
    }
    return nv;
}

spawn_ennemi initialiser_spawn_ennemi(int y_ecran, int x_ecran, int x_map, int y_map, int type){ //Temporaire, à charger depuis fichier map
    spawn_ennemi nv;
    nv.y_ecran = y_ecran;
    nv.x_ecran = x_ecran;
    nv.x_map = x_map;
    nv.y_map = y_map;
    nv.type = type;
    return nv;
}

tab_ennemi initialiser_tab_ennemi(){ //Temporaire, à charger depuis fichier map
    tab_ennemi nv;
    nv.indice = 0;
    nv.taille = 5; //A charger depuis fichier map
    nv.ennemi = malloc(sizeof(spawn_ennemi)*nv.taille);
    for(int i = 0; i<nv.taille; i++){
        nv.ennemi[i] = initialiser_spawn_ennemi(rand()%SCREEN_W, SCREEN_H, 0,0,0);
    }
    return nv;
}

data_ennemi initialiser_data_ennemi(){
    data_ennemi nv;
    nv.tab = initialiser_tab_ennemi();
    nv.liste = initialiser_liste_ennemis();
    return nv;
}

//Crée
/**
void apparition_ennemi(data_ennemi* data_e){
    tab_ennemi temp = data_e->tab; //Pour que cela soit plus simple à parcourir
    if(temp.ennemi[temp.indice].)
}**/

void creer_ennemi(liste_ennemi* liste_e, spawn_ennemi enn){
    noeud_e *nv = malloc(sizeof(noeud_e));
    if(nv == NULL){
        printf("Erreur d'allocution mémoire modele");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    nv->enn = initialisation_ennemi(liste_e->modele[enn.type], enn);
    nv->next = liste_e->debut;
    nv->prev = NULL;
    if(liste_e->debut !=NULL){
        liste_e->debut->prev = nv;
    }
    liste_e->debut = nv;
}


//Détruire
void detruire_ennemie(liste_ennemi* liste_e, noeud_e * noeudE){
    if(noeudE->next != NULL){
        noeudE->next->prev = noeudE -> prev;
    }
    if(noeudE->prev !=NULL){
        noeudE->prev->next = noeudE -> next;
    }else{
        liste_e->debut = noeudE->next;
    }
    free(noeudE);
}

void liberation_liste_ennemi(liste_ennemi * liste_e){
    while(liste_e->debut != NULL){
        noeud_e* temp = liste_e->debut->next;
        detruire_ennemie(liste_e, liste_e->debut);
        liste_e->debut = temp;
    }
    for(int i = 0; i<liste_e->nombre_modele; i++){
        destruction_tableau_bitmap(&liste_e->modele[i].sprite, 0);
    }
    free(liste_e->modele);
}

void liberation_tab_ennemi(tab_ennemi* tab_e){
    free(tab_e->ennemi);
}
void liberation_data_ennemi(data_ennemi* data_e){
    liberation_liste_ennemi(&data_e->liste);
    liberation_tab_ennemi(&data_e->tab);
}
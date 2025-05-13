#include "boutons.h"
#include <allegro.h>

//Fonction qui permet d'éviter les rebonds des boutons (Attention : 1 appel de la fonction par bounce, sinon erreur)
bool bounce(bool etat, bool* bounce){ //évite les rebonds des boutons
    if(etat){                  //Si la condition est vraie,
        if(*bounce){           //et s'il n'y a pas de rebond :
            (*bounce) = false; //on indique qu'il a du rebond maintenant
            return 1;          //et on indique que la condition est vraie
        }
    }else{                     //Sinon si la condition est fausse
        (*bounce = true);      //on indique qu'il n'y a pas de rebond
    }
    return 0;                  //On indique que la condition est fausse (si non appuyé ou si rebond)
}

//Fonction qui vérifie qu'une touche est pressée et renvoie la valeur de la touche, sinon 0
int touche_pressee(){
    for(int i =0; i<KEY_MAX; i++){ //Recherche dans toute les touches
        if(key[i]){                //Si une touche est pressée,
            return conversion_azerty(i);  //renvoie la valeur de la touche convertie en azerty
        }
    }                              //Sinon;
    return 0;                      //renvoie 0
}

//Fonction qui fait la conversion QWERTY -> AZERTY d'après les lettres renvoyées par allegro
int conversion_azerty(int touche){
    switch(touche){ //On vérifie la touche pressée, et si elle correspond aux touches à convertir -> conversion
        case KEY_A: touche = KEY_Q; break;   //En allegro, appuie sur A -> renvoie Q. On fait donc Q -> A
        case KEY_Q: touche = KEY_A; break;   //En allegro, appuie sur Q -> renvoie A. On fait donc A -> Q
        case KEY_W: touche = KEY_Z; break;   //En allegro, appuie sur W -> renvoie Z. On fait donc Z -> W
        case KEY_Z: touche = KEY_W; break;   //En allegro, appuie sur Z -> renvoie W. On fait donc W -> Z
        case KEY_M: touche = KEY_COMMA;break;//En allegro, appuie sur ',' -> renvoie m. On fait donc m -> ','
        case KEY_SEMICOLON: touche = KEY_M;  //En allegro, appuie sur m -> renvoie KEY_SEMICOLON. on fait donc la conversion
    }
    return touche; //On renvoie ensuite la touche convertie
}
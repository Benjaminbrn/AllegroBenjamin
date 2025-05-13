//Inclusion Bibliothèque / .H
#include "musique.h"
#include <stdio.h>

//Fonction pour intialiser musique
SAMPLE* initialiser_musique(const char* chemin){
    SAMPLE* son = load_sample(chemin); //Initialisation du morceau
    if (son != NULL) { //Si le son est initialisé ...
        return son;  //On le retourne
    }
    printf("Impossible de charger le son : %s\n", chemin); //Sinon on affiche un message d'erreur
    allegro_exit(); //Et on quitte allegro ...
    exit(EXIT_FAILURE);//Et enfin le programme
}

//Fonctions pour diminuer le son

//Fonctions pour augmenter le son

//Fonction pour couper la musique
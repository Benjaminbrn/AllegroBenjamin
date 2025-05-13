#ifndef PROJETJEU_MUSIQUE_H
#define PROJETJEU_MUSIQUE_H

//Inclusion Bibliothèque / .H nécessaires aux déclarations
#include <allegro.h>

//Déclaration constantes
#define pan 128 //Paranomique de la musique, ne change pas

//Definition Structure
typedef struct{         //Contient les paramètres de la musique
    SAMPLE* morceau;    //Musique jouée
    int volume;         //Volume de la musique jouée
}MUSIC;

//Déclaration sous programmes
SAMPLE* initialiser_musique(const char* chemin); //Initialise musique

#endif //PROJETJEU_MUSIQUE_H

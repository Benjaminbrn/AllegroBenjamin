//Inclusion Bibliothèque / .H
#include <allegro.h>
#include "../Code/fonctions_globales/affichage.h"
#include "../Code/fonctions_globales/musique.h"
#include "Menu.h"
#include "Initialisation_jeu.h"

//Code
int main(){
    //Initialise allegro
    allegro_init();

    //Initialise les périphérique
    install_keyboard();                                                     //Installe le clavier
    install_mouse();                                                        //Installe la souris
    install_timer();                                                        //Installe le timer
    install_joystick(JOY_TYPE_AUTODETECT);                             //Installe la manette
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, "");   //Installe le son

    //Initialise la résolution de l'écran
    set_color_depth(desktop_color_depth()); //Initialise les couleurs
    if((set_gfx_mode(GFX_AUTODETECT_WINDOWED,LARGEUR_ECRAN,HAUTEUR_ECRAN,0,0))!=0){ //Initialise le GFX
        allegro_message("Pb de mode graphique") ;
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    BITMAP *page = create_bitmap(SCREEN_W, SCREEN_H);  //Initialise la double buffer de la fenêtre

    //Initialise musique
    MUSIC musique = {NULL, 255}; //Met la music joué à NULL et le volume initiale à 255

    //Execute le jeu
    bool jouer = true; //On enregistre si le joueur veut jouer ou non
    do{                                          //On execute le programme ...
        jouer = MenuPrincipale(page, &musique);  //On enregistre le choix du joueur (s'il veut jouer ou quitter)
        if(jouer){                               //Si le joueur veut jouer ...
            lancer_jeu(page, &musique);    //On lance le jeu
        }
    }while(jouer != false);                      // ... jusqu'à ce que le joueur choisissent d'arrêter de jouer (quitter)

    //Fin de l'execution
    show_mouse(screen); //Réaffiche la souris dans l'écran (sinon crash quand on détruit double buffer)
    destroy_bitmap(page); //Supprime le double buffer
    allegro_exit(); //Quitte Allegro
    return 0;
}END_OF_MAIN()

void Brouillon(){

    //Bitmaps

    //Musique

    //Variables

    //Code
}
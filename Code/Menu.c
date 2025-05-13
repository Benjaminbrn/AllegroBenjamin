//Inclusion Bibliothèque / .H
#include "Menu.h"
#include "../Code/fonctions_globales/boutons.h"

//Constantes
    //Etat selection écran
#define Quitter 0
#define Parametres 1
#define Lancer_jeu 2
#define Ecran_titre 3
#define Selection_menus 4

    //Nombre bitmap
        //Nombre bitaps animations
const int nmb_bmp_ecran_titre = 1; //Nombre de bitmap de écran titre
const int nmb_bmp_curseur = 16;    //Nombre de bitmap de curseur
const int nmb_bmp_fond = 1;        //Nombre de bitmap du fond
        //taille tableau bitmap
const int nmb_element_statique = 5;//Nombre de bitmap statique (pas d'animation)
const int nmb_tab_bmp = 2;         //Nombre de tableau de bitmap (dynamique + statique)

    //Selection menus
const int nombre_cases = 3;   //Nombre de cases
const int case_y1[] = {600, 360, 120};//Coodonnées y1 respectivement des cases quitter, options, lancer le jeu
const int case_x = 400; //Coodonnées x1 des cases
const int case_h = 100, case_w = 560; //Respectivement hauteur et largeur des cases
const int position_curseur_y[] = {630, 390, 150}; //Position y du curseur pour chaque valeur de position_curseur : O->Quitter, 1->Parametres, 2->Lancer jeu
const int position_curseur_x = 335; //Coordonnées x1 du curseur

//Fonction qui gère les différents menues de l'écran d'accueil
bool MenuPrincipale(BITMAP* page, MUSIC* musique){
    //Bitmaps
        //Bitmaps Arrière-Plan
    BITMAP *fond = initialiser_bitmap("../Sprites/Menu/MenuPrincipale/fond_ecran.bmp");
        //Bitmaps Ecran titre
    BITMAP *ecran_titre = initialiser_bitmap("../Sprites/Menu/MenuPrincipale/ecran_titre.bmp");
        //Bitmaps Menu selection
    tab_bitmap curseur = initialiser_tableau_bitmap("../Sprites/Menu/MenuSelection/Curseur/curseur", nmb_bmp_curseur);
    BITMAP *case_jouer = initialiser_bitmap("../Sprites/Menu/MenuSelection/Case/casejouer.bmp");
    BITMAP *case_options = initialiser_bitmap("../Sprites/Menu/MenuSelection/Case/caseoptions.bmp");
    BITMAP *case_quitter = initialiser_bitmap("../Sprites/Menu/MenuSelection/Case/casequitter.bmp");
    BITMAP *cases[] = {case_quitter, case_options, case_jouer};
        //Bitmap paramètres

    //Musique
    musique->morceau = initialiser_musique("../Musique/menu.wav"); //Initialisation musique
    play_sample(musique->morceau, musique->volume, pan, 1000, true); //On joue le son

    //Variables
    int selection_ecran = Ecran_titre; //Correspond à l'écran actuel affiché
    bool bounce_menu = 1;    //Gère les rebonds dans les menues

    //Execution
    while(1){

        //Dessiner fond
        stretch_blit(fond, page,0,0, fond->w, fond->h, 0, 0, SCREEN_W, SCREEN_H); //Dessine l'arrière plan en premier ...

        //Fonction Menu (Gérer input + affichage des menus)
        if(selection_ecran == Ecran_titre){
            selection_ecran = ecranTitre(page, ecran_titre, &bounce_menu);       // Renvoie l'écran sélectionné selon choix à écran titre
        }else if(selection_ecran == Selection_menus){
            selection_ecran = ecranSelection(page, &curseur, cases, &bounce_menu);// Renvoie l'écran sélectionné selon choix à menu selection
        }else if(selection_ecran == Parametres) {
            //Fonction pour mettre paramètres
        }else{// 'Quitter' ou 'Lancer jeu'
            //Destruction des bitmaps
                //Liste des bitmaps statiques (afin de ne pas les confondre lors de la destruction des bitmaps)
            BITMAP* statique[] = {ecran_titre, fond,case_jouer, case_quitter, case_options};
                //Liste des bitmaps (afin les supprimer facilement)
            tab_bitmap liste[] = {{statique, nmb_element_statique}, curseur};
            destruction_bitmaps(liste, nmb_tab_bmp, true); //Destruction de toutes les bitmaps

            //Destruction de la musique et des sound effect
            destroy_sample(musique->morceau);

            //Fin menu et redirection
            return selection_ecran; // 'Quitter' -> Arrêt programme, 'Jouer' -> Quitte menu et lance jeu
        }

        //Affichage
        vsync(); // Bloque à 60 FPS
        afficherJeu(page); //Affiche le jeu
    }
}

//Fonction qui affiche et gère les imputs à l'écran titre
int ecranTitre(BITMAP* page, BITMAP* ecran_titre, bool* bounce_menu){
    //Code
    //Changer selection_ecran
     if(bounce(touche_pressee()||mouse_b, bounce_menu)){ //Si un bouton ou la souris est activé sans rebond
        if(key[KEY_ESC]){ //Si echap est pressé,
            return Quitter;     //On arrête le programme
        }
        return Selection_menus; //Sinon on passe au menu de selection
    }

    //Afficher bitmaps
    draw_sprite(page, ecran_titre, 0, 0);

    return Ecran_titre; //On renvoie l'écran titre sinon
}

//Fonction qui affiche et gère les imputs à l'écran de selection
int ecranSelection(BITMAP* page, tab_bitmap* curseur,  BITMAP* cases[], bool* bounce_menu){

    //Variables
    int choix = Selection_menus; //Par défaut , on reste sur écran selection
        //Curseur
    static int case_curseur = Lancer_jeu; //Représente la case sur laquelle est posé le curseur
    static bool bounce_fleches = true;  //Position des flèches haut et bas
    static bool bounce_souris = true;   //Bounce pour que le joueur puisse choisir de contrôler avec la souris ou le clavier

    //Code
         //Selection case avec flèches :
    if(bounce(key[KEY_DOWN]||key[KEY_UP], &bounce_fleches)) { //On vérifie avec un bounce si les flèches haut ou bas sont pressées
        if (key[KEY_UP]) {                                    //Si c'est haut ...
            case_curseur = (case_curseur + 1) % nombre_cases; //On passe à la case du haut (modulo nombre de cases pour ne pas dépasser)
        }else{                                                //Sinon si c'est bas
            case_curseur -= 1;                                //On passe à la case du bas
            if (case_curseur == -1) {                         //Si on dépasse la dernière case ...
                case_curseur = Lancer_jeu;                    //On revient à la case du haut
            }
        }
    }else{//Selection case avec souris :
        int case_touchee = case_souris(); //On vérifie la case touché avec case_souris qui renvoie la case ou -1 si aucune case
        if(bounce(case_touchee>-1, &bounce_souris)){ //On vérifie qu'une case soit touché (soit que case_touchée > -1) ...
            case_curseur = case_touchee;    //Et on met le curseur à la case touché.
        }
    }

        //Attribuer choix
    //On vérifie : si esc touché -> quitter; si (souris cliqué | espace | entrée) -> selection menu. Avec un seul bounce
    if(bounce(mouse_b & 1||key[KEY_ESC]||key[KEY_SPACE]||key[KEY_ENTER], bounce_menu)){
        if(key[KEY_ESC]){        //Si touche esc touchée ...
            choix = Ecran_titre; //Retour à l'écran titre
        }else{                   //Sinon ...
            choix = case_curseur;//On renvoie le choix de l'utilisateur
        }
    }

    //Affichage
    for(int i =0; i<nombre_cases; i++){  //On affiche toutes les cases
        draw_sprite(page, cases[i], case_x, case_y1[i]); //aux différentes coordonnées des cases
    }
    animation(page, curseur, position_curseur_x, position_curseur_y[case_curseur]); //Anime le curseur et le place en fonction de position Curseur

    return choix; //On retourne le choix
}

//Fonction qui renvoie la case touché par la souris ou -1 si aucune case n'est touchée
int case_souris(){
    if(mouse_x > case_x && mouse_x < case_x + case_w){ //On vérifie que les position x de la souris correspondent à celles des cases ...
        for(int i = Quitter; i<nombre_cases; i++){     //On vérifie chaque position y des cases ...
            if(mouse_y > case_y1[i] && mouse_y < case_y1[i] + case_h){ //Pour voir si elle correspond à celle de la souris
                return i; //Si c'est le cas on retourne la case touchée
            }
        }
    }
    return -1; //Sinon on renvoie -1 pour spécifier qu'aucune case n'a été touchée
}
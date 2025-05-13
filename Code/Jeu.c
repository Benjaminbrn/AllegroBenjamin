//Inclusion Bibliothèque / .H
#include "Jeu.h"
#include "../Code/fonctions_acteurs/Map.h"
#include <time.h>
#include "fonctions_acteurs/Collisions.h"
#include "../Code/fonctions_acteurs/Collisions.h"
#include "fonctions_acteurs/Vie.h"

//Fonction qui execute la boucle de jeu avec les différents acteurs
void jeu(BITMAP* page, t_joueur* j, data_ennemi * data_e, liste_projectile* liste_p, MUSIC* musique, t_map* map){
    TOUCHES touches = {0};
    play_sample(musique->morceau, musique->volume, pan, 1000, true);
    bool pause = false;
    srand(time(NULL));

    int temp = 0;
    while(!bounce(key[KEY_ESC], &touches.bounceESC)){
        if(pause == false) {
            //Actions
            action_joueur(j, liste_p, &pause, &touches);

            //Evenements
            //Création ennemies
            temp = (temp + 1) % 150;
            if (temp == 0) {
                creer_ennemi(&data_e->liste, *data_e->tab.ennemi);
            }
            //Tirs ennemis
            for (noeud_e *noeudE = data_e->liste.debut; noeudE != NULL; noeudE = noeudE->next) {
                if (rand() % 100 == 0) {
                    creer_projectile(liste_p, 0, noeudE->enn.mouv);
                }
            }
            // Perte de vie et destruction ennemis
            for (noeud_e *noeudE = data_e->liste.debut, *next; noeudE != NULL; noeudE = next) {
                {
                    next = noeudE->next;
                    // Si les ennemis sortent de l'écran (par la gauche)
                    if (noeudE->enn.mouv.x <= 0) {
                        detruire_ennemie(&data_e->liste, noeudE);
                    }
                    // S'ils entrent en collision avec un projectile allié
                    if (collision_projectiles(noeudE->enn.hitbox, liste_p, 0)) {
                        degats_sur_ennemi(&data_e->liste, noeudE, j->prop.degat);
                    }
                }
            }
                //Destruction projectile
            for (noeud_p *noeudP = liste_p->debut, *next; noeudP != NULL; noeudP = next) {
                next = noeudP->next;
                if (noeudP->proj.mouv.x >= SCREEN_W ||
                    noeudP->proj.mouv.x <= 0) { // Si le projectile sort de l'écran (d'un côté ou de l'autre)
                    detruire_projectile(liste_p, noeudP);
                }
            }

                //Actualisation
            mouvement_acteurs(j, &data_e->liste, liste_p);

            //Affichage
            vsync();
            // Dessiner d'abord le fond (map)
            actualiser_scrolling(map);
            dessiner_map(map, page);

            // Dessiner ensuite tous les sprites du jeu
            for (noeud_p *noeudP = liste_p->debut;
                 noeudP != NULL; noeudP = noeudP->next) { //On dessine les projectiles
                animation(page, &noeudP->proj.sprite, noeudP->proj.mouv.x, noeudP->proj.mouv.y);
            }
            for (noeud_e *noeudE = data_e->liste.debut;
                 noeudE != NULL; noeudE = noeudE->next) { //On dessine les ennemis
                animation(page, &noeudE->enn.sprite, noeudE->enn.mouv.x, noeudE->enn.mouv.y);
            }
            animation(page, &j->sprite, j->mouv.x,
                      j->mouv.y); // Dessiner le joueur en dernier pour qu'il soit au-dessus

            // Afficher le tout
            afficherJeu(page);
        }else{
            action_pause(&pause, &touches.bounceP);
        }
    }
}

//Fonction qui effectue le déplacement de tout les acteurs du jeu
void mouvement_acteurs(t_joueur* j, liste_ennemi *liste_e, liste_projectile* liste_p) {
    {
        mouvement(&j->mouv, &j->hitbox);              //Dépacement du joueur
        for (noeud_e *noeudE = liste_e->debut;
             noeudE != NULL; noeudE = noeudE->next) { //Pour chaque ennemi dans la liste chaînée ...
            mouvement(&noeudE->enn.mouv, &noeudE->enn.hitbox); //Déplacement de l'ennemi
        }
        for (noeud_p *noeudE = liste_p->debut;
             noeudE != NULL; noeudE = noeudE->next) { //Pour chaque projectile dans la liste chaînée ...
            mouvement(&noeudE->proj.mouv, &noeudE->proj.hitbox);//Déplacement du projectile
        }
        //Detection collisions
    }

}
//Fonction qui effectue le deplacement d'un objet selon son vecteur déplacement et actualise sa hitbox
void mouvement(t_mouv* mouv, t_hitbox* hb) {
    int mouv_x = mouv->vitesse * (mouv->dx);
    int mouv_y = mouv->vitesse * (mouv->dy);
    mouv->x += mouv_x; //Déplace l'objet en x selon sa vitesse et dx
    mouv->y += mouv_y; //Déplace l'objet en y selon sa vitesse et dy
    // On actualise la position de la hitbox de l'objet
    hb->x1 += mouv_x;
    hb->y1 += mouv_y;
}
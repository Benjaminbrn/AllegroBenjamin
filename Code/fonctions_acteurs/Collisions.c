#include <stdbool.h>
#include "Collisions.h"
#include "../Initialisation_jeu.h"
#include "Map.h"
#include "Projectile.h"

/// Fonction testant la collision entre 2 acteurs grâce à leurs hitboxs respectives
bool test_collision_acteurs(t_hitbox hb1, t_hitbox hb2) {
    if ((hb1.x1)<=(hb2.x1)+(hb2.w) && (hb2.x1)<=(hb1.x1)+(hb1.w) && (hb1.y1)<=(hb2.y1)+(hb2.h) && (hb2.y1)<=(hb1.y1)+(hb1.h)) { // Test de collision entre les 2 acteurs
        return true; // Acteurs en collision
    }
    // Sinon :
    return false; // Acteurs pas en collision
}

/// Fonction testant la collision avec le décor grâce à la hitbox de l'acteur ainsi que le décor (grâce à la bitmap des obstacles du décor et la position de l'écran réel dans le décor (avec decor.mouv.x et decor.mouv.y))
bool test_collision_acteur_decor(t_hitbox hb_acteur, t_map decor) {
    // On définit la couleur des obstacles de la carte des obstacles
    int couleur_obstacles = makecol(255, 255, 255); // Les obstacles sont en blanc dans la bitmap des obstacles
    // On teste si couleur_obstacle est touchée sur l'ensemble du contour de la hitbox de l'acteur
    // Bords gauches et droits
    for (int y=0; y<(hb_acteur.h); y++) {
        if ((getpixel(decor.Hitbox, decor.mouv.x+(hb_acteur.x1), decor.mouv.y+(hb_acteur.y1)+y) == couleur_obstacles)||(getpixel(decor.Hitbox, decor.mouv.x+(hb_acteur.x1)+(hb_acteur.w), decor.mouv.y+(hb_acteur.y1)+y) == couleur_obstacles)) {
            return true;
        }
    }
    // Bords hauts et bas
    for (int x=0; x<(hb_acteur.w); x++){
        if ((getpixel(decor.Hitbox, decor.mouv.x+(hb_acteur.x1)+x, decor.mouv.y+(hb_acteur.y1)) == couleur_obstacles)|| (getpixel(decor.Hitbox, decor.mouv.x+(hb_acteur.x1)+x, decor.mouv.y+(hb_acteur.y1)+(hb_acteur.h)) == couleur_obstacles)) {
            return true;
        }
    }
    // Sinon :
    return false;
}

/// Fonction qui teste si un objet est entré en collision avec un projectile qui n'est pas de son camp, détruit le projectile le cas échéant, et retourne un booléen répondant à la question
bool collision_projectiles(t_hitbox hb_objet, liste_projectile * liste_p, bool alliee){ // bool alliee : le camp de l'objet (1 = allié et 0 = ennemi)
    for(noeud_p* noeudP = liste_p->debut; noeudP != NULL; noeudP = noeudP->next){
        if(test_collision_acteurs(hb_objet, noeudP->proj.hitbox)){
            if(noeudP->proj.tir_alliee != alliee){
                detruire_projectile(liste_p, noeudP);
                return true;
            }
        }
    }
    return false;
}
#include "Ennemi.h"

/// Fonction appliquant des dégâts sur un ennemi (perte de pv ou de vie)
void degats_sur_ennemi(liste_ennemi* liste_e, noeud_e* noeudE, int nombre_degats) {
    if (noeudE->enn.prop.pv > nombre_degats) { // S'il a strictement plus de pv que les dégats qu'on lui inflige
        noeudE->enn.prop.pv -= nombre_degats;
    } else { // S'il a moins de pv que les dégats qu'on lui inflige
        if (noeudE->enn.prop.vie > 1) { // S'il a encore des vies de rechange (il lui reste plus d'une vie)
            noeudE->enn.prop.pv = noeudE->enn.prop.pv_initial; // On réinitialise ses pv
            noeudE->enn.prop.vie -= 1; // Il perd une vie
        } else { // S'il n'a plus de vie de rechange (il ne lui reste qu'une vie)
            detruire_ennemie(liste_e, noeudE);
        }
    }
}
#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <stdbool.h>
#include "Map.h"
#include "Projectile.h"
#include "../Initialisation_jeu.h"

bool test_collision_acteurs(t_hitbox hb1, t_hitbox hb2);
bool test_collision_acteur_decor(t_hitbox hb_acteur, t_map decor);
bool collision_projectiles(t_hitbox hb_objet, liste_projectile * liste_p, bool alliee);

#endif //COLLISIONS_H
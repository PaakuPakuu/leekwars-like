#ifndef COMMANDES_H
#define COMMANDES_H

#include "jeu.h"
#include "strats.h"

void show(Jeu *jeu);
void show_vars(Jeu *jeu, Tableaux* tableaux, char *arg);
void show_var_i(Jeu *jeu, Tableaux* tableaux, char *arg, int i);
int exit_game(Jeu *jeu);
void fight(Jeu *jeu, int v, int s1, int f, int s2);
void equip(Jeu* jeu, int arme, int protect, int soin);
void move(Jeu *jeu, char *dir, int n);
void use_weapon(Jeu *jeu, int n);
void use_protection(Jeu *jeu);
void use_care(Jeu *jeu, int n);
void add_action(Jeu *jeu, int n);
void end(Jeu *jeu);

#endif

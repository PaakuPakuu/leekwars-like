#ifndef PROMPT_H
#define PROMPT_H

#include "jeu.h"
#include "strats.h"

#define _POSIX_C_SOURCE 200809L

#define L_CMD 7
#define NB_CMD 9
#define NB_ARGS 6

/*char *ma_commande[L_CMD];*/

typedef enum {SHOW, FIGHT, EQUIP, MOVE, USE, ADD, END, EXIT, ERROR} Commande;

void affichePrompt(Jeu* jeu, Tableaux* tableaux, char** ma_commande);
Commande strToCmd(char **ma_commande);
void prompt(Commande cmd, Jeu* jeu, Tableaux* tableaux, char** ma_commande);

#endif

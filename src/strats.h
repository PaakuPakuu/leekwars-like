#ifndef STRATS_H
#define STRATS_H

#include "jeu.h"

#define TAILLE 256
#define ESP " \n,/\t"
#define NB_MOTS_C 18
#define NB_MOTS_C_C 6
#define NB_MOTS_C_P 4

#define Maj(c) (('A' <= c && 'Z' >= c)? c : (c-'a'+'A'))

#define NB_STRATS 5

typedef struct {
  char *nom;
  char *filename;
  char **tab;
  Equipement *equip;
  int cout;
} Strat;

typedef struct {
    Strat** mes_strats;
    int nb_strats;
    char** listesNomsStrats;
    char** motcles;
    char** motclescomp;
    char** motclesprompt;
} Tableaux;

void replace(char *src, char c, char newc);
char **lireFile(char *filename);
int estNombre(char *tmp, int fin);
int verifCommande(char **tmp, Tableaux* tableaux);
int verifIf(char **tmp, Tableaux* tableaux);
int verifChoose(char **tmp, Tableaux* tableaux);
int verifSyntaxe(char** tmp, Tableaux* tableaux);
void prompt_exec(Jeu* jeu, Tableaux* tableaux, char** machaine, int j, char** ma_commande);
char** exec_condition(Jeu* jeu, Tableaux* tableaux, char **machaine, char** ma_commande);
char** exec_else(char **machaine, Tableaux* tableaux);
char **execif(Jeu *jeu, Tableaux* tableaux, char **machaine, char** ma_commande);
void exec(Jeu* jeu, Tableaux* tableaux, Strat* mastrat, char** ma_commande);
Strat *creerStrat(char *nom, char *filename, char **tab);
void creerListeStrats(Tableaux* tableaux, char **listenoms);
Arme *findWeapon(Jeu *jeu,char *nom);
Protection *findProtec(Jeu *jeu, char *nom);
Soin *findHeal(Jeu *jeu,char *nom);
void equipementStrats(Jeu *jeu, Tableaux* tableaux);
void printAllStrats(Tableaux* tableaux);
void printStrat(Tableaux* tableaux, int i);
void remplirTab(Tableaux* tableau);
void free_strats(Tableaux** tableau);
Tableaux* initStrats(Jeu *jeu);

#endif

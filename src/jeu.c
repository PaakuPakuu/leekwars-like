#include "equipement.h"
#include "jeu.h"
#include "prompt.h"
#include "affichage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Initialise une instance de la structure Champion.
 *  Args :
 *      char* variete : nom du légume ou du fruit.
 *      Type type : type (légume ou fruit).
 *      int force
 *      int resist
 *      int pv_max
 *      int ce : crédits d'équipement.
 *  Return :
 *      Champion* : instance de Champion.
 */
Champion* initChamp(char* variete, Type type, int force, int resist, int pv_max, int ce)
{
    Champion* champ = (Champion*)malloc(sizeof(Champion));

    champ->variete = (char*)calloc(strlen(variete) + 1, sizeof(char));
    strcpy(champ->variete, variete);

    champ->type = type;
    champ->force = force;
    champ->resist = resist;
    champ->pv_max = pv_max;
    champ->pv = pv_max;
    champ->ce = ce;

    return champ;
}

/** Initialise une instance de la structure Joueur.
 *  Args :
 *      int ce_start : crédut d'équipement au début du jeu.
 *      int c_max : crédit d'équipement/action maximum.
 *      int pos : position initiale.
 *  Return :
 *      Joueur* : instance de Joueur.
 */
Joueur* initJoueur(int ce_start, int c_max, int pos)
{
    Joueur* joueur = (Joueur*)malloc(sizeof(Joueur));
    joueur->ce = ce_start;
    joueur->ce_used = 0;
    joueur->ce_max = c_max;
    joueur->ca_init = c_max;
    joueur->ca_max = c_max;
    joueur->ca = c_max;
    joueur->champ = NULL;
    joueur->equip = NULL;
    joueur->pos_init = pos;
    joueur->pos = pos;
    joueur->bouclier = 0;
    joueur->id_strat = -1;

    return joueur;
}

/** Initialise une instance de la structure Jeu.
 *  Args :
 *      int ce_start : crédut d'équipement au début du jeu.
 *      int c_max : crédit d'équipement/action maximum.
 *  Return :
 *      Jeu* : instance de Jeu.
 */
Jeu* initJeu(int ce_start, int c_max)
{
    Jeu* jeu = (Jeu*)malloc(sizeof(Jeu));

    jeu->legume = initJoueur(ce_start, c_max, 4);
    jeu->fruit = initJoueur(ce_start, c_max, TERRAIN_WIDTH - 4);
    jeu->courant = jeu->legume;

    jeu->message = (char*)calloc(L_MESSAGE, sizeof(char));
    jeu->texte = (char*)calloc(L_TEXT, sizeof(char));
    strcpy(jeu->texte, SHOW_START);

    jeu->champs = initChamps();
    jeu->armes = initArmes();
    jeu->protects = initProtections();
    jeu->soins = initSoins();

    jeu->combat = 0;
    jeu->equiping = 0;
    jeu->fin = 0;

    return jeu;
}

/* Initialisation en brut */

/** Initialise tous les champions.
 *  Args : None.
 *  Return :
 *      Champion** : liste des champions.
 */
Champion** initChamps()
{
    Champion **champs = (Champion**)malloc(sizeof(Champion*) * NB_CHAMPS);

    champs[0] = initChamp("Haricot", LEGUME, 10, 10, 40, 5);
    champs[1] = initChamp("Fenouil", LEGUME, 12, 15, 40, 7);
    champs[2] = initChamp("Poireau", LEGUME, 15, 20, 60, 10);
    champs[3] = initChamp("Aubergine", LEGUME, 20, 20, 60, 15);
    champs[4] = initChamp("Courgette", LEGUME, 20, 25, 80, 20);
    champs[5] = initChamp("Carotte", LEGUME, 25, 25, 80, 25);

    champs[6] = initChamp("Banane", FRUIT, 10, 10, 40, 5);
    champs[7] = initChamp("Kiwi", FRUIT, 12, 15, 40, 7);
    champs[8] = initChamp("Poire", FRUIT, 15, 20, 60, 10);
    champs[9] = initChamp("Pomme", FRUIT, 20, 20, 60, 15);
    champs[10] = initChamp("Ananas", FRUIT, 20, 25, 80, 20);
    champs[11] = initChamp("Durian", FRUIT, 25, 25, 80, 25);

    return champs;
}

/* Free de la mémoire */

/** Libère la mémoire utilisée par une instance de Joueur.
 *  Args :
 *      Joueur** joueur : adresse de l'instance.
 *  Return :
 *      None.
 */
void freeJoueur(Joueur** joueur)
{
    if ((*joueur)->equip != NULL) free((*joueur)->equip);
    free(*joueur);
}

/** Libère la mémoire utilisée par une liste d'instances de Champion.
 *  Args :
 *      Champion*** champs : adresse de la liste.
 *  Return :
 *      None.
 */
void freeChamps(Champion*** champs)
{
    int i;
    for (i = 0; i < NB_CHAMPS; i++) {
        free((*champs)[i]->variete);
        free((*champs)[i]);
    }
    free(*champs);
}

/** Libère la mémoire utilisée par une instance de Jeu.
 *  Args :
 *      Jeu** jeu : adresse de l'instance.
 *  Return :
 *      None.
 */
void freeJeu(Jeu** jeu)
{
    free((*jeu)->texte);
    free((*jeu)->message);

    freeJoueur(&(*jeu)->legume);
    freeJoueur(&(*jeu)->fruit);

    freeChamps(&(*jeu)->champs);
    freeArmes(&(*jeu)->armes);
    freeProtections(&(*jeu)->protects);
    freeSoins(&(*jeu)->soins);

    free(*jeu);
}

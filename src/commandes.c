#include "commandes.h"
#include "affichage.h"
#include "strats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/** Permet d'afficher les détails du joueur courant
  * Args :
  *   Jeu *jeu : instance du Jeu
  * Return:
  *   NONE
  */
void show(Jeu *jeu)
{
    if (jeu->combat) {
        Joueur *j = jeu->courant;
        sprintf(jeu->texte,
                        "\t--- %s ---\n"
                        "CE : %d/%d\n"
                        "Arme : %s\n"
                        "Protection : %s\n"
                        "Soin : %s\n"
                        "PV : %d/%d\n"
                        "Position : %d\n"
                        "\t-------------\n",
                        j->champ->variete,
                        j->ca_init - j->ce_used, j->ca_init,
                        j->equip->arme->nom,
                        j->equip->protect->nom,
                        j->equip->soin->nom,
                        j->champ->pv, j->champ->pv_max, j->pos);
        if (BETA_TESTING) printf(BOLD "\nOUT :" NORMAL " \n%s\n", jeu->texte);
        sprintf(jeu->message, "Voici en haut les détails du %s.", j->champ->variete);
    } else
        sprintf(jeu->message, NOT_FIGHTING);
}

/** Permet d'afficher les détails d'un certain camp
  * Args :
  *   Jeu *jeu : instance du Jeu
  *   char *arg : nom du camp
  * Return:
  *   NONE
  */
void show_vars(Jeu *jeu, Tableaux* tableaux, char *arg)
{
    int i;
    char* temp = (char*)calloc(100, sizeof(char));

    *(jeu->texte) = '\0';
    if(strcmp(arg, "vegetables") == 0) {
        strcat(jeu->texte, "\t--- Légumes ---\n");
        for (i = 0; i < NB_CHAMPS / 2; i++) {
            sprintf(temp, "%d -- %s\n", i, jeu->champs[i]->variete);
            strcat(jeu->texte, temp);
        }
        strcat(jeu->texte, "\t---------------\n");
    }
    else if (strcmp(arg, "fruits") == 0){
        strcat(jeu->texte, "\t--- Fruits ---\n");
        for (i = NB_CHAMPS / 2; i < NB_CHAMPS ; i++) {
            sprintf(temp, "%d -- %s\n", i, jeu->champs[i]->variete);
            strcat(jeu->texte, temp);
        }
        strcat(jeu->texte, "\t--------------\n");
    }
    else if (strcmp(arg, "weapons") == 0) {
        strcat(jeu->texte, "\t--- Weapons ---\n");
        for (i = 0; i < NB_ARMES; i++) {
            sprintf(temp, "%d -- %s\n", i, jeu->armes[i]->nom);
            strcat(jeu->texte, temp);
        }
        strcat(jeu->texte, "\t----------------\n");
    }
    else if (strcmp(arg, "protections") == 0) {
        strcat(jeu->texte, "\t--- Protections ---\n");
        for (i = 0; i < NB_PROTECTS; i++) {
            sprintf(temp, "%d -- %s\n", i, jeu->protects[i]->nom);
            strcat(jeu->texte, temp);
        }
        strcat(jeu->texte, "\t-------------------\n");
    }
    else if (strcmp(arg, "cares") == 0) {
        strcat(jeu->texte, "\t--- Soins ---\n");
        for (i = 0; i < NB_SOINS; i++) {
            sprintf(temp, "%d -- %s\n", i, jeu->soins[i]->nom);
            strcat(jeu->texte, temp);
        }
        strcat(jeu->texte, "\t-------------\n");
    } else if (strcmp(arg, "strategies") == 0) {
        strcat(jeu->texte, "\t--- Stratégies ---\n");
        for(i = 0; i < tableaux->nb_strats; i++) {
            sprintf(temp, "/ %d / %s\n", i, tableaux->mes_strats[i]->nom);
            strcat(jeu->texte, temp);
        }
        strcat(jeu->texte, "\t------------------\n");
    }

    if (BETA_TESTING) printf(BOLD "\nOUT :" NORMAL " \n%s\n", jeu->texte);
    sprintf(jeu->message, "Voici en haut tous les %s.", arg);

    free(temp);
}

/** Permet d'afficher les détails d'un champion i
  * Args :
  *   Jeu *jeu : intance du Jeu
  *   char *arg : nom du camp
  *   int i : numéro du champion
  * Return:
  *   NONE
  */
void show_var_i(Jeu *jeu, Tableaux* tableaux, char *arg, int i)
{
    if (strcmp(arg, "vegetable") == 0 && i >= 0 && i < NB_CHAMPS / 2) {
        Champion* c = jeu->champs[i];
        sprintf(jeu->texte,
                        "\t%d -- %s\n"
                        "Force : %d\n"
                        "Resistance : %d\n"
                        "PV : %d\n"
                        "Crédit d'équip. : %d\n"
                        "\t-----\n",
                        i, c->variete, c->force, c->resist, c->pv_max, c->ce);
        if (BETA_TESTING) printf(BOLD "\nOUT :" NORMAL " \n%s\n", jeu->texte);
        sprintf(jeu->message, "Voici en haut les caractéristique du Champion n°%d.", i);
    }
    else if (strcmp(arg, "fruit") == 0 && i >= NB_CHAMPS / 2 && i < NB_CHAMPS) {
        Champion* c = jeu->champs[i];
        sprintf(jeu->texte,
                        "\t%d -- %s\n"
                        "Force : %d\n"
                        "Resistance : %d\n"
                        "PV : %d\n"
                        "Crédit d'équip. : %d\n"
                        "\t-----\n",
                        i, c->variete, c->force, c->resist, c->pv_max, c->ce);
        if (BETA_TESTING) printf(BOLD "\nOUT :" NORMAL " \n%s\n", jeu->texte);
        sprintf(jeu->message, "Voici en haut les caractéristique du Champion n°%d.", i);
    }
    else if (strcmp(arg, "weapon") == 0 && i >= 0 && i < NB_ARMES) {
        Arme* a = jeu->armes[i];
        sprintf(jeu->texte,
                        "\t%d -- %s\n"
                        "Crédit d'équip. : %d\n"
                        "Crédit d'action : %d\n"
                        "Dégâts : %d - %d\n"
                        "Portée : %d\n"
                        "\t-----\n",
                        i, a->nom, a->ce, a->ca, a->d_min, a->d_max, a->portee);
        if (BETA_TESTING) printf(BOLD "\nOUT :" NORMAL " \n%s\n", jeu->texte);
        sprintf(jeu->message, "Voici en haut les caractéristique de l'Arme n°%d.", i);
    }
    else if (strcmp(arg, "protection") == 0 && i >= 0 && i < NB_PROTECTS) {
        Protection* p = jeu->protects[i];
        sprintf(jeu->texte,
                        "\t%d -- %s\n"
                        "Crédit d'équip. : %d\n"
                        "Crédit d'action : %d\n"
                        "Probabilité : %d\n"
                        "\t-----\n",
                        i, p->nom, p->ce, p->ca, p->prob);
        if (BETA_TESTING) printf(BOLD "\nOUT :" NORMAL " \n%s\n", jeu->texte);
        sprintf(jeu->message, "Voici en haut les caractéristique de la Protection n°%d.", i);
    }
    else if (strcmp(arg, "care") == 0 && i >= 0 && i < NB_SOINS) {
        Soin* s = jeu->soins[i];
        sprintf(jeu->texte,
                        "\t%d -- %s\n"
                        "Crédit d'équip. : %d\n"
                        "Crédit d'action : %d\n"
                        "Volume : %d\n"
                        "PV rendus : %d - %d\n"
                        "\t-----\n",
                        i, s->nom, s->ce, s->ca, s->volume, s->hp_min, s->hp_max);
        if (BETA_TESTING) printf(BOLD "\nOUT :" NORMAL " \n%s\n", jeu->texte);
        sprintf(jeu->message, "Voici en haut les caractéristique du Soin n°%d.", i);
    }
    else if (strcmp(arg, "strategy") == 0 && i >= 0 && i < tableaux->nb_strats) {
        Strat* s = tableaux->mes_strats[i];
        sprintf(jeu->texte,
                        "\t--- %s ---\n"
                        "\tNom : %s\n"
                        "\tArme : %s\n"
                        "\tProtection : %s\n"
                        "\tSoin : %s\n"
                        "\tCout en Ce : %d\n"
                        "\t----%.*s----\n",
                        s->filename, s->nom, s->equip->arme->nom, s->equip->protect->nom, s->equip->soin->nom,
                        s->cout, (int)strlen(s->filename), "-----------------------------------------------");
        if (BETA_TESTING) printf(BOLD "\nOUT :" NORMAL " \n%s\n", jeu->texte);
        sprintf(jeu->message, "Voici en haut les détails de la Stratégie n°%d.", i);
    }
    else
        sprintf(jeu->message, MERROR "Cet identifiant n'existe pas.");
}

/** Permet de lancer le combat
  * Args :
  *   Jeu *jeu : intance du Jeu
  *   int v : numéro du champion légume
  *   int f : numéro du champion fruit
  * Return:
  *   NONE
  */
void fight(Jeu *jeu, int v, int s1, int f, int s2, int nb_strats)
{
    if (!jeu->combat) {
        if (v >= 0 && v < NB_CHAMPS / 2) {
            if (f >= NB_CHAMPS / 2 && f < NB_CHAMPS) {
                if (s1 >= -1 && s1 < nb_strats) {
                    if (s2 >= -1 && s2 < nb_strats) {
                        jeu->legume->champ = jeu->champs[v];
                        jeu->fruit->champ = jeu->champs[f];
                        jeu->equiping = 1;

                        jeu->legume->id_strat = s1;
                        jeu->fruit->id_strat = s2;

                        sprintf(jeu->message, BOLD "%s " NORMAL RED "< VERSUS >" NORMAL BOLD " %s" NORMAL,
                                jeu->champs[v]->variete, jeu->champs[f]->variete);
                    } else
                        sprintf(jeu->message, MERROR "Stratégie n°%d inexistante.", s2);
                } else
                    sprintf(jeu->message, MERROR "Stratégie n°%d inexistante.", s1);
            } else
                sprintf(jeu->message, MERROR "L'identifiant" BOLD " %d"
                        NORMAL " n'appartient à aucun " BOLD "Fruit." NORMAL, f);
        } else
            sprintf(jeu->message, MERROR "L'identifiant" BOLD " %d"
                    NORMAL " n'appartient à aucun " BOLD "Légume." NORMAL, v);
    } else
        sprintf(jeu->message, MERROR "Vous êtes déjà en combat.");
}

/** Permet d'équiper un champion
  * Args :
  *   Jeu *jeu : intance du Jeu
  *   int arme : numéro de l'arme
  *   int protect : numéro de la protection
  *   int soin : numéro du soin
  * Return:
  *   NONE
  */
void equip(Jeu* jeu, int arme, int protect, int soin)
{
    if (arme >= NB_ARMES)
        sprintf(jeu->message, MERROR "L'identifiant " BOLD "%d" NORMAL " n'appartient à aucune Arme.", arme);
    else if (protect >= NB_PROTECTS)
        sprintf(jeu->message, MERROR "L'identifiant " BOLD "%d" NORMAL " n'appartient à aucune Protection.", protect);
    else if (soin >= NB_SOINS)
        sprintf(jeu->message, MERROR "L'identifiant " BOLD "%d" NORMAL " n'appartient à aucun Soin.", soin);
    else {
        Arme* a = jeu->armes[arme];
        Protection* p = jeu->protects[protect];
        Soin* s = jeu->soins[soin];

        jeu->courant->equip = initEquipement(a, p, s);
        jeu->courant->ce_used = a->ce + p->ce + s->ce;

        if (jeu->equiping && jeu->courant == jeu->legume) {
            jeu->courant = jeu->fruit;
            sprintf(jeu->message, GREEN "Bien ! Au tour du fruit." NORMAL);
        } else {
            jeu->courant = jeu->legume;
            jeu->equiping = 0;
            jeu->combat = 1;

            sprintf(jeu->message, RED "Combat lancé ! " NORMAL BOLD "%s "
                    NORMAL RED "< VERSUS >" NORMAL BOLD " %s" NORMAL,
                    jeu->legume->champ->variete, jeu->fruit->champ->variete);
        }
    }
}

/** Permet de déplacer son champion
  * Args :
  *   Jeu *jeu : intance du Jeu
  *   char *dir : direction du déplacement
  *   int n : nombre de case
  * Return:
  *   NONE
  */
void move(Jeu *jeu, char *dir, int n) {
    if (jeu->legume == jeu->courant){
        if (strcmp(dir, "forward") == 0 && jeu->courant->ca - n >= 0 &&
                jeu->courant->pos + n < jeu->fruit->pos) {
            jeu->courant->ca -= n;
            jeu->courant->pos += n;
            sprintf(jeu->message, "Vous avez avancé de %d pas.", n);
        }
        else if (strcmp(dir, "backward") == 0 && jeu->courant->ca - (n * 2) >= 0 && jeu->courant->pos - n >= 0) {
            jeu->courant->ca = jeu->courant->ca - (n * 2);
            jeu->courant->pos -= n;
            sprintf(jeu->message, "Vous avez reculé de %d pas.", n);
        }
        else
            sprintf(jeu->message, MERROR "Déplacement impossible.");
    }
    else {
        if (strcmp(dir, "forward") == 0 && jeu->courant->ca - n >= 0 &&
                jeu->courant->pos - n > jeu->legume->pos) {
            jeu->courant->ca -= n;
            jeu->courant->pos -= n;
            sprintf(jeu->message, "Vous avez avancé de %d pas.", n);
        }
        else if (strcmp(dir, "backward") == 0 && jeu->courant->ca - (n * 2) >= 0 && jeu->courant->pos + n <= TERRAIN_WIDTH) {
            jeu->courant->ca = jeu->courant->ca - (n * 2);
            jeu->courant->pos += n;
            sprintf(jeu->message, "Vous avez reculé de %d pas.", n);
        }
        else
            sprintf(jeu->message, MERROR "Déplacement impossible.");
    }
}

/** Termine le combat et affecte les gains.
  * Args :
  *     Jeu* jeu : instance du Jeu
  * Return :
  *     NONE
  */
void termine_combat(Jeu* jeu)
{
    int diff = jeu->legume->ce_used - (jeu->courant == jeu->fruit ? jeu->fruit->ce_used : jeu->legume->ce_used);
    jeu->combat = 0;

    jeu->courant->ce += 5 * (diff > 1 ? diff : 1);

    jeu->legume->ce_used = 0;
    jeu->fruit->ce_used = 0;

    jeu->legume->champ->pv = jeu->legume->champ->pv_max;
    jeu->legume->pos = jeu->legume->pos_init;
    jeu->legume->ca_max = jeu->legume->ca_init;
    jeu->legume->ca = jeu->legume->ca_init;

    jeu->fruit->champ->pv = jeu->fruit->champ->pv_max;
    jeu->fruit->pos = jeu->fruit->pos_init;
    jeu->fruit->ca_max = jeu->fruit->ca_init;
    jeu->fruit->ca = jeu->fruit->ca_max;

    jeu->courant = jeu->legume;

    jeu->legume->champ = NULL;
    jeu->fruit->champ = NULL;

    *(jeu->texte) = '\0';
    strcpy(jeu->texte, SHOW_START);

    if (jeu->legume->id_strat == -1) free(jeu->legume->equip);
    if (jeu->fruit->id_strat == -1) free(jeu->fruit->equip);

    jeu->legume->equip = NULL;
    jeu->fruit->equip = NULL;

    jeu->legume->id_strat = -1;
    jeu->fruit->id_strat = -1;
}

/** Arrondi une nombre vers l'entier le plus proche.
 *  Args :
 *      float f : nombre à arrondir.
 *  Return :
 *      int : nombre arrondi.
 */
int arrondi(float f)
{
    float tmp = f + 0.5f;
    return ((int)f == (int)tmp ? f : f + 1);
}

/** Permet d'utiliser son arme
  * Args :
  *   Jeu *jeu : intance du Jeu
  *   int n : nombre de tirs
  * Return:
  *   NONE
  */
void use_weapon(Jeu *jeu, int n)
{
    int cout = n * jeu->courant->equip->arme->ca;
    int somme = 0, bloquages = 0;
    float random;

    srand(time(NULL));

    if (cout > jeu->courant->ca)
        sprintf(jeu->message, MERROR "Vous n'avez pas assez de" BOLD " crédit d'action" NORMAL);
    else {
        Joueur *adversaire;
        jeu->courant->ca -= cout;

        if (jeu->courant == jeu->fruit)
            adversaire = jeu->legume;
        else
            adversaire = jeu->fruit;

        if (jeu->courant->equip->arme->portee >= jeu->fruit->pos - jeu->legume->pos) {
            while (n > 0) {
                int blocked = (rand() % 100) + 1 <= adversaire->equip->protect->prob;
                if (adversaire->bouclier == 0 || (adversaire->bouclier == 1 && !blocked)) {
                    Arme* arme = jeu->courant->equip->arme;
                    int b = arme->d_min;
                    int a = arme->d_max + 1 - b;

                    random = rand() % a + b;
                    random *= (float)(100 + jeu->courant->champ->force) / 100;
                    random *= (float)(100 - adversaire->champ->resist) / 100;
                    somme += arrondi(random);
                } else
                    bloquages++;
                n--;
            }

            adversaire->champ->pv -= somme;
            sprintf(jeu->message, "Vous infligez %d ! Il a bloqué %d de vos attaques.", somme, bloquages);

            if (adversaire->champ->pv <= 0) {
                wait(jeu);
                sprintf(jeu->message, YELLOW "Le %s a remporté le combat contre le %s!" NORMAL,
                        jeu->courant->champ->variete, adversaire->champ->variete);
                wait(jeu);
                termine_combat(jeu);
                sprintf(jeu->message, "Prêt pour le prochain duel ?");
            }

        }
        else sprintf(jeu->message, "Oh non ! L'ennemi était trop loin !");
    }
}

/** Permet d'utiliser sa protection
  * Args :
  *   Jeu *jeu : intance du Jeu
  * Return:
  *   NONE
  */
void use_protection(Jeu *jeu)
{
    if (jeu->combat) {
        if (!jeu->courant->bouclier) {
            int cout = jeu->courant->equip->protect->ca;
            if (cout <= jeu->courant->ca) {
                jeu->courant->bouclier = 1;
                jeu->courant->ca -= cout;
                sprintf(jeu->message, CYAN "Vous venez d'enfiler votre Protection !" NORMAL);
            } else
                sprintf(jeu->message, NOT_ENOUGH_CA);
        } else
            sprintf(jeu->message, MERROR "Vous avez déjà enfilé votre Protection.");
    } else
        sprintf(jeu->message, NOT_FIGHTING);
}

/** Permet d'utiliser son soin
  * Args :
  *   Jeu *jeu : intance du Jeu
  *   int n : nombre d'utilisation
  * Return:
  *   NONE
  */
void use_care(Jeu *jeu, int n)
{
    if (jeu->combat) {
        int cout = n * jeu->courant->equip->soin->ca;
        int somme = 0, random;

        if (cout > jeu->courant->ca)
            sprintf(jeu->message, NOT_ENOUGH_CA);
        else{
            jeu->courant->ca -= cout;
            while (n > 0) {
                int a = jeu->courant->equip->soin->hp_max + 1 - jeu->courant->equip->soin->hp_min;
                int b = jeu->courant->equip->soin->hp_min;
                random = rand() % a + b;
                somme += random;
                n--;
            }
            jeu->courant->champ->pv += somme;

            if(jeu->courant->champ->pv > jeu->courant->champ->pv_max)
                jeu->courant->champ->pv = jeu->courant->champ->pv_max;

            sprintf(jeu->message, GREEN "Vous vous êtes soigné ! Vos PV sont maintenant a "
                    BOLD "%d" NORMAL, jeu->courant->champ->pv);
        }
    } else
        sprintf(jeu->message, NOT_FIGHTING);
}

void add_action(Jeu* jeu, int n)
{
    if (n > 0) {
        Joueur* j = jeu->courant;
        if (j->ce - n >= 0) {
            if (j->ce_used + n <= j->ce_max) {
                j->ce_used += n;
                j->ce -= n;
                j->ca_max += n;
                j->ca += n;
                sprintf(jeu->message, GREEN "Vous pouvez maintenant utiliser %dCA par tour." NORMAL, j->ca_max);
            } else
                sprintf(jeu->message, MERROR "Vous ne pouvez pas dépasser la limite des %d CE par duel.", j->ce_max);
        } else
            sprintf(jeu->message, NOT_ENOUGH_CE);
    } else
        sprintf(jeu->message, MERROR "Vous ne pouvez ajouter qu'un nombre de CA supérieur à 0.");
}

/** Permet de finir son tour
  * Args :
  *   Jeu *jeu : intance du Jeu
  * Return:
  *   NONE
  */
void end(Jeu *jeu) {
    if (jeu->combat == 1) {
        if (jeu->courant == jeu->fruit) {
            sprintf(jeu->message, "Fin du tour du " BOLD "Fruit" NORMAL);
            jeu->courant = jeu->legume;
            jeu->legume->bouclier = 0;
        } else {
            sprintf(jeu->message, "Fin du tour du " BOLD "Légume" NORMAL);
            jeu->courant = jeu->fruit;
            jeu->fruit->bouclier = 0;
        }
        jeu->courant->ca = jeu->courant->ca_max;
    } else
        sprintf(jeu->message, NOT_FIGHTING);
}

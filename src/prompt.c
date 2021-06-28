#include "prompt.h"
#include "jeu.h"
#include "commandes.h"
#include "affichage.h"
#include "strats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int is_number(const char *str)
{
    while (*str != '\0') {
        if (*str < '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}

/** Permet de lancer tous les cas de la commande show
  * Args :
  *   Jeu *jeu : instance du Jeu
  * Return:
  *   NONE
  */
void prompt_show(Jeu *jeu, Tableaux* tableaux, char** ma_commande) {
    if(ma_commande[1] == NULL && jeu->combat)
        show(jeu);
    else if(ma_commande[1] == NULL)
      sprintf(jeu->message, NOT_FIGHTING);
    else {
        int i, fin = 0;
        char *arg1[NB_ARGS] = {"vegetables", "fruits", "weapons", "protections", "cares", "strategies"};
        char *arg2[NB_ARGS] = {"vegetable", "fruit", "weapon", "protection", "care", "strategy"};

        for (i = 0; !fin && i < NB_ARGS; i++) {
            if (strcmp(ma_commande[1], arg1[i]) == 0) {
                if (ma_commande[2] == NULL)
                    show_vars(jeu, tableaux, ma_commande[1]);
                else
                    sprintf(jeu->message, TOO_MUCH_ARGS);
                fin = 1;
            }
        }

        for (i = 0; !fin && i < NB_ARGS; i++) {
            if (strcmp(ma_commande[1], arg2[i]) == 0) {
                if (ma_commande[2] == NULL)
                    show_var_i(jeu, tableaux, ma_commande[1], 0);
                else if ((!atoi(ma_commande[2]) && strcmp(ma_commande[2], "0") != 0) ||
                        atoi(ma_commande[2]) < 0 || ma_commande[3] != NULL)
                    sprintf(jeu->message, INVALID_CMD);
                else
                    show_var_i(jeu, tableaux, ma_commande[1], atoi(ma_commande[2]));
                fin = 1;
            }
        }

        if (!fin) sprintf(jeu->message, WRONG_FIRST_ARG);
    }
}

/** Permet de lancer tous les cas de la commande equip
  * Args :
  *   Jeu *jeu : instance du Jeu
  * Return:
  *   NONE
  */
void prompt_equip(Jeu* jeu, char** ma_commande)
{
    if (ma_commande[1] == NULL || ma_commande[2] == NULL || ma_commande[3] == NULL || ma_commande[4] != NULL)
        sprintf(jeu->message, MERROR "Vous devez entrer " BOLD "3" NORMAL " identifiants.");
    else {
        int a = atoi(ma_commande[1]);
        int p = atoi(ma_commande[2]);
        int s = atoi(ma_commande[3]);

        if ((a == 0 && strcmp(ma_commande[1], "0") != 0) || a < 0)
            sprintf(jeu->message, MERROR "Le premier identifiant est incorrect.");
        else if ((p == 0 && strcmp(ma_commande[2], "0") != 0) || p < 0)
            sprintf(jeu->message, MERROR "Le deuxième identifiant est incorrect.");
        else if ((s == 0 && strcmp(ma_commande[3], "0") != 0) || s < -1)
            sprintf(jeu->message, MERROR "Le troisième identifiant est incorrect.");
        else
            equip(jeu, a, p, s);
    }
}

/** Permet de lancer tous les cas de la commande fight
  * Args :
  *   Jeu *jeu : instance du Jeu
  * Return:
  *   NONE
  */
void prompt_fight(Jeu* jeu, char** ma_commande)
{
    int v, f, s1, s2;

    if (ma_commande[1] == NULL || ma_commande[2] == NULL)
        sprintf(jeu->message, ARGS_MISSING);
    else if (!is_number(ma_commande[1]))
        sprintf(jeu->message, POS_NUMBER_NEEDED " [v]");
    else {
        if (!is_number(ma_commande[2])) {
            if (strcmp(ma_commande[2], "versus") != 0)
                sprintf(jeu->message, MERROR "Le 2ème paramètre doit être un nombre ou \"versus\".");
            else {
                v = atoi(ma_commande[1]);

                if (ma_commande[3] == NULL) {
                    sprintf(jeu->message, ARGS_MISSING " [f]");
                } else if (!is_number(ma_commande[3]))
                    sprintf(jeu->message, POS_NUMBER_NEEDED " [f]");
                else if (ma_commande[4] == NULL) {
                    f = atoi(ma_commande[3]);
                    fight(jeu, v, -1, f, -1);
                } else if (!is_number(ma_commande[4]))
                    sprintf(jeu->message, POS_NUMBER_NEEDED " [s2]");
                else {
                    f = atoi(ma_commande[3]);
                    s2 = atoi(ma_commande[4]);
                    fight(jeu, v, -1, f, s2);
                }
            }
        } else {
            v = atoi(ma_commande[1]);
            s1 = atoi(ma_commande[2]);

            if (ma_commande[3] == NULL)
                sprintf(jeu->message, ARGS_MISSING);
            else if (!is_number(ma_commande[3]) && strcmp(ma_commande[3], "versus") != 0)
                sprintf(jeu->message, MERROR "Le 3ème paramètre doit être un nombre ou \"versus\".");
            else if (ma_commande[4] == NULL)
                sprintf(jeu->message, ARGS_MISSING " [v]");
            else if (!is_number(ma_commande[4]))
                sprintf(jeu->message, POS_NUMBER_NEEDED " [v]");
            else if (ma_commande[5] == NULL) {
                f = atoi(ma_commande[4]);
                fight(jeu, v, s1, f, -1);
            } else if (!is_number(ma_commande[5]))
                sprintf(jeu->message, POS_NUMBER_NEEDED " [s2]");
            else {
                f = atoi(ma_commande[4]);
                s2 = atoi(ma_commande[5]);
                fight(jeu, v, s1, f, s2);
            }
        }
    }
}

/** Permet de lancer tous les cas de la commande move
  * Args :
  *   Jeu *jeu : instance du Jeu
  * Return:
  *   NONE
  */
void prompt_move(Jeu* jeu, char** ma_commande) {
    if (ma_commande[1] == NULL)
        sprintf(jeu->message, ARGS_MISSING);
    else if (strcmp(ma_commande[1], "forward") == 0 || strcmp(ma_commande[1], "backward") == 0) {
        if (ma_commande[3] != NULL)
            sprintf(jeu->message, TOO_MUCH_ARGS);
        else if (ma_commande[2] == NULL)
            move(jeu, ma_commande[1], 1);
        else if ((!atoi(ma_commande[2]) && strcmp(ma_commande[2], "0") != 0) || atoi(ma_commande[2]) < 0)
            sprintf(jeu->message, POS_NUMBER_NEEDED);
        else
            move(jeu, ma_commande[1], atoi(ma_commande[2]));
    } else
        sprintf(jeu->message, WRONG_FIRST_ARG);
}

/** Permet de lancer tous les cas de la commande use
  * Args :
  *   Jeu *jeu : instance du Jeu
  * Return:
  *   NONE
  */
void prompt_use(Jeu* jeu, char** ma_commande) {
    if (ma_commande[1] != NULL) {
        if (strcmp(ma_commande[1], "weapon") == 0 || strcmp(ma_commande[1], "care") == 0) {
            if ((ma_commande[2] != NULL && !atoi(ma_commande[2]) && strcmp(ma_commande[2], "0") != 0) ||
                    (ma_commande[2] != NULL &&  atoi(ma_commande[2]) < 0) || ma_commande[3] != NULL) {
                sprintf(jeu->message, INVALID_CMD);
            }
            else if (ma_commande[2] == NULL){
                if(strcmp(ma_commande[1], "weapon") == 0)
                    use_weapon(jeu, 1);
                else
                    use_care(jeu, 1);
            }
            else{
                if(strcmp(ma_commande[1], "weapon") == 0)
                    use_weapon(jeu, atoi(ma_commande[2]));
                else
                    use_care(jeu, atoi(ma_commande[2]));
            }
        }
        else if (strcmp(ma_commande[1], "protection") == 0) {
            if (ma_commande[2] != NULL)
                sprintf(jeu->message, INVALID_CMD);
            else
                use_protection(jeu);
        } else
            sprintf(jeu->message, INVALID_CMD);
    } else
        sprintf(jeu->message, ARGS_MISSING);
}

void prompt_add(Jeu* jeu, char** ma_commande)
{
    if (ma_commande[1] != NULL) {
        if (ma_commande[3] == NULL) {
            if (strcmp(ma_commande[1], "action") == 0) {
                if (ma_commande[2] != NULL) {
                    if (is_number(ma_commande[2]))
                        add_action(jeu, atoi(ma_commande[2]));
                    else
                        sprintf(jeu->message, POS_NUMBER_NEEDED);
                } else
                    sprintf(jeu->message, ARGS_MISSING);
            } else
                sprintf(jeu->message, WRONG_FIRST_ARG);
        } else
            sprintf(jeu->message, TOO_MUCH_ARGS);
    } else
        sprintf(jeu->message, ARGS_MISSING);
}

/** Permet de lancer tous les cas de la commande end
  * Args :
  *   Jeu *jeu : instance du Jeu
  * Return:
  *   NONE
  */
void prompt_end(Jeu* jeu, char** ma_commande) {
    if (ma_commande[1] != NULL)
        sprintf(jeu->message, MERROR "Cette commande ne prend pas de paramètre.");
    else
        end(jeu);
}

/** Permet de transformer une chaine en commande
  * Args :
  *   NONE
  * Return:
  *   NONE
  */
Commande strToCmd(char** ma_commande) {
    int i;
    char *listecmd[NB_CMD] = {"show", "fight", "equip", "move", "use", "add", "end", "exit", "error"};

    for (i = 0; i < NB_CMD - 1; i++) {
        if (strcmp(listecmd[i], ma_commande[0]) == 0)
            return i;
    }

    return i;
}

/** Permet de vider le buffer de la chaine de carac qui reçoit la commande
  * Args :
  *   NONE
  * Return:
  *   NONE
  */
void vider_ma_commande(char** ma_commande)
{
    int i;
    for (i = 0; i < L_CMD; i++)
        ma_commande[i] = NULL;
}

/** Permet de choisir quelle fonction lancer selon l'entrée de l'utilisateur
  * Args :
  *   Commande cmd : Commande de l'utilisateur
  *   Jeu *jeu : instance du Jeu
  * Return:
  *   NONE
  */
void prompt(Commande cmd, Jeu* jeu, Tableaux* tableaux, char** ma_commande) {
    /*void (*funcs[])(Jeu*) = {prompt_show, prompt_fight, prompt_move, prompt_use, prompt_end};*/

    (jeu->message)[0] = '\0';
    switch (cmd) {
        case SHOW:
            prompt_show(jeu, tableaux, ma_commande);
            break;
        case FIGHT:
            if(!jeu->combat && !jeu->equiping) prompt_fight(jeu, ma_commande);
            else sprintf(jeu->message, NOT_FIGHTING);
            break;
        case EQUIP:
            if(jeu->equiping) prompt_equip(jeu, ma_commande);
            else if (jeu->combat) sprintf(jeu->message, MERROR "Votre champion est déjà équipé.");
            else sprintf(jeu->message, NOT_FIGHTING);
            break;
        case MOVE:
            if(jeu->combat) prompt_move(jeu, ma_commande);
            else sprintf(jeu->message, NOT_FIGHTING);
            break;
        case USE:
            if(jeu->combat) prompt_use(jeu, ma_commande);
            else sprintf(jeu->message, NOT_FIGHTING);
            break;
        case ADD:
            if (jeu->combat) prompt_add(jeu, ma_commande);
            else sprintf(jeu->message, NOT_FIGHTING);
            break;
        case END:
            if(jeu->combat) prompt_end(jeu, ma_commande);
            else sprintf(jeu->message, NOT_FIGHTING);
            break;
        case EXIT:
            jeu->fin = 1;
            break;
        case ERROR:
        default:
            sprintf(jeu->message, INVALID_CMD);
            break;
    }
    vider_ma_commande(ma_commande);
}

/** Place dans le buffer l'entrée de l'utilisateur
  * Args :
  *   char *cmd : l'entrée de l'utilisateur
  * Return:
  *   bool
  */
int rangecommand(char *cmd, char** ma_commande) {
    int i = 1, fin = 0;
    ma_commande[0] = strtok(cmd, " \n");

    if (ma_commande[0] == NULL)
        return 0;

    while (!fin) {
        ma_commande[i] = strtok(NULL, " \n");
        if (ma_commande[i] == NULL)
            fin=1;
        if (i >= L_CMD && ma_commande[i] != NULL)
            return 0;
        i++;
    }

    return 1;
}

void equip_bot(Jeu* jeu, Strat* s)
{
    jeu->courant->equip = s->equip;
    jeu->courant->ce -= s->cout;
    jeu->courant->ce_used += s->cout;

    if (jeu->courant == jeu->legume) {
        jeu->courant = jeu->fruit;
        sprintf(jeu->message, "Le Légume est entrain de s'équiper.");
        wait(jeu);
    } else {
        jeu->courant = jeu->legume;
        jeu->equiping = 0;
        jeu->combat = 1;

        sprintf(jeu->message, "Le Fruit est entrain de s'équiper.");
        wait(jeu);
        sprintf(jeu->message, RED "Combat lancé ! " NORMAL BOLD "%s "
                NORMAL RED "< VERSUS >" NORMAL BOLD " %s" NORMAL,
                jeu->legume->champ->variete, jeu->fruit->champ->variete);
    }
}

/** Permet de récuperer ce qu'a écrit l'utilisateur et de lancer l'analyse
  * Args :
  *   Jeu *jeu : instance du Jeu
  * Return:
  *   NONE
  */
void affichePrompt(Jeu *jeu, Tableaux* tableaux, char** ma_commande) {
    char *commande = NULL;
    size_t entier = 0;
    int bot = jeu->courant->id_strat != -1;

    if (!BETA_TESTING) gotoxy(3, S_HEIGHT - 1);

    if (jeu->combat) {
        if (bot) printf("[BOT] ");
        printf(BOLD "%s (%d)" NORMAL " ", jeu->courant->champ->variete, jeu->courant->ca);
    } else if (jeu->equiping)
        printf("Equipez votre " BOLD "%s" NORMAL " ! ", jeu->courant->champ->variete);

    if (!bot) {
        printf("> ");
        getline(&commande, &entier, stdin);

        if (rangecommand(commande, ma_commande)) {
            prompt(strToCmd(ma_commande), jeu, tableaux, ma_commande);
            if (jeu->courant->ca <= 0) {
                wait(jeu);
                prompt_end(jeu, ma_commande);
            }
        } else
            sprintf(jeu->message, INVALID_CMD);
    } else {
        Strat* s = tableaux->mes_strats[jeu->courant->id_strat];
        if (jeu->equiping)
            equip_bot(jeu, s);
        else {
            exec(jeu, tableaux, s, ma_commande);
            prompt_end(jeu, ma_commande);
        }
    }

    free(commande);
}

#include "equipement.h"
#include "jeu.h"
#include "strats.h"
#include "prompt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/** remplace des caractères dans une chaine
  * Args :
  *   char *src : source
  *   char c : caractère a remplacer
  *   char newc : nouveau caractère
  * Return:
  *   NONE
  */
void replace(char *src, char c, char newc){
    int i;
    for(i = 0; i < strlen(src); i++){
        if(src[i] == c)
            src[i] = newc;
    }
}

/** lis le fichier pour le ranger dans un tableau
  * Args :
  *   char *filename : nom du fichier
  * Return:
  *   char **
  */
char **lireFile(char *filename){
    FILE *file = fopen(filename, "r");
    char *myfile, *mot;
    char **tab;
    int i = 0, fin = 0;
    int taille = TAILLE, taillefile;

    fseek(file, 0, SEEK_END);
    taillefile = ftell(file);
    fseek(file, 0, SEEK_SET);
    myfile = (char *)calloc(sizeof(char), taillefile);
    fread(myfile, taillefile, 1, file);
    myfile[taillefile - 1] = '\0';
    fclose(file);

    tab = (char **)calloc(sizeof(char *), TAILLE);
    mot = strtok(myfile, ESP);

    if(!file) return NULL;

    tab[0] = (char*)calloc(sizeof(char), strlen(mot) + 1);
    strcpy(tab[i++], mot);

    while (!fin){
        mot = strtok(NULL, ESP);
        if (mot != NULL) {
            if (i == taille) {
                taille += TAILLE;
                tab = (char **)realloc(tab, sizeof(char *) * taille);
            }
            tab[i] = (char*)calloc(sizeof(char), strlen(mot) + 1);
            strcpy(tab[i++], mot);
        } else
            fin = 1;
    }

    tab = (char **)realloc(tab, sizeof(char *) * (i + 1));
    tab[i] = NULL;

    free(myfile);
    return tab;
}

/** Test si le nombre en argument est un nombre
  * Args :
  *   char *tmp : chaine a analyser
  *   int fin : nombre de carac a lire
  * Return:
  *   int
  */
int estNombre(char *tmp, int fin){
    int i;
    for(i = 0;i < fin;i++)
        if(!isdigit(tmp[i]))
            return 0;
    return 1;
}

/**DEBUT VERIFICATION SYNTAXIQUE*/

/** Verifie si la commande est syntaxiquement correcte
  * Args :
  *   char **tmp : Tableau de mots
  * Return:
  *   int
  */
int verifCommande(char **tmp, Tableaux* tableaux){
    char** motclesprompt = tableaux->motclesprompt;
    char** motcles = tableaux->motcles;

    if(!strcmp(*tmp, motclesprompt[0])){
        tmp++;
        if( !strcmp(*tmp,motcles[7]) || !strcmp(*tmp,motcles[8]) || !strcmp(*tmp,motcles[9]) ){
            tmp++;
            if(estNombre(*tmp,strlen(*tmp)))return 2;
            else return 1;
        }
    }
    else if(!strcmp(*tmp,motclesprompt[1])){
        tmp++;
        if( !strcmp(*tmp,motcles[15]) || !strcmp(*tmp,motcles[16]) ){
            tmp++;
            if(estNombre((*tmp),strlen(*tmp)))return 2;
            else return 1;
        }
    }
    else if( !strcmp(*tmp,motclesprompt[2]) ){
        tmp ++;
        if( !strcmp(*tmp,motcles[5])){
            tmp++;
            if(estNombre((*tmp),strlen(*tmp)))return 2;
            else return 1;
        }
    }
    else if(!strcmp(*tmp,motclesprompt[3]))return 0;
    return -1;
}

/** Verifie si le if est syntaxiquement correct
  * Args :
  *   char **tmp : Tableau de mots
  * Return:
  *   int
  */
int verifIf(char **tmp, Tableaux* tableaux){
    char** motcles = tableaux->motcles;
    char** motclescomp = tableaux->motclescomp;

    int inscope = 0,telse = 0,tendif = 0;
    int i,j=0,k=0;
    if( !strcmp(*tmp,motcles[10]) || !strcmp(*tmp,motcles[11]) ){
        tmp++;
        k++;
        for(i = 0; i < NB_MOTS_C_C; i++)if( !strcmp(*tmp,motclescomp[i]) )j=1;
        if(!j){
            printf("ERROR SYNT IF\n");
            return 0;
        }
        tmp++;
        k++;
        if ((*tmp)[strlen(*tmp)-1] == '%' && !estNombre(*tmp,strlen(*tmp)-1))
            return 0;
        else if ((*tmp)[strlen(*tmp)-1] != '%' && !estNombre(*tmp,strlen(*tmp)))
            return 0;
    }
    else if( !strcmp(*tmp,motcles[12]) )inscope = 1;
    else return 0;
    tmp++;
    k++;
    while( (*tmp) && !tendif){
        if(!strcmp(*tmp,motcles[13]))telse++;
        else if(!strcmp(*tmp,motcles[14])){
            tendif++;
            tmp--;
            k--;
        }
        else if(!strcmp(*tmp,motcles[1])){
            tmp++;
            k++;
            if(!(j = verifIf(tmp, tableaux)))
                return 0;
            else{
                tmp+=j;
                k+=j;
            }
        }
        else{
            if((j = verifCommande(tmp, tableaux)) == (-1))
                return 0;
            else{
                tmp += j;
                k+=j;
            }
        }
        tmp++;
        k++;
    }
    if( telse > 1 || !tendif || (inscope && !telse))
        return 0;
    return k;
}

/** Verifie si le choose est syntaxiquement correct
  * Args :
  *   char **tmp : Tableau de mots
  * Return:
  *   int
  */
int verifChoose(char **tmp, Tableaux* tableaux){
    char** motcles = tableaux->motcles;

    int i;
    if(!strcmp(*tmp,motcles[7]) || !strcmp(*tmp,motcles[8]) || !strcmp(*tmp,motcles[9])){
        tmp++;
        for(i = 0;i < NB_MOTS_C;i++)if(!strcmp(*tmp,motcles[i]))return 0;
        return 1;
    }
    return 0;
}

/** Verifie si la stratégie est syntaxiquement correcte
  * Args :
  *   char **tmp : Tableau de mots
  * Return:
  *   int
  */
int verifSyntaxe(char** tmp, Tableaux* tableaux){
    char** motcles = tableaux->motcles;  

    int i, j, chooseweapon = 0;

    if (!strcmp(*tmp, motcles[0])) {
        tmp++;
        for(i = 0; i < NB_MOTS_C; i++) {
            if (!strcmp(*tmp, motcles[i]))
                return 0;
        }
        tmp++;

        while (!strcmp(*tmp, motcles[6])) {
            if (!(j = verifChoose(++tmp, tableaux)))
                return 0;
            else {
                if (!strcmp(*tmp, motcles[7]))
                    chooseweapon=1;
                tmp += j;
            }
            tmp++;
        }

        if (!chooseweapon)
            return 0;

        while (*tmp) {
            if (!strcmp(*tmp, motcles[1])) {
                tmp++;
                if ((j = verifIf(tmp, tableaux)))
                    tmp += j;
                else return 0;
            } else{
                if ((j = verifCommande(tmp, tableaux)) != -1)
                    tmp+=j;
                else return 0;
            }
            tmp++;
        }
        return 1;
    }
    return 0;
}

/**FIN VERIFICATION SYNTAXIQUE*/

/*DEBUT EXEC STRAT*/

/** Execute la commande dans le prompt
  * Args :
  *   Jeu *jeu : instance du jeu
  *   char **machaine : Tableau de mots
  *   int j : nombre de mots dans la commande a traiter
  * Return:
  *   NONE
  */
void prompt_exec(Jeu* jeu, Tableaux* tableaux, char** machaine, int j, char** ma_commande)
{
    if (j == 0) {
        /*sprintf(jeu->message, "Commande executé : %s\n", *machaine);*/
        ma_commande[0] = *machaine;
    }
    else if (j == 1) {
        /*sprintf(jeu->message, "Commande executé : %s %s\n", *machaine, machaine[1]);*/
        ma_commande[0] = *machaine;
        ma_commande[1] = machaine[1];
    } else if (j == 2) {
        /*sprintf(jeu->message, "Commande executé : %s %s %s\n", *machaine, machaine[1], machaine[2]);*/
        ma_commande[0] = *machaine;
        ma_commande[1] = machaine[1];
        ma_commande[2] = machaine[2];
    }

    prompt(strToCmd(ma_commande), jeu, tableaux, ma_commande);
    /*wait(jeu);*/
}

/** Execute la condition valider d'un if
  * Args :
  *   Jeu *jeu : instance du jeu
  *   char **machaine : Tableau de mots
  * Return:
  *   char **
  */
char** exec_condition(Jeu* jeu, Tableaux* tableaux, char **machaine, char** ma_commande) {
    int i;
    if( !strcmp(tableaux->motcles[1], *machaine) ){
        machaine = execif(jeu, tableaux, machaine, ma_commande);
        if (*machaine != NULL) {
            machaine++;
            i = verifIf(machaine, tableaux);
        }
    } else {
        i = verifCommande(machaine, tableaux);

        if (strcmp(*machaine, "end") == 0)
            while (*(++machaine) != NULL);
        else
            prompt_exec(jeu, tableaux, machaine, i, ma_commande);
    }
    if (*machaine != NULL) machaine += i + 1;
    return machaine;
}

/** Execute la partie inutile d'un if
  * Args :
  *   char **machaine : Tableau de mots
  * Return:
  *   char **
  */
char** exec_else(char **machaine, Tableaux* tableaux)
{
    int i;
    if( !strcmp(*machaine,tableaux->motcles[1]) ){
        machaine++;
        i = verifIf(machaine, tableaux);
        machaine += i;
    }
    machaine++;
    return machaine;
}

/** Execute le if
  * Args :
  *   Jeu *jeu : instance du jeu
  *   char **machaine : Tableau de mots
  * Return:
  *   char **
  */
char **execif(Jeu *jeu, Tableaux* tableaux, char **machaine, char** ma_commande){
    char** motcles = tableaux->motcles;
    char** motclescomp = tableaux->motclescomp;

    int condition = -1, test, test2;
    Joueur *lifetest;
    machaine++;

    if( !strcmp(*machaine,motcles[10]) || !strcmp(*machaine,motcles[11]) ){
        if (!strcmp(*machaine, motcles[10]))
            lifetest = jeu->courant;
        else {
            if (jeu->courant == jeu->legume)
                lifetest = jeu->fruit;
            else
                lifetest = jeu->legume;
        }
        test = lifetest->champ->pv;
        /*verif du comparateurs*/
        machaine++;
        if (machaine[1][strlen(machaine[1]) - 1] == '%')
            test = (test * 100) / lifetest->champ->pv_max;
        test2 = atoi(machaine[1]);

        /*Verif de la condition*/
        if (!strcmp(motclescomp[0], *machaine))
            condition = !(test < test2);
        else if (!strcmp(motclescomp[1], *machaine))
            condition = !(test <= test2);
        else if (!strcmp(motclescomp[2], *machaine))
            condition = !(test == test2);
        else if (!strcmp(motclescomp[3], *machaine))
            condition = !(test != test2);
        else if (!strcmp(motclescomp[4], *machaine))
            condition = !(test >= test2);
        else if (!strcmp(motclescomp[5],*machaine))
            condition = !(test > test2);
        /* 0 : < - 1 : <= - 2 : = - 3 : != - 4 : >= - 5 : >*/
        machaine++;
    }
    else
        condition = !(fabs((float)(jeu->legume->pos - jeu->fruit->pos)) <= jeu->courant->equip->arme->portee);

    /*je traite le if*/
    machaine++;
    if(!condition){
        /*Exec jusqu'au else*/
        while(*machaine != NULL && strcmp(motcles[13], *machaine) && strcmp(motcles[14], *machaine) )
            machaine = exec_condition(jeu, tableaux, machaine, ma_commande);

        while(*machaine != NULL && strcmp(motcles[14],*machaine) )
            machaine = exec_else(machaine, tableaux);
        /*Fin premier cas*/
    }
    else{
        /*Traverser la premiere partie de if*/
        while( strcmp(motcles[13],*machaine) && strcmp(motcles[14],*machaine) )
            machaine = exec_else(machaine, tableaux);

        if( !strcmp(*machaine,motcles[13]) ) machaine++;
        /*faire l exec*/

        while(*machaine != NULL && strcmp(motcles[14],*machaine) )
            machaine = exec_condition(jeu, tableaux, machaine, ma_commande);
    }

    return machaine;
}

/** Execute la stratégie en argument
  * Args :
  *   Jeu *jeu : instance du jeu
  *   Strat *mastrat : stratégie que l'on execute
  * Return:
  *   NONE
  */
void exec(Jeu *jeu, Tableaux* tableaux, Strat *mastrat, char** ma_commande){
    char** motcles = tableaux->motcles;
    char **machaine = mastrat->tab;
    int j;

    while( strcmp(*machaine,motcles[1]) && strcmp(*machaine,motcles[2]) && \
            strcmp(*machaine,motcles[3]) && strcmp(*machaine, motcles[4]) && strcmp(*machaine,motcles[17]) )
        machaine++;

    while(*machaine != NULL){
        if (!strcmp(motcles[1], *machaine))
            machaine = execif(jeu, tableaux, machaine, ma_commande);
        else {
            j = verifCommande(machaine, tableaux);

            if ( !strcmp(*machaine, "end") )
              return;
            else{
              prompt_exec(jeu, tableaux, machaine, j, ma_commande);
              machaine += j;
            }
        }
        if (*machaine != NULL) machaine++;
    }
}

/*FIN DE L EXECUTION DE LA STRAT*/

/** créé une nouvelle strat
  * Args :
  *   Jeu *jeu : instance du jeu
  *   char *filename : nom du fichier lu
  *   char **tmp : Tableau de mots
  * Return:
  *   Strat *
  */
Strat *creerStrat(char *nom, char *filename, char **tab){
    Strat *newStrat = (Strat*)calloc(sizeof(Strat), 1);
    newStrat->tab = tab;
    newStrat->nom = (char*)calloc(sizeof(char), strlen(nom) + 1);
    newStrat->filename = (char*)calloc(sizeof(char), strlen(filename) + 1);

    strcpy(newStrat->filename, filename);
    strcpy(newStrat->nom, nom);

    return newStrat;
}

/** creer la liste des stratégies valide
  * Args :
  *   Tableaux* tableaux
  *   char **listenoms : liste des noms de stratégies
  * Return:
  *   None
  */
void creerListeStrats(Tableaux* tableaux, char **listenoms){
    char **tab, **tmp;
    int i, j = 0;

    tableaux->mes_strats = (Strat**)calloc(sizeof(Strat*), NB_STRATS);
    tableaux->listesNomsStrats = (char**)calloc(sizeof(char *), NB_STRATS);

    for (i = 0; i < NB_STRATS; i++) {
        tmp = lireFile(listenoms[i]);
        if (!strcmp(tmp[0],tableaux->motcles[0])) {
            if (verifSyntaxe(tmp, tableaux)) {
                tableaux->listesNomsStrats[j] = tmp[1];
                tableaux->mes_strats[j] = creerStrat(tableaux->listesNomsStrats[j], listenoms[i], tmp);
                j++;
            } else {
              tab = tmp;
              while (*tab != NULL)
                  free(*tab++);
              free(tmp);
            }

        }
        else printf("ERROR\n");
    }

    tableaux->nb_strats = j;
}

/** trouve l arme associé au nom
  * Args :
  *   Jeu *jeu : instance du jeu
  *   char *nom : nom de l'arme
  * Return:
  *   Arme *
  */
Arme *findWeapon(Jeu *jeu,char *nom){
    char* test;
    int i,j;
    for(i = 0; nom[i] != '\0'; i++)
        nom[i] = toupper(nom[i]);
    for(i = 0;i < NB_ARMES;i++){
        test = calloc(sizeof(char), strlen(jeu->armes[i]->nom) + 1);
        strcpy(test,jeu->armes[i]->nom);
        replace(test,' ','_');
        replace(test,'-','_');
        for(j = 0;j < strlen(test);j++)
            test[j] = toupper(test[j]);
        if(!strcmp(test,nom)){
            free(test);
            return jeu->armes[i];
        }
        free(test);
    }
    return NULL;
}

/** trouve la protection associé au nom
  * Args :
  *   Jeu *jeu : instance du jeu
  *   char *nom : nom de l'arme
  * Return:
  *   Protection *
  */
Protection *findProtec(Jeu *jeu, char *nom){
    char* test;
    int i,j;
    for(i = 0; nom[i] != '\0'; i++)
        nom[i] = toupper(nom[i]);
    for(i = 0;i < NB_PROTECTS;i++){
        test = calloc(sizeof(char), strlen(jeu->protects[i]->nom) + 1);
        strcpy(test, jeu->protects[i]->nom);
        replace(test,' ','_');
        replace(test,'-','_');
        for(j = 0;j < strlen(test);j++)
            test[j] = toupper(test[j]);
        if(!strcmp(test,nom)){
            free(test);
            return jeu->protects[i];
        }
        free(test);
    }
    return NULL;
}

/** trouve le soin associé au nom
  * Args :
  *   Jeu *jeu : instance du jeu
  *   char *nom : nom de l'arme
  * Return:
  *   Soin *
  */
Soin *findHeal(Jeu *jeu,char *nom){
    char *test;
    int i,j;
    for(i = 0; nom[i] != '\0'; i++)
        nom[i] = toupper(nom[i]);
    for(i = 0;i < NB_ARMES;i++){
        test = calloc(sizeof(char), strlen(jeu->soins[i]->nom) + 1);
        strcpy(test,jeu->soins[i]->nom);
        replace(test,' ','_');
        replace(test,'-','_');
        for(j = 0;j < strlen(test);j++)
            test[j] = toupper(test[j]);
        if(!strcmp(test,nom)){
            free(test);
            return jeu->soins[i];
        }
        free(test);
    }
    return NULL;
}

/** Equipe les equipements au strats
  * Args :
  *   Jeu *jeu : instance du jeu
  * Return:
  *   NONE
  */
void equipementStrats(Jeu *jeu, Tableaux* tableaux){
    char** motcles = tableaux->motcles;

    char **tmp;
    Equipement *equip;
    int i, arme, prot, heal;
    for(i = 0; i < tableaux->nb_strats; i++) {
        arme = 0;
        prot = 0;
        heal = 0;
        equip = calloc(sizeof(Equipement),1);
        tmp = tableaux->mes_strats[i]->tab;
        tmp++;
        while(!strcmp(*(++tmp), motcles[6])){
            tmp++;
            if(!strcmp(*tmp,motcles[7]) && !arme){ /*Si une arme*/
                equip->arme = findWeapon(jeu, *(++tmp));
                tableaux->mes_strats[i]->cout += equip->arme->ce;
                arme = 1;
            }
            else if(!strcmp(*tmp,motcles[8]) && !prot){
                equip->protect = findProtec(jeu, *(++tmp));
                tableaux->mes_strats[i]->cout += equip->protect->ce;
                prot = 1;
            }
            else if(!strcmp(*tmp,motcles[9]) && !heal){
                equip->soin = findHeal(jeu,*(++tmp));
                tableaux->mes_strats[i]->cout += equip->soin->ce;
                heal = 1;
            }
            else printf("ERROR\n");
        }
        tableaux->mes_strats[i]->equip = equip;
        if(!tableaux->mes_strats[i]->equip->arme)
          printf("ERROR\n");
    }
}

/** print toutes les strats
  * Args :
  *   NONE
  * Return:
  *   NONE
  */
void printAllStrats(Tableaux* tableaux){
    int i = 0;
    printf("\t--- Strats ---\n");
    for(i = 0; i < tableaux->nb_strats; i++)
        printf("\t/ %d / %s\n", i, tableaux->mes_strats[i]->nom);
    printf("\t-------------\n\n");
}

/** print une strat mais version detaillé
  * Args :
  *   int i : indice de la stratégie
  * Return:
  *   NONE
  */
void printStrat(Tableaux* tableaux, int i){
    printf("\t--- %s ---\n", tableaux->mes_strats[i]->filename);
    printf("\tNom : %s\n", tableaux->mes_strats[i]->nom);
    printf("\tArme : %s\n", tableaux->mes_strats[i]->equip->arme->nom);
    printf("\tProtection : %s\n", tableaux->mes_strats[i]->equip->protect->nom);
    printf("\tSoin : %s\n", tableaux->mes_strats[i]->equip->soin->nom);
    printf("\tCout en Ce : %d\n", tableaux->mes_strats[i]->cout);
    printf("\t----%.*s----\n\n",(int)strlen(tableaux->mes_strats[i]->filename),
            "-----------------------------------------------");
}

/** rempli les tableaux
  * Args :
  *   NONE
  * Return:
  *   NONE
  */
void remplirTab(Tableaux* tableau){
    int i;
    char *tab[] = {"use","move","add","end"};
    /* 0 : use - 1 : move - 2 : add - 3 : end*/
    char *tab2[] = {"strategy","if","use","move","add","action","choose","weapon","protection",\
        "care","life","enemyLife","enemyInScope","else","endif","forward","backward","end"};

    /* 0 : strategy - 1 : if - 2 : use - 3 : move - 4 : add - 5 : action
6 : choose - 7 : weapon - 8 : protection - 9 : care - 10 : life
11 : enemyLife - 12 : enemyInScope - 13 : else - 14 : endif
15 : forward - 16 : backward - 17 : end*/
    char *tab3[] = {"<","<=","=","!=",">=",">"};
    /* 0 : < - 1 : <= - 2 : = - 3 : != - 4 : >= - 5 : >*/
    tableau->motclesprompt = calloc(sizeof(char *),NB_MOTS_C_P);
    tableau->motclescomp = calloc(sizeof(char *),NB_MOTS_C_C);
    tableau->motcles = calloc(sizeof(char *),NB_MOTS_C);
    for(i = 0;i < NB_MOTS_C_P;i++)
      tableau->motclesprompt[i] = tab[i];
    for(i = 0;i < NB_MOTS_C;i++)
      tableau->motcles[i] = tab2[i];
    for(i = 0;i < NB_MOTS_C_C;i++)
      tableau->motclescomp[i] = tab3[i];
}

/** free toutes les stratss
  * Args :
  *   NONE
  * Return:
  *   NONE
  */
void free_strats(Tableaux** tableau)
{
    int i;
    for(i = 0; i < (*tableau)->nb_strats; i++){
        char** tab = (*tableau)->mes_strats[i]->tab;
        while (*tab != NULL)
            free(*tab++);
        free((*tableau)->mes_strats[i]->tab);
        free((*tableau)->mes_strats[i]->equip);
        free((*tableau)->mes_strats[i]->nom);
        free((*tableau)->mes_strats[i]->filename);
        free((*tableau)->mes_strats[i]);
    }
    free((*tableau)->mes_strats);
    free((*tableau)->motcles);
    free((*tableau)->motclesprompt);
    free((*tableau)->motclescomp);
    free((*tableau)->listesNomsStrats);
    free(*tableau);
}

/** initialise les stratégies
  * Args :
  *   Jeu *jeu : instance du jeu
  * Return:
  *   NONE
  *
  * Si vous voulez modif les strats rajouter le nom dans le tableau pouet
  * N'oubliez pas d'incrementer nbStrats
  */
Tableaux* initStrats(Jeu *jeu) {
    char *pouet[] = {"./build/Strats/1.strat","./build/Strats/2.strat","./build/Strats/3.strat","./build/Strats/4.strat","./build/Strats/5.strat"};

    Tableaux *tab = (Tableaux*)malloc(sizeof(Tableaux));

    remplirTab(tab);
    creerListeStrats(tab, pouet);
    equipementStrats(jeu, tab);

    return tab;
}

#include "equipement.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Equipement* initEquipement(Arme* arme, Protection* protect, Soin* soin)
{
    Equipement* equip = (Equipement*)malloc(sizeof(Equipement));

    equip->arme = arme;
    equip->protect = protect;
    equip->soin = soin;

    return equip;
}

Arme* initArme(char *nom, int ce, int ca, int d_min, int d_max, int portee)
{
    Arme* arme = (Arme*)malloc(sizeof(Arme));

    arme->nom = (char*)malloc(sizeof(char) * (strlen(nom) + 1));
    strcpy(arme->nom, nom);

    arme->ce = ce;
    arme->ca = ca;
    arme->d_min = d_min;
    arme->d_max = d_max;
    arme->portee = portee;

    return arme;
}

Protection* initProtection(char *nom, int ce, int ca, int prob)
{
    Protection* protect = (Protection*)malloc(sizeof(Protection));

    protect->nom = (char*)malloc(sizeof(char) * (strlen(nom) + 1));
    strcpy(protect->nom, nom);

    protect->ce = ce;
    protect->ca = ca;
    protect->prob = prob;

    return protect;
}

Soin* initSoin(char *nom, int ce, int ca, int volume, int hp_min, int hp_max)
{
    Soin* soin = (Soin*)malloc(sizeof(Soin));

    soin->nom = (char*)malloc(sizeof(char) * (strlen(nom) + 1));
    strcpy(soin->nom, nom);

    soin->ce = ce;
    soin->ca = ca;
    soin->volume = volume;
    soin->hp_min = hp_min;
    soin->hp_max = hp_max;

    return soin;
}

/* Initialisations en brut.*/

Arme** initArmes()
{
    Arme **armes = (Arme**)malloc(sizeof(Arme*) * NB_ARMES);
    armes[0] = initArme("Eplucheur Laser", 2, 1, 1, 2, 2);
    armes[1] = initArme("Mandoline Sonique", 5, 3, 1, 3, 3);
    armes[2] = initArme("Couperet Laser", 10, 5, 2, 6, 5);
    armes[3] = initArme("Hachoir Neuronique", 20, 7, 4, 9, 7);
    armes[4] = initArme("Mixeur Blaster", 30, 10, 7, 12, 11);

    return armes;
}

Protection** initProtections()
{
    Protection **protects = (Protection**)malloc(sizeof(Protection*) * NB_PROTECTS);
    protects[0] = initProtection("Casque-Egouttoir", 1, 2, 25);
    protects[1] = initProtection("Casque-Entonnoir", 3, 4, 40);
    protects[2] = initProtection("Woklier", 5, 6, 60);
    protects[3] = initProtection("Tableur-Armure", 10, 8, 80);

    return protects;
}

Soin** initSoins()
{
    Soin **soins = (Soin**)malloc(sizeof(Soin*) * NB_SOINS);
    soins[0] = initSoin("Humus-Neutronique", 1, 5, 4, 2, 4);
    soins[1] = initSoin("Composte-Protonique", 5, 10, 3, 5, 8);
    soins[2] = initSoin("Engrais-Ionique", 7, 15, 2, 8, 12);

    return soins;
}

/* Free de la mémoire*/

void freeArmes(Arme*** armes)
{
    int i;
    for (i = 0; i < NB_ARMES; i++) {
        free((*armes)[i]->nom);
        free((*armes)[i]);
    }
    free(*armes);
}

void freeProtections(Protection*** protects)
{
    int i;
    for (i = 0; i < NB_PROTECTS; i++) {
        free((*protects)[i]->nom);
        free((*protects)[i]);
    }
    free(*protects);
}

void freeSoins(Soin*** soins)
{
    int i;
    for (i = 0; i < NB_SOINS; i++) {
        free((*soins)[i]->nom);
        free((*soins)[i]);
    }
    free(*soins);
}

#ifndef __ENTITIES__
#define __ENTITIES__

#define NB_ARMES 5
#define NB_PROTECTS 4
#define NB_SOINS 3

/*
 * Structures
 */

typedef struct {
    char* nom;
    int ce;
    int ca;
    int d_min;
    int d_max;
    int portee;
} Arme;

typedef struct {
    char* nom;
    int ce;
    int ca;
    int prob;
} Protection;

typedef struct {
    char* nom;
    int ce;
    int ca;
    int volume;
    int hp_min;
    int hp_max;
} Soin;

typedef struct {
    Arme *arme;
    Protection *protect;
    Soin *soin;
} Equipement;

/*
 * Headers
 */

Arme* initArme(char *nom, int ce, int ca, int d_min, int d_max, int portee);
Protection* initProtection(char *nom, int ce, int ca, int prob);
Soin* initSoin(char *nom, int ce, int ca, int volume, int hp_min, int hp_max);

Arme** initArmes();
Protection** initProtections();
Soin** initSoins();

void freeArmes(Arme*** armes);
void freeProtections(Protection*** protects);
void freeSoins(Soin*** soins);

#endif

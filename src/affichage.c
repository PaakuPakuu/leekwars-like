#include "affichage.h"
#include "jeu.h"
#include "prompt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

/** Affiche l'écran d'introduction du jeu.
 *  Args : NONE
 *  Return : NONE
 */
void print_bienvenu()
{
    print_texte(BIENVENU, 25, 10);
    gotoxy(0, 0);
    getchar();
}

/** Affiche le support graphique dans lequel se déroule le jeu.
 *  Args : None.
 *  Return : None.
 */
void print_support()
{
    int x, y;
    gotoxy(0, 0);
    for (y = 0; y < S_HEIGHT; y++) {
        for (x = 0; x < S_WIDTH; x++) {
            if (x == 0) {
                if (y == 0) printf("╔");
                else if (y == SEP_INPUT_FIELD) printf("╠");
                else if (y == S_HEIGHT - 1) printf("╚");
                else printf("║");
            } else if (x == SEP_CMD_MESS) {
                if (y == SEP_INPUT_FIELD) printf("╤");
                else if (y == S_HEIGHT - 1) printf("╧");
                else if (y > SEP_INPUT_FIELD) printf("│");
                else if (y == 0) printf("═");
                else printf(" ");
            } else if (x == S_WIDTH - 1) {
                if (y == 0) printf("╗");
                else if (y == SEP_INPUT_FIELD) printf("╣");
                else if (y == S_HEIGHT - 1) printf("╝");
                else printf("║");
            } else {
                if (y == 0 || y == SEP_INPUT_FIELD || y == S_HEIGHT - 1) printf("══");
                else printf("  ");
            }
        }
        putchar('\n');
    }
}

/** Affiche un texte en position (x ; y)
 *  Args :
 *      char* texte : chaine de caractère à afficher.
 *      int x : position x.
 *      int y : position y.
 *  Return :
 *      None.
 */
void print_texte(char* texte, int x, int y)
{
    char *ligne, *str = (char*)malloc(sizeof(char) * L_TEXT);
    strcpy(str, texte);

    ligne = strtok(str, "\n");
    while (ligne != NULL) {
        gotoxy(x, y);
        printf("%s", ligne);
        ligne = strtok(NULL, "\n");
        y++;
    }
    free(str);
}

/** Affiche le cadre dans lequel sera afficher le résultat de la commande "show".
 *  Args :
 *      Jeu* jeu : instance du jeu.
 *  Return :
 *      None.
 */
void print_show(Jeu* jeu)
{
    int x, y;
    gotoxy(SHOW_START_X, 0);
    for (y = 0; /*!jeu->combat &&*/ y < SHOW_END_Y; y++) {
        for (x = SHOW_START_X; x < SHOW_END_X; x++) {
            if (x == SHOW_START_X) {
                if (y == 0) printf("╤");
                else if (y == SHOW_END_Y - 1) printf("╰");
                else printf("│");
            } else if (x == SHOW_END_X - 1) {
                if (y == 0) printf("╤");
                else if (y == SHOW_END_Y - 1) printf("╯");
                else printf("│");
            } else {
                if (y == 0) printf("══");
                else if (y == SHOW_END_Y - 1) printf("──");
                else printf("  ");
            }
        }
        gotoxy(SHOW_START_X, y + 2);
    }

    print_texte(jeu->texte, SHOW_START_X + 8, 2);
}

void print_wrongsize(int sx, int sy)
{
    gotoxy(1, 1);
    printf(RED  "- AUGMENTEZ LA TAILLE DE LA FENÊTRE -\n" NORMAL);
    sx = S_WIDTH * 2 + 3 - sx;
    sy = S_HEIGHT + 3 - sy;
    if (sx > 0) printf("Longueur : +%d\n", sx);
    if (sy > 0) printf("Hauteur : +%d\n", sy);
}

void get_win_value(int *col, int *win)
{
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  *col = w.ws_col;
  *win = w.ws_row;
}

void wait(Jeu* jeu)
{
    maj_affichage(jeu);
    if (!BETA_TESTING) {
        gotoxy(S_WIDTH - 4, S_HEIGHT + 1);
        printf("- 2 -\n");
        sleep(1);
        gotoxy(S_WIDTH - 4, S_HEIGHT + 1);
        printf("- 1 -\n");
        sleep(1);
    }
}

/** Met à jour l'affichage.
 *  Args :
 *      Jeu* jeu : instance du jeu.
 *  Return :
 *      None.
 */
void maj_affichage(Jeu* jeu)
{
    if (!BETA_TESTING) {
        int sx, sy;
        clear();

        get_win_value(&sx, &sy);
        if (sx >= S_WIDTH * 2 - 3 && sy >= S_HEIGHT + 3) {
            print_support();
            print_show(jeu);

            if (!jeu->combat) {
                print_texte(LEG_SPRITE, 8, 3);
                print_texte(FRU_SPRITE, (S_WIDTH - 12) * 2, 3);
                if (jeu->equiping){
                    print_texte(INSTRUCTIONS_E, INSTRUCT_X, INSTRUCT_Y);
                    print_texte(INSTRUCTIONS_E_2, INSTRUCT_X, INSTRUCT_Y + 6);
                }
                else{
                    print_texte(INSTRUCTIONS_F, INSTRUCT_X, INSTRUCT_Y);
                    print_texte(INSTRUCTIONS_F_2, INSTRUCT_X, INSTRUCT_Y + 6);
                }
            } else {
                int x1 = (S_WIDTH - TERRAIN_WIDTH - SPRITE_WIDTH - 1) + jeu->legume->pos * S_MULT;
                int x2 = (S_WIDTH - TERRAIN_WIDTH) + (jeu->fruit->pos - 1) * S_MULT;
                print_texte(LEG_SPRITE, x1, SPRITE_Y);
                print_texte(FRU_SPRITE, x2, SPRITE_Y);
            }

            gotoxy((SEP_CMD_MESS + 1) * 2, S_HEIGHT - 1);
        } else
            print_wrongsize(sx, sy);
    }

    printf("%s\n", jeu->message);
}

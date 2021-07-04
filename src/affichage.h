#ifndef __AFFICHAGE__
#define __AFFICHAGE__

#include "jeu.h"
#include "prompt.h"

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

#define BETA_TESTING 1

/*
 *  Caractères d'échappement.
 */

#define NORMAL "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[34m"
#define GRAY "\033[37m"
#define BLINK "\033[5m"
#define OVER "\033[7m"
#define MERROR BOLD RED "ERROR : " NORMAL

/*
 *  Messages d'erreur.
 */

#define INVALID_CMD MERROR "Commande invalide."
#define TOO_MUCH_ARGS MERROR "Trop de paramètres."
#define WRONG_FIRST_ARG MERROR "Premier paramètre invalide."
#define ARGS_MISSING MERROR "Paramètres manquants."
#define POS_NUMBER_NEEDED MERROR "Nombre positif requis."
#define NOT_FIGHTING MERROR "Vous n'êtes pas en combat."
#define NOT_ENOUGH_CA MERROR "Vous n'avez pas assez de " BOLD "crédit d'action." NORMAL
#define NOT_ENOUGH_CE MERROR "Vous n'avez pas assez de " BOLD "crédit d'équipement." NORMAL

/*
 *  Constantes de positionnement.
 */

#define S_MULT 2
#define S_WIDTH (28 * S_MULT)
#define S_HEIGHT (16 * S_MULT)

#define SEP_INPUT_FIELD ((S_HEIGHT) - 3)
#define SEP_CMD_MESS ((S_WIDTH) / 2 - 1)

#define SHOW_START_X (15 * S_MULT)
#define SHOW_END_X (28 * S_MULT)
#define SHOW_END_Y (7 * S_MULT)

#define INSTRUCT_X (3 * S_MULT)
#define INSTRUCT_Y (8 * S_MULT)

#define TERRAIN_WIDTH (15 * S_MULT)
#define SPRITE_Y (S_HEIGHT - 13)
#define SPRITE_WIDTH 14

/*
 *  Textes.
 */

#define L_TEXT 1024

#define BETA_TEXT RED BOLD\
    BLINK "* * * * * * * * * * * * * * *\n"\
    "" NORMAL RED BOLD "   BETA-TEST MODE ACTIVATED  \n" BLINK\
    BLINK "* * * * * * * * * * * * * * *\n" NORMAL

#define BIENVENU \
    " _     _____ _____ _  ____        ___    ____  ____\n"\
    "| |   | ____| ____| |/ /\\ \\      / / \\  |  _ \\/ ___|\n"\
    "| |   |  _| |  _| | ' /  \\ \\ /\\ / / _ \\ | |_) \\___ \\\n"\
    "| |___| |___| |___| . \\   \\ V  V / ___ \\|  _ < ___) |\n"\
    "|_____|_____|_____|_|\\_\\   \\_/\\_/_/   \\_\\_| \\_\\____/\n"\
    " \n \n \n"\
    "\t\t  " BLINK ">" NORMAL " Press [ENTER] " BLINK "<" NORMAL


#define INSTRUCTIONS_F \
    "                                      " OVER BOLD " LISTE DES COMMANDES \n" NORMAL\
    "                                       ╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌\n"\
    " \n"\
    BOLD    "▻ show [ vegetables / fruits / weapons / protections / cares ]\n" NORMAL \
    GRAY    "                       - Affiche la liste des légumes, des fruits, des armes, ...\n" NORMAL \
    BOLD    "▻ show [ vegetable / fruit / weapon / protection / care ] [ID]\n" NORMAL

#define INSTRUCTIONS_F_2\
    GRAY    "                       - Affiche les caractéristiques d'un légume, d'un fruit, d'une arme, ...\n" NORMAL \
    BOLD    "▻ fight [ID légume] versus [ID fruit]\n" NORMAL \
    GRAY    "                       - Lance le combat entre un Légume et un Fruit.\n" NORMAL \
    BOLD    "▻ exit\n" NORMAL \
    GRAY    "                       - Permet de quitter LEEKWARS à tout moment." NORMAL

#define INSTRUCTIONS_E \
    "                              " OVER BOLD " IL EST TEMPS D'EQUIPER VOS CHAMPIONS \n" NORMAL \
    "                               ╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌\n"\
    " \n"\
    BOLD    "▻ show [ vegetables / fruits / weapons / protections / cares ]\n" NORMAL \
    GRAY    "                       - Affiche la liste des légumes, des fruits, des armes, ...\n" NORMAL \
    BOLD    "▻ show [ vegetable / fruit / weapon / protection / care ] [ID]\n" NORMAL

#define INSTRUCTIONS_E_2 \
    GRAY    "                       - Affiche les caractéristiques d'un légume, d'un fruit, d'une arme, ...\n" NORMAL \
    BOLD    "▻ equip [ID Arme] [ID Protection] [ID Soin]\n" NORMAL \
    GRAY    "                       - Equipe votre champion d'une arme, d'une protection et d'un soin.\n" NORMAL \
    BOLD    "▻ exit\n" NORMAL \
    GRAY    "                       - Permet de quitter LEEKWARS à tout moment." NORMAL

#define SHOW_START \
    " ▏  LANCEZ UNE COMMANDE \"show\"  ▕\n"\
    " ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n"\
    " \n" BOLD\
    "          |`-._/\\_.-`|\n"\
    "          | 4  ||  2 |\n"\
    "          |___o()o___|\n"\
    "          |__((<>))__|\n"\
    "          \\   o\\/o   /\n"\
    "           \\   ||   /\n"\
    "            \\  ||  /\n"\
    "             '.||.'\n"\
    "               ``" NORMAL

/*
 *  Sprites.
 */

#define LEG_SPRITE GREEN\
    "╭ ╌ ╌ ╌ ╌ ╌ ╌ ╮\n"\
    "╎ L E G U M E ╎\n"\
    "╎ L E G U M E ╎\n"\
    "╎ L E G U M E ╎\n"\
    "╎ L E G U M E ╎\n"\
    "╎ L E G U M E ╎\n"\
    "╎ L E G U M E ╎\n"\
    "╎ L E G U M E ╎\n"\
    "╰ ╌ ╌ ╌ ╌ ╌ ╌ ╯" NORMAL
                            /* TEMPORAIRE */
#define FRU_SPRITE YELLOW \
    "╭ ╌ ╌ ╌ ╌ ╌ ╌ ╮\n"\
    "╎  F R U I T  ╎\n"\
    "╎  F R U I T  ╎\n"\
    "╎  F R U I T  ╎\n"\
    "╎  F R U I T  ╎\n"\
    "╎  F R U I T  ╎\n"\
    "╎  F R U I T  ╎\n"\
    "╎  F R U I T  ╎\n"\
    "╰ ╌ ╌ ╌ ╌ ╌ ╌ ╯" NORMAL

/*
 *  Prototypes.
 */

void print_bienvenu();
void wait(Jeu* jeu);
void maj_affichage(Jeu* jeu);
void print_texte(char* str, int x, int y);

#endif

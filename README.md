# Projet-Rpg-C-avanc-
Rpg Fruit vs Légumes (LeekWars)
Projet créé par Alexis SALVETTI et JORDAN HERENG

Pour compiler utiliser la commande :
  make
Cela a pour effet de créer un dossier build contenant le fichier éxécutable
pour supprimer le dossier build ainsi que l'éxécutable :
  make clean

Pour lancer le jeu après avoir make
./build/leekwars
  depuis le fichier racine du jeu (car sinon il ne trouve pas la destination des fichiers strats).

   ===========================

   INFOS :

   - Quand vous voulez ajouter une stratégie il faut la mettre dans le fichier src/Strats.
   Nous avons quelque stratégie de test si vous ne souhaitez pas en créer.
   Pour chaque stratégie ajouté il faut dans le fichier src/strats.c changer le tableau contenant
   tous les liens vers les fichiers et modifier aussi la variable nbStrats.
   Enfin après avoir rajouter une nouvelle stratégie veuillez make clean et make pour qu'elle soit prise
   en compte.

   - Dans le fichier affichage.h il vous est possible de changer la variable BETA_TESTING entre 0 et 1 pour activer
   le mode developpeur du jeu (et ainsi voir les informations essentiels, sans attendre les délais implémenter
   entre chaque action) ou laissez le jeu avec son affichage.

   ===========================

   FONCTIONNALITES NON PREVU :

   Pour équiper le champion, écrire la commande suivante :
          equip [id_arme] [id_protection] [id_soin]

   ===========================

   PROBLEME "CONNU" :

   Quand le combat entre deux bot fini notre programme essaye de refaire une boucle d execution
   pour chacun des deux joueurs. Mais notre projet le gere et affiche tout simplement deux erreurs.
   Le problème n'est donc qu'esthétique.

  ===========================

affichage.c/affichage.h :
  Création de l'affichage

  - print_support() : Affiche le support dans lequel est affiché le jeu.
  - print_texte(char* texte, int x, int y) : Permet d'afficher un chaine de caractère à la position x;y.
  - print_show(Jeu* jeu) : Affiche le cadre où sera afficher les textes de la commande "show".
  - maj_affichage(Jeu* jeu) : Met à jour l'affichage du jeu.

commande.c/commande.h :
  Toutes les commandes liés au jeu et utilisable par le joueur

  - show(Jeu) : Permet d'afficher les détails du personnage courant
  (commande utilisable seulement en combat)
  - show_vars(Jeu,Char*) : Permet d'afficher la liste des personnages d'un certain camp
  (commande utilisable a n'importe quel moment)
  - show_vars_i(Jeu,Char*,int) : Permet d'afficher les détails du personnage a l'indice i
  (commande utilisable a n'importe quel moment)
  - exit_game(Jeu) : Permet de fermer le Jeu
  (commande utilisable a n'importe quel moment)
  - equip(Jeu,int,int,int) : Permet d'équiper les personnages
  (commande utilisable quand le match vient d'être lancé et que les personnages ne sont pas encore équipés)
  - move(Jeu,char*,int) : Permet de bouger son personnage
  (commande utilisable seulement en combat)
  use_weapon(Jeu,int)/use_protection(Jeu)/use_care(Jeu,int) : Permet d'utiliser son arme/protection/soin
  (commande utilisable seulement en combat)

equipement.c/equipement.h :
  Gère les equipements

  - initArme(char*,int,int,int,int,int)/
    initProtection(char*,int,int,int)/
    initSoin(char*,int,int,int,int,int) : Initialise une arme/protection/soin
  - initArmes(Arme***)/initProtections(Protection***)/initSoins(Soin***) : Permet d'initialiser la liste des armes/protections/soins
  - freeArmes(Arme***)/freeProtections(Protection***)/freeSoins(Soin***)

jeu.c/jeu.h :
 - initEquipement(Arme*,Protection*,Soin*)/
   initChamp(char*,Type,int,int,int,int)/
   initJoueur(int,int,int)/
   initJeu() : Initialise l'Equipement/Champion/Joueur/Jeu
 - initChamps() : initialise la liste des champions
 - boucle_combat(Jeu*) : Gère la boucle de combat
 - freeJoueur(Joueur**)/
   freeChamps(Champion**)/
   freeJeu(Jeu**) : Free tous les Joueurs/Champions/Jeu

prompt.c/prompt.h :
 - prompt_show(Jeu*)/
   prompt_equip(Jeu*)/
   prompt_fight(Jeu*)/
   prompt_move(Jeu*)/
   prompt_use(Jeu*)/
   prompt_end(Jeu*) : Permet de lancer les commandes
 - strToCmd() : Permet de transformer une chaine en une commande de base
 - vider_ma_commande() : Permet de vider la chaine de caractère qui sert de buffer
 - prompt(Commande,Jeu*) : Prompt général
 - rangecommand(char*) : range la commande dans la chaine de caractère buffer
 - affichePrompt(Jeu*) : affiche le prompt et demande une commande

 strats.c/strats.h :

 - void wait(Jeu* jeu)
 - void replace(char *src, char c, char newc)
 - char **lireFile(char *filename)
 - int estNombre(char *tmp, int fin)
 - int verifCommande(char **tmp)
 - int verifIf(char **tmp)
 - int verifChoose(char **tmp)
 - int verifSyntaxe(char** tmp)
 - void prompt_exec(Jeu* jeu, char** machaine, int j)
 - char** exec_condition(Jeu* jeu, char **machaine)
 - char** exec_else(char **machaine)
 - char **execif(Jeu *jeu, char **machaine)
 - void exec(Jeu* jeu, Strat* mastrat)
 - Strat *creerStrat(char *nom, char *filename, char **tab)
 - Strat **creerListeStrats(char **listenoms,int n)
 - Arme *findWeapon(Jeu *jeu,char *nom)
 - Protection *findProtec(Jeu *jeu, char *nom)
 - Soin *findHeal(Jeu *jeu,char *nom)
 - void equipementStrats(Jeu *jeu)
 - void printAllStrats()
 - void printStrat(int i)
 - void remplirTab()
 - void free_strats()
 - void initStrats(Jeu *jeu)

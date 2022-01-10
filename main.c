#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAB 10 //constante du nombre de lignes et colonnes de la grille de jeu
#define DECAL 49

void clear_screen();

int menu_accueil();

void menu_aide();

void menu_jouer();

void init_coup();

void init_carte();

void afficher_coup();

void afficher_carte();

void demander_coup();

//toutes les déclarations de fonctions ci-dessus sont faites pour être utilisées dans les différentes fonctions qui suivent
int carte[MAX_TAB][MAX_TAB];
char coup_joue[MAX_TAB][MAX_TAB];

void clear_screen() {
#ifdef __unix__
    system("clear");
#elif defined(_WIN32) || defined(WIN32)
    system("cls");
#else
    system("clear");
#endif
}

int menu_accueil() {
    int choix = 0;
    printf("BATAILLE NAVALE\n");
    printf("================\n\n");

    printf("1. Aide\n");
    printf("2. Jouer\n");
    printf("3. Scores\n\n");
    do {
        printf("Votre choix ?\n");
        scanf("%d", &choix);
        if (choix < 1 || choix > 3) {
            printf("Choix impossible ! ");
        }
    } while (choix < 1 || choix > 3);
    switch (choix) {
        case 1:
            menu_aide();
            break;
        case 2:
            menu_jouer();
            break;
        case 3:
            printf("MEILLEURS SCORES\n");
            break;
        default:
            break;
    }
}

int continuer_aide() {
    char interaction_menu;
    int continuer = 1;
    printf("Que souhaitez-vous faire (Pour quitter 'Q', pour continuer les explications 'C')\n");
    fflush(stdin);
    scanf("%c", &interaction_menu);
    continuer = (interaction_menu == 'Q' || interaction_menu == 'q') ? 0 : 1;
}

void menu_aide() {
    char retourner_menu_accueil[3];

    printf("\nAIDE\n");
    printf("=====\n");
    printf("Vous trouverez un tutoriel video via https://www.youtube.com/watch?v=klO6vPWPkzE\n\n");

    printf("Voici quelques regles pour jouer a la Bataille Navale\n\n");

    printf("Vous annoncerez a tour de role une case de la grille que vous souhaitez attaquer\n");
    printf("Vous commencerez par saisir la colonne puis la ligne que vous désirez attaquer\n");
    printf("Lorsque vous ratez votre cible, le jeu annoncera 'Manque'\n");
    printf("Lorsque vous atteignez votre cible, le jeu annoncera 'Touche'\n");
    printf("Lorsque vous abattez votre cible, le jeu annoncera 'Touche-coule'\n");
    printf("Le but du jeu est de couler tous les bateaux de votre adversaire avant que celui-ci ne coule tous les votres\n");
    printf("Vous avez la possibilite de jouer le coup 'Q' pour quitter la partie en cours de route\n\n");
    if (continuer_aide() == 1) {
        printf("Description de la flotte:\n");
        printf("- Un zodiaque de 1 case\n");
        printf("- Une vedette rapide de 2 cases\n");
        printf("- Un croiseur de 3 cases\n");
        printf("- Un cuirasse de 4 cases\n");
        printf("- Un porte-avion de 5 cases\n\n");
        if (continuer_aide() == 1) {
            printf("Positionnement des bateaux:\n");
            printf("- Les bateaux n'ont pas le droit de se toucher sur la grille\n");
            printf("- Un bateau n'a pas le droit de toucher le bord de la grille par plus d'une case\n\n");
        }
    }
    printf("Souhaitez-vous retourner au menu d'accueil (Oui/Non) ?\n");
    fflush(stdin);
    scanf("%s", retourner_menu_accueil);
    if (strcmp(retourner_menu_accueil, "Oui") == 0 || strcmp(retourner_menu_accueil, "oui") == 0) {
        menu_accueil();
    }
}

void menu_jouer() {
    int score = 5;
    char nom_joueur[50];
    int index_col = 0;
    char choix_coup[2];
    char retourner_menu_accueil[3];

    init_carte();
    init_coup();

    printf("JOUER\n");
    printf("=====\n\n");
    printf("Votre nom :");
    fflush(stdin);
    scanf("%s", &nom_joueur);

    do {
        printf("Score : %d\n", score);
        afficher_coup();
        printf("\n");
        //afficher_carte();
        demander_coup(choix_coup);
        printf("\n");

        switch (choix_coup[0]) {
            case 'A':
            case 'a':
                // A représente la colonne 0 du tableau
                index_col = 0;
                break;
            case 'B':
            case 'b':
                index_col = 1;
                break;
            case 'C':
            case 'c':
                index_col = 2;
                break;
            case 'D':
            case 'd':
                index_col = 3;
                break;
            case 'E':
            case 'e':
                index_col = 4;
                break;
            case 'F':
            case 'f':
                index_col = 5;
                break;
            case 'G':
            case 'g':
                index_col = 6;
                break;
            case 'H':
            case 'h':
                index_col = 7;
                break;
            case 'I':
            case 'i':
                index_col = 8;
                break;
            case 'J':
            case 'j':
                index_col = 9;
                break;
            case 'O':
            case 'o':
                menu_aide();
                break;
        }
        if (choix_coup[0] != 'Q' && choix_coup[0] != 'q') {
            int index_ligne = choix_coup[1] - DECAL;
            if (index_ligne == 0) {
                if (choix_coup[2] == '0') {
                    index_ligne = 9;
                }
            }
            if (carte[index_col][index_ligne] == 1) {
                printf("Touche ! \n");
                coup_joue[index_col][index_ligne] = 88;
            } else {
                printf("Manque !\n\n");
                coup_joue[index_col][index_ligne] = 48;
                score--;
            }
        }
    }
    while (choix_coup[0] != 'q' && choix_coup[0] != 'Q' && score > 0);

    if (score < 1) {
        printf("DOMMAGE ! Vous avez perdu !\n\n");
        printf("Souhaitez-vous retourner au menu d'accueil (Oui/Non) ?\n");
        fflush(stdin);
        scanf("%s", retourner_menu_accueil);
        if (strcmp(retourner_menu_accueil, "Oui") == 0 || strcmp(retourner_menu_accueil, "oui") == 0) {
            menu_accueil();
        }
    }
    if (choix_coup[0] == 'q' || choix_coup[0] == 'Q') {
        printf("Souhaitez-vous retourner au menu d'accueil (Oui/Non) ?\n");
        fflush(stdin);
        scanf("%s", retourner_menu_accueil);
        if (strcmp(retourner_menu_accueil, "Oui") == 0 || strcmp(retourner_menu_accueil, "oui") == 0) {
            menu_accueil();
        }
    }
}

void init_carte() {
    carte[1][1] = 1;
    carte[1][3] = 1;
    carte[2][3] = 1;
    carte[1][5] = 1;
    carte[2][5] = 1;
    carte[3][5] = 1;
    carte[1][7] = 1;
    carte[2][7] = 1;
    carte[3][7] = 1;
    carte[4][7] = 1;
    carte[8][0] = 1;
    carte[8][1] = 1;
    carte[8][2] = 1;
    carte[8][3] = 1;
    carte[8][4] = 1;
}

void init_coup() {
    for (int x = 0; x < MAX_TAB; x++) {
        for (int y = 0; y < MAX_TAB; y++) {
            coup_joue[y][x] = 126;
        }
    }
}

void afficher_coup() {
    int index_col = 0;
    printf("     A  B  C  D  E  F  G  H  I  J\n");
    for (int y = 0; y < MAX_TAB; y++) {
        index_col++;
        printf("%3d", index_col);
        for (int x = 0; x < MAX_TAB; x++) {
            printf("%3c", coup_joue[x][y]);
        }
        printf("\n");
    }
}

void afficher_carte() {   //fonction pour afficher la carte du placement des bateaux pour les tests
    for (int x = 0; x < MAX_TAB; x++) {
        for (int y = 0; y < MAX_TAB; y++) {
            printf("%2i ", carte[y][x]);
        }
        printf("\n");
    }
}

void demander_coup(char monchoix[2]) {
    printf("Merci de donner votre choix :");
    fflush(stdin);
    scanf("%s", monchoix);
}

int main(int argc, char *argv[]) {

    menu_accueil();

    return 0;
}
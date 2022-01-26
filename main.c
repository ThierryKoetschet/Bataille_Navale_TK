#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define MAX_TAB 10 //constante du nombre de lignes et colonnes de la grille de jeu
#define DECAL 49 //constante servant à décaler la valeur du coup joué en un entier
#define NOMBRE_CARTE 5 // nombre de cartes différentes qui peuvent être générées
#define NOMBRE_SCORE_MAX 10 //constante du nombre maximum de scores affichables
#define MAX_CHAR_NAME 50 //constante définissant la longueur du nom du joueur

void clear_screen();

int menu_accueil();

void menu_aide();

void menu_jouer();

int test_fin_partie();

void bateau_touche();

int touche_coule();

void init_coup();

void init_carte();

void afficher_coup();

void afficher_carte();

void demander_coup();

void ajouter_joueur();

void imprimer_fichier();

void imprimer_console();

int carte[MAX_TAB][MAX_TAB];
char coup_joue[MAX_TAB][MAX_TAB];
//toutes les déclarations de fonctions ci-dessus sont faites pour être réutilisées dans d'autres fonctions

void clear_screen() {
#ifdef __unix__
    system("clear");
#elif defined(_WIN32) || defined(WIN32)
    system("cls");
#else
    system("clear");
#endif
}//fonction permettant de nettoyer l'écran en fonction du système d'exploitation

int menu_accueil() {
    int choix = 0;
    char retourner_menu_accueil[3];
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
            clear_screen();
            menu_aide();
            break;
        case 2:
            clear_screen();
            menu_jouer();
            break;
        case 3:
            clear_screen();
            printf("MEILLEURS SCORES\n");
            printf("================\n\n");
            imprimer_console();
            printf("\nSouhaitez-vous retourner au menu d'accueil (Oui/Non) ?\n");
            fflush(stdin);
            scanf("%s", retourner_menu_accueil);
            if (strcmp(retourner_menu_accueil, "Oui") == 0 || strcmp(retourner_menu_accueil, "oui") == 0) {
                clear_screen();
                menu_accueil();
            }
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
    printf("Vous trouverez un tutoriel vidéo via https://www.youtube.com/watch?v=klO6vPWPkzE\n\n");

    printf("Voici quelques règles pour jouer à la Bataille Navale\n\n");

    printf("Vous annoncerez à tour de role une case de la grille que vous souhaitez attaquer\n");
    printf("Vous commencerez par saisir la colonne puis la ligne que vous désirez attaquer\n");
    printf("Lorsque vous ratez votre cible, le jeu annoncera 'MANQUE !' et un 0 apparaîtra sur la grille de jeu\n");
    printf("Lorsque vous atteignez votre cible, le jeu annoncera 'TOUCHE !' et un X apparaîtra sur la grille de jeu\n");
    printf("Lorsque vous abattez votre cible, le jeu annoncera 'TOUCHE-COULE !' un # apparaitra sur la grille de jeu\n");
    printf("Le but du jeu est de couler tous les bateaux de votre adversaire avant que celui-ci ne coule tous les votres\n");
    printf("Vous avez la possibilité de jouer le coup 'Q' pour quitter la partie en cours de jeu\n\n");
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
        clear_screen();
        menu_accueil();
    }
}

void menu_jouer() {
    int score = 50;
    char nom_joueur[50];
    int index_col = 0;
    char choix_coup[2];
    char retourner_menu_accueil[3];

    init_carte(); //initialisation de la carte et du coup à 0
    init_coup(); //

    printf("JOUER\n");
    printf("=====\n\n");
    printf("Votre nom :");
    fflush(stdin);
    scanf("%s", &nom_joueur);

    do {
        printf("Score : %d\n", score);
        afficher_coup();
        printf("\n");
        demander_coup(choix_coup);
        printf("\n");
        clear_screen();

        switch (choix_coup[0]) {
            case 'A':
            case 'a':
                // A représente la colonne 0 du tableau et ainsi de suite
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
            case 'Q':
            case 'q':
                printf("\nSouhaitez-vous retourner au menu d'accueil (Oui/Non) ?\n");
                fflush(stdin);
                scanf("%s", retourner_menu_accueil);
                if (strcmp(retourner_menu_accueil, "Oui") == 0 || strcmp(retourner_menu_accueil, "oui") == 0) {
                    clear_screen();
                    menu_accueil();
                }
                break;
        }
        if (choix_coup[0] != 'Q' && choix_coup[0] != 'q') {
            int index_ligne = choix_coup[1] - DECAL;
            if (index_ligne == 0) {
                if (choix_coup[2] == '0') {
                    index_ligne = 9;
                }
            }
            if (carte[index_col][index_ligne] >= 1) {
                bateau_touche(carte[index_col][index_ligne], index_ligne, index_col);
            }
            else {
                printf("MANQUE !\n");
                coup_joue[index_col][index_ligne] = 48;
                score--;
            }
        }
        test_fin_partie();
    } while (score > 0 && test_fin_partie() < 5);

    if (score >= 1) {
        printf("Score : %d\n", score);
        afficher_coup();
        printf("\nBRAVO ! Vous avez gagné !\n\n");

        FILE *fp;

        fp = fopen("scores.txt", "w+");

        if(fp == NULL) {
            printf("Impossible d'ouvrir le fichier\n");
            exit(1);
        }

        fflush(stdin);

        ajouter_joueur(nom_joueur,score);
        imprimer_fichier(fp);


        fclose(fp);

        printf("Souhaitez-vous retourner au menu d'accueil (Oui/Non) ?\n");
        fflush(stdin);
        scanf("%s", retourner_menu_accueil);
        if (strcmp(retourner_menu_accueil, "Oui") == 0 || strcmp(retourner_menu_accueil, "oui") == 0) {
            clear_screen();
            menu_accueil();
        }
    }
    if (score < 1) {
        printf("\nDOMMAGE ! Vous avez perdu !\n\n");
        printf("Souhaitez-vous retourner au menu d'accueil (Oui/Non) ?\n");
        fflush(stdin);
        scanf("%s", retourner_menu_accueil);
        if (strcmp(retourner_menu_accueil, "Oui") == 0 || strcmp(retourner_menu_accueil, "oui") == 0) {
            clear_screen();
            menu_accueil();
        }
    }
}

int test_fin_partie() {
    int test = 0;

    for (int y = 0; y < MAX_TAB; y++) {
        for (int x = 0; x < MAX_TAB; x++) {
            if (coup_joue[x][y] == 35) {
                test++;
            }
        }
    }
    return test;
}

void bateau_touche(int valeur, int ligne, int colonne) {
    switch (valeur) {
        case 100:
            coup_joue[colonne][ligne] = 35;
            printf("\nTOUCHE-COULE !\n");
            break;
        case 200:
            carte[colonne][ligne] = 210;
            if (touche_coule(valeur) == 0) {
                coup_joue[colonne][ligne] = 35;
                printf("\nTOUCHE-COULE !\n");
            } else {
                coup_joue[colonne][ligne] = 88;
                printf("\nTOUCHE !\n");
            }
            break;
        case 300:
            carte[colonne][ligne] = 310;
            if (touche_coule(valeur) == 0) {
                coup_joue[colonne][ligne] = 35;
                printf("\nTOUCHE-COULE !\n");
            } else {
                coup_joue[colonne][ligne] = 88;
                printf("\nTOUCHE !\n");
            }
            break;
        case 400:
            carte[colonne][ligne] = 410;
            if (touche_coule(valeur) == 0) {
                coup_joue[colonne][ligne] = 35;
                printf("\nTOUCHE-COULE !\n");
            } else {
                coup_joue[colonne][ligne] = 88;
                printf("\nTOUCHE !\n");
            }
            break;
        case 500:
            carte[colonne][ligne] = 510;
            if (touche_coule(valeur) == 0) {
                coup_joue[colonne][ligne] = 35;
                printf("\nTOUCHE-COULE !\n");
            } else {
                coup_joue[colonne][ligne] = 88;
                printf("\nTOUCHE !\n");
            }
            break;
    }
}

int touche_coule(int valeur) {
    int retour = 0;

    for (int y = 0; y < MAX_TAB; y++) {
        for (int x = 0; x < MAX_TAB; x++) {
            if (carte[x][y] == valeur) {
                retour++;
            }
        }
    }
    return retour;
}

void init_carte() {
    for (int x = 0; x<MAX_TAB; x++) {
        for (int y = 0; y<MAX_TAB; y++) {
            carte[x][y] = 0;
        }
    }

    int r = rand() % NOMBRE_CARTE;

    printf("SALUT");

    switch (r) {
        case 0:
            carte[1][1] = 100;
            carte[1][3] = 200;
            carte[2][3] = 200;
            carte[1][5] = 300;
            carte[2][5] = 300;
            carte[3][5] = 300;
            carte[1][7] = 400;
            carte[2][7] = 400;
            carte[3][7] = 400;
            carte[4][7] = 400;
            carte[8][0] = 500;
            carte[8][1] = 500;
            carte[8][2] = 500;
            carte[8][3] = 500;
            carte[8][4] = 500;
            break;
        case 1:
            carte[7][7] = 100;
            carte[2][5] = 200;
            carte[2][6] = 200;
            carte[1][1] = 300;
            carte[1][2] = 300;
            carte[1][3] = 300;
            carte[9][5] = 400;
            carte[9][6] = 400;
            carte[9][7] = 400;
            carte[9][8] = 400;
            carte[4][8] = 500;
            carte[5][8] = 500;
            carte[6][8] = 500;
            carte[7][8] = 500;
            carte[8][8] = 500;
            break;
        case 2:
            carte[7][6] = 100;
            carte[9][5] = 200;
            carte[9][6] = 200;
            carte[6][4] = 300;
            carte[7][4] = 300;
            carte[8][4] = 300;
            carte[3][4] = 400;
            carte[3][5] = 400;
            carte[3][6] = 400;
            carte[3][7] = 400;
            carte[0][5] = 500;
            carte[0][6] = 500;
            carte[0][7] = 500;
            carte[0][8] = 500;
            carte[0][9] = 500;
            break;
        case 3:
            carte[9][2] = 100;
            carte[1][8] = 200;
            carte[1][9] = 200;
            carte[1][2] = 300;
            carte[2][2] = 300;
            carte[3][2] = 300;
            carte[5][2] = 400;
            carte[5][3] = 400;
            carte[5][4] = 400;
            carte[5][5] = 400;
            carte[3][5] = 500;
            carte[3][6] = 500;
            carte[3][7] = 500;
            carte[3][8] = 500;
            carte[3][9] = 500;
            break;
        case 4:
            carte[2][8] = 100;
            carte[8][3] = 200;
            carte[8][4] = 200;
            carte[2][4] = 300;
            carte[2][5] = 300;
            carte[2][6] = 300;
            carte[4][0] = 400;
            carte[5][0] = 400;
            carte[6][0] = 400;
            carte[7][0] = 400;
            carte[0][3] = 500;
            carte[0][4] = 500;
            carte[0][5] = 500;
            carte[0][6] = 500;
            carte[0][7] = 500;
            break;
        default:
            break;
    }
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

typedef struct{
    int score;
    char nom[MAX_CHAR_NAME];
} t_score;
t_score scores[NOMBRE_SCORE_MAX] = {0,0};

void ajouter_joueur(char nom[MAX_CHAR_NAME] , int score) {

}

void imprimer_fichier(FILE *fp) {
    for (int i = 0; i < NOMBRE_SCORE_MAX; i++) {
        fprintf(fp, "Nom: %s\t score: %d \n", scores[i].nom, scores[i].score);
    }
}

void imprimer_console() {
    int buffer_size = 1000;
    char buffer[buffer_size];
    int totalRead;

    FILE *fp;
    fp = fopen("scores.txt", "r");

    if(fp == NULL)
    {
        printf("Ouverture du fichier impossible.\n");
        exit(EXIT_FAILURE);
    }

    while(fgets(buffer, buffer_size, fp) != NULL)
    {
        totalRead = strlen(buffer);
        buffer[totalRead - 1] = buffer[totalRead - 1] == '\n' ? '\0' : buffer[totalRead - 1];
        printf("%s\n", buffer);
    }
    fclose(fp);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    SetConsoleOutputCP(65001);

    menu_accueil();

    return 0;
}
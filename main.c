#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct joueurs {
    char nom[256];
}joueurs;

void clear() {
    // Clear pour Windows
    #ifdef _WIN32
    system("cls");
    #endif
    // Clear pour Linux
    #ifdef linux
    system("clear");
    #endif
}

void couleur(int couleurDuTexte) {
    /*
        Liste des couleurs :
        0  reset
        91 rouge clair
        93 jaune clair
        94 bleu
    */
    printf("\033[0;%dm", couleurDuTexte);
}

int askTypePartie() {
    // Définie si la partie est en mode JcJ ou IA
    clear();
    int rep;
    do {
        printf("Sélectionnez votre type de partie\n(1) JcJ\n(2) IA\n\n> ");
        scanf("%i", &rep);

    } while (rep < 0 || rep > 1);
    return rep;
}

void nomJoueurs(int partieJcJIA[], joueurs j[]) {
    clear();
    if (partieJcJIA[0] == 1) {
        printf("Nom de l'équipe ");
        couleur(93);
        printf("jaune : ");
        while ((getchar()) != '\n');
        fgets(j[0].nom, sizeof(j[0].nom), stdin);
        j[0].nom[strcspn(j[0].nom, "\n")] = 0;
        couleur(33);
        printf("\nNom de l'équipe ");
        couleur(91);
        printf("rouge : ");
        fgets(j[1].nom, sizeof(j[1].nom), stdin);
        j[1].nom[strcspn(j[1].nom, "\n")] = 0;
        couleur(33);
    } else {
        printf("Nom de l'équipe ");
        couleur(93);
        printf("jaune : ");
        while ((getchar()) != '\n');
        fgets(j[0].nom, sizeof(j[0].nom), stdin);
        j[0].nom[strcspn(j[0].nom, "\n")] = 0;
        couleur(33);
    }
}

void initPlateau(int plateau[][7]) {
    // Initialisation du plateau pour une nouvelle partie
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            plateau[i][j] = 0;
        }
    }
    // 0 équivaut à une case libre, 1 à une case remplie de jaune, 2 à une case remplie de rouge
}

void affichagePlateau(int plateau[][7]) {
    couleur(33);
    printf("  1 2 3 4 5 6 7\n");
    printf("  +-+-+-+-+-+-+\n");
    for (int i = 0; i < 6; i++) {
        printf("%c", 'A' + i);
        for (int j = 0; j < 7; j++) {
            if (plateau[i][j] == 1) {
                couleur(33);
                printf("|");
                couleur(93);
                printf("O");
            } else if (plateau[i][j] == 2) {
                couleur(33);
                printf("|");
                couleur(91);
                printf("O");
            } else {
                couleur(33);
                printf("| ");
            }
        }
        couleur(33);
        printf("|\n");
        printf("  +-+-+-+-+-+-+\n");
    }
}

void boucleJeu(int plateau[][7], joueurs j[], int enCoursDeJeu[], int partieJcJIA[]) {
    int retourmenu = 0, win = 0, tourJoueur = 1, cordX, cordY;
    do {
        if (tourJoueur == 3) tourJoueur = 1;
        while ((getchar()) != '\n');
        clear();
        couleur(33);
        affichagePlateau(plateau);
        printf("\n\nAu tour du joueur ");
        if (tourJoueur == 1) {
            couleur(93);
            printf("%s", j[0].nom);
        } else {
            couleur(91);
            printf("%s", j[1].nom);
        }
        couleur(33);
        printf(" !");
        do {
            printf("\n\nSélectionnez votre colonne (1 2 3 4 5 6 7) : ");
            scanf("%i", &cordX);
            cordX--;
        } while ((cordX < 0 || cordX > 6 ) || plateau[0][cordX] != 0);
        cordY = 5;
        while (cordY > -1) {
            if (plateau[cordY][cordX] == 0) {
                if (tourJoueur == 1) {
                    plateau[cordY][cordX] = 1;
                }
                else {
                    plateau[cordY][cordX] = 2;
                }
                break;
            }
            cordY--;
        }
        tourJoueur++;
    } while (win == 0 && retourmenu == 0);
}

void menu(int plateau[][7], joueurs j[], int enCoursDeJeu[], int partieJcJIA[]) {
    int rep;
    do {
        couleur(94);
        printf("=========================================\n               PUISSANCE 4\n=========================================\n\n");
        couleur(33);
        printf("1. Nouvelle partie\n2. Charger une partie\n3. Quitter le jeu\n");
        printf("\n> ");
        scanf("%i", &rep);
        switch (rep) {
            case 1:
                partieJcJIA[0] = askTypePartie();
                nomJoueurs(partieJcJIA, j);
                enCoursDeJeu[0] = 1;
                boucleJeu(plateau, j, enCoursDeJeu, partieJcJIA);
                break;
            case 2:
                break;
            case 3:
                exit(0);
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                clear();
                break;
        }
    } while (rep < 1 || rep > 5);
    couleur(0);
}

int main() {
    int plateau[6][7], enCoursDeJeu[1], partieJcJIA[1];
    joueurs j[2]; // Déclaration des joueurs (2 max)
    initPlateau(plateau);
    clear();
    menu(plateau, j, enCoursDeJeu, partieJcJIA);
}

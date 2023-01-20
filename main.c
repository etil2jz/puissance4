#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

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

int verifVictoire(int plateau[][7], int joueur[]) {
    // Vérification des lignes
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7 - 3; j++) {
            if (plateau[i][j] == joueur[0] && plateau[i][j + 1] == joueur[0] && plateau[i][j + 2] == joueur[0] && plateau[i][j + 3] == joueur[0]) return joueur[0];
        }
    }

    // Vérification des colonnes
    for (int i = 0; i < 6 - 3; i++) {
        for (int j = 0; j < 7; j++) {
            if (plateau[i][j] == joueur[0] && plateau[i + 1][j] == joueur[0] && plateau[i + 2][j] == joueur[0] && plateau[i + 3][j] == joueur[0]) return joueur[0];
        }
    }

    // Vérification des diagonales de gauche à droite
    for (int i = 0; i < 6 - 3; i++) {
        for (int j = 0; j < 7 - 3; j++) {
            if (plateau[i][j] == joueur[0] && plateau[i + 1][j + 1] == joueur[0] && plateau[i + 2][j + 2] == joueur[0] && plateau[i + 3][j + 3] == joueur[0]) return joueur[0]; 
        }
    }

    // Vérification des diagonales de droite à gauche
    for (int i = 0; i < 6 - 3; i++) {
        for (int j = 0; j < 7; j++) {
            if (plateau[i][j] == joueur[0] && plateau[i + 1][j - 1] == joueur[0] && plateau[i + 2][j - 2] == joueur[0] && plateau[i + 3][j - 3] == joueur[0]) return joueur[0];
        }
    }

    return 0; // Pas de victoire
}

void writeSauvegarde(int plateau[][7], joueurs j[], int enCoursDeJeu[], int partieJcJIA[], int tourJoueur[]) {
    FILE * sauvegarde; // Erreur de segmentation - à corriger
    sauvegarde = fopen("sauvegarde.esiee", "w");
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            fprintf(sauvegarde, "%i\n", plateau[i][j]);
        }
    }
    fprintf(sauvegarde, "j[0].nom=%s\nj[1].nom=%s\nenCoursDeJeu[0]=%i\npartieJcJIA[0]=%i\ntourJoueur[0]=%i\n", j[0].nom, j[1].nom, enCoursDeJeu[0], partieJcJIA[0], tourJoueur[0]);
    fclose(sauvegarde);
}

void readSauvegarde(int plateau[][7], joueurs j[], int enCoursDeJeu[], int partieJcJIA[], int tourJoueur[]) {
    FILE * sauvegarde = NULL;
    sauvegarde = fopen("sauvegarde.esiee", "r");
    if (sauvegarde == NULL) printf("\nAucune sauvegarde détectée dans le dossier du jeu\nFermeture...");
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            fscanf(sauvegarde, "%i\n", &plateau[i][j]);
        }
    }
    fscanf(sauvegarde, "j[0].nom=%s\nj[1].nom=%s\nenCoursDeJeu[0]=%i\npartieJcJIA[0]=%i\ntourJoueur[0]=%i\n", &j[0].nom, &j[1].nom, &enCoursDeJeu[0], &partieJcJIA[0], &tourJoueur[0]);
    fclose(sauvegarde);
}

void boucleJeu(int plateau[][7], joueurs j[], int enCoursDeJeu[], int partieJcJIA[], int tourJoueur[]) {
    int retourmenu = 0, win = 0, cordX, cordY;
    tourJoueur[0] = 1;
    do {
        if (tourJoueur[0] == 3) tourJoueur[0] = 1;
        while ((getchar()) != '\n');
        clear();
        couleur(33);
        affichagePlateau(plateau);
        printf("\n\nAu tour du joueur ");
        if (tourJoueur[0] == 1) {
            couleur(93);
            printf("%s", j[0].nom);
        } else {
            couleur(91);
            printf("%s", j[1].nom);
        }
        couleur(33);
        printf(" !");
        do {
            printf("\n\nSélectionnez votre colonne (1 2 3 4 5 6 7)\n> ");
            scanf("%i", &cordX);
            cordX--;
        } while ((cordX < 0 || cordX > 7 ) || plateau[0][cordX] != 0);
        cordY = 5;
        while (cordY > -1) {
            if (plateau[cordY][cordX] == 0) {
                if (tourJoueur[0] == 1) {
                    plateau[cordY][cordX] = 1;
                }
                else {
                    plateau[cordY][cordX] = 2;
                }
                break;
            }
            cordY--;
        }
        win = verifVictoire(plateau, tourJoueur);
        if (win != 0) break;
        tourJoueur[0]++;
        clear();
        affichagePlateau(plateau);
        if (cordX == 7) {
            clear();
            couleur(94);
            printf("=========================================\n               PUISSANCE 4\n=========================================\n\n");
            couleur(33);
            printf("1. Reprendre la partie\n2. Sauvegarder la partie\n3. Quitter le jeu\n\n> ");
            scanf("%i", &retourmenu);
            switch (retourmenu) {
                case 1: break;
                case 2: writeSauvegarde(plateau, j, enCoursDeJeu, partieJcJIA, tourJoueur);
                        break;
                case 3: exit(0);
                        break;
            }
        }
    } while (win == 0);
    if(win==1)printf("Bravo %s tu as gagné !\n",j[0].nom);
    if(win==2)printf("Bravo %s tu as gagné !\n",j[1].nom);
    Sleep(2000);
    clear();
}

void menu(int plateau[][7], joueurs j[], int enCoursDeJeu[], int partieJcJIA[]) {
    int rep, tourJoueur[1];
    enCoursDeJeu[0] = 0;
    do {
        couleur(94);
        printf("=========================================\n               PUISSANCE 4\n=========================================\n\n");
        couleur(33);
        printf("1. Nouvelle partie\n2. Charger une partie\n3. Quitter le jeu\n");
        printf("\n> ");
        scanf("%i", &rep);
        switch (rep) {
            case 1:
                initPlateau(plateau);
                partieJcJIA[0] = askTypePartie();
                nomJoueurs(partieJcJIA, j);
                enCoursDeJeu[0] = 1;
                boucleJeu(plateau,  j, enCoursDeJeu, partieJcJIA, tourJoueur);
                break;
            case 2:
                readSauvegarde(plateau, j, enCoursDeJeu, partieJcJIA, tourJoueur);
                boucleJeu(plateau, j, enCoursDeJeu, partieJcJIA, tourJoueur);
                break;
            case 3:
                exit(0);
                break;
            default:
                clear();
                break;
        }
    } while (1);
    couleur(0);
}

int main() {
    int plateau[6][7], enCoursDeJeu[1], partieJcJIA[1];
    joueurs j[2]; // Déclaration des joueurs (2 max)
    clear();
    menu(plateau, j, enCoursDeJeu, partieJcJIA);
}

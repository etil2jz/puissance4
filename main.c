#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
    #include <windows.h>
#endif

typedef struct joueurs {
    char nom[128];
}joueurs;

void clear() {
    #ifdef _WIN32
        // Clear pour Windows
        system("cls");
    #else
        // Clear pour Linux
        system("clear");
    #endif
}

void sleep(int seconds) {
    #ifdef _WIN32
        // Sleep pour Windows
        Sleep(seconds * 1000);
    #else
        // Sleep pour Linux
        struct timespec ts;
        ts.tv_sec = seconds;
        ts.tv_nsec = 0;
        nanosleep(&ts, NULL);
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

    } while (rep < 0 || rep > 2);
    return rep;
}

void nomJoueurs(int partieJcJIA[], joueurs j[]) {
    clear();
    if (partieJcJIA[0] == 1) {
        printf("Nom de l'équipe ");
        couleur(93);
        printf("jaune : ");
        //fgets // il faut trouver un moyen de faire fonctionner fgets, qu'importe la situation
        fgets(j[0].nom, sizeof(j[0].nom), stdin);
        fgets(j[0].nom, sizeof(j[0].nom), stdin);
        strtok(j[0].nom, "\n");
        couleur(33);
        printf("\nNom de l'équipe ");
        couleur(91);
        printf("rouge : ");
        //fgets // il faut trouver un moyen de faire fonctionner fgets, qu'importe la situation
        fgets(j[1].nom, sizeof(j[1].nom), stdin);
        strtok(j[1].nom, "\n");
    } else {
        printf("Nom de l'équipe ");
        couleur(93);
        printf("jaune : ");
        //fgets // il faut trouver un moyen de faire fonctionner fgets, qu'importe la situation
        fgets(j[0].nom, sizeof(j[0].nom), stdin);
        fgets(j[0].nom, sizeof(j[0].nom), stdin);
        strtok(j[0].nom, "\n");
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

void tourOrdinateur(int plateau[][7]) {
    // Modifier la seed du générateur pseudo-aléatoire
    srand(time(NULL));

    // Choisir une colonne au hasard entre 1 et 7 (0 et 6 pour le tableau)
    int colonne = rand() % 7;

    // Vérifier la disponibilité de la colonne et jouer le tour
    while (plateau[0][colonne] != 0) {
        colonne = rand() % 7;
    }
    for (int i = 5; i >= 0; i--) {
        if (plateau[i][colonne] == 0) {
            plateau[i][colonne] = 2;
            break;
        }
    }
}

void writeSauvegarde(int plateau[][7], joueurs j[], int enCoursDeJeu[], int partieJcJIA[], int tourJoueur[]) {
    FILE * sauvegarde;
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
    if (sauvegarde == NULL) {
        printf("\nAucune sauvegarde détectée dans le dossier du jeu\nFermeture...");
        exit(0);
    }
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
        clear();
        couleur(33);
        affichagePlateau(plateau);
        if (partieJcJIA[0] == 1 || partieJcJIA[0] == 2 && tourJoueur[0] == 1) printf("\n\nAu tour du joueur ");
        if (tourJoueur[0] == 1) {
            couleur(93);
            printf("%s", j[0].nom);
        } else if (partieJcJIA[0] == 2) {

        } else {
            couleur(91);
            printf("%s", j[1].nom);
        }
        couleur(33);
        if (partieJcJIA[0] == 1 || partieJcJIA[0] == 2 && tourJoueur[0] == 1) printf(" !");
        if (tourJoueur[0] == 2 && partieJcJIA[0] == 2) {
            tourOrdinateur(plateau);
            sleep(1);
        }
        if (partieJcJIA[0] == 1 || partieJcJIA[0] == 2 && tourJoueur[0] == 1) {
            do {
                printf("\n\nSélectionnez votre colonne (1 2 3 4 5 6 7)\t\t[8 pour afficher le menu]\n> ");
                scanf("%i", &cordX);
                cordX--;
            } while ((cordX < 0 || cordX > 7 ) || plateau[0][cordX] != 0);
            if (cordX != 7) {
                cordY = 5;
                while (cordY > -1) {
                    if (plateau[cordY][cordX] == 0) {
                        if (tourJoueur[0] == 1) {
                            plateau[cordY][cordX] = 1;
                        } else {
                            plateau[cordY][cordX] = 2;
                        }
                        break;
                    }
                    cordY--;
                }
            }
        }
        if (cordX != 7) {
            win = verifVictoire(plateau, tourJoueur);
            if (win != 0) break;
            tourJoueur[0]++;
            clear();
            affichagePlateau(plateau);
        } else {
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
                case 3: clear();
                        exit(0);
                        break;
            }
        }
    } while (win == 0);
    clear();
    affichagePlateau(plateau);
    if (win == 1) {
        printf("\n\nFélicitations %s, tu es le plus fort !", j[0].nom);
    } else if (win == 2 && partieJcJIA[0] == 1) {
        printf("\n\nFélicitations %s, tu es le plus fort !", j[1].nom);
    } else {
        printf("\n\nTu t'es fait battre par une IA à base de fonctions rand() ...");
    }
    sleep(5);
    clear();
}

void menu(int plateau[][7], joueurs j[], int enCoursDeJeu[], int partieJcJIA[]) {
    int rep, tourJoueur[1];
    do {
        enCoursDeJeu[0] = 0;
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
                clear();
                exit(0);
                break;
            default:
                clear();
                break;
        }
    } while (rep < 1 || rep > 5 || enCoursDeJeu[0] == 1);
    couleur(0);
}

int main() {
    int plateau[6][7], enCoursDeJeu[1], partieJcJIA[1];
    joueurs j[2]; // Déclaration des joueurs (2 max)
    clear();
    menu(plateau, j, enCoursDeJeu, partieJcJIA);
    return 0;
}

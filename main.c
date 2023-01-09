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

    } while (rep < 1 || rep > 2);
    return rep;
}

void nomJoueurs(int partieVsIA[], joueurs j[]) {
    clear();
    if (partieVsIA[0] == 1) {
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
        while ((getchar()) != '\n');
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
}

void placement(int plateau[][7],int bcl){
    int a
    printf("Choisissez la colonne ou vous souhaitez poser votre pion.\n");
    scanf("%i",&a);
    for (int b=6,b>0;b--){
        if( plateau[a][b]==0){
            if(bcl==1)plateau[a][b]=1;
            if(bcl==2)plateau[a][b]=2;
            break;
        }
    }
}

void affichagePlateau(int plateau[][7]) {
    
}

void menu(int plateau[][7], joueurs j[], int enCoursDeJeu[], int partieVsIA[]) {
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
                partieVsIA[0] = askTypePartie();
                nomJoueurs(partieVsIA, j);
                enCoursDeJeu[0] = 1;
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
    int plateau[6][7], enCoursDeJeu=0, partieVsIA[1],int victoire=0;
    joueurs j[2]; // Déclaration des joueurs (2 max)
    initPlateau(plateau);
    clear();
   // menu(plateau, j, enCoursDeJeu, partieVsIA);
   do{
    enCoursDeJeu++;
    if(enCoursDeJeu==3)enCoursDeJeu=1;
   placement(plateau,enCoursDeJeu);
   affichagePlateau(plateau);
   }while (victoire==0);
   
   

}

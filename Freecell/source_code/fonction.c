#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "fonction.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define HEART "\u2665"
#define DIAMOND "\u2666"
#define CLUB "\u2663"
#define SPADE "\u2660"

#ifdef _WIN32
#define PAUSE(milliseconds) Sleep(milliseconds)
#endif

/** Fonctions pour manipuler les piles **/
// Fontion pour creer une pile
Pile *createPile(){
    Pile *newPile = (Pile *)malloc(sizeof(Pile));
    newPile->top = NULL;
    newPile->size = 0;
    return newPile;
}
// Fonction pour empiler une carte
void pushCard(Pile *pile, Carte *card) {
    Element *newElement = (Element *)malloc(sizeof(Element));
    newElement->card = card;
    newElement->next = pile->top;
    pile->top = newElement;
    pile->size++;
}
// Fonction pour depiler une carte
Carte *popCard(Pile *pile) {
    if (pile->size == 0) {
        return NULL;  // Pile est vide
    }
    Element *topElement = pile->top;
    Carte *topCard = topElement->card;
    pile->top = topElement->next;
    free(topElement);
    pile->size--;
    return topCard;
}
// Fonction pour verifier si une pile est vide
int isEmpty(Pile *pile) {
    return (pile == NULL || pile->top == NULL);
}
// Fonction pour retourner peek de pile
Carte *peekCard(Pile *pile) {
    if (pile->size == 0) {
        return NULL;  // Pile est vide
    }
    return pile->top->card;
}
//
Carte *peekCardAtLevel(Pile *pile, int level) {
    Element *current = pile->top;
    for (int i = 0; i < level; i++) {
        current = current->next;
    }
    return current->card;
}
/**======================================================================**/

/** des fonction d'affichage **/
// Fonction pour la couleur d'ecriture et d'arriere plan
void color(int t, int f){
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, f * 16 + t);
}
// Fonction qui fait "refresh" de l'affichage
void effacerEcran() {
    system("cls");
}
// Fonction pour afficher message erreur en rouge
void afficherErreurAvecPause(const char *message, int dureeEnMillisecondes) {
    printf(ANSI_COLOR_RED "Erreur: %s\n" ANSI_COLOR_RESET, message);
    PAUSE(dureeEnMillisecondes);
    color(15,18);
}
/**======================================================================**/

/** Manipulation des cartes **/
// Fonction pour afficher les symboles de jeu de carte
void printCardSymbol(const char *type) {
    if (strcmp(type, "P") == 0) {
        printf("%s ", CLUB);
    } else if (strcmp(type, "D") == 0) {
        printf("%s ", DIAMOND);
    } else if (strcmp(type, "C") == 0) {
        printf("%s ", HEART);
    } else if (strcmp(type, "T") == 0) {
        printf("%s ", SPADE);
    }
}
// Fonction pour afficher la carte
void printCard(Carte *card) {
    if (card == NULL) {
        printf("Carte invalide\n");
        return;
    }
    // Definir les codes ANSI pour les couleurs
    const char *resetColor = "\033[0m";
    const char *whiteBackground = "\033[47m";
    const char *redText = "\033[91m";
    const char *blackText = "\033[30m";
    // Choisir la couleur en fonction du type de carte
    const char *cardColor;
    if (card->type[0] == 'C' || card->type[0] == 'D') {
        cardColor = redText; // Rouge pour coeur et carreau
    } else {
        cardColor = blackText; // Noir pour pique et trefle
    }
    // Imprimer la carte avec le symbole defini
    switch (*(card->value)) {
        case 1:
            printf("%s%s A  ", whiteBackground, cardColor);
            printCardSymbol(card->type);
            printf("%s%s", resetColor, resetColor);
            color(15, 18);
            printf(" ");
            break;
        case 10 :
            printf("%s%s 10 ", whiteBackground, cardColor);
            printCardSymbol(card->type);
            printf("%s%s", resetColor, resetColor);
            color(15, 18);
            printf(" ");
            break;
        case 11:
            printf("%s%s J  ", whiteBackground, cardColor);
            printCardSymbol(card->type);
            printf("%s%s", resetColor, resetColor);
            color(15, 18);
            printf(" ");
            break;
        case 12:
            printf("%s%s Q  ", whiteBackground, cardColor);
            printCardSymbol(card->type);
            printf("%s%s", resetColor, resetColor);
            color(15, 18);
            printf(" ");
            break;
        case 13:
            printf("%s%s K  ", whiteBackground, cardColor);
            printCardSymbol(card->type);
            printf("%s%s", resetColor, resetColor);
             color(15, 18);
            printf(" ");
            break;
        default:
            printf("%s%s %d  ", whiteBackground, cardColor, *(card->value));
            printCardSymbol(card->type);
            printf("%s%s", resetColor, resetColor);
            color(15, 18);
            printf(" ");
            break;
    }
}
/**======================================================================**/

/** Fonctions pour manipuler le plateau de jeu**/
// Fonction pour reserver l'espace memoire de la table (creer la table)
Board *initializeBoard() {
    Board *gameBoard = (Board *)malloc(sizeof(Board));
    for (int i = 0; i < 8; i++) {
        gameBoard->zone1[i] = createPile();
    }
    for (int i = 0; i < 4; i++) {
        gameBoard->zone2[i] = createPile();
        gameBoard->zone3[i] = createPile();
    }
    return gameBoard;
}
// Fonction pour creer la carte
Carte *createCard(int value, const char *type) {
    Carte *newCard = (Carte *)malloc(sizeof(Carte));
    newCard->value = (int *)malloc(sizeof(int));
    *(newCard->value) = value;
    newCard->type = strdup(type); //strdup : reserve la memoire et copie le contenu de la chaine retourne un pointeur
    return newCard;
}
// Fonction pour remplire les piles des cartes
void remplirPiles(Board *gameBoard) {
    srand((unsigned int)time(NULL)); // Initialisation du generateur de nombres aleatoires
    // Creer et initialiser les valeurs et types pour chaque couleur
    const char *types[4] = { "C", "P", "D", "T" }; // C pour coeur P pour pique D pour Carreau T pour trefle
    int values[13] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
    // Creer un tableau pour stocker toutes les cartes
    Carte *allCards[52];
    int index = 0;
    // Ajouter toutes les cartes dans le tableau
    for (int suit = 0; suit < 4; suit++) {
        for (int value = 0; value < 13; value++) {
            allCards[index++] = createCard(values[value], types[suit]);
        }
    }
    /* Melanger les cartes dans le tableau en utilisant l'algorithme de melange */ /**Fisher-Yates**/
    for (int i = 51; i > 0; i--) {
        int j = rand() % (i + 1);
        Carte *temp = allCards[i];
        allCards[i] = allCards[j];
        allCards[j] = temp;
    }
    // Ajouter les cartes melangees aux piles du plateau de jeu
    index = 0;
    for (int col = 0; col < 8; col++) {
        int cardsToAdd = (col < 4) ? 7 : 6; // Determiner le nombre de cartes a ajouter a chaque pile
        for (int i = 0; i < cardsToAdd; i++) {
            pushCard(gameBoard->zone1[col], allCards[index++]);
        }
    }
}
// Fonction pour afficher verticalement les cartes sous forme de colonne
void printVertically(Pile *pile) {
    Element *current = pile->top;
    // Stocker les elements dans un tableau temporaire
    Carte *cards[12];
    int count = 0;
    while (current != NULL && count < 12) {
        cards[count++] = current->card;
        current = current->next;
    }
    // Afficher chaque carte de la pile verticalement dans l'ordre inverse
    for (int i = count - 1; i >= 0; i--) {
             color(15, 18);
        printCard(cards[i]);
        printf("\n");
    }
    printf(" ");
}
//affichage du Board
void printBoard(Board *gameBoard) {
     printf("\n========================================={ FreeCell Game BY HAMZA BOUDA }===============================================\n\n");
    // Afficher les numeros de colonne pour Zone 2 et Zone 3
    printf("\n---------------------| Zone 2 (FREECELLS) |-------------------------------------| Zone 3 (Foundation) |-----------------\n\n");
    printf("                    9       10       11       12                             13       14       15       16 \n\n");
    printf("                 ");
        // Afficher les cartes de Zone 2
        for (int col = 0; col < 4; col++) {
            Pile *currentColumn = gameBoard->zone2[col];
            if (0 < currentColumn->size) {
                printCard(peekCard(currentColumn));
            } else {
                // Utiliser des espaces pour maintenir la largeur
                printf("       ");
            }
            printf("  ");
        }
        // Ajouter des espaces entre Zone 2 et Zone 3
        printf("                      ");
        // Afficher les cartes de Zone 3
        for (int col = 0; col < 4; col++) {
            Pile *currentColumn = gameBoard->zone3[col];
            if (0< currentColumn->size) {
                printCard(peekCard(currentColumn));
            } else {
                // Utiliser des espaces pour maintenir la largeur
                printf("       ");
            }
            printf("  ");
        }
        printf("\n");
    printf("\n------------------------------------------------------| Zone 1 |--------------------------------------------------------\n\n");
    // Afficher les numeros de colonne  pour Zone 1
    printf("                      ");
    for (int i = 0; i < 8; i++) {
        printf("   %d     ", i + 1);
    }
    printf("\n\n");
    // Trouver la hauteur maximale parmi toutes les colonnes de Zone 1
    int maxColumnHeightZone1 = 0;
    for (int i = 0; i < 8; i++) {
        if (gameBoard->zone1[i]->size > maxColumnHeightZone1) {
            maxColumnHeightZone1 = gameBoard->zone1[i]->size;
        }
    }
    // Afficher les cartes de bas en haut pour chaque colonne de Zone 1
    for (int row = maxColumnHeightZone1 - 1; row >= 0; row--) {
        printf("                       ");
        for (int col = 0; col < 8; col++) {
            Pile *currentColumn = gameBoard->zone1[col];
            if (row < currentColumn->size) {
                printCard(peekCardAtLevel(currentColumn,row));
            } else {
                // Utiliser des espaces pour maintenir la largeur
                printf("       ");
            }
            printf("  ");
        }
        printf("\n");
    }
}
/**======================================================================**/

/**Conditions sur le Deplacement des carte*/
// Fonction pour verifier si deux cartes peuvent etre empilees selon les regles
int isMoveValid(Carte *sourceCard, Carte *destinationCard) {
    if (sourceCard == NULL && destinationCard == NULL) {
        return 0;
    }
    // Verifier si la carte destination est de rang immediatement superieur
    if (*(sourceCard->value) == *(destinationCard->value) - 1) {
        // Verifier si les couleurs sont opposees
        if (sourceCard->type[0] == 'C' && (destinationCard->type[0] == 'P' || destinationCard->type[0] == 'T'))
            return 1;
        else if (sourceCard->type[0] == 'P' && (destinationCard->type[0] == 'C' || destinationCard->type[0] == 'D'))
            return 1;
        else if (sourceCard->type[0] == 'T' && (destinationCard->type[0] == 'C' || destinationCard->type[0] == 'D'))
            return 1;
        else if (sourceCard->type[0] == 'D' && (destinationCard->type[0] == 'T' || destinationCard->type[0] == 'P'))
            return 1;
    }
    return 0;
}
// Fonction pour deplacer une carte
void deplacerCarte(Pile *source, Pile *destination) {
    Carte *carteDeplacee = popCard(source);
    if (carteDeplacee != NULL) {
        pushCard(destination, carteDeplacee);
        // Ajouter des espaces vides dans la colonne source
    for (int i = 0; i < source->size; i++) {
        printf("         ");
    }
    }
}
// Fonction pour deplacer de n'importe quelle zone vers n'importe quelle zone
void deplacerCarteEntreZones(Board *gameBoard, Pile **sourceZone, int sourceIndex, Pile **destinationZone, int destinationIndex) {
    if (sourceIndex < 0 || sourceIndex >= 8 || destinationIndex < 0 || destinationIndex >= 8) {
             color(15, 18);
        afficherErreurAvecPause(" Colonnes invalides ",3000);
        return;
    }
    Pile *source = sourceZone[sourceIndex];
    Pile *destination = destinationZone[destinationIndex];
    if (source->size == 0) {
             color(15, 18);
        afficherErreurAvecPause("La pile source est vide.",3000);
        return;
    }
    if (destination->size > 0 && !isMoveValid(peekCard(source), peekCard(destination))) {
             color(15, 18);
        afficherErreurAvecPause("Deplacement invalide selon les regles.",3000);
        return;
    }
    deplacerCarte(source, destination);
}
// Fonction pour deplacer de zone1 vers zone2
void deplacerZone1VersZone2(Board *gameBoard, int sourceColumn, int destinationFreecell) {
    deplacerCarteEntreZones(gameBoard, gameBoard->zone1, sourceColumn, gameBoard->zone2, destinationFreecell);
}
// Fonction pour deplacer de zone2 vers zone2
void deplacerZone2VersZone2(Board *gameBoard, int sourceColumn, int destinationFreecell) {
    deplacerCarteEntreZones(gameBoard, gameBoard->zone2, sourceColumn, gameBoard->zone2, destinationFreecell);
}
// Fonction pour deplacer de zone1 vers zone1
void deplacerZone1VersZone1(Board *gameBoard, int sourceColumn, int destinationColumn) {
    Pile *source = gameBoard->zone1[sourceColumn];
    Pile *destination = gameBoard->zone1[destinationColumn];
    if (source->size == 0) {
             color(15,2);
        afficherErreurAvecPause("La pile source est vide.",3000);
        return;
    }
    if (destination->size > 0 && !isMoveValid(peekCard(source), peekCard(destination))) {
             color(15,2);
        afficherErreurAvecPause("Deplacement invalide selon les regles.",3000);
        return;
    }
    deplacerCarte(source, destination);
}
// Fonction pour deplacer de zone1 vers zone3
void deplacerZone1VersZone3(Board *gameBoard, int sourceColumn, int destinationFoundation) {
    Pile *source = gameBoard->zone1[sourceColumn];
    Pile *destination = gameBoard->zone3[destinationFoundation];

    if (source->size == 0) {
             color(15, 18);
        afficherErreurAvecPause("La pile source est vide.",3000);
        return;
    }
    if (destination->size >= 13) {
             color(15, 18);
        afficherErreurAvecPause("La fondation est pleine. Vous ne pouvez pas ajouter plus de cartes.",3000);
        return;
    }
    if (destination->size > 0) {
        Carte *sourceCard = peekCard(source);
        Carte *destinationCard = peekCard(destination);
        if (*(sourceCard->value) == *(destinationCard->value) + 1 && strcmp(sourceCard->type, destinationCard->type) == 0) {
            popCard(destination);
            deplacerCarte(source, destination);
        } else {
             color(15, 18);
            afficherErreurAvecPause("Deplacement invalide selon les regles.",3000);
        }
    } else {
        if (*(peekCard(source)->value) == 1) {
            deplacerCarte(source, destination);
        } else {
             color(15, 18);
            afficherErreurAvecPause("Deplacement invalide. La fondation doit commencer par un As.\n",3000);
        }
    }
}
// Fonction pour deplacer de zone2 vers zone3
void deplacerZone2VersZone3(Board *gameBoard, int sourceColumn, int destinationFoundation) {
    Pile *source = gameBoard->zone2[sourceColumn];
    Pile *destination = gameBoard->zone3[destinationFoundation];
    if (source->size == 0) {
        afficherErreurAvecPause("La pile source est vide.",3000);
        return;
    }
    if (destination->size >= 13) {
        afficherErreurAvecPause("La fondation est pleine. Vous ne pouvez pas ajouter plus de cartes.",3000);
        return;
    }
    if (destination->size > 0) {
        Carte *sourceCard = peekCard(source);
        Carte *destinationCard = peekCard(destination);
        if (*(sourceCard->value) == *(destinationCard->value) + 1 && strcmp(sourceCard->type, destinationCard->type) == 0) {
            popCard(destination);
            deplacerCarte(source, destination);
        } else {
            afficherErreurAvecPause("Deplacement invalide selon les regles.",3000);
        }
    } else {
        if (*(peekCard(source)->value) == 1) {
            deplacerCarte(source, destination);
        } else {
            afficherErreurAvecPause("Deplacement invalide. La fondation doit commencer par un As.\n",3000);
        }
    }
}
// Fonction pour deplacer de zone2 vers zone1
void deplacerZone2VersZone1(Board *gameBoard, int sourceFreecell, int destinationColumn) {
    Pile *source = gameBoard->zone2[sourceFreecell];
    Pile *destination = gameBoard->zone1[destinationColumn];
    if (source->size == 0) {
        color(15, 18);
        afficherErreurAvecPause("La pile source est vide.",3000);
        return;
    }
    if (destination->size > 0 && !isMoveValid(peekCard(source), peekCard(destination))) {
        color(15, 18);
        afficherErreurAvecPause("Deplacement invalide selon les regles.",3000);
        return;
    }
    deplacerCarte(source, destination);
}
/**======================================================================**/

/** FONCTIONS DE JEU */
// Fonction pour lancer le jeu
void playGame() {
 Board *gameBoard = initializeBoard();
    remplirPiles(gameBoard);
    char choixSource[3], choixDestination[3];
    while (!youWin(gameBoard)) {
        effacerEcran();
        printBoard(gameBoard);
        color(15, 18);
         printf("\n=====================================================================================================================\n");
        color(15, 18);
printf("Choisissez la source ([1-8] Zone 1, [9-12] Zone 2, [13-16] Zone 3, [R,r] pour restart, [Q,q] pour quitter): ");
if (scanf("%s", choixSource) != 1) {
    afficherErreurAvecPause("Erreur de saisie.", 3000);
    continue;
}
if (strcmp(choixSource, "R") == 0 || strcmp(choixSource, "r") == 0) {
    restartGame(gameBoard);
    continue;
} else if (strcmp(choixSource, "Q") == 0 || strcmp(choixSource, "q") == 0) {
    break;
}
printf("Choisissez la destination ([1-8] Zone 1, [9-12] Zone 2, [13-16] Zone 3, [R,r] pour restart, [Q,q] pour quitter): ");
if (scanf("%s", choixDestination) != 1) {
    afficherErreurAvecPause("Erreur de saisie.", 3000);
    continue;
}
if (strcmp(choixDestination, "R") == 0 || strcmp(choixDestination, "r") == 0) {
    restartGame(gameBoard);
    continue;
} else if (strcmp(choixDestination, "Q") == 0 || strcmp(choixDestination, "q") == 0) {
    break;
}
         else {
                int choixsource = atoi(choixSource) ;
         int choixdestination = atoi(choixDestination);
        Pile *source, *destination;
        if (choixsource >= 1 && choixsource <= 8) {
            source = gameBoard->zone1[choixsource - 1];
        } else if (choixsource >= 9 && choixsource <= 12) {
            source = gameBoard->zone2[choixsource - 9];
        } else if (choixsource >= 13 && choixsource <= 16) {
            source = gameBoard->zone3[choixsource - 13];
        } else {
            afficherErreurAvecPause("Choix de source invalide.",3000);
            continue;
        }
        if (choixdestination >= 1 && choixdestination <= 8) {
            destination = gameBoard->zone1[choixdestination - 1];
        } else if (choixdestination >= 9 && choixdestination <= 12) {
            destination = gameBoard->zone2[choixdestination - 9];
        } else if (choixdestination >= 13 && choixdestination <= 16) {
            destination = gameBoard->zone3[choixdestination - 13];
        }
         else {
            afficherErreurAvecPause("Choix de destination invalide.",3000);
            continue;
        }
        // Appel de la fonction de deplacement en fonction des zones
if (choixsource >= 1 && choixsource <= 8 && choixdestination >= 1 && choixdestination <= 8) {
    deplacerZone1VersZone1(gameBoard,choixsource - 1, choixdestination-1);
} else if (choixsource >= 1 && choixsource <= 8 && choixdestination >= 9 && choixdestination <= 12) {
    deplacerZone1VersZone2(gameBoard, choixsource - 1, choixdestination - 9);
} else if (choixsource >= 1 && choixsource <= 8 && choixdestination >= 13 && choixdestination <= 16) {
    deplacerZone1VersZone3(gameBoard, choixsource - 1, choixdestination - 13);
} else if (choixsource >= 9 && choixsource <= 12 && choixdestination >= 13 && choixdestination <= 16) {
    deplacerZone2VersZone3(gameBoard, choixsource - 9, choixdestination - 13);
} else if (choixsource >= 9 && choixsource <= 12 && choixdestination >= 1 && choixdestination <= 8) {
    deplacerZone2VersZone1(gameBoard, choixsource - 9, choixdestination - 1);
} else if (choixsource >= 9 && choixsource <= 12 && choixdestination >= 9 && choixdestination <= 12) {
    deplacerZone2VersZone2(gameBoard, choixsource - 9, choixdestination - 9);
}
         }
  effacerEcran();
    }
if(youWin(gameBoard)==1){
    printWinMessage();
    }
free(gameBoard);
}
// Fonction pour verifier si la partie est gagne
int youWin(Board *gameBoard) {
    for (int i = 0; i < 4; i++) {
        Pile *foundationPile = gameBoard->zone3[i];
        // Verifier si la pile est vide
        if (foundationPile == NULL || isEmpty(foundationPile)) {
            return 0;
        }
        // Verifier si la carte superieure est un Roi (valeur = 13)
        if (*(peekCard(foundationPile)->value) != 13) {
            return 0;
        }
    }
    return 1; // Toutes les piles de fondation ont un Roi en haut
}
// Fonction pour reinitialiser le jeu
void restartGame(Board *gameBoard) {
    // Liberer la memoire des cartes existantes dans le plateau de jeu et reinitialiser les piles
    for (int i = 0; i < 8; i++) {
        while (gameBoard->zone1[i]->size > 0) {
            popCard(gameBoard->zone1[i]);
        }
    }
    for (int i = 0; i < 4; i++) {
        while (gameBoard->zone2[i]->size > 0) {
            popCard(gameBoard->zone2[i]);
        }
        while (gameBoard->zone3[i]->size > 0) {
            popCard(gameBoard->zone3[i]);
        }
    }

    // Remplir les piles avec des cartes uniques
    remplirPiles(gameBoard);
}
// Fonction pour afficher message de win
void printWinMessage() {
     printf("\n\n\n\n\n\n");
    printf("                                                       ___________\n");
    printf("                                                      '._==_==_=_.'\n");
    printf("                                                      .-\\:      /-.\n");
    printf("                                                     | (|:.     |) |\n");
    printf("                                                      '-|:.     |-'\n");
    printf("                                                        \\::.    /\n");
    printf("                                                         '::. .'\n");
    printf("                                                           ) (\n");
    printf("                                                         _.' '._\n");
    printf("                                                        `\"\"\"\"\"\"\"`\n");
    printf("                                            Felicitations ! Vous avez gagne ! \n");
}
/**======================================================================**/

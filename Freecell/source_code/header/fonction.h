#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

/** structure de donnees de carte/Element/pile/Board **/
typedef struct {
    int value;
    char *type;
}Carte;
typedef struct element {
    Carte *card;
    struct element *next;
}Element;
typedef struct {
    Element *top;
    int size;
}Pile;
typedef struct {
    Pile *zone1[8];   // Colonnes sur le plateau principal
    Pile *zone2[4];   // Pile FreeCell
    Pile *zone3[4];   // Pile de fondation
}Board;
/**======================================================================**/

/** Fonctions pour manipuler les piles **/
// Fontion pour creer une pile
Pile *createPile();
// Fonction pour empiler une carte
void pushCard(Pile *pile, Carte *card);
// Fonction pour depiler une carte
Carte *popCard(Pile *pile);
// Fonction pour verifier si une pile est vide
int isEmpty(Pile *pile);
// Fonction pour retourner peek de pile
Carte *peekCard(Pile *pile);
// Fonction pour retourner peek d'un niveau
Carte *peekCardAtLevel(Pile *pile, int level);
/**======================================================================**/
/** Fonctions d'affichage **/
// Fonction pour la couleur d'ecriture et d'arriere plan
void color(int t, int f);
// Fonction qui fait "refresh" de l'affichage
void effacerEcran();
// Fonction pour afficher message erreur en rouge
void afficherErreurAvecPause(const char *message, int dureeEnMillisecondes);
/**======================================================================**/
/** Affichage des cartes **/
// Fonction pour afficher les symboles de jeu de carte
void printCardSymbol(const char *type);
// Fonction pour afficher la carte
void printCard(Carte *card);
/**======================================================================**/
/** Fonctions pour manipuler le plateau de jeu**/
// Fonction pour reserver l'espace memoire de la table (creer la table)
Board *initializeBoard();
// Fonction pour creer la carte
Carte *createCard(int value, const char *type);
// Fonction pour remplire les piles des cartes
void remplirPiles(Board *gameBoard);
// Fonction pour afficher verticalement les cartes sous forme de colonne
void printVertically(Pile *pile);
// Affichage du Board
void printBoard(Board *gameBoard);
/**======================================================================**/
/**Conditions_sur_le_Deplacement_des_carte*/
// Fonction pour verifier si deux cartes peuvent etre empilees selon les regles
int isMoveValid(Carte *sourceCard, Carte *destinationCard);
// Fonction pour deplacer une carte
void deplacerCarte(Pile *source, Pile *destination);
// Fonction pour deplacer de n'importe quelle zone vers n'importe quelle zone
void deplacerCarteEntreZones(Board *gameBoard, Pile **sourceZone, int sourceIndex, Pile **destinationZone, int destinationIndex);
// Fonction pour deplacer de zone1 vers zone2
void deplacerZone1VersZone2(Board *gameBoard, int sourceColumn, int destinationFreecell);
// Fonction pour deplacer de zone2 vers zone2
void deplacerZone2VersZone2(Board *gameBoard, int sourceColumn, int destinationFreecell);
// Fonction pour deplacer de zone1 vers zone1
void deplacerZone1VersZone1(Board *gameBoard, int sourceColumn, int destinationColumn);
// Fonction pour deplacer de zone1 vers zone3
void deplacerZone1VersZone3(Board *gameBoard, int sourceColumn, int destinationFoundation);
// Fonction pour deplacer de zone2 vers zone3
void deplacerZone2VersZone3(Board *gameBoard, int sourceColumn, int destinationFoundation);
// Fonction pour deplacer de zone2 vers zone1
void deplacerZone2VersZone1(Board *gameBoard, int sourceFreecell, int destinationColumn);
/**======================================================================**/
/** FONCTIONS DE JEU */
// Fonction pour lancer le jeu
void playGame();
// Fonction pour verifier si la partie est gagne
int youWin(Board *gameBoard);
// Fonction pour reinitialiser le jeu
void restartGame(Board *gameBoard);
// Fonction pour afficher message de win
void printWinMessage();
/**======================================================================**/
#endif // FONCTION_H_INCLUDED

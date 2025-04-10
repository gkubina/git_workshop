#include "card.h"

/*
 * Afficher correctement la valeur de la carte pour le jeu de base.
 * Pour les cartes 11, 12, 13, afficher respectivement "Valet", "Dame", "Roi".
 */
void print_card(const Card *card) {
    char *suit;
    switch (card->suit) {
        case HEARTS:   suit = "♥"; break;
        case DIAMONDS: suit = "♦"; break;
        case CLUBS:    suit = "♣"; break;
        case SPADES:   suit = "♠"; break;
        default:       suit = "?"; break;
    }

    // TODO: Implémenter une conversion pour afficher "Valet", "Dame" et "Roi" pour les valeurs 11, 12, 13
    if (card->value == 11)
        printf("[Valet%s] ", suit);
    else if (card->value == 12)
        printf("[Dame%s] ", suit);
    else if (card->value == 13)
        printf("[Roi%s] ", suit);
    else
        printf("[%d%s] ", card->value, suit);
}

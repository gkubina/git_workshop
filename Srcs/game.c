#include "game.h"

/*
 * Initialiser le jeu avec le deck, la distribution initiale des cartes pour le joueur et le croupier.
 */
void init_game(Game *game) {
    init_deck(&game->deck);
    shuffle_deck(&game->deck);
    game->player_card_count = 0;
    game->dealer_card_count = 0;

    // Distribution initiale : deux cartes pour le joueur et une pour le croupier
    game->player_cards[game->player_card_count++] = draw_card(&game->deck);
    game->player_cards[game->player_card_count++] = draw_card(&game->deck);
    game->dealer_cards[game->dealer_card_count++] = draw_card(&game->deck);
    // TODO: Vérifier que les cartes distribuées respectent les règles du blackjack de base
}

void display_game(const Game *game) {
    printf("\n--- État de la partie ---\n");
    printf("Croupier: ");
    for (int i = 0; i < game->dealer_card_count; i++) {
        print_card(&game->dealer_cards[i]);
    }
    printf("\nScore partiel croupier: %d\n", compute_score(game->dealer_cards, game->dealer_card_count));
    printf("Joueur: ");
    for (int i = 0; i < game->player_card_count; i++) {
        print_card(&game->player_cards[i]);
    }
    printf("\nScore du joueur: %d\n", compute_score(game->player_cards, game->player_card_count));
    // TODO: Afficher un message clair si le joueur est "busted" (score > 21)
}

void player_hit(Game *game) {
    int res = 0;
    if (game->player_card_count < 10) {
        game->player_cards[game->player_card_count++] = draw_card(&game->deck);
        printf("You hit a ");
        print_card(&game->player_cards[game->player_card_count - 1]);
        for (int i = 0; i < game->player_card_count; i++)
            res += game->player_cards[i].value;
        if (res > 21)
        {
            printf("You have %d, you lost \n", res);
            exit (0);
        }
    } else {
        printf("Nombre maximum de cartes atteint pour le joueur.\n");
        // TODO: Gérer la situation de manière à ne pas dépasser la limite prévue par les règles de base
    }
}

void dealer_play(Game *game) {
    // Le croupier tire tant que son score est inférieur à 17, conformément aux règles de base du blackjack
    while (compute_score(game->dealer_cards, game->dealer_card_count) < 17) {
        if (game->dealer_card_count < 10) {
            game->dealer_cards[game->dealer_card_count++] = draw_card(&game->deck);
            // TODO: Vérifier après chaque tirage si le croupier dépasse 21 et afficher "Busted" si c'est le cas
        } else {
            printf("Nombre maximum de cartes atteint pour le croupier.\n");
            // TODO: Gérer la limite de cartes pour le croupier conformément aux règles du jeu
            break;
        }
    }
}

int compute_score(Card *cards, int count) {
    int score = 0;
    int as_count = 0;
    for (int i = 0; i < count; i++) {
        int val = cards[i].value;
        if (val > 10) {
            // Les figures valent 10
            val = 10;
        } else if (val == 1) {
            // Pour le jeu de base, l'as est compté comme 11
            val = 11;
            as_count++;
        }
        score += val;
    }
    // Ajuster la valeur des as si le score dépasse 21
    while (score > 21 && as_count) {
        score -= 10;
        as_count--;
    }
    // TODO: Vérifier que le calcul du score respecte bien les règles du blackjack de base
    return score;
}

//
//  main.c
//  dd
//
//  Created by SB on 2021/08/29.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CARDS 52
#define RANKS 13
#define SUITS 4

typedef struct card{
    char rank[10];
    char suit[10];
}Card;

void fillDeck(Card deck[]);
void shuffle(Card deck[]);
void deal(Card deck[], int start, int count);

char rank[RANKS][10]={ "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };

char suit[SUITS][10] = { "Hearts", "Diamonds", "Clubs", "Spades" };

void fillDeck(Card deck[]) {
    for (int i = 0; i < CARDS; i++) {
        strcpy(deck[i].rank, rank[i % RANKS]);///0~12
        strcpy(deck[i].suit, suit[i / RANKS]);///0~3, ace~king 일때 0, ace~king일 때 1..
    }
}
void shuffle(Card deck[]) {
    for (int i = 0; i < CARDS; i++) {
        int random = rand() % CARDS;
        Card temp = deck[i];
        deck[i] = deck[random];
        deck[random] = temp;
    }
}
void deal(Card deck[], int start, int count){
    for (int i = start; i < start+count; i++) {
        if (i<CARDS) {
            printf("%10s of %s\n", deck[i].rank, deck[i].suit);
            }
        else {
            printf("There is no more card!\n");
            break;
        }
    }
}

int main() {
    int count = 0, num_picked_cards = 0; Card deck[CARDS];
    srand((unsigned)time(NULL));
    fillDeck(deck); // initializing 52 cards
    shuffle(deck); // shuffling the 52 cards

    while (num_picked_cards < CARDS) {
        printf("How many cards do you want? ");
        scanf("%d", &count);
        deal(deck, num_picked_cards, count); // dealing cards
        num_picked_cards += count;
        printf("%d cards are picked.\n\n", num_picked_cards);

    }

    return 0;
}

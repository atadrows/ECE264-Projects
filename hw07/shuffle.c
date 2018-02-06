#include "shuffle.h"
#include <string.h>
#include <stdlib.h>

#include <stdio.h>
// You may add more functions in this file.

void _custom_interleave(CardDeck, CardDeck, CardDeck, int, int);

void divide(CardDeck orig_deck, CardDeck * upper_deck, CardDeck * lower_deck) {
	for (int i = 0; i < orig_deck.size - 1; i++){

		//Divide upper_deck
		for (int card = 0; card < i + 1; card++){
			upper_deck[i].cards[card] = orig_deck.cards[card];
			upper_deck[i].size = i + 1;
		}
		
		//Divide lower_deck
		for (int card = 0; card < orig_deck.size - i - 1; card++){ 
			lower_deck[i].cards[card] = orig_deck.cards[card + i + 1];
			lower_deck[i].size = orig_deck.size - i - 1;
		}
	}
}

void interleave(CardDeck upper_deck, CardDeck lower_deck) {
	CardDeck shuffled = {.size = 0};
	_custom_interleave(shuffled, upper_deck, lower_deck, 0, 0);
}	

void shuffle(CardDeck orig_deck) {
	CardDeck * upper_deck = NULL;
	CardDeck * lower_deck = NULL;

	// allocate memory
	upper_deck = malloc((orig_deck.size) * sizeof(CardDeck));
	lower_deck = malloc((orig_deck.size) * sizeof(CardDeck));

	if (upper_deck == NULL) {
		free(upper_deck);
		return;
	}
	if (lower_deck == NULL) {
		free(lower_deck);
		return;
	} 
		
	// call divideDeck to fill upper_deck and lower_deck 
	divide(orig_deck, upper_deck, lower_deck);

	for(int i = 0; i < orig_deck.size; i++) {
		// for each pairs call interleave
		interleave(upper_deck[i], lower_deck[i]);
	}

	free(upper_deck);
	free(lower_deck);
}

void _custom_interleave(CardDeck shuffled, CardDeck upper_deck, CardDeck lower_deck, int udi, int ldi) {
	if(upper_deck.size <= 0 && lower_deck.size <= 0 && shuffled.size != 0){
		print_deck(shuffled);
		fputc('\n', stdout);
		return;
	}

	CardDeck copy_upper_deck = upper_deck;
	CardDeck copy_shuffled = shuffled;

	if(upper_deck.size > 0){
		shuffled.cards[shuffled.size++] = upper_deck.cards[udi];
		upper_deck.size -= 1;
		_custom_interleave(shuffled, upper_deck, lower_deck, udi + 1, ldi);
	}
	if(lower_deck.size > 0){
		copy_shuffled.cards[copy_shuffled.size++] = lower_deck.cards[ldi];
		lower_deck.size -= 1;
		_custom_interleave(copy_shuffled, copy_upper_deck, lower_deck, udi, ldi + 1);
	}
}

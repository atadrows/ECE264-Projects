#include "shuffle.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// You can add more functions to this file.  Helper functions must start with '_'.

void _custom_interleave(CardDeck, CardDeck, CardDeck, int, int, int);
void _shuffle(CardDeck, int);

void divide(CardDeck orig_deck, CardDeck * upper_deck, CardDeck * lower_deck) {
	for (int i = 0; i < orig_deck.size - 1; i++){

		for (int card = 0; card < i + 1; card++){
			upper_deck[i].cards[card] = orig_deck.cards[card];
			upper_deck[i].size = i + 1;
		}
		
		for (int card = 0; card < orig_deck.size - i - 1; card++){ 
			lower_deck[i].cards[card] = orig_deck.cards[card + i + 1];
			lower_deck[i].size = orig_deck.size - i - 1;
		}
	}
}

void interleave(CardDeck upper_deck, CardDeck lower_deck) {
	CardDeck shuffled = {.size = 0};
	_custom_interleave(shuffled, upper_deck, lower_deck, 0, 0, 1);
}	

void _shuffle(CardDeck orig_deck, int times_to_shuffle) {
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

	CardDeck shuffled = {.size = 0};

	for(int i = 0; i < orig_deck.size - 1; i++) {
		// for each pairs call interleave
		_custom_interleave(shuffled, upper_deck[i], lower_deck[i], 0, 0, times_to_shuffle);
	}

	free(upper_deck);
	free(lower_deck);
}

void shuffle(CardDeck orig_deck) {
	_shuffle(orig_deck, 1);
}

void repeat_shuffle(CardDeck orig_deck, int k) {
	if(k <= 0){
		printDeck(orig_deck);
	} else {
		_shuffle(orig_deck, k);
	}
}

void _custom_interleave(CardDeck shuffled, CardDeck upper_deck, CardDeck lower_deck, int udi, int ldi, int times_to_shuffle) {
	if(upper_deck.size <= 0 && lower_deck.size <= 0 && shuffled.size != 0){

		if(times_to_shuffle > 0){
			repeat_shuffle(shuffled, times_to_shuffle - 1);
		}

		return;
	}

	CardDeck copy_upper_deck = upper_deck;
	CardDeck copy_shuffled = shuffled;
	
	if(upper_deck.size > 0){
		shuffled.cards[shuffled.size++] = upper_deck.cards[udi];
		upper_deck.size -= 1;
		_custom_interleave(shuffled, upper_deck, lower_deck, udi + 1, ldi, times_to_shuffle);
	}
	if(lower_deck.size > 0){
		copy_shuffled.cards[copy_shuffled.size++] = lower_deck.cards[ldi];
		lower_deck.size -= 1;
		_custom_interleave(copy_shuffled, copy_upper_deck, lower_deck, udi, ldi + 1, times_to_shuffle);
	}
}


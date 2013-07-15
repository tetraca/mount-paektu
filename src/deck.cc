/* This file is part of Mount Paektu.

 * Mount Paektu is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.

 * Mount Paektu is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Mount Paektu.  If not, see <http://www.gnu.org/licenses/>. */


#include "header/deck.hh"

using namespace std;

Deck::Deck (int stacks) 
{
  if(stacks < 1)
    throw invalid_argument("Deck: Stacks declared are less than one.");

  this->stacks = stacks;
  out_of_cards = false;

  build_deck();
  shuffle();
}

Card Deck::draw_card () 
{
  Card drawn_card;

  // If the card deck isn't empty
  // Grab a card, and pop that off its end
  if(!card_deck.empty())
    {
      drawn_card = card_deck.back();
      card_deck.pop_back();
    }
  else
    {
      throw runtime_error("Attempted to pull a card from the deck that wasn't there.");
    }

  return drawn_card;
}

vector<Card> Deck::draw_hand (int n) 
{
  vector<Card> drawn_cards;

  if(!is_out_of_cards())
    {
      if(card_deck.size() >= n)
	{
	  // Draw the cards from the deck
	  for(int i = 0; i < n; i++) 
	    drawn_cards.push_back(draw_card());
	}
      else
	{
	  // Draw the remainder of the cards and signal
	  // That the deck is out of cards
	  for(int i = 0; i < card_deck.size(); i++)
	    drawn_cards.push_back(draw_card());

	  out_of_cards = true;
	}
    }
  else
    {
      throw runtime_error("Deck is out of cards.");
    }

  return drawn_cards;
}

bool Deck::is_out_of_cards()
{
  return out_of_cards;
}


void Deck::build_deck () 
{
  Card::Suit deck_suit;

  // Repeat for number of deck stacks
  for (int s = 0; s < stacks; s++) {
    // Repeat for each card suit
    for (int i = 0; i < 4; i++) {
      if (i == 0)
	deck_suit = Card::CLUBS;
      else if (i == 1)
	deck_suit = Card::DIAMONDS;
      else if (i == 2)
	deck_suit = Card::HEARTS;
      else if (i == 3)
	deck_suit = Card::SPADES;

      // Repeat for each card rank
      for (int j = 1; j < 14; j++) 
	this->card_deck.push_back(Card(j, deck_suit));
    }
  }
}

void Deck::shuffle () 
{
  // This could have been complicated but standard library saved the day.
  random_shuffle(card_deck.begin(), card_deck.end());
}

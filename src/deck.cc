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
#include <iostream>
#include "header/deck.hh"

Deck::Deck (int stacks) : s_card_deck(0), s_out_of_cards(false)
{
  if(stacks < 1)
    throw std::invalid_argument("Deck: Stacks declared are less than one.");

  stacks = s_stacks;

  build_deck();
  shuffle();
}

Card Deck::draw_card () 
{
  Card drawn_card;

  // If the card deck isn't empty
  // Grab a card, and pop that off its end
  if(!s_card_deck.empty())
    {
      drawn_card = s_card_deck.back();
      s_card_deck.pop_back();
    }
  else
    {
      throw std::runtime_error("Attempted to pull a card from the deck that wasn't there.");
    }

  return drawn_card;
}

QVector<Card> Deck::draw_hand (int n) 
{
  QVector<Card> drawn_cards(0);

  if(!is_out_of_cards())
    {
      if(s_card_deck.size() >= n)
	{
	  // Draw the cards from the deck
	  for(int i = 0; i < n; i++) 
	    drawn_cards.append(draw_card());
	}
      else
	{
	  // Draw the remainder of the cards and signal
	  // That the deck is out of cards
	  for(int i = 0; i < s_card_deck.size(); i++)
	    drawn_cards.append(draw_card());

	  s_out_of_cards = true;
	}
    }
  else
    {
      throw std::runtime_error("Deck is out of cards.");
    }

  return drawn_cards;
}

bool Deck::is_out_of_cards()
{
  return s_out_of_cards;
}


void Deck::build_deck () 
{
  Card::Suit deck_suit;

  // Repeat for number of deck stacks
  for (int s = 0; s < s_stacks; s++) {
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
	s_card_deck.append(Card(j, deck_suit));
    }
  }
}

void Deck::shuffle () 
{
  // Seed RNG
  qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

  // Iterate across the deck, swapping a random card
  // with the currently selected card
  for(int i = 0; i < s_card_deck.size(); i++)
    {
      // Select a random card
      int sel = qrand() % s_card_deck.size();

      // Swap the randomly selected card
      Card card = s_card_deck[i];
      s_card_deck[i] = s_card_deck[sel];
      s_card_deck[sel] = card;
    }
}

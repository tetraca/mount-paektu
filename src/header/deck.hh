#include <algorithm>
#include <vector>
#include <exception>

#include "card.hh"

#pragma once

class Deck 
{
public:
  Deck(int stacks);
  Card draw_card();
  std::vector<Card> draw_hand(int n);
  bool is_out_of_cards();

private:
  std::vector<Card> card_deck;
  int  stacks;
  bool out_of_cards;

  void build_deck();
  void shuffle();
};

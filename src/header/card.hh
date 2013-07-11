#include <string>
#include <sstream>
#include <stdexcept>

#pragma once

class Card 
{
public:
  enum Suit {CLUBS, DIAMONDS, HEARTS, SPADES, UNDEFINED};

  Card();
  Card(int rank, Suit suit);
  int  get_rank();
  Suit get_suit();
  std::string to_string();

  static int compare(Card card1, Card card2);

private:
  int  s_rank;
  Suit s_suit;
  std::string get_suit_as_string();
};

#include "header/card.hh"

using namespace std;

Card::Card () 
{
  // A "blank" card. Appears as the zero of spades.
  // If you see a zero of spades, something bad happened.
  s_rank = 0;
  s_suit = UNDEFINED;
}

Card::Card (int rank, Card::Suit suit) 
{
  if(rank < 1)
    throw invalid_argument("Card: Rank declared is less than 1.");
  if(rank > 13)
    throw invalid_argument("Card: Rank is greater than 13.");
  
  s_rank = rank;
  s_suit = suit;
}

int Card::get_rank () 
{
  return s_rank;
}

Card::Suit Card::get_suit () 
{
  return s_suit;
}

string Card::get_suit_as_string ()
{
  string strep;

  if(s_suit == SPADES)
    strep = "Spades";
  else if(s_suit == DIAMONDS)
    strep = "Diamonds";
  else if(s_suit == HEARTS)
    strep = "Hearts";
  else if(s_suit == CLUBS)
    strep = "Clubs";
  else if(s_suit == UNDEFINED)
    strep = "UNDEFINED CARD";

  return strep;
}

string Card::to_string () 
{
  ostringstream ss;
  
  ss << s_rank << " of " << get_suit_as_string();
  
  return ss.str();
}

int Card::compare(Card card1, Card card2)
{
  return card1.get_rank() - card2.get_rank();
}


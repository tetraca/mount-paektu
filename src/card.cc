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

#include "header/card.hh"

Card::Card () : s_rank(0), s_suit(UNDEFINED)
{
  // A "blank" card. Appears as the zero of UNDEFINED
  // If you see a zero of spades, something bad happened.
}

Card::Card (int rank, Card::Suit suit) 
{
  if(rank < 1)
    throw std::invalid_argument("Card: Rank declared is less than 1.");
  if(rank > 13)
    throw std::invalid_argument("Card: Rank is greater than 13.");
  
  s_rank = rank;
  s_suit = suit;
}

int Card::rank () const
{
  return s_rank;
}

Card::Suit Card::suit () const 
{
  return s_suit;
}

std::string Card::suit_as_string ()
{
  // This function exists purely for debug purposes.

  std::string strep;

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

std::string Card::to_string () const
{
  // This function exists purely for debug purposes.
  std::string ret;
  std::ostringstream ss;
  
  ss << s_rank << " of " << suit_as_string();
  
  return ss.str();
}

bool Card::compare(Card card1, Card card2)
{
  return card1.rank() > card2.rank();
}


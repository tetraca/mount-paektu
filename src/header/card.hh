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

#include <string>
#include <sstream>
#include <stdexcept>

#pragma once

class Card 
{
public:
  enum Suit 
    {
      CLUBS     = 0, 
      DIAMONDS  = 1, 
      HEARTS    = 2, 
      SPADES    = 3, 
      UNDEFINED = 4
    };

  Card();
  Card(int rank, Suit suit);
  int  rank()  const;
  Suit suit()  const;
  std::string to_string() const;

  static bool compare(Card card1, Card card2);

private:
  int  s_rank;
  Suit s_suit;
  std::string suit_as_string() const;
};

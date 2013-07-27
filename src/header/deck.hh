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

#include <QVector>
#include <QTime>
#include <stdexcept>

#include "card.hh"

#pragma once

class Deck 
{
public:
  Deck(int stacks);
  Card draw_card();
  QVector<Card> draw_hand(int n);
  bool is_out_of_cards();

private:
  QVector<Card> s_card_deck;
  int  s_stacks;
  bool s_out_of_cards;

  void build_deck();
  void shuffle();
};

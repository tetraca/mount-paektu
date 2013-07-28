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
#include "header/dealer.hh"

Dealer::Dealer()
{
  Player("Dealer", 1);
}

void Dealer::choose_cards()
{
  std::cout << "Size of dealer hand: " << s_full_hand.size() << std::endl;
  qSort(s_full_hand.begin(), s_full_hand.end(), Card::compare);
  // Get the highest rated cards
  // Put them in the drop hand
  add_to_drop_hand(s_full_hand[0]);
  add_to_drop_hand(s_full_hand[1]);
}

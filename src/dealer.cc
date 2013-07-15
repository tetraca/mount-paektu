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

#include "header/dealer.hh"

Dealer::Dealer()
{
  Player("Dealer", 1);
}

std::vector<Card> Dealer::choose_cards()
{
  std::sort(s_full_hand.begin(), s_full_hand.end(), Card::compare);
  // Get the highest rated cards

  std::vector<Card> to_ret(&s_full_hand[0], &s_full_hand[2]);

  return to_ret;
}

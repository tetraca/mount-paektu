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
#include <vector>
#include <sstream>
#include <stdexcept>

#include "card.hh"
#include "deck.hh"

#pragma once

class Player 
{
public:
  // Constructors
  Player();
  Player(std::string name, long bank);

  // General Functions
  void new_hand(Deck* deck, int hand_size);
  void add_bank(long displacement);
  void set_wager(long wager);
  void promote_tier();
  void demote_tier();
  void advance_turn();
  void push_drop_hand(Card card);

  static bool compare(const Player& x, const Player& y);

  // Accessors
  std::string name() const;
  long bank() const;
  long wager() const;
  int  tier() const;
  int  turn() const;

  std::vector<Card> drop_hand();
  std::vector<Card> full_hand();

  // Debug
  std::string drop_hand_string();
  std::string full_hand_string();

protected:
  // State
  long s_bank;
  std::string s_name; 
  long s_wager;
  std::vector<Card> s_drop_hand;
  std::vector<Card> s_full_hand;
  int s_turn;
  int s_tier;

  // Deprecated
  void set_drop_hand(std::vector<Card> hand);
  void set_full_hand(std::vector<Card> hand);
};

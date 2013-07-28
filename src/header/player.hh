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

#include <QString>
#include <QVector>
#include <stdexcept>

#include "card.hh"
#include "deck.hh"

#pragma once

class Player 
{
public:
  Player();
  Player(QString name, long bank);

  void new_hand(Deck deck, int hand_size);

  QString name() const;

  long bank() const;
  void set_bank(long displacement);

  long wager() const;
  void set_wager(long wager);

  int  tier() const;
  void promote_player();
  void demote_player();

  int  turn() const;
  void advance_turn();

  QVector<Card> drop_hand() const;
  QString drop_hand_string() const;

  void add_to_drop_hand(Card card);
  void clear_drop_hand();

  QVector<Card> full_hand() const;
  QString full_hand_string() const;


  static bool cmp_player(const Player& x, const Player& y);


protected:
  long s_bank;
  QString s_name; 
  long s_wager;
  QVector<Card> s_drop_hand;
  QVector<Card> s_full_hand;
  int s_turn;
  int s_tier;
};

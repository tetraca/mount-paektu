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

#include <vector>
#include <algorithm>

#include "card.hh"
#include "player.hh"
#include "dealer.hh"

#pragma once

class PlayerAI
{
public:
  PlayerAI();
  PlayerAI(Player* player, Dealer* dealer);
  
  void consider();

private:
  Player*  s_player;
  Dealer*  s_dealer;
};

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

#include <array>
#include <vector>
#include <gtkmm/grid.h>

#include "player.hh"
#include "boardslot.hh"

#pragma once

class Board : public Gtk::Grid
{
public:
  Board(std::array<Player*, 7> players);
  void update();

private:
  std::array<BoardSlot, 28> s_slots;
  std::array<Player*, 7>    s_players;

  std::vector<BoardSlot*> slots(int tier);
};

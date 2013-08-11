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

#include "header/boardslot.hh"

BoardSlot::BoardSlot() : Gtk::Image(BLANK_SLOT_PATH), 
			 s_occupied(false)
{
  // Create a board slot with a blank space
}

BoardSlot::BoardSlot(Player* player) : Gtk::Image(PLAYER_SLOT_PATH), 
				       s_occupied(true), 
				       s_player(player)
{
  // Create a slot occupied by a player (Joker card)
  if(player == NULL)
    throw std::invalid_argument("Tried to initialize a BoardSlot with a player that does not exist");
}

void BoardSlot::clear()
{
  // Change the image and remove the associated player

  set(BLANK_SLOT_PATH);
  s_player = NULL;
  s_occupied = false;
}

void BoardSlot::set_player(Player* player)
{
  // Place a player card in the slot

  if(player == NULL)
    {
      clear();
    }
  else
    {
      s_player = player;
      set(PLAYER_SLOT_PATH);
      s_occupied = true;
    }
}

bool BoardSlot::is_occupied()
{
  return s_occupied;
}

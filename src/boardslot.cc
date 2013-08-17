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

const Glib::ustring BoardSlot::BLANK_SLOT_PATH("../img/empty.png");
const Glib::ustring BoardSlot::BLANK_SLOT_LABEL("[          ]");
const Glib::ustring BoardSlot::PLAYER_SLOT_PATH("../img/player.png");


BoardSlot::BoardSlot() : Gtk::VBox(),
			 s_image(BLANK_SLOT_PATH), 
			 s_occupied(false),
			 s_label(BLANK_SLOT_LABEL)
{
  // Create a board slot with a blank space (Blank card)

  pack_end(s_image);
  pack_end(s_label);
}

BoardSlot::BoardSlot(Player* player) : s_image(PLAYER_SLOT_PATH), 
				       s_occupied(true), 
				       s_player(player)
{
  // Create a slot occupied by a player (Joker card)
  if(player == NULL)
    throw std::invalid_argument("Tried to initialize a BoardSlot with a player that does not exist");

  s_label.set_label(Glib::ustring(s_player->name()));

  pack_end(s_image);
  pack_end(s_label);

  s_image.show();
  s_label.show();
}

void BoardSlot::clear()
{
  // Change the image and remove the associated player

  s_image.set(BLANK_SLOT_PATH);
  s_player = NULL;
  s_label.set_label(BLANK_SLOT_LABEL);
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
      s_image.set(PLAYER_SLOT_PATH);
      s_label.set_label(Glib::ustring(player->name()));
      s_occupied = true;
    }
}

bool BoardSlot::is_occupied()
{
  return s_occupied;
}





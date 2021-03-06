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

#include <stdexcept>

#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <glibmm/ustring.h>

#include "player.hh"

#pragma once

// This is a small extension of the standard Gtk::Box class
// Which will allow us to build an array that checks whether a slot
// in the board is occupied or not.
class BoardSlot : public Gtk::VBox
{
public:
  BoardSlot();
  BoardSlot(Player* player);

  bool is_occupied();
  void set_player(Player* player);
  void clear();

private:
  bool       s_occupied;
  Player*    s_player;
  Gtk::Image s_image;
  Gtk::Label s_label;

  static const Glib::ustring BLANK_SLOT_PATH;
  static const Glib::ustring BLANK_SLOT_LABEL;
  static const Glib::ustring PLAYER_SLOT_PATH;
};

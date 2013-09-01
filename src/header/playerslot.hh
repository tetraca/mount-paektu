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

#include <glibmm/ustring.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <stdexcept>

#include "card.hh"
#include "player.hh"

#pragma once

class PlayerSlot : public Gtk::Box
{
public:
  PlayerSlot();
  PlayerSlot(Player* player);

  void update();
  void assign(Player* player);

private:
  Player*                   s_player;
  Gtk::Image                s_player_avatar;
  std::array<Gtk::Image, 2> s_drop_hand; 
  Gtk::Label                s_player_name;

  Glib::ustring card_path(Card card);

  static const Glib::ustring PLAYER_DEFAULT_AVATAR;
  static const Glib::ustring PLAYER_CARD_BACK;
};


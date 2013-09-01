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

#include "board.hh"
#include "player.hh"
#include "playerslot.hh"
#include "paektu.hh"
#include <array>
#include <gtkmm/action.h>
#include <gtkmm/window.h>

#pragma once

class MainWindow : public Gtk::Window
{
public:
  MainWindow(Paektu* game);
  virtual ~MainWindow();

private:
  Gtk::Grid                 s_grid;
  Paektu*                   s_game;
  Board                     s_board;
  std::array<PlayerSlot, 6> s_player_slots;

  std::array<Player*, 7> collect_players(Paektu* game);

  //Gtk::ActionGroup* s_action_group;
};

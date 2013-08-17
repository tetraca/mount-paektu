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

#include "header/main-window.hh"

MainWindow::MainWindow(Paektu* game) : s_game(game),
				       s_board(collect_players(game))
{
  s_grid.attach(s_board, 2, 0, 1, 3);
  add(s_grid);

  show_all_children();
}

std::array<Player*, 7> MainWindow::collect_players(Paektu* game)
{
  std::array<Player*,7> players;
  for(int i = 0; i < 7; i++)
    players[i] = &game->player_at(i);

  return players;
}


MainWindow::~MainWindow()
{

}


int main(int argc, char *argv[])
{
  Glib::RefPtr<Gtk::Application> app = 
    Gtk::Application::create(argc, argv, "org.infrosoft.paektu");

  Paektu game;
  MainWindow main_window(&game);

  main_window.set_default_size(200, 200);
  return app->run(main_window);
}

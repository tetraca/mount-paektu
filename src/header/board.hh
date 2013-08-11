#include <array>
#include <gtkmm/widget.h>

#include "player.hh"
#include "boardslot.hh"

#pragma once

class Board : public Gtk::Widget
{
public:
  Board(std::array<Player*, 7> players);
  void update();

private:
  std::array<BoardSlot, 28> s_slots;
  Gtk::Grid                 s_grid;
  std::array<Player*, 7>    s_players;

  std::vector<BoardSlot*> slots(int tier);
};

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

#include <string>
#include <vector>
#include <array>
#include <sstream>
#include <stdexcept>

#include "deck.hh"
#include "player.hh"
#include "dealer.hh"

class Paektu 
{
public:
  Paektu();

  void advance_round();

  std::vector<Player*> tier_residents(int tier);
  std::array<int, 7> tier_list();

  long current_pot() const;
  void add_current_pot(long wager);

  enum GameStatus {PLAYING, COMPLETE};
  bool is_complete() const;

  Player& player_at(int i);
  Dealer& dealer();

  void round_won(Player& player);
  void round_lost(Player& player);

private:
  int                   s_current_turn;
  Deck                  s_deck;
  long                  s_pot;
  std::array<Player, 7> s_players;
  Dealer                s_dealer;
  GameStatus            s_game_status;

  bool are_players_synchronized();
  void draw_new_round();
  Player& highest_player();
  std::vector<int> player_tiers();
};

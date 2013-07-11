#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <array>
#include <stdexcept>

#include "deck.hh"
#include "player.hh"
#include "dealer.hh"

class Paektu 
{
public:
  Paektu();

  void advance_round();

  std::vector<Player*> get_tier(int tier);
  std::array<int, 7> get_player_tiers();
  static int cmp_tier(int x, int y);

  long get_current_pot();
  void add_current_pot(long wager);

  enum GameStatus {PLAYING, COMPLETE};
  bool is_complete();
  Player get_player_at(int i);

  Dealer get_dealer();

  void player_round_won(Player* player);
  void player_round_lost(Player* player);



private:
  int                   s_current_turn;
  Deck                  s_deck;
  long                  s_pot;
  std::array<Player, 7> s_players;
  Dealer                s_dealer;
  GameStatus            s_game_status;

  bool are_players_synchronized();
  void draw_new_round();
};

#include <string>
#include <vector>
#include <stdexcept>

#include "card.hh"
#include "deck.hh"

#pragma once

class Player 
{
public:
  Player();
  Player(std::string name, long bank);

  void new_hand(Deck* deck, int hand_size);

  // Accessors
  std::string get_name();

  long get_bank();
  void set_bank(long displacement);

  long get_wager();
  void set_wager(long wager);

  int  get_tier();
  void set_tier(int tier);

  int  get_turn();
  void advance_turn();

  std::vector<Card> get_drop_hand();
  std::string get_drop_hand_string();
  void set_drop_hand(std::vector<Card> hand);

  std::vector<Card> get_full_hand();
  std::string get_full_hand_string();
  void set_full_hand(std::vector<Card> hand);

protected:
  long s_bank;
  std::string s_name; 
  long s_wager;
  std::vector<Card> s_drop_hand;
  std::vector<Card> s_full_hand;
  int s_turn;
  int s_tier;
};

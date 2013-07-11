#include <algorithm>
#include "player.hh"

#pragma once

class Dealer : public Player
{
  // A dealer is just a player with a rudimentary AI

public:
  Dealer();
  std::vector<Card> choose_cards();
};


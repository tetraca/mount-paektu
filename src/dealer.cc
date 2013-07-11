#include "header/dealer.hh"

Dealer::Dealer()
{
  Player("Dealer", 1);
}

std::vector<Card> Dealer::choose_cards()
{
  std::sort(s_full_hand.begin(), s_full_hand.end(), Card::compare);
  // Get the highest rated cards

  std::vector<Card> to_ret(&s_full_hand[0], &s_full_hand[2]);

  return to_ret;
}

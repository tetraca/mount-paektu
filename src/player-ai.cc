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

#include "header/player-ai.cc"

PlayerAI::PlayerAI(Player* player, Dealer* dealer) : s_player(player),
						     s_dealer(dealer)
{
  // This is a rudimentary player AI. It attempts to play the game blindly
  // using a reference to the player and a reference to the dealer to at the
  // very least choose cards that can beat the dealer's, or doubles if that
  // condition is impossible to reach.

  // In order to use a player AI, the interface must initialize it with a reference
  // to the player it wants to control, and the dealer assigned to the game.
}


void PlayerAI::consider()
{
  std::vector<Card> full_hand = s_player->full_hand();

  // Firstly, sort the cards owned by the player, as with the Dealer AI
  s_player->std::sort(full_hand.begin(), full_hand.end(), Card::compare);
  
  // Sum the highest value cards in the player
  // Calculate the rank of the dealer
  int player_sum = s_player->full_hand()[0].rank() + s_player->full_hand()[1].rank();
  int dealer_sum = s_dealer->drop_hand()[0].rank() + s_dealer->drop_hand()[1].rank();

  // When we have enough to advance
  if(player_sum > dealer_sum)
    {
      // Place the highest level cards onto the drop hand
      s_player->push_drop_hand(s_player->full_hand()[0]);
      s_player->push_drop_hand(s_player->full_hand()[1]);

      // When we're ahead of the dealer, bet a conservative 25% of it      
      s_player->set_wager(s_player->bank() * .25);
    }
  // When we can't advance
  else
    {
      // Search for doubles to be rude to other players
      // Since the cards are sorted in rank order at this point
      // We can search for dupes by comparing the rank of the current card
      // With the next on in the index.

      int dup_index = -1;

      for(int i = 0; i < s_player->full_hand().size() - 1; i++)
	if(full_hand[i].rank() == full_hand[i + 1].rank())
	  dup_index = i;

      // Use a low brow wager
      s_player->set_wager(1);

      if(dup_index >= 0)
	{
	  s_player->push_drop_hand(full_hand[dup_index]);
	  s_player->push_drop_hand(full_hand[dup_index + 1]);
	}
      else
	{
	  // When we don't find doubles
	  // Just place the highest cards we can
	  s_player->push_drop_hand(full_hand[0]);
	  s_player->push_drop_hand(full_hand[1]);
	}

    }

  // Regardless of what happens we must advance the turn
  s_player->advance_turn();
}

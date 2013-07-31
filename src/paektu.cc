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

#include "header/paektu.hh"

// Debug constructor
Paektu::Paektu() : s_deck(40), 
		   s_pot(0),
		   s_game_status(PLAYING)
{
  // Notes on Initialization:

  // - Build 40 stack deck
  //      Since a game is played with 7 players and a dealer
  //      Each drawing 5 cards, this will ensure that there will
  //      Never be a case where the game ends with an unequal quantity
  //      of cards
  // - The lcm for us to never run out of cards off round is 10 decks.
  // - Set the pot to zero
  // - Note the game is PLAYING rather than FINISHED

  std::stringstream playername;

  // Make a generic set of players with 2000 gold pots
  for(int i = 1; i <= s_players.size(); i++) 
    {
      playername << "Player " << i;
      s_players[i - 1] = Player(playername.str(), 2000);

      // Clear after player creation
      playername.str(std::String(""));
    }

  // Draw a new round after initialization
  draw_new_round();
}

void Paektu::advance_round() 
{
  // Ensure all players are on the same turn and the game hasn't been won
  if(are_players_synchronized() && (s_game_status == PLAYING))
    {
      // Sum the two cards the dealer picked.
      int sum_dealer = 
	s_dealer.drop_hand()[0].rank() +
	s_dealer.drop_hand()[1].rank();

      int sum_player;
      int diff_player;
      bool trump = false;

      for(Player &player : s_players)
	{
	  // Sum the two cards the current player picked.
	  sum_player = 
	    player.drop_hand()[0].rank() +
	    player.drop_hand()[1].rank();

	  // Dealer - Player Relationships
	  if(sum_dealer > sum_player)
	    {
	      // Exception to the general round-win conditions
	      // A pair of aces beats a pair of kings
	      if((sum_player == 2) && (sum_dealer == 26))
		round_won(player);
	      else
		round_lost(player);
	    }
	  else if(sum_dealer < sum_player)
	    {
	      round_won(player);
	    }

	  // When diff player = 0 doubles have been reached
	  diff_player = 
	    player.drop_hand().at(0).rank() -
	    player.drop_hand().at(1).rank();

	  // Player - Player Relationships
	  if((diff_player == 0) && (tier_residents(7).size() < 7))
	    {
	      // The case of doubles.
	      // Doubles will demote a player.
	      // You cannot demote a player if all players are on the first tier

	      if(player.name() == highest_player().name())
		{
		  // If the player is the highest player by ranking
		  // He trumps the attempt at demotion
		  trump = true;
		}

	      if(!trump)
		{
		  // Demote the highest player if there's a double
		  round_lost(highest_player());
		}
	    }
	}
    }
  else
    {
      if(!are_players_synchronized())
	throw std::runtime_error("Players are not on a concurrent state.");
      else if(!s_game_status == PLAYING)
	throw std::runtime_error("Game has been finished already.");
    }

  // Check to see if someone hasn't gotten to the top of the mountain
  if(highest_player().tier() == 1)
    {
      s_game_status = COMPLETE;
    }
  // Draw a new round if the game is good for another one
  else
    {
      draw_new_round();
    }
}

Player& Paektu::highest_player()
{
  std::sort(s_players.begin(), s_players.end(), Player::cmp_player);

  return s_players[6];
}

void Paektu::round_won(Player& player)
{
  // Grab all the players being held in the next tier
  int next_tier = player.get_tier() + 1;
  std::vector<Player*> tier = tier_residents(next_tier);

  // Check to see if the tier is full
  if(ntier.size() >= next_tier)
    {
      // When the next tier is full
      // Demote a player in that tier
      // The first that appears in that tier will suffice
      tier.at(0)->demote_tier();
    }

  // Finally, place the player into a new tier
  player.promote_tier();
}

void Paektu::round_lost(Player& player)
{
  // Add wager to pot
  add_current_pot(player.wager());

  // Subtract the wager from their bank
  player.set_bank(0 - player.wager());
  player.set_wager(0);
}


void Paektu::draw_new_round()
{
  // When the deck isn't out of cards try to...
  if(!s_deck.is_out_of_cards())
    {
      try
	{
	  // Draw a new dealer hand.
	  s_dealer.new_hand(&s_deck, 5);
	  // Run the dealer AI, this will go into the drop hand
	  s_dealer.choose_cards();

	  // Draw a new hand for each player.
	  for(Player &player : s_players)
	    player.new_hand(&s_deck, 5);

	  // Advance the turn we are currently on.
	  s_current_turn++;
	}
      catch(std::runtime_error& e)
	{
	  // There shouldn't be any case where we run out of cards
	  // In the middle of a round, but if this happens
	  // Just crash the program,
	  // Because you deserve it for not doing the math correctly.

	  throw std::runtime_error("Ran out of cards in middle of round.");
	}
    }
  // Otherwise declare the highest tiered player the winner
  else
    {
      s_game_status = COMPLETE;

      // If there is more than one person at the highest level
      // The pot is split

      // Find the highest tier
      // Get the players located in that tier
      // Then split the pot into equal portions

      int* highest_tier;
      std::vector<int> tier_list = player_tiers();
      highest_tier = std::max_element(tier_list.begin(), tier_list.end());

      std::vector<Player*> tier_players;
      tier_players = tier(*highest_tier);

      int split_pot = s_pot / tier_players.size();
      for(Player* i: tier_players)
	i->set_bank(split_pot);
    }
}


bool Paektu::are_players_synchronized()
{
  for(Player &player : s_players)
    {
      // Return false at the first sign of problems.
      if(player.turn() != s_current_turn)
	return false;
    }

  // If  we go about without finding anything, return true.
  return true;
}

Player& Paektu::player_at(int i)
{
  if(i < 0)
    throw std::invalid_argument("Tried to get player at less than zero");
  else if(i > 6)
    throw std::invalid_argument("Tried to get player at more than six");

  return s_players[i];
}

Dealer& Paektu::dealer()      const { return s_dealer; }
long    Paektu::current_pot() const { return s_pot; }
bool    Paektu::is_complete() const { return (s_game_status == COMPLETE); }

std::vector<Player*> Paektu::tier_residents(int tier) 
{
  if(tier > 6)
    throw std::invalid_argument("get_tier supplied with tier > 6");
  else if(tier < 0)
    throw std::invalid_argument("get_tier supplied with tier < 0");

  QVector<Player*> players_of_tier;

  for(Player &player : s_players) 
    {
      if(player.tier() == tier)
	players_of_tier.push_back(&player);
    }

  return players_of_tier;
}

std::array<int, 7> Paektu::tier_list()
{
  std::array<int, 7> tiers;

  for(int i = 0; i < 7; i++)
    {
      tiers[i] = s_players[i].tier();
    }

  return tiers;
}



void Paektu::add_current_pot(long wager) 
{
  s_pot += wager;
}


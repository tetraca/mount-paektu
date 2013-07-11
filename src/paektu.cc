#include "header/paektu.hh"

using namespace std;

// Debug constructor
Paektu::Paektu() : s_deck(40)
{
  stringstream playername;

  // Make a generic set of players with 2000 gold pots
  for(int i = 1; i < s_players.size(); i++) 
    {
      playername << "Player " << i;
      s_players.at(i - 1) = Player (playername.str(), 2000);
      playername.str(string());
    }

  // Build 40 stack deck
  // Since a game is played with 7 players and a dealer
  // Each drawing 5 cards, this will ensure that there will
  // Never be a case where the game ends with an unequal quantity
  // of cards

  // The lcm for us to never run out of cards off round is 10 decks.


  // Set the pot to zero
  // Note the game is PLAYING rather than FINISHED
  s_pot = 0;
  s_game_status = PLAYING;

  // Draw a new round
  draw_new_round();
}

void Paektu::advance_round() 
{
  // Ensure all players are on the same turn and the game hasn't been won
  if(are_players_synchronized() && (s_game_status == PLAYING))
    {
      // Sum the two cards the dealer picked.
      int sum_dealer = 
	s_dealer.get_drop_hand().at(0).get_rank() +
	s_dealer.get_drop_hand().at(1).get_rank();

      int sum_player;

      for(Player &i : s_players)
	{
	  // Sum the two cards the current player picked.
	  sum_player = 
	    i.get_drop_hand().at(0).get_rank() +
	    i.get_drop_hand().at(1).get_rank();

	  // Dealer - Player Relationships
	  if(sum_dealer > sum_player)
	    {
	      if(sum_player == 2 && 
		 sum_dealer == 26)
		{
		  // Exception to the general round-win conditions
		  player_round_won(&i);
		}
	      else
		{
		  player_round_lost(&i);
		}
	    }
	  else if(sum_dealer < sum_player)
	    {
	      player_round_won(&i);
	    }

	  // Player - Player Relationships
	  if((i.get_drop_hand().at(0).get_rank() == i.get_drop_hand().at(1).get_rank())
	     && (get_tier(0).size() < 7))
	    {
	      // The case of doubles.
	      // Doubles will demote a player.
	      // You cannot demote a player if all players are on the first tier

	      if()
		{
		  // If the player is the highest player by ranking
		}
	      else
		{
		  // Demote the highest player if there's a double
		}
	    }
	}
    }
  else
    {
      if(!are_players_synchronized())
	throw runtime_error("Players are not on a concurrent state.");
      else if(!s_game_status == PLAYING)
	throw runtime_error("Game has been finished already.");
    }

  draw_new_round();
}

void Paektu::player_round_won(Player* player)
{
  // Grab all the players being held in the next tier
  int next_tier = player->get_tier() + 1;
  vector<Player*> tier = get_tier(next_tier);

  // Check to see if the tier is full
  if(tier.size() > next_tier)
    {

    }

  // Finally, place the player into a new tier
  player->set_tier(player->get_tier() + 1);
}

void Paektu::player_round_lost(Player* player)
{
  // Subtract the wager from their bank
  player->set_bank(0 - player->get_wager());
  player->set_wager(0);
}


void Paektu::draw_new_round()
{
  // When the deck isn't out of cards try to...
  if(!s_deck.is_out_of_cards())
    {
      try
	{
	  // Draw a new dealer hand.
	  s_dealer.set_full_hand(s_deck.draw_hand(5));
	  // Run the dealer AI, this will go into the drop hand
	  s_dealer.set_drop_hand(s_dealer.choose_cards());

	  // Draw a new hand for each player.
	  for(Player &i : s_players)
	    i.new_hand(&s_deck, 5);

	  // Advance the turn we are currently on.
	  s_current_turn++;
	}
      catch(runtime_error& e)
	{
	  // There shouldn't be any case where we run out of cards
	  // In the middle of a round, but if this happens
	  // Just crash the program,
	  // Because you deserve it for not doing the math correctly.

	  throw runtime_error("Ran out of cards in middle of round.");
	}
    }
  // Otherwise declare the highest tiered player the winner
  else
    {
      s_game_status = COMPLETE;

      // If there is more than one person at the highest level
      // The pot is split

    }
}


bool Paektu::are_players_synchronized()
{
  for(Player i : s_players)
    {
      // Return false at the first sign of problems.
      if(i.get_turn() != s_current_turn)
	return false;
    }

  // If  we go about without finding anything, return true.
  return true;
}

Player Paektu::get_player_at(int i)
{
  if(i < 0)
    throw invalid_argument("Tried to get player at less than zero");
  else if(i > 6)
    throw invalid_argument("Tried to get player at more than six");

  return s_players.at(i);
}

Dealer Paektu::get_dealer()
{
  return s_dealer;
}

std::vector<Player*> Paektu::get_tier(int tier) 
{
  if(tier > 6)
    throw invalid_argument("get_tier supplied with tier > 6");
  else if(tier < 0)
    throw invalid_argument("get_tier supplied with tier < 0");

  vector<Player*> players_of_tier;
  for(Player &i : s_players) 
    {
      if(i.get_tier() == tier)
	players_of_tier.push_back(i);
    }

  return players_of_tier;
}

std::array<int, 7> Paektu::get_player_tiers()
{
  std::array<int 7> tiers;

  for(Player &i : s_players)
    {
      tiers.push_back(i.get_tier());
    }

  return tiers;
}

int Paektu::cmp_tier(int x, int y)
{
  return (x - y);
}

long Paektu::get_current_pot() 
{
  return s_pot;
}

void Paektu::add_current_pot(long wager) 
{
  s_pot += wager;
}

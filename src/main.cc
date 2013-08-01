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


#include <iostream>
#include <sstream>
#include <array>
#include "header/player.hh"
#include "header/player-ai.hh"
#include "header/dealer.hh"
#include "header/paektu.hh"

std::string read_user_input (std::string query);
long get_wager(Player &player);
Card get_card(Player &player);
void round_end_summary(Paektu& game);

int main (int argc, char *argv[]) 
{
  std::string input;
  std::stringstream ss;
  long wager;

  Paektu paektu_test;

  std::array<PlayerAI, 6> ai;

  // Assign each bot a player slot, excluding the first
  for(int i = 1; i < 7; i++)
    ai.at(i - 1) = PlayerAI(&paektu_test.player_at(i), &paektu_test.dealer());


  input = "default";

  std::cout << "Welcome to the mount paektu test utility! Write no to quit at any time." << std::endl;


  // Continue playing until the user says no, or the game is finished
  while(!input.compare("no") || !paektu_test.is_complete()) 
    {
      for(int i = 0; i < 7; i++)
	{
	  // Bot test! Only 'Player 1' is actually real.
	  if(paektu_test.player_at(i).name() != "Player 1")
	    {
	      // The rest consider their turns automatically
	      ai.at(i - 1).consider();
	    }
	  else
	    {
	      // Note which player we are on
	      std::cout << "-> NEW TURN: " 
			<< paektu_test.player_at(i).name() << " <-" << std::endl;

	      // Show the dealer's cards.
	      std::cout << "The dealer has drawn:" << std::endl 
			<< paektu_test.dealer().drop_hand_string() << std::endl;

	      // Show your cards.
	      std::cout << "You have drawn:" << std::endl 
			<< paektu_test.player_at(i).full_hand_string() 
			<< std::endl;

	      // Get the wager
	      try
		{
		  wager = get_wager(paektu_test.player_at(i));
		}
	      catch(std::runtime_error& e)
		{
		  input = "no";
		}

	      // Try to grab cards
	      for(int j = 0; j < 2; j++)
		{
		  try
		    {
		      paektu_test.player_at(i).push_drop_hand(get_card(paektu_test.player_at(i)));
		    }
		  catch(std::runtime_error& e)
		    {
		      // If we throw a runtime error, quit.
		      // This should be checked better.
		      return 0;
		    }
		}
	  
	      // Advance the player's turn
	      paektu_test.player_at(i).advance_turn();
	    }
	}

      // Process all the player's results
      paektu_test.advance_round();

      // Give an end of the round summary.
      round_end_summary(paektu_test);
    }

  return 0;
}


std::string read_user_input(std::string query)
{
  std::string input;

  std::cout << query;
  std::cin >> input;

  std::transform(input.begin(), input.end(), input.begin(), ::tolower);  

  return input;
}

long get_wager(Player &player)
{
  long wager;
  std::string input;
  std::stringstream ss;
  bool validity;

  validity = false;

  // Keep asking until:
  //   We get a valid answer
  //   Or the user wishes to quit
  while(!validity || !input.compare("no"))
    {
      // Get a wager.
      ss << player.name() 
	 << ", what is your wager? [Max " 
	 << player.bank() << "] ";
      input = read_user_input(ss.str());
      ss.str(std::string());

      // Convert to long and place in wager.
      try
	{
	  wager = std::stol(input);
	  player.set_wager(wager);
	  validity = true;
	}
      catch(std::invalid_argument e)
	{
	  // If it's not capable of turning into a long
	  // Make sure to check if the user just doesn't want to quit.

	  if(!input.compare("no"))
	    {
	      std::cout << "Goodbye!" << std::endl;
	      throw std::runtime_error("We want to quit.");
	    }
	  else
	    {
	      std::cout << "Invalid input!" << std::endl;
	    }
	}
    }

  return wager;
}

Card get_card(Player &player)
{

  std::string input;
  bool validity;

  validity = false;

  int selection;
  Card card;

  while(!validity)
    {
      input = read_user_input("Please enter the number of the card you wish to use. [1 - 5] ");

      try
	{
	  selection = std::stoi(input);
	  if((player.drop_hand().size() < 2) &&
	     ((selection > 0) && (selection < 6)))
	    {
	      validity = true;
	      card = player.full_hand().at(selection - 1);
	      std::cout << "You have selected:" << player.full_hand().at(selection -1 ).to_string() << std::endl;
	    }
	  else
	    {
	      std::cout << "Please select a card between 1 and 5." << std::endl;
	    }
	}
      catch(std::invalid_argument e)
	{
	  if(!input.compare("no"))
	    {
	      std::cout << "Goodbye!" << std::endl;
	      throw std::runtime_error("We want to quit.");
	    }
	  else
	    {
	      std::cout << "Invalid input!" << std::endl;
	    }
	}

    }

  return card;
}

void round_end_summary(Paektu& game)
{
  std::cout << "______________________________" << std::endl;
  std::cout << "__/   END OF ROUND SUMMARY   /" << std::endl;
  std::cout << "_/__________________________/ " << std::endl;

  for(int i = 0; i < 7; i++)
    {
      Player player = game.player_at(i);
      std::cout << "Standings for: " << player.name() << std::endl;
      std::cout << "  Tier: " << player.tier() << std::endl;
      std::cout << "  Bank: " << player.bank() << std::endl;
      std::cout << std::endl;
    }
}

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
#include "header/player.hh"
#include "header/dealer.hh"
#include "header/paektu.hh"

std::string read_user_input (std::string query);
long get_wager(Player &player);
Card get_card(Player &player);


int main (int argc, char *argv[]) 
{
  std::string input;
  std::stringstream ss;

  long wager;

  Paektu paektu_test;

  input = "default";

  std::cout << "Welcome to the mount paektu test utility! Write no to quit at any time." << std::endl;

  while(input.compare("no")) 
    {
      for(int i = 0; i < 7; i++)
	{
	  // Note which player we are on
	  std::cout << "+---+ PLAYER " << i + 1 << " +---+" << std::endl;

	  // Show the dealer's cards.
	  std::cout << "The dealer has drawn:" << std::endl <<
	    (paektu_test.get_dealer()).get_drop_hand_string() << std::endl;

	  // Show your cards.
	  std::cout << "You have drawn:" << std::endl <<
	    (paektu_test.get_player_at(i)).get_full_hand_string() << std::endl;

	  // Get the wager
	  try
	    {
	      wager = get_wager(paektu_test.get_player_at(i));
	    }
	  catch(std::runtime_error e)
	    {
	      input = "no";
	    }

	  // Try to grab cards
	  for(int j = 0; j < 2; j++)
	    {
	      try
		{
		  paektu_test.get_player_at(i).add_to_drop_hand(get_card(paektu_test.get_player_at(i)));
		}
	      catch(std::runtime_error& e)
		{
		  return 0;
		}
	    }

	}

      paektu_test.advance_round();
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
      ss << player.get_name() 
	 << ", what is your wager? [Max " 
	 << player.get_bank() << "] ";
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
      input = read_user_input("Please enter the number of the card you wish to use: ");

      try
	{
	  selection = std::stoi(input);
	  if((player.get_drop_hand().size() < 2) &&
	     ((selection > 0) && (selection < 6)))
	    {
	      validity = true;
	      card = player.get_full_hand().at(selection - 1);
	      std::cout << "You have selected:" << player.get_full_hand().at(selection -1 ).to_string() << std::endl;
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

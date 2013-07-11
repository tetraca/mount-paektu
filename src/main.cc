#include <iostream>
#include "header/player.hh"
#include "header/dealer.hh"
#include "header/paektu.hh"

std::string read_user_input (std::string query);
long get_wager(Paektu game);
Card* get_card(Paektu game, Player player);


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
	  // Show the dealer's cards.
	  std::cout << "The dealer has drawn:" << std::endl <<
	    (paektu_test.get_dealer()).get_drop_hand_string() << std::endl;

	  // Show your cards.
	  std::cout << "You have drawn:" << std::endl <<
	    (paektu_test.get_player_at(i)).get_full_hand_string() << std::endl;

	  // Get the wager
	  try
	    {
	      wager = get_wager(paektu_test);
	    }
	  catch(std::runtime_error e)
	    {
	      input = "no";
	    }

	  // Try to grab cards
	  for(int i = 0; i < 2; i++)
	    {
	      std::cout << "Your cards are:" << std::endl <<
		paektu_test.get_player_at(i).get_full_hand_string() << std::endl;
	      
	     
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

long get_wager(Paektu game)
{
  long wager;
  std::string input;
  stringstream ss;
  bool validity;

  validity = false;

  // Keep asking until:
  //   We get a valid answer
  //   Or the user wishes to quit
  while(!validity || input.compare("no"))
    {
      // Get a wager.
      ss << game.get_player_at(i).get_name() 
	 << ", what is your wager? [Max " 
	 << game.get_player_at(i).get_bank() << "] ";
      input = read_user_input(ss.str());
      ss.str(std::string());

      // Convert to long and place in wager.
      try
	{
	  wager = std::stol(input);
	  game.get_player_at(i).set_wager(wager);
	  validity = true;
	}
      catch(std::invalid_argument e)
	{
	  if(!input.compare("no"))
	    {
	      std::cout << "Goodbye!" << std::endl;
	      throw runtime_error("We want to quit.");
	    }
	  else
	    {
	      std::cout << "Invalid input!" << std::endl;
	    }
	}
    }

  return wager;
}

Card* get_card(Paektu *game, Player player)
{

  std::string input;
  bool validity;

  validity = false;

  while(!validity)
    {
      input = read_user_input("Please enter the number of the card you wish to use:");

      try
	{

	}
      catch()
	{

	}

    }
}

#include <iostream>
#include "header/player.hh"

using namespace std;

Player::Player ()
{
  s_name  = "UNDEFINED_PLAYER";
  s_bank  = 200;
  s_wager = 0;
  s_turn  = 0;
  s_tier  = 0;
}

// Constructors
Player::Player (string name, long bank) 
{
  if(name.empty())
    throw invalid_argument("Player name is blank.");
  if(bank < 1)
    throw invalid_argument("Player cannot play if their bank is empty.");

  s_name  = name;
  s_bank  = bank;
  s_wager = 0;
  s_turn  = 0;
  s_tier  = 0;
}

// General Functions
void Player::new_hand (Deck* deck, int hand_size) 
{
  s_full_hand = deck->draw_hand(hand_size);
}



// Accessor Functions

// For Name
string Player::get_name () 
{
  return s_name;
}

// For bank
long Player::get_bank () 
{
  return s_bank;
}
void Player::set_bank (long displacement) 
{
  s_bank = s_bank + displacement;
}

// For Wager
long Player::get_wager () 
{
  return s_wager;
}

void Player::set_wager (long wager) 
{
  if (wager < 0)
    throw invalid_argument("Player has attempted to place negative wager.");
  else if(wager > get_bank())
    throw invalid_argument("Player has attempted to place a wager greater than the amount of money he has.");

  s_wager = wager;
}

// For the current tier
int Player::get_tier ()
{
  return s_tier;
}

void Player::set_tier (int tier)
{
  if(tier < 0)
    throw invalid_argument("Player has been placed in negative tier.");
  else if(tier > 6)
    throw invalid_argument("Player has been placed in excessive tier.");
  s_tier = tier;
}

// For the current turn
int Player::get_turn()
{
  return s_turn;
}

void Player::advance_turn()
{
  s_turn++;
}


// For the Drop Hand
vector<Card> Player::get_drop_hand () 
{
  return s_drop_hand;
}
std::string Player::get_drop_hand_string()
{
  stringstream ss;

  for(int i = 0; i < s_drop_hand.size(); i++)
    {
      ss << i + 1 << ". " << s_drop_hand.at(i).to_string() << endl;
    }

  return ss.str();
}

void Player::set_drop_hand (vector<Card> hand) 
{
  // TODO: Make sure drop hand contains valid values. 
  s_drop_hand = hand;
}



// For the Full Hand
vector<Card> Player::get_full_hand() 
{
  return s_full_hand;
}
string Player::get_full_hand_string()
{
  stringstream ss;

  for(int i = 0; i < s_full_hand.size(); i++)
    {
      ss << i + 1 << ". " << s_full_hand.at(i).to_string() << endl;
    }

  return ss.str();
}

void Player::set_full_hand(vector<Card> hand) 
{
  s_full_hand = hand;
}

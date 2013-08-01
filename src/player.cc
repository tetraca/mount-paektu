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

/* * * * * * * * * * * 
 * Constructors
 * * * * * * * * * * */
Player::Player () : s_name("UNDEFINED_PLAYER"),
		    s_bank(1),
		    s_wager(0),
		    s_turn(0),
		    s_tier(7)
{
  // This is a blank character template
  // For the purposes of allowing you to initialize
  // an array of players before knowing who they are
}

Player::Player (std::string name, long bank) : s_wager(0),
					       s_turn(0),
					       s_tier(7)
{
  if(name.empty())
    throw std::invalid_argument("Player name is blank.");
  if(bank < 1)
    throw std::invalid_argument("Player cannot play if their bank is empty.");

  s_name  = name;
  s_bank  = bank;
}

/* * * * * * * * * *
 * General Functions
 * * * * * * * * * */
void Player::new_hand (Deck* deck, int hand_size) 
{
  s_drop_hand.clear();
  s_full_hand = deck->draw_hand(hand_size);
}

void Player::add_bank (long displacement) 
{
  s_bank = s_bank + displacement;
}

void Player::set_wager (long wager) 
{
  if (wager < 0)
    throw std::invalid_argument("Player has attempted to place negative wager.");
  else if(wager > bank())
    throw std::invalid_argument("Player has attempted to place a wager greater than the amount of money he has.");

  s_wager = wager;
}

void Player::promote_tier ()
{
  // Promote a player only if they are below tier 1
  if(s_tier > 1)
    s_tier--;
}

void Player::demote_tier ()
{
  // Demote a player only if they are on a tier lower than 7
  if(s_tier < 7)
    s_tier++;
}

void Player::advance_turn ()
{
  s_turn++;
}

void Player::push_drop_hand(Card card)
{
  if(s_drop_hand.size() < 3)
    s_drop_hand.push_back(card);
  else
    throw std::invalid_argument("Cannot add more cards to your hand");
}

bool Player::compare(const Player& x, const Player& y)
{
  return x.tier() > y.tier();
}

// Accessor Functions
std::string Player::name () const { return s_name; }
long        Player::bank () const { return s_bank; }
long        Player::wager() const { return s_wager;} 
int         Player::tier () const { return s_tier; }
int         Player::turn () const { return s_turn; }

std::vector<Card> Player::drop_hand() const { return s_drop_hand; }
std::vector<Card> Player::full_hand() const { return s_full_hand; }


// Display functions purely for the test client
std::string Player::drop_hand_string()
{
  std::stringstream ss;

  for(int i = 0; i < s_drop_hand.size(); i++)
    ss << i + 1 << ". " << s_drop_hand.at(i).to_string() << std::endl;
  
  return ss.str();
}

std::string Player::full_hand_string()
{
  std::stringstream ss;

  for(int i = 0; i < s_full_hand.size(); i++)
    ss << i + 1 << ". " << s_full_hand.at(i).to_string() << std::endl;

  return ss.str();
}


// Deprecated functions
void Player::set_drop_hand (std::vector<Card> hand) 
{
  // TODO: Make sure drop hand contains valid values. 
  s_drop_hand = hand;
}



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

<<<<<<< HEAD
Player::Player()
=======
using namespace std;

Player::Player ()
>>>>>>> parent of b87a8a7... Minor bug fixes
{
  // This function exists for debug purposes
  // Don't actually create a blank player ever.
  s_name  = QString("UNDEFINED_PLAYER");
  s_bank  = 1;
  s_wager = 0;
  s_turn  = 0;
  s_tier  = 0;
}

// Constructors
<<<<<<< HEAD
Player::Player(QString name, long bank) : s_wager(0), s_turn(0), s_tier(0), s_full_hand(5), s_drop_hand(0)
{
  if(name.isEmpty())
    throw std::invalid_argument("Player name is blank.");
=======
Player::Player (string name, long bank) 
{
  if(name.empty())
    throw invalid_argument("Player name is blank.");
>>>>>>> parent of b87a8a7... Minor bug fixes
  if(bank < 1)
    throw invalid_argument("Player cannot play if their bank is empty.");

  s_name  = name;
  s_bank  = bank;
}

// General Functions
void Player::new_hand(Deck deck, int hand_size) 
{
  // This should be the only way to remove the full hand
  s_full_hand.clear();
  QVector<Card> temp(deck.draw_hand(hand_size));
  for(int i = 0; i < hand_size; i++)
    s_full_hand.append(temp[i]);

  std::cout << "Dispensing " << s_full_hand.size() << " cards" << std::endl;
}



// Accessor Functions

// For Name
<<<<<<< HEAD
QString Player::name() const
=======
string Player::get_name () 
>>>>>>> parent of b87a8a7... Minor bug fixes
{
  return s_name;
}

// For bank
long Player::bank() const
{
  return s_bank;
}
void Player::set_bank(long displacement) 
{
  s_bank = s_bank + displacement;
}

// For Wager
long Player::wager() const
{
  return s_wager;
}

void Player::set_wager(long wager) 
{
  if (wager < 0)
<<<<<<< HEAD
    throw std::invalid_argument("Player has attempted to place negative wager.");
  else if(wager > bank())
    throw std::invalid_argument("Player has attempted to place a wager greater than the amount of money he has.");
=======
    throw invalid_argument("Player has attempted to place negative wager.");
  else if(wager > get_bank())
    throw invalid_argument("Player has attempted to place a wager greater than the amount of money he has.");
>>>>>>> parent of b87a8a7... Minor bug fixes

  s_wager = wager;
}

// For the current tier
int Player::tier() const
{
  return s_tier;
}

void Player::promote_player()
{
<<<<<<< HEAD
  if(s_tier < 6)
    s_tier++;
  else
    throw std::runtime_error("Attempted to promote player beyond winning capacity");
}

void Player::demote_player()
{
  if(s_tier > 0)
    s_tier--;
  else
    throw std::runtime_error("Attempted to demote player beyond lowest rung");
=======
  if(tier < 0)
    throw invalid_argument("Player has been placed in negative tier.");
  else if(tier > 6)
    throw invalid_argument("Player has been placed in excessive tier.");
  s_tier = tier;
>>>>>>> parent of b87a8a7... Minor bug fixes
}


// For the current turn
int Player::turn() const
{
  return s_turn;
}

void Player::advance_turn()
{
  s_turn++;
}


// For the Drop Hand
<<<<<<< HEAD
QVector<Card> Player::drop_hand() const 
=======
vector<Card> Player::get_drop_hand () 
>>>>>>> parent of b87a8a7... Minor bug fixes
{
  return s_drop_hand;
}

QString Player::drop_hand_string() const
{
<<<<<<< HEAD
  // This exists for debug purposes
  QString str;

  for(int i = 0; i < s_drop_hand.size(); i++)
    {
      str.append(QString::number(i + 1));
      str.append(". ");
      str.append(s_drop_hand[i].to_string()); 
      str.append("\n");
    }

  return str;
=======
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
>>>>>>> parent of b87a8a7... Minor bug fixes
}

void Player::add_to_drop_hand (Card card)
{
  if(s_drop_hand.size() < 3)
    s_drop_hand.push_back(card);
  else
    throw std::invalid_argument("Cannot add more cards to your hand");
}

void Player::clear_drop_hand()
{
  s_drop_hand.clear();
}


// For the Full Hand
<<<<<<< HEAD
QVector<Card> Player::full_hand() const
{
  return s_full_hand;
}
QString Player::full_hand_string() const
{
  QString str;
=======
vector<Card> Player::get_full_hand() 
{
  return s_full_hand;
}
string Player::get_full_hand_string()
{
  stringstream ss;
>>>>>>> parent of b87a8a7... Minor bug fixes

  // This exists purely for debug purposes
  for(int i = 0; i < s_full_hand.size(); i++)
    {
<<<<<<< HEAD
      str.append(QString::number(i + 1));
      str.append(". ");
      str.append(s_full_hand[i].to_string());
      str.append("\n");
=======
      ss << i + 1 << ". " << s_full_hand.at(i).to_string() << endl;
>>>>>>> parent of b87a8a7... Minor bug fixes
    }

  return str;
}

<<<<<<< HEAD

bool Player::cmp_player(const Player& x, const Player& y)
=======
void Player::set_full_hand(vector<Card> hand) 
>>>>>>> parent of b87a8a7... Minor bug fixes
{
  return x.tier() < y.tier();
}


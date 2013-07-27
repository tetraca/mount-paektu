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

#include "header/player.hh"

Player::Player()
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
Player::Player(QString name, long bank) 
{
  if(name.isEmpty())
    throw std::invalid_argument("Player name is blank.");
  if(bank < 1)
    throw std::invalid_argument("Player cannot play if their bank is empty.");

  s_name  = name;
  s_bank  = bank;
  s_wager = 0;
  s_turn  = 0;
  s_tier  = 0;
}

// General Functions
void Player::new_hand(Deck* deck, int hand_size) 
{
  // This should be the only way to remove the full hand
  s_full_hand.clear();
  s_full_hand = deck->draw_hand(hand_size);
}



// Accessor Functions

// For Name
QString Player::name() const
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
    throw std::invalid_argument("Player has attempted to place negative wager.");
  else if(wager > bank())
    throw std::invalid_argument("Player has attempted to place a wager greater than the amount of money he has.");

  s_wager = wager;
}

// For the current tier
int Player::tier() const
{
  return s_tier;
}

void Player::promote_player()
{
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
QVector<Card> Player::drop_hand() const 
{
  return s_drop_hand;
}

QString Player::drop_hand_string() const
{
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
QVector<Card> Player::full_hand() const
{
  return s_full_hand;
}
QString Player::full_hand_string() const
{
  QString str;

  // This exists purely for debug purposes
  for(int i = 0; i < s_full_hand.size(); i++)
    {
      str.append(QString::number(i + 1));
      str.append(". ");
      str.append(s_full_hand[i].to_string());
      str.append("\n");
    }

  return str;
}


bool Player::cmp_player(const Player& x, const Player& y)
{
  return x.tier() < y.tier();
}


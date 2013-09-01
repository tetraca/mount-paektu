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

#include "header/playerslot.hh"

const Glib::ustring PlayerSlot::PLAYER_DEFAULT_AVATAR("../img/player.png");
const Glib::ustring PlayerSlot::PLAYER_CARD_BACK("../img/b1fv.png");

PlayerSlot::PlayerSlot() : s_player_avatar(PLAYER_DEFAULT_AVATAR),
			   s_player_name(Glib::ustring("UNINITIALIZED_PLAYER")),
			   s_player(0)
{
  s_drop_hand.at(0).set(PLAYER_CARD_BACK);
  s_drop_hand.at(1).set(PLAYER_CARD_BACK);

  pack_start(s_player_name);
  pack_start(s_player_avatar);
  pack_end(s_drop_hand.at(0));
  pack_end(s_drop_hand.at(1));
}

PlayerSlot::PlayerSlot(Player* player) : s_player_avatar(PLAYER_DEFAULT_AVATAR),
					 s_player_name(Glib::ustring(player->name()))
{
  if(player != NULL)
    {
      if(player->drop_hand().size() != 0)
	{
	  s_drop_hand.at(0).set(card_path(player->drop_hand().at(0)));
	  s_drop_hand.at(1).set(card_path(player->drop_hand().at(1)));
	}
      else
	{
	  s_drop_hand.at(0).set(PLAYER_CARD_BACK);
	  s_drop_hand.at(1).set(PLAYER_CARD_BACK);
	}
    }

  pack_start(s_player_name);
  pack_start(s_player_avatar);
  pack_end(s_drop_hand.at(0));
  pack_end(s_drop_hand.at(1));
}


void PlayerSlot::update()
{
  // Update the state of the cards
  // It's up to the implementation to update at the correct time.
  s_drop_hand.at(0).set(card_path(s_player->drop_hand().at(0)));
  s_drop_hand.at(1).set(card_path(s_player->drop_hand().at(1)));
}


void PlayerSlot::assign(Player* player)
{
  // Assign a player to this empty slot.
  // Update the view.
  if(player != NULL)
    {
      s_player = player;
      s_player_name.set_label(Glib::ustring(s_player->name()));
      //update();
    }
  else
    {
      throw std::runtime_error("Attempted to assign nonexistant player.");
    }
}

Glib::ustring PlayerSlot::card_path(Card card)
{
  // Offsetting a number by this much will get you to the next card in that series
  // 0 - Clubs 
  // 1 - Spades 
  // 2 - Hearts
  // 3 - Diamonds
  // The images are stored ace down, thus face cards are at values 5 - 16
  // (NOTE: These values are defined in the Card::Suit enumeration)



  // Regardless of what card we do return, where we find them is always the same
  // The img directory in the base of the distribution.
  Glib::ustring path("../img/");

  if(card.suit() < 4)
    path += card.suit() + ".png";
  else
    {
      // The cards are found in reverse
      int rankoff = 52 - (card.rank() * 4) + card.suit();

      path += rankoff + ".png";
    }

  return path;
}

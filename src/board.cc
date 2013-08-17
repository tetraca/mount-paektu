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

#include "header/board.hh"

Board::Board(std::array<Player*, 7> players) : Gtk::Grid(),
					       s_players(players)
{
  // Attach the board's slots, bottom to top
  // In a pyramid fashion on a 14x7 grid
  // i is the index of the array during this process
  int i = 0;
  for(int vert = 7; vert > 0; vert--)
    {
      for(int horiz = 0; horiz < 14; horiz++)
	{
	  // Skip is the amount to offset the pyramid every level
	  // As spaces before the skip are blank
	  // We also want to fill up every other space on the 14x7 grid

	  int skip = 7 - vert;
	  bool fill_flag = (((horiz - skip) % 2) != 0);

	  if((horiz > skip) && fill_flag && (horiz < (14 - skip)))
	    {
	      // Fill the very bottom row with players
	      if(vert == 7)
		s_slots.at(i).set_player(s_players[i]);

	      attach(s_slots.at(i), horiz, vert, 1, 1);
	      i++;
	    }
	}
    }
}

void Board::update()
{
  // Clear the status of all slots
  for(BoardSlot &slot : s_slots)
    slot.clear();

  // Fill the slots with their new values
  for(Player* player : s_players)
    {
      // Grab pointers to slots available on the player's current tier
      // Then stuff the player in the next available slot
      std::vector<BoardSlot*> tier_slot = slots(player->tier());
      for(BoardSlot *slot : tier_slot)
	if(!slot->is_occupied())
	  slot->set_player(player);
    }

}

std::vector<BoardSlot*> Board::slots(int tier)
{
  // Find the beginning and endpoints of the slots
  // belonging to the tier requested
  int end;
  for(int i = 7; i > tier; i--)
    end += i;

  int begin = end - tier;

  // Stuff the lvalues of each slot into a vector which
  // will be returned
  std::vector<BoardSlot*> tier_slots;
  for(int i = begin; i <= end; i++)
    tier_slots.push_back(&s_slots[i]);

  return tier_slots;
}

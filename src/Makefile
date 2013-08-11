# This file is part of Mount Paektu.
#
# Mount Paektu is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3.
#
# Mount Paektu is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Mount Paektu.  If not, see <http://www.gnu.org/licenses/>.


# Setting some things about the environment we're using
CC=g++
CFLAGS=--std=c++11
default: model


# "Model" builds
# Model is a text based version of paektu for testing game logic
MODELTARGET=paektu
MODELOBJ=card.o deck.o player.o dealer.o player-ai.o paektu.o
model: paektu.o
	$(CC) $(CFLAGS) -o $(MODELTARGET) main.cc $(MODELOBJ)



# "View" builds
# View builds use gtkmm and are for testing the GUI
VIEWTARGET=paektu-gui
VIEWOBJ=main-window.o board.o boardslot.o
VIEWFLAGS=`pkg-config gtkmm-3.0 --cflags --libs`
view: main-window.o paektu.o
	$(CC) $(CFLAGS) $(VIEWFLAGS) -o $(VIEWTARGET) $(MODELOBJ) $(VIEWOBJ)



# Object definitions: Model related
card.o:
	$(CC) $(CFLAGS) -c -o card.o card.cc

deck.o: card.o
	$(CC) $(CFLAGS) -c -o deck.o deck.cc

player.o: card.o
	$(CC) $(CFLAGS) -c -o player.o player.cc

dealer.o: player.o
	$(CC) $(CFLAGS) -c -o dealer.o dealer.cc

player-ai.o: player.o
	$(CC) $(CFLAGS) -c -o player-ai.o player-ai.cc

paektu.o: card.o deck.o player.o dealer.o player-ai.o
	$(CC) $(CFLAGS) -c -o paektu.o paektu.cc 


# Object definitions: View related
boardslot.o:
	$(CC) $(CFLAGS) $(LIBFLAGS) -c -o boardslot.o boardslot.cc

board.o: boardslot.o
	$(CC) $(CFLAGS) $(LIBFLAGS) -c -o board.o board.cc

main-window.o: board.o
	$(CC) $(CFLAGS) $(LIBFLAGS) -c -o main-window.o main-window.cc



# Useful non-build related functions
clean:
	rm *.o
	rm $(TARGET)

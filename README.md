# Mount Paektu
Mount Paektu is a Korean gambling card game played by 7 players implemented in C++. Currently, Mount Paektu is not complete.

Mount Paektu is licensed under GPL v3. See the [LICENSE](/LICENSE) file for details.

## Requirements
Mount Paektu requires:
* Gtk+ 3.0
* Boost

Though the boost portion is currently not implemented.

## Rules
The game is played with 10 decks of cards and 7 players and a computer-based dealer. Players must compete against themselves to get to the top of the legendary Mount Paektu while the dealer attempts to slow their progress. The player who reaches the top of the mountain first is the victor.

### Setting up
The players have representative tokens which are placed on a triangular board with 7 tiers, the top tier being tier 1 and the bottom tier 7. Each tier can hold as many players as the number of the tier itself. Players start at the bottom tier.

### Drawing a round
All players, including the dealer draw 5 cards from the deck. The dealer will go first. Players pick two cards from their hand to place face down along with their bets in a clockwise fashion. After everyone is done selecting their cards, they are revealed.

#### Regular Hands
For the purposes of hands the values of cards are based on their face value - A is 1, 2 is 2, etc. Face cards are counted 11, 12, and 13 respectively. Hands are summed together. Suit is irrelevant. The maximum value hand is 2 Kings, which can be beaten only by two aces. 

Players who beat the dealer will keep their bet and raise their position. Players who lose will fall and have their bet added to the pot, which will be given to who reaches the highest position in the mountain.

#### Special Hands
Players who hold doubles in their drop can lower the score of the highest hand by the face value of the double. If this causes the player to lose the round, he drops in tier and the player with the doubles will acquire his bet.

A dealer can also have doubles, which lowers the status of everyone's hand. 

### Rising and falling
When rising or falling to a tier that is completely full the player with the weakest hand will be dropped to the previous tier. You cannot fall below tier 7. However, if you lack the funds to bet, you will be out of the game. The game immediately end when a player occupied tier 1.

### Victory


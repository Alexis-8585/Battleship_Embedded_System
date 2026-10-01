# Battleship

Battleship board game with digital matrix LED boards, with physical button inputs, developed on an arduino board.

## Hardware components 
The Adafruit Feather STM32F04 Series Board is compatible with many of the existing Arduino libraries and served as our main controller, which allowed us to handle the processing and communication of data between all the project components. The two 8x8 LED matrices serve as the output to the user communicating each action chosen to the player. 5 buttons serve as the input of the user which can let the software know of the movements a player wishes to make. Since the LED matrices draw lots of current, we also have a battery pack of 6V to properly power the LED matrices. 

## Software Implementation

The way we chose to develop the game logic was by implementing a state machine on primary.ino with the following states:
-placeP1 :Player 1 places their boats at the start of the game
-placeP2 :Player 2 places their boats at the start of the game
-chooseP1 : Player 1 attacking
-chooseP2 : Player 2 attacking
-endGame : End of Game, resets back to placeP1 for a new game

Used Object Oriented Programing to implement the game board and boat object. 

![Design](<Battleship design.png>)


## Depencencies
To run this code, the following libraries need to be added within the Arduino IDE:
- Adafruit GFX Library 
- Adafruit NeoMatrix
- Adafruit NeoPixel

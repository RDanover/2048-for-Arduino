##### 2048 For Arduino

### Introduction:
This project is a clone of 2048 which has been modified to work on the 2 X 16 LCD. The game works by spawning in tiles on the 8 X 2 gameboard and having the user combine tiles by sliding them next to each other using the joystick. The user will win if they create a tile with the value of 2048. The user will lose if they can no longer combine any tiles on the screen. The user will also see their score during gameplay to the right of the gameboard which will show the total score of tiles they have combined.

### Complexities
The first complexity is the spawning of tiles randomly which was implemented successfully using a random number generator that I wrote.
The second complexity is the writing to the lcd screen by pixels. This was not fully implemented as I created new characters and had them printed to a position on the lcd screen. I did create characters for numbers 16, 32, 64, 128, 256, 512, 1024, 2048 so that way they only took up a single tile. This complexity was difficult due to the size of the lcd screen which I did not know when I proposed this game.
The third complexity is the system of determining when the user is out of moves. This was successfully implemented and successfully tells the game when the user has lost the game.
The fourth complexity is the alternate game mode which was not implemented in any capacity.

### User Guide
The user will use the joystick button by clicking it to begin the game. Clicking the button during gameplay will reset the game and send the user back to the start menu. The user will move the tiles on the lcd screen by moving the joystick up, down, left, right which will move the tiles in the respective direction. When the user loses or wins they can click the joystick button again to return to the start screen. The user will also see their score to the right of the gameboard which will be separated by a line on the screen. The symbols for the respective numbers are:

<img width="268" alt="Screenshot 2023-10-07 at 4 14 22 PM" src="https://github.com/RDanover/2048-For-Arduino/assets/60625627/f1ffeccf-199a-4cd0-b196-45616d5184e0">
                   
### Hardware Components Used
- Computing:
    Elegoo Uno R3 microcontroller
  
- Inputs:
    Joystick module
    Reset and Start button
  
- Outputs:
    Lcd screen
    Potentiometer
  
- Microcontroller pins:
  - Joystick:
      X axis: A0
      Y axis: A1
      Button: 2
    
  - LCD Screen:
      Vss : GND
      Vcc: 5V
      V0: Potentiometer
      RS:D4
      RW: GND
      E:D5
      Db4-Db7: D8-D11
      A:5V
      K:GND
  
 - Potentiometer

### Software Libraries Used
LiquidCrystal.h: I used this inorder to write and print to the lcd screen.

### Wiring Diagrams

<img width="542" alt="Screenshot 2023-10-07 at 4 15 14 PM" src="https://github.com/RDanover/2048-For-Arduino/assets/60625627/df9376ad-d448-497e-b7e5-177413322f4e">

<img width="674" alt="Screenshot 2023-10-07 at 4 15 00 PM" src="https://github.com/RDanover/2048-For-Arduino/assets/60625627/42b5f25b-4e22-4ac4-bad4-6c1b72822d41">

### Task Diagram
<img width="635" alt="Screenshot 2023-10-07 at 4 15 29 PM" src="https://github.com/RDanover/2048-For-Arduino/assets/60625627/34a1e8aa-e9c6-4af4-a4a9-349b5c3a2293">

### SynchSM Diagrams
<img width="717" alt="Screenshot 2023-10-07 at 4 15 52 PM" src="https://github.com/RDanover/2048-For-Arduino/assets/60625627/f26734a7-64e9-4e21-966e-afb2564b034e">

<img width="480" alt="Screenshot 2023-10-07 at 4 16 08 PM" src="https://github.com/RDanover/2048-For-Arduino/assets/60625627/a41e6c32-a187-4a4c-a279-06eef24e046d">

### Final Demo:

https://youtu.be/GYvozkpuCbw


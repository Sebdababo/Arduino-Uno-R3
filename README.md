# Arduino Uno R3 Projects

This repository contains two Arduino projects using the Arduino Uno R3:

1. [Morse Code Translator](#1-morse-code-translator)
2. [Mini Game with LCD](#2-mini-game-with-lcd)

## 1. Morse Code Translator

### Description
The Morse Code Translator project allows you to select letters from the alphabet using a joystick and convert them into Morse code. The translated Morse code is played through a buzzer and displayed on an LCD screen.

### Components Required
- Arduino Uno R3
- LCD display (20x4) with I2C interface
- Joystick module (analog joystick)
- Push buttons (3 buttons)
- Buzzer
- Connecting wires
- Breadboard

### Circuit Diagram
- Connect the joystick's vertical movement pin to `A0`.
- Connect a select button to digital pin `2` for selecting letters.
- Connect additional buttons to digital pins `3`, `4`, and `5` for reset, transcribe, and remove functionalities.
- Connect the buzzer to digital pin `10`.
- Connect the LCD using I2C with the address `0x27`.

### Setup
1. Install the required libraries: `LiquidCrystal_I2C.h`.
2. Build the circuit according to the diagram provided above.
3. Upload the `translator.ino` sketch to your Arduino Uno R3.

### How to Use
1. Use the joystick to navigate through the alphabet.
2. Press the select button to add the current letter to your string.
3. Use the reset button to clear the string, the transcribe button to convert the string to Morse code, and the remove button to delete the last character.
4. The selected string and current letter are displayed on the LCD.
5. The Morse code will play through the buzzer.

## 2. Mini Game with LCD

### Description
The Mini Game project is a simple game displayed on an LCD screen using two analog joysticks. One joystick controls a player character, and the other joystick controls a point character. The goal is for the player to reach the point to earn a score.

### Components Required
- Arduino Uno R3
- LCD display (20x4) with I2C interface
- Two joystick modules (analog joysticks)
- Two push buttons
- Connecting wires
- Breadboard

### Circuit Diagram
- Connect the first joystick's `x` and `y` pins to `A0` and `A1`, respectively.
- Connect the second joystick's `x` and `y` pins to `A3` and `A2`, respectively.
- Connect the select button for the first joystick to digital pin `2`.
- Connect the select button for the second joystick to digital pin `4`.
- Connect the LCD using I2C with the address `0x27`.

### Setup
1. Install the required libraries: `LiquidCrystal_I2C.h`.
2. Build the circuit according to the diagram provided above.
3. Upload the `mini game.ino` sketch to your Arduino Uno R3.

### How to Use
1. Use the first joystick to move the player character (represented by a custom character on the LCD).
2. Use the second joystick to move the point character (also represented by a custom character).
3. If the player character reaches the point character, a collision is detected, and the score is incremented.
4. Pressing the select button for the player resets the player's position and score.
5. Pressing the select button for the point shows the current score on the LCD.

# Project Images
![image](https://github.com/user-attachments/assets/169f0f47-2226-4746-aecd-3924a14045fc)


![image](https://github.com/user-attachments/assets/ac9b5c8a-db73-4e16-b898-b15178b7b33d)



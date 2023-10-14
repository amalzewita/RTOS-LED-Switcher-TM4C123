# TM4C123GH6PM LED State Manager

This repository contains embedded system code designed for the TM4C123GH6PM microcontroller. The primary function is to adjust the LED's color state based on user button inputs. It offers a basic scheduling mechanism to manage tasks related to reading the button states and updating the LED display.

## Table of Contents
1. [Introduction](#tm4c123gh6pm-led-state-manager)
2. [Features](#features)
3. [How It Works](#how-it-works)
    - [Initialization](#initialization)
    - [Button Reading](#button-reading)
    - [LED Updating](#led-updating)
4. [Setup](#setup)
5. [Contributions](#contributions)

## Features:
- Dynamically change between four LED states: White, Red, Green, and Blue.
- The LED color shifts based on the button(s) pressed.
- Uses a simple task scheduler for efficient multitasking.

## How It Works:
1. **Initialization**: When the system starts, it configures the GPIO ports for the LED and buttons.
2. **Button Reading**: The state of the buttons is continuously checked. There are three primary conditions:
   - Both buttons pressed: Sets the LED to White.
   - Button1 pressed: Cycles the LED color to the next state.
   - Button2 pressed: Cycles the LED color to the previous state.
3. **LED Updating**: Depending on the current state, the LED displays the corresponding color.

## Setup:
1. Ensure you have the necessary libraries:
   - `TM4C123GH6PM.h`: MCU-specific definitions.
   - `Port_Config.h`: Port configurations for the MCU.
   - `SysTick.h`: System tick timer header for task scheduling.
   - `scheduler.h`: Task scheduler library.
2. Load the code onto the TM4C123GH6PM microcontroller using your preferred method or IDE (e.g., Code Composer Studio, Keil uVision).
3. Power up the board and observe the LED behavior based on button presses.

## Contributions:
Feel free to fork this repository and contribute. Pull requests are welcome!

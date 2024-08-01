# Arduino Train System

## Description
This project is designed to create a train system with 6 stations using Arduino. Each station is equipped with an IR sensor, a servo motor, and an LCD display. The Arduino controls the movement of trains between stations and updates the LCD messages accordingly.

## Features
- **Train Stations**: Six stations, each with an IR sensor, servo motor, and LCD display.
- **Arduino Controlled**: The entire system is controlled by an Arduino, managing train movements and LCD updates.
- **Sensor and Servo Integration**: Each station uses an IR sensor to detect train positions and a servo motor to control train movements.
- **LCD Display Updates**: LCD displays at each station show relevant messages when a train arrives or leaves.

## Components
1. **Servo and Sensor Pins**:
   - The servo motors and IR sensors are connected to specific pins on the Arduino.
   - Each station has unique pin assignments for the IR sensor and servo motor.

2. **LCD Addresses**:
   - Each station has an LCD display with a unique I2C address for communication.
   - The addresses are configured in the Arduino code to ensure correct data display.

3. **Train Initialization**:
   - Trains are initialized to their starting positions.
   - IR sensors detect the presence of trains at specific stations during startup.

4. **Movement Logic**:
   - Trains move from one station to another following a predefined sequence.
   - The movement is controlled by the Arduino, which updates the servos and LCD displays accordingly.

5. **Functions**:
   - Functions are implemented to handle various tasks:
     - **Move Trains**: Controls the movement of trains between stations.
     - **Detect Train Positions**: Uses IR sensors to determine the current position of trains.
     - **Wait for Trains at Stations**: Ensures trains stop at each station for a set period.
     - **Update LCD Displays**: Changes the messages on the LCD displays based on train movements.

## Learning Objectives
This project provides a hands-on opportunity to learn how to integrate sensors, servos, and LCDs with Arduino. It covers:
- Interfacing IR sensors with Arduino for position detection.
- Controlling servo motors to manage train movements.
- Using I2C communication to update LCD displays.
- Writing Arduino code to automate a sequence of tasks.

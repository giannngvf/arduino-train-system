# arduino-train-system
This project is for a train system with 6 stations. Each station has an IR sensor and a servo motor, and an LCD display. The train system uses an Arduino to control the movement of trains and update LCD messages.

Servo and Sensor Pins: The servo motors and IR sensors are connected to specific pins on the Arduino.
LCD Addresses: Each station has an LCD display with a unique I2C address.
Train Initialization: Trains are given initial positions and detected at certain stations.
Movement Logic: Trains move from one station to another based on a predefined sequence. When a train moves, the servos and LCD displays update accordingly.
Functions: There are functions to move trains, detect train positions, wait for trains at stations, and update the LCD displays.

This project helps in learning how to integrate sensors, servos, and LCDs with Arduino for automation tasks.
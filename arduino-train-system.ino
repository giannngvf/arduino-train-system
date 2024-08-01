#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Define servo and sensor pins for each station
const int servoPins[6] = {8, 9, 10, 11, 12, 13}; // Servo pins for each station
const int irSensorPins[6] = {2, 3, 4, 5, 6, 7}; // IR sensor pins for each station

// Define I2C addresses for each station
const int lcdAddresses[6] = {0x22, 0x23, 0x24, 0x25, 0x26, 0x27}; // I2C addresses for each station

// Create LCD objects for each station
LiquidCrystal_I2C lcds[6] = {
  LiquidCrystal_I2C(0x22, 16, 2),
  LiquidCrystal_I2C(0x23, 16, 2),
  LiquidCrystal_I2C(0x24, 16, 2),
  LiquidCrystal_I2C(0x25, 16, 2),
  LiquidCrystal_I2C(0x26, 16, 2),
  LiquidCrystal_I2C(0x27, 16, 2)
};

Servo servos[6];
bool trainDetected[6] = {false, false, false, false, false, false};

// Train names and initial positions
String trainNames[3] = {"Alex", "Irish", "JM"};
int trainPositions[3] = {0, 2, 4}; // Alex at Crystal Station, Irish at Verdant Station, JM at Ebony Station

// Station names
String stationNames[6] = {"Crystal", "Saffron", "Verdant", "Maplewood", "Ebony", "Oasis"};

void setup() {
  // Attach servos and set initial positions
  for (int i = 0; i < 6; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(100); // Initial position of each servo motor
    pinMode(irSensorPins[i], INPUT);

    // Initialize LCDs
    lcds[i].init();
    lcds[i].backlight();
    lcds[i].clear();
    lcds[i].print("Waiting...");
  }
  
  // Manually set initial train detections
  for (int i = 0; i < 3; i++) {
    trainDetected[trainPositions[i]] = true; 
  }

  // Start serial communication for monitoring
  Serial.begin(9600);
}

void loop() {
  static int moveSequence[48][2] = {
    {0, 1}, {2, 3}, {4, 5}, {1, 2}, {3, 4}, {5, 0},
    {0, 1}, {2, 3}, {4, 5}, {1, 2}, {3, 4}, {5, 0},
    {0, 1}, {2, 3}, {4, 5}, {1, 2}, {3, 4}, {5, 0},
    {0, 1}, {2, 3}, {4, 5}, {1, 2}, {3, 4}, {5, 0}
  };

  for (int i = 0; i < 12; i++) {
    moveTrain(moveSequence[i][0], moveSequence[i][1]);
  }
}

// Function to move the train from one station to another
void moveTrain(int fromStation, int toStation) {
  if (trainDetected[fromStation] && digitalRead(irSensorPins[fromStation]) == LOW) {
    int trainIndex = getTrainIndexAtStation(fromStation);
    
    if (trainIndex != -1) {
      Serial.print(trainNames[trainIndex]);
      Serial.print(" moving from ");
      Serial.print(stationNames[fromStation]);
      Serial.print(" to ");
      Serial.println(stationNames[toStation]);

      // Update LCD displays
      updateLCD(fromStation, "Waiting...", " ");
      // updateLCD(toStation, "Train " + trainNames[trainIndex], "arrived at " + stationNames[toStation]);

      trainDetected[fromStation] = false; // Reset detection for the current station
      trainDetected[toStation] = true; // Set detection for the next station
      trainPositions[trainIndex] = toStation; // Update the train position
      
      delay(2000); // Wait for 5 seconds
      servos[fromStation].write(180); // Open servo at 180 degrees
      delay(4000); // Wait for 2 seconds
      servos[fromStation].write(100); // Close servo back to 100 degrees
      
      waitForTrainAtStation(toStation);
    }
  }
}

// Function to wait for the train at a station
void waitForTrainAtStation(int station) {
  // Serial.print("Waiting...");
  // Serial.println(stationNames[station]);
  while (digitalRead(irSensorPins[station]) == HIGH) {
    // Wait until the train is detected
  }
  Serial.print("Train detected at ");
  Serial.println(stationNames[station]);
  updateLCD(station, "Train " + trainNames[getTrainIndexAtStation(station)], "at " + stationNames[station]);
}

// Function to get the train index at a station
int getTrainIndexAtStation(int station) {
  for (int i = 0; i < 3; i++) {
    if (trainPositions[i] == station) {
      return i;
    }
  }
  return -1; // No train at the station
}

// Function to update LCD display at a station
void updateLCD(int station, String line1, String line2) {
  lcds[station].clear();
  lcds[station].setCursor(0, 0);
  lcds[station].print(line1);
  lcds[station].setCursor(0, 1);
  lcds[station].print(line2);
}
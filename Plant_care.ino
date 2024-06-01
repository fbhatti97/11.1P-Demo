#include <Wire.h>
#include <BH1750.h>

const int moistureSensorPin = A0;   // Analog pin connected to the moisture sensor's signal output
const int vccPin = 2;               // Digital pin connected to the sensors' VCC
const int waterPumpLedPin = 3;      // Digital pin connected to the external LED for water pump
const int sunlightLedPin = 4;       // Digital pin connected to the external LED for sunlight
const int moistureThreshold = 100;  // Moisture threshold for water pump

BH1750 lightMeter;

void setup() {
  Serial.begin(9600);               // Start serial communication at 9600 baud rate
  pinMode(moistureSensorPin, INPUT);// Set the moisture sensor pin as an input
  pinMode(vccPin, OUTPUT);          // Set the VCC pin as an output to control power to the sensors
  pinMode(waterPumpLedPin, OUTPUT); // Set the water pump LED pin as an output
  pinMode(sunlightLedPin, OUTPUT);  // Set the sunlight LED pin as an output

  digitalWrite(vccPin, HIGH);       // Power the sensors

  Wire.begin();
  lightMeter.begin();
}

void loop() {
  // Read the moisture sensor value
  int moistureValue = analogRead(moistureSensorPin);

  // Read the light sensor value from the BH1750
  float lightValue = lightMeter.readLightLevel();

  // Print the sensor values to the Serial Monitor
  Serial.print("Moisture Level: ");
  Serial.print(moistureValue);
  Serial.print(" | Light Level: ");
  Serial.print(lightValue);
  Serial.println(" lx");

  // Control the water pump LED based on moisture level
  if (moistureValue < moistureThreshold) {
    digitalWrite(waterPumpLedPin, HIGH);  // Turn the water pump LED on
  } else {
    digitalWrite(waterPumpLedPin, LOW);   // Turn the water pump LED off
  }

  // Control the sunlight LED based on light level
  if (lightValue < 10) {  // Adjust the light level threshold as needed
    digitalWrite(sunlightLedPin, HIGH);  // Turn the sunlight LED on
  } else {
    digitalWrite(sunlightLedPin, LOW);   // Turn the sunlight LED off
  }

  // Additional delay for stability
  delay(1000);
}

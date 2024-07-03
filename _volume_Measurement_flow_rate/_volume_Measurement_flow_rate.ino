#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int sensorPin = 2;
volatile long pulse;
volatile long pulseLastSecond;
unsigned long lastTime;
float totalVolume;
float currentFlowRate;

void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(sensorPin), increase, RISING);
  
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);
}

void loop() {
  // Calculate total volume
  totalVolume = 2.663 * pulse;

  // Calculate flow rate
  if (millis() - lastTime > 1000) {
    currentFlowRate = 2.663 * pulseLastSecond;
    pulseLastSecond = 0;
    lastTime = millis();
  }

  // Print the total volume and the current flow rate to Serial Monitor
  Serial.print("Total Volume transferred: ");
  Serial.print(totalVolume);
  Serial.println(" mL");

  Serial.print("Current Flow Rate: ");
  Serial.print(currentFlowRate);
  Serial.println(" mL/s");

  // Print the total volume and the current flow rate to LCD
  lcd.setCursor(0, 0);
  lcd.print("Volume: ");
  lcd.print(totalVolume);
  lcd.print(" mL");

  lcd.setCursor(0, 1);
  lcd.print("Flow: ");
  lcd.print(currentFlowRate);
  lcd.print(" mL/s");

  delay(500); // Adjust the delay as needed for your requirements
}

void increase() {
  pulse++;
  pulseLastSecond++;
}
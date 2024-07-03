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

  // Print the total volume and the current flow rate
  Serial.print("Total Volume transferred: ");
  Serial.print(totalVolume);
  Serial.println(" mL");

  Serial.print("Current Flow Rate: ");
  Serial.print(currentFlowRate);
  Serial.println(" mL/s");

  delay(500); // Adjust the delay as needed for your requirements
}

void increase() {
  pulse++;
  pulseLastSecond++;
}

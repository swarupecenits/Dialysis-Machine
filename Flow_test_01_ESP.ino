#include <Arduino.h>
//#include <WiFi.h>               //we are using the ESP32
#include <ESP8266WiFi.h>      // uncomment this line if you are using esp8266 and comment the line above
#include <Firebase_ESP_Client.h>


int sensorPin = D2;
volatile long pulse;
volatile long pulseLastSecond;
unsigned long lastTime;
float totalVolume;
float currentFlowRate;
//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "POCOM5"
#define WIFI_PASSWORD "12345.net"

// Insert Firebase project API Key
#define API_KEY "AIzaSyAgblajS6-f_Ld8INMoMzvFxAHOZ90D4l8"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://real-time-data-8c582-default-rtdb.asia-southeast1.firebasedatabase.app/" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;                     //since we are doing an anonymous sign in 

void setup(){

  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(sensorPin), increase, RISING);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop(){

  // Calculates the total volume
  totalVolume = 2.663 * pulse;

  // Calculates the flow rate
  if (millis() - lastTime > 1000) {
    currentFlowRate = 2.663 * pulseLastSecond;
    pulseLastSecond = 0;
    lastTime = millis();
  }
  
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
    //since we want the data to be updated every second
    sendDataPrevMillis = millis();
  
    if (Firebase.RTDB.setInt(&fbdo, "Flow_Sensor/Flow_Rate", currentFlowRate)){
      // This command will be executed even if you dont serial print but we will make sure its working
      Serial.print("Flow Rate : ");
      Serial.println(currentFlowRate);
    }
    else {
      Serial.println("Failed to Read from the Sensor");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    
    if (Firebase.RTDB.setFloat(&fbdo, "Flow_Sensor/Volume", totalVolume)){
      Serial.print("Volume : ");
      Serial.println(totalVolume);
    }
    else {
      Serial.println("Failed to Read from the Sensor");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }
}
ICACHE_RAM_ATTR void increase() {
  pulse++;
  pulseLastSecond++;
}

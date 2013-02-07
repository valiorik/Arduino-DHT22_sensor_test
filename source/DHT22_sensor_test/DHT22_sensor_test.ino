#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22   // DHT 22  (AM2302)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHTPIN, DHTTYPE);
String inputString = "";
String getTempCommand = "GetTemp";
boolean stringComplete = false;

void setup() {
  Serial.begin(9600); 
  Serial.println("DHTxx test! Send commecnd GetTemp to get sensor data.");
 
  inputString.reserve(200);
  dht.begin();
}

void loop() {
  
  if (stringComplete)
  {
    String trunkInputString = inputString.substring(0,7);
    
    if(trunkInputString.equalsIgnoreCase(getTempCommand))
    {
      float h = dht.readHumidity();
      float t = dht.readTemperature();
  
      if (isnan(t) || isnan(h)) {
        Serial.println("Failed to read from DHT");
      } else {
        Serial.print("Humidity: ");
        Serial.print(h);
        Serial.print(" %\t");
        Serial.print("Temperature: ");
        Serial.print(t);
        Serial.println("*C");
      }
      
      inputString = "";
      stringComplete = false;
    }
    else
    {
      Serial.print("Waiting for: ");
      Serial.println(getTempCommand);

      Serial.print("Got: ");
      Serial.println(inputString.substring(0,7));
    }
  }
}

void serialEvent() {
  while (Serial.available()) {

    char inChar = (char)Serial.read(); 
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}

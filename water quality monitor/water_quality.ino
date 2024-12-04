#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_ADS1X15.h>
#include <DFRobot_EC.h>

#define ONE_WIRE_BUS 25                // this is the gpio pin 25 on esp32.
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

DFRobot_EC ec;
Adafruit_ADS1115 ads;

float voltage, ecValue, tdsValueFactor05, tdsValueFactor065, temperature = 25;

String apiKey = "OD67F457L5CDU6J9";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "Keerthan Ghodiwal";     // replace with your wifi ssid and wpa2 key
const char *pass =  "massbunk";
const char* server = "api.thingspeak.com";

WiFiClient client;

void setup()
{
  Serial.begin(115200);
  EEPROM.begin(32); //needed EEPROM.begin to store calibration k in eeprom
  ec.begin();
  sensors.begin();

  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop()
{
  voltage = analogRead(33); // A0 is the gpio 33
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);  // read your temperature sensor to execute temperature compensation
  ecValue = ec.readEC(voltage, temperature); // convert voltage to EC with temperature compensation
  
  // Calculate TDS using factor 0.5
  tdsValueFactor05 = ecValue * 0.5;

  // Calculate TDS using factor 0.65
  tdsValueFactor065 = ecValue * 0.65;

  // Print Temperature
  Serial.print("Temperature: ");
  Serial.print(temperature, 2);
  Serial.println(" ºC");

  // Print EC with units
  Serial.print("EC: ");
  Serial.print(ecValue, 2);
  Serial.println(" µS/cm");

  // Print TDS with units using factor 0.5
  Serial.print("TDS (Factor 0.5): ");
  Serial.print(tdsValueFactor05, 2);
  Serial.println(" ppm");
  ec.calibration(voltage, temperature); // calibration process by Serial CMD
  Serial.println(" ");

  if (client.connect(server, 80))  //   "184.106.153.149" or api.thingspeak.com
  {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(temperature, 2);
    postStr += "&field2=";
    postStr += String(ecValue, 2);
    postStr += "&field3=";
    postStr += String(tdsValueFactor05, 2);
    postStr += "&field4=";
    postStr += String(tdsValueFactor065, 2);
    postStr += "\r\n\r\n";
    delay(500);

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    delay(5000);
  }
  client.stop();
}



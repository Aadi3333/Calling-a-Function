#include <Arduino.h>
#include <WiFiNINA.h>
#include <ArduinoJson.h>
#include <Firebase_Arduino_WiFiNINA.h>

#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""

char ssid[] = "Aadi";
char pass[] = "aadi1234";

FirebaseData object;
String path = "/Light/status/";

#define RedLed  4
#define YellowLed  10
#define GreenLed  11

void setup()
{
  Serial.begin(9600);
  pinMode(RedLed, OUTPUT);
  pinMode(YellowLed, OUTPUT);
  pinMode(GreenLed, OUTPUT);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED)
  {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.print("You're connected to the ");
  Serial.println(ssid);
  Serial.print("WiFi localIP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, ssid, pass);
  Firebase.reconnectWiFi(true);

  if (Firebase.setString(object, path, "OFF"))
  {
    Serial.println("Connected: OK");
  }
  else
  {
    Serial.println("Error: " + object.errorReason());
  }
}

void loop()
{

  if (Firebase.getString(object, path))
  {
   LedStatus(object.stringData());
  }
  else
  {
    Serial.println("Error");

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, ssid, pass);
    Firebase.reconnectWiFi(true);

   if (Firebase.setString(object, path, "OFF"))
   {
    Serial.println("Connected: OK");
   }
   else
    {
    Serial.println("Error: " + object.errorReason());
    }
  }
}


void LedStatus(String Status)
{
  if (Status == "RED")
  {
    Serial.println("Red");
    digitalWrite(RedLed, HIGH);
    digitalWrite(YellowLed, LOW);
    digitalWrite(GreenLed, LOW);
  }
  else if (Status == "YELLOW")
  {
    Serial.println("Yellow");
    digitalWrite(RedLed, LOW);
    digitalWrite(YellowLed, HIGH);
    digitalWrite(GreenLed, LOW);
  }
  else if (Status == "GREEN")
  {
    Serial.println("Green");
    digitalWrite(RedLed, LOW);
    digitalWrite(YellowLed, LOW);
    digitalWrite(GreenLed, HIGH);
  }
  else if(Status == "OFF")
  {
    Serial.println("Off");
    digitalWrite(RedLed, LOW);
    digitalWrite(YellowLed, LOW);
    digitalWrite(GreenLed, LOW);
  }
}

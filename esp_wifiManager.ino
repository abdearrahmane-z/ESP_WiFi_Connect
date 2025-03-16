#include <ESP8266WiFi.h>
#include <WiFiManager.h>  // WiFiManager Library

#define RESET_BUTTON 14  // GPIO 0 (Flash Button or Custom Button)
#define led 12  // GPIO 12 (reset wifi setting button)

WiFiManager wifiManager;

void setup() {
  Serial.begin(115200);
  pinMode(RESET_BUTTON, INPUT_PULLUP);  // Set button pin as input with pull-up resistor
  pinMode(led, OUTPUT);  // Set led pin as output
  

  wifiManager.setCaptivePortalEnable(false); // set the auto open browser Off
  wifiManager.setBreakAfterConfig(true); // exit from portal after recive data

  digitalWrite(led,HIGH); // "set the led On" whil not connected with wifi
  // Start WiFi AutoConnect
  // hotspot                      AP name & password
  if (!wifiManager.autoConnect("ESP8266_AP", "12345678")) {
      Serial.println("Failed to connect, restarting...");
      delay(3000);
      ESP.restart();
  }

  Serial.println("Connected to WiFi!");
  Serial.println("IP Address: " + WiFi.localIP().toString());
  digitalWrite(led,LOW); // "set the led Off" when connected
}

void loop() {
    // reset the wifi setting and connect with other wifi
    if (digitalRead(RESET_BUTTON) == LOW) {
      Serial.println("Button pressed. Waiting for reset...");
      delay(5000);  // Wait 5 seconds to confirm reset

      if (digitalRead(RESET_BUTTON) == LOW) {
        Serial.println("Resetting WiFi settings...");
        wifiManager.resetSettings();
        ESP.restart();
      }
    }

    //code ...

}

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";
unsigned long channelID = YOUR_CHANNEL_ID;
const char* apiKey = "YOUR_API_KEY";

WiFiClient client;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  ThingSpeak.begin(client);
}

void loop() {
  if (Serial.available()) {
    int gasValue = Serial.parseInt();
    ThingSpeak.writeField(channelID, 1, gasValue, apiKey);
    
    // Trigger IFTTT/SMS alert if gas > 1000ppm
    if (gasValue > 1000) {
      sendAlert();
    }
  }
}

void sendAlert() {
  // Use HTTP to trigger IFTTT/SMS (example)
  WiFiClientSecure client;
  client.connect("maker.ifttt.com", 443);
  client.print("GET /trigger/gas_alert/with/key/YOUR_IFTTT_KEY");
  client.stop();
}

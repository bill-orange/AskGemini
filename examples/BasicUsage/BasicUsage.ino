#include <WiFi.h>
#include <AskGemini.h>

// Replace with your credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
String Gemini_APIKey = "YOUR_API_KEY";
String Gemini_Model  = "gemini-2.0-flash";

void errorHandler(int code) {
  Serial.printf("AskGemini error: %d\n", code);
}

void setup() {
  Serial.begin(115200);

  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("\nConnected.");

  delay(200);  // Small stability delay for ESP32 HTTPS

  // Basic request
  String reply = askGemini(
    "Tell me a fun fact about space.",
    "Respond with one concise sentence.",
    0.2
  );

  Serial.println("Gemini says:");
  Serial.println(reply);
}

void loop() {
  // Nothing here
}

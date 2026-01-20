#include <WiFi.h>
#include <AskGemini.h>

// Replace with your credentials before running
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
String Gemini_APIKey = "YOUR_API_KEY";
String Gemini_Model = "gemini-2.0-flash";

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

  // Mode A — Concise
  String concise = askGemini(
    "Explain what a microcontroller is.",
    "Respond with one short, clear sentence.",
    0.1);
  delay(200);

  // Mode B — Friendly
  String friendly = askGemini(
    "Explain what a microcontroller is.",
    "Respond in a friendly tone suitable for beginners.",
    0.4);
  delay(200);

  // Mode C — Technical
  String technical = askGemini(
    "Explain what a microcontroller is.",
    "Respond with a technical description suitable for engineers.",
    0.0);

  Serial.println("Concise:");
  Serial.println(concise);

  Serial.println("\nFriendly:");
  Serial.println(friendly);

  Serial.println("\nTechnical:");
  Serial.println(technical);
}

void loop() {}
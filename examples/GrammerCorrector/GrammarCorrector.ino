#include <WiFi.h>
#include <AskGemini.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
String Gemini_APIKey = "YOUR_API_KEY";
String Gemini_Model = "gemini-2.0-flash";

void errorHandler(int code) {
  Serial.printf("AskGemini error: %d\n", code);
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(100);

  String userSentence = "I did not see nuthen.";

  String reply = askGemini(
    userSentence,
    "You are a grammar‑correcting assistant. "
    "Return only the corrected sentence with no commentary.",
    0.0);

  Serial.println("Original:");
  Serial.println(userSentence);
  Serial.println("\nCorrected:");
  Serial.println(reply);
}

void loop() {}
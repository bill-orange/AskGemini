#ifndef ASK_GEMINI_H
#define ASK_GEMINI_H

// Uncomment to enable raw response debugging
//#define ASK_GEMINI_DEBUG



#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#ifndef ERR_UNKNOWN
#define ERR_UNKNOWN -1
#endif

// Provided by the user's sketch
extern String Gemini_APIKey;
extern String Gemini_Model;
void errorHandler(int code);

// Sends a request to the Gemini API and returns the combined text output.
String askGemini(const String& userText,
                 const String& instruction,
                 float temperature);

// Internal helpers
String jsonEscape(const String& input);
String extractAllTextFields(const String& json);
char* sanitizeQuip(const char* input);
String jsonUnescape(const String& in);   // if you added this

#endif
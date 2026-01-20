#include "AskGemini.h"
#include <WiFiClientSecure.h>

// ------------------------------------------------------------
// Persistent TLS client for speed (global)
// ------------------------------------------------------------
static WiFiClientSecure geminiClient;

// ------------------------------------------------------------
// Escape JSON special characters
// ------------------------------------------------------------
String jsonEscape(const String& input) {
    String out;
    out.reserve(input.length() * 1.2);

    for (unsigned int i = 0; i < input.length(); i++) {
        char c = input[i];
        switch (c) {
            case '\\': out += "\\\\"; break;
            case '\"': out += "\\\""; break;
            case '\n': out += "\\n";  break;
            case '\r': out += "\\r";  break;
            case '\t': out += "\\t";  break;
            default:   out += c;      break;
        }
    }
    return out;
}

// ------------------------------------------------------------
// Unescape JSON escape sequences
// ------------------------------------------------------------
String jsonUnescape(const String& in) {
    String out;
    out.reserve(in.length());

    for (int i = 0; i < in.length(); i++) {
        char c = in[i];

        if (c == '\\' && i + 1 < in.length()) {
            char next = in[i + 1];

            switch (next) {
                case 'n': out += '\n'; i++; continue;
                case 'r': out += '\r'; i++; continue;
                case 't': out += '\t'; i++; continue;
                case '\\': out += '\\'; i++; continue;
                case '"': out += '"'; i++; continue;
            }
        }

        out += c;
    }

    return out;
}

// ------------------------------------------------------------
// Extract all "text" fields from Gemini JSON response
// ------------------------------------------------------------
String extractAllTextFields(const String& json) {
    String out;
    int searchIndex = 0;

    while (true) {
        int keyIndex = json.indexOf("\"text\":", searchIndex);
        if (keyIndex < 0) break;

        int startQuote = json.indexOf('"', keyIndex + 7);
        if (startQuote < 0) break;

        int endQuote = json.indexOf('"', startQuote + 1);
        if (endQuote < 0) break;

        // Unescape JSON before appending
        String raw = json.substring(startQuote + 1, endQuote);
        out += jsonUnescape(raw);
        out += " ";

        searchIndex = endQuote + 1;
    }

    out.trim();
    return out;
}

// ------------------------------------------------------------
// Optional helper for display-safe strings (TTS-friendly)
// ------------------------------------------------------------
char* sanitizeQuip(const char* input) {
    String safe = String(input);

    // Convert escaped sequences to real characters
    safe.replace("\\n", " ");
    safe.replace("\\r", " ");
    safe.replace("\\t", " ");
    safe.replace("\\\"", "\"");
    safe.replace("\\\\", "\\");

    // Remove any remaining real newlines
    safe.replace("\n", " ");
    safe.replace("\r", " ");

    // Allocate C-string
    int len = safe.length() + 1;
    char* result = (char*)malloc(len);
    if (result) {
        safe.toCharArray(result, len);
    }
    return result;
}

// ------------------------------------------------------------
// Main Gemini request function
// ------------------------------------------------------------
String askGemini(const String& userText,
                 const String& instruction,
                 float temperature)
{
    if (WiFi.status() != WL_CONNECTED) {
        errorHandler(ERR_UNKNOWN);
        return "";
    }

    // Initialize persistent TLS client once
    if (!geminiClient.connected()) {
        geminiClient.setInsecure();   // Required for ESP32-S3
    }

    String url =
        "https://generativelanguage.googleapis.com/v1/models/" +
        Gemini_Model +
        ":generateContent?key=" + Gemini_APIKey;

    HTTPClient http;
    http.begin(geminiClient, url);
    http.setReuse(true); 
    http.setTimeout(20000);  // 20 seconds for long responses
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Connection", "keep-alive");

    // Add maxOutputTokens for speed + cost control
    const int maxTokens = 128;

    String payload = "{"
        "\"contents\":[{"
            "\"parts\":["
                "{\"text\":\"" + jsonEscape(instruction) + "\"},"
                "{\"text\":\"" + jsonEscape(userText) + "\"}"
            "]"
        "}],"
        "\"generationConfig\":{"
            "\"temperature\":" + String(temperature, 3) + ","
            "\"maxOutputTokens\":" + String(maxTokens) +
        "}"
    "}";

    int code = http.POST(payload);
    Serial.print("HTTP POST code: ");
    Serial.println(code);

    if (code <= 0) {
        http.end();
        errorHandler(ERR_UNKNOWN);
        return "";
    }

    String response = http.getString();

    #ifdef ASK_GEMINI_DEBUG
    Serial.println("RAW RESPONSE:");
    Serial.println(response);
    #endif

    http.end();

    if (response.length() == 0) {
        errorHandler(ERR_UNKNOWN);
        return "";
    }

    return extractAllTextFields(response);
}
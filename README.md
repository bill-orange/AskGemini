# AskGemini — Lightweight Gemini Client for ESP32 (S3‑Optimized)

A minimal, fast, Arduino‑friendly library for calling Google Gemini models from ESP32 boards — optimized for ESP32‑S3 stability, TLS performance, and clean JSON parsing.

AskGemini is designed for:
- Voice assistants
- Embedded AI devices
- Robotics
- IoT dashboards
- Creative LLM experiments on microcontrollers

## Features
- Simple one‑call API: `String reply = askGemini(prompt, instruction, temperature);`
- Works with Gemini 2.0 Flash and other text‑capable models
- Persistent TLS client for fast HTTPS on ESP32‑S3
- Clean JSON extraction (no heavy JSON libraries)
- Optional text sanitizer for TTS engines
- Three polished examples:
  - BasicUsage
  - InstructionMode
  - GrammarCorrector

## Requirements
**ESP32 Arduino Core 3.x (Required)**  
AskGemini uses the modern HTTPS API:
- WiFiClientSecure
- client.setInsecure()
- http.begin(client, url)

These functions do not exist in ESP32 Core 2.x.

## Supported Boards
- ESP32‑S3
- ESP32‑S2
- ESP32‑C3
- ESP32 classic (running Arduino Core 3.x)

### Not Supported
- ESP32 Arduino Core 2.x
- Boards without HTTPS capability

## Installation
1. Install ESP32 Arduino Core 3.x  
   Arduino IDE → Boards Manager → search “esp32” → install 3.x.x
2. Download or clone this repository
3. Place the folder into: `Documents/Arduino/libraries/AskGemini`
4. Restart Arduino IDE
5. Open: File → Examples → AskGemini

## Setup in Your Sketch
### Define your credentials
String Gemini_APIKey = "YOUR_API_KEY";  
String Gemini_Model = "gemini-2.0-flash";

### Provide an error handler
void errorHandler(int code) {  
  Serial.printf("AskGemini error: %d\n", code);  
}

## Basic Example
String reply = askGemini(
  "Tell me a fun fact about space.",
  "Respond with one concise sentence.",
  0.2
);
Serial.println(reply);

## Instruction Mode Example
String concise = askGemini(
  "What is a microcontroller?",
  "Respond with one short, clear sentence.",
  0.1
);

String friendly = askGemini(
  "What is a microcontroller?",
  "Respond in a friendly tone suitable for beginners.",
  0.4
);

String technical = askGemini(
  "What is a microcontroller?",
  "Respond with a technical description suitable for engineers.",
  0.0
);

## Grammar Corrector Example
String reply = askGemini(
  "I did not see nuthen.",
  "You are a grammar-correcting assistant. Return only the corrected sentence.",
  0.0
);

## Using sanitizeQuip() (Optional)
char* cleaned = sanitizeQuip(reply.c_str());
Serial.println(cleaned);
free(cleaned);   // Important: avoid memory leaks

sanitizeQuip() allocates memory using malloc(), so you must call free() after use.

## Performance Notes (ESP32‑S3)
The ESP32‑S3’s TLS stack is slower than classic ESP32. AskGemini includes several optimizations:
- Persistent WiFiClientSecure (avoids repeated TLS handshakes)
- Keep‑alive enabled
- http.setReuse(true) for connection reuse
- Efficient JSON extraction
- 20‑second read timeout for long responses

### For even faster responses:
- Use shorter instructions
- Use smaller models (gemini-2.0-flash-lite)
- Limit output tokens (e.g., 16–64)
- Add small delays between back‑to‑back calls

## License
MIT License.  
See LICENSE.txt for details.

## Credits
Created by William E. Webb  
Designed for clarity, reliability, and embedded AI experimentation.

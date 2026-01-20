# AskGemini — Lightweight Gemini Client for ESP32 (S3‑Optimized)

A minimal, fast, Arduino‑friendly library for calling Google Gemini models from ESP32 boards — optimized for ESP32‑S3 stability, TLS performance, and clean JSON parsing.

AskGemini is designed for:

- Voice assistants
- Embedded AI devices
- Robotics
- IoT dashboards
- Creative LLM experiments on microcontrollers

---

## Features

- Simple one‑call API:  
  `String reply = askGemini(prompt, instruction, temperature);`
- Works with Gemini 2.0 Flash and other text‑capable models
- Persistent TLS client for fast HTTPS on ESP32‑S3
- Clean JSON extraction (no heavy JSON libraries)
- Optional text sanitizer for TTS engines
- Three polished examples:
  - BasicUsage
  - InstructionMode
  - GrammarCorrector

---

## Requirements

**ESP32 Arduino Core 3.x (Required)**  
AskGemini uses the modern HTTPS API:

- `WiFiClientSecure`
- `client.setInsecure()`
- `http.begin(client, url)`

These functions do **not** exist in ESP32 Core 2.x.

---

## Supported Boards

- ESP32‑S3  
- ESP32‑S2  
- ESP32‑C3  
- ESP32 classic (running Arduino Core 3.x)

### Not Supported

- ESP32 Arduino Core 2.x  
- Boards without HTTPS capability

---

## Installation

1. Install **ESP32 Arduino Core 3.x**  
   Arduino IDE → Boards Manager → search “esp32” → install **3.x.x**

2. Download or clone this repository

3. Place the folder into:  
   `Documents/Arduino/libraries/AskGemini`

4. Restart Arduino IDE

5. Open:  
   **File → Examples → AskGemini**

---

## Setup in Your Sketch

### Define your credentials
```cpp
String Gemini_APIKey = "YOUR_API_KEY";
String Gemini_Model = "gemini-2.0-flash";

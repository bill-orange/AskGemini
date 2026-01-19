# AskGemini — Hardened Gemini API Wrapper for ESP32

`AskGemini` is a lightweight Arduino‑style library that provides a robust, fault‑tolerant interface to Google’s Gemini Flash API. It is designed for embedded devices such as the ESP32‑S3, where reliability, predictable behavior, and clean JSON handling matter.

This library wraps the full request/response cycle:

- JSON escaping  
- instruction + user prompt assembly  
- HTTP POST  
- hardened response parsing  
- error handling hooks  

It is ideal for projects that need deterministic, low‑latency text generation from Gemini Flash.

---

## ✨ Features

- Simple API:  
  ```cpp
  askGemini(userText, instruction, temperature);
  ```
- Hardened JSON escaping for safe payload construction  
- Instruction‑first prompting for consistent model behavior  
- Deterministic temperature control  
- Graceful error handling via user‑supplied callback  
- Portable: no global state except your API key  
- Optional sanitization helper for safe display strings  
- Compatible with ESP32/ESP32‑S3 using Arduino framework  

---

## 📦 Installation

1. Create a folder named `AskGemini`
2. Place the following files inside:
   - `AskGemini.h`
   - `AskGemini.cpp`
   - `library.properties`
3. Drop the folder into your Arduino `libraries/` directory
4. Restart the Arduino IDE

---

## 🚀 Quick Start

### Include the library

```cpp
#include <AskGemini.h>
```

### Provide your API key

```cpp
String Gemini_APIKey = "YOUR_API_KEY_HERE";
```

### Call the function

```cpp
String reply = askGemini(
    "Fix this sentence: I did not see nuthen.",
    "You are a grammar‑correcting assistant. ",
    0.0
);

Serial.println(reply);
```

---

## 🧠 API Overview

### askGemini()

```cpp
String askGemini(
    const String& userText,
    const String& instruction,
    float temperature
);
```

**Parameters**

| Name | Description |
|------|-------------|
| `userText` | The user’s input text |
| `instruction` | System‑style instruction block |
| `temperature` | Model creativity (0.0 = deterministic) |

**Returns:**  
A clean text string extracted from Gemini’s response.

---

### sanitizeQuip()

```cpp
char* sanitizeQuip(const char* input);
```

Escapes backslashes, quotes, and newlines for safe display on small screens.

---

## 🛠 Requirements

- ESP32 or ESP32‑S3  
- Arduino framework  
- WiFi connection  
- A valid Gemini API key  

---

## 🧩 Error Handling

The library calls your project’s error handler:

```cpp
void errorHandler(int code);
```

You may define this however you like — LED blink, display message, safe state, etc.

---

## 📁 File Structure

```
AskGemini/
 ├── AskGemini.h
 ├── AskGemini.cpp
 └── library.properties
```

---

## 🧪 Example Sketch

```cpp
#include <AskGemini.h>

String Gemini_APIKey = "YOUR_KEY";

void setup() {
  Serial.begin(115200);
  WiFi.begin("ssid", "password");
  while (WiFi.status() != WL_CONNECTED) delay(100);
}

void loop() {
  String out = askGemini(
      "Tell me a short fact about cats.",
      "Respond with one concise sentence. ",
      0.2
  );

  Serial.println(out);
  delay(5000);
}
```

---

## 📚 Future Enhancements

- Optional retry logic  
- Timeout configuration  
- Streaming mode  
- Structured error objects  
- Example folder with multiple sketches  

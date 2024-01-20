#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid     = "your_SSID";
const char* password = "your_PASSWORD";

// Replace with your OpenAI API key
const char* apiKey = "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";

void setup() {
  // Initialize Serial
  Serial.begin(9600);

  // Connect to Wi-Fi network
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
      Serial.print('.');
      delay(1000);
  }
  Serial.println(WiFi.localIP());

  // Send request to OpenAI API
  String inputText = "Hello, ChatGPT!";
  String apiUrl = "https://api.openai.com/v1/completions";
  String payload = "{\"prompt\":\"" + inputText + "\",\"max_tokens\":100, \"model\": \"text-davinci-003\"}";

  HTTPClient http;
  http.begin(apiUrl);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + String(apiKey));
  
  int httpResponseCode = http.POST(payload);
  if (httpResponseCode == 200) {
    String response = http.getString();
  
    // Parse JSON response
    DynamicJsonDocument jsonDoc(1024);
    deserializeJson(jsonDoc, response);
    String outputText = jsonDoc["choices"][0]["text"];
    Serial.println(outputText);
  } else {
    Serial.printf("Error %i \n", httpResponseCode);
  }
}

void loop() {
  // do nothing
}

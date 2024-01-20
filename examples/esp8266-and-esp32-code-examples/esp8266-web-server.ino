#include <ESP8266WiFi.h>

const char* ssid = "YourNetworkName";
const char* password = "YourNetworkPassword";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi network: " + String(ssid));

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());

  server.begin();
  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New client");
    String currentLine = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("<h1>Hello World!</h1>");
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }

    client.stop();
    Serial.println("Client disconnected");
  }
}

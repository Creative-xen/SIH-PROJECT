#include <LoRa.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#define LORA_SS_PIN 5
#define LORA_RST_PIN 17
#define LORA_DIO0_PIN 16

const char *ssid = "receive";
const char *password = "123456789";

String receivedData = "No data received yet";

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  if (!LoRa.begin(868E6)) {
    while (1);
  }
  Serial.println("LoRa Initialized");

  WiFi.softAP(ssid, password);
  Serial.println("ESP32 Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<html><body>";
    html += "<h1>Live LoRa Data</h1>";
    html += "<p>Received Data: " + receivedData + "</p>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  server.begin();
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    receivedData = "";
    while (LoRa.available()) {
      receivedData += (char)LoRa.read();
    }
    Serial.println("Received Data: " + receivedData);
  }

  delay(1000);
}

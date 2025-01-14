#include <WiFi.h>
//  CHECK IF YOU ARE USING ESP32 or  ESP8266 MODULE
#include <FirebaseESP32.h>         

#include <LoRa.h>
#include <DHT.h>
// WIFI CREDENTIALS (ADD  YOUR OWN)
#define WIFI_SSID "xen"                       
#define WIFI_PASSWORD "1234567899"
// FIREBASE CREDENTIALS  (ADD YOUR OWN)
#define FIREBASE_HOST "database_url"
#define FIREBASE_AUTH "database_secretKEY"
// ---------------------------------------------------   CHANGE IT AS YOUR SETUP ON HARDWARES
#define LORA_SS_PIN 5 
#define LORA_RST_PIN 17
#define LORA_DIO0_PIN 16
#define DHTPIN 4                    
#define DHTTYPE DHT11
#define SOIL_MOISTURE_PIN 34
// ----------------------------------------------------
DHT dht(DHTPIN, DHTTYPE);
FirebaseData firebaseData;

void setup() {
    Serial.begin(115200);    // Baude rate - fix it on ide terminal

   
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to xen...");     // xen - wifi name
    }
    Serial.println("Connected to xen");


    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);
    if (Firebase.ready()) {
        Serial.println("Connected to Firebase");
    } else {
        Serial.println("Failed to connect with Firebase");
    }

 
    if (!LoRa.begin(868E6)) {
        Serial.println("LoRa is causing issue !");
        while (1);
    }
    Serial.println("LoRa is not causing issue");

   
    dht.begin();


    pinMode(SOIL_MOISTURE_PIN, INPUT);
}

void loop() {
  
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    int soilMoisture = analogRead(SOIL_MOISTURE_PIN);    // using analog pins for muntiple senser nodes


    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Failed to read data from DHT 11 sensor!");             // check if yours is DHT 11 or DHT 22 - change accordingly :)
        return;
    }

    String sensorData = "Humidity: " + String(humidity) + "%, Temperature: " + String(temperature) + "C, Soil Moisture: " + String(soilMoisture);

    LoRa.beginPacket();
    LoRa.print(sensorData);
    LoRa.endPacket();
    Serial.println("Data sent via LoRa: " + sensorData);

    String path = "/SensorData";
    if (Firebase.setFloat(firebaseData, path + "/Humidity", humidity)) {
        Serial.println("Humidity updated on Firebase");
    } else {
        Serial.println("Failed to update Humidity on Firebase server: " + firebaseData.errorReason());
    }

    if (Firebase.setFloat(firebaseData, path + "/Temperature", temperature)) {
        Serial.println("Temperature got updated on Firebase");
    } else {
        Serial.println("Failed to update Temperature on Firebase: " + firebaseData.errorReason());
    }

    if (Firebase.setInt(firebaseData, path + "/SoilMoisture", soilMoisture)) {
        Serial.println("Soil Moisture got updated on Firebase");
    } else {
        Serial.println("Failed to update Soil Moisture value on Firebase: " + firebaseData.errorReason());
    }


    delay(2000);  // 2 sec delay min for correct fetching of data
}

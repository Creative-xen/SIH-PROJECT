#include <WiFi.h>
#include <FirebaseESP32.h>
#include <LoRa.h>
#include <DHT.h>

#define WIFI_SSID "xen"
#define WIFI_PASSWORD "1234567899"
#define FIREBASE_HOST "your_firebase_database_url"
#define FIREBASE_AUTH "your_firebase_database_secret"
#define LORA_SS_PIN 5
#define LORA_RST_PIN 17
#define LORA_DIO0_PIN 16
#define DHTPIN 4
#define DHTTYPE DHT11
#define SOIL_MOISTURE_PIN 34

DHT dht(DHTPIN, DHTTYPE);
FirebaseData firebaseData;

void setup() {
    Serial.begin(115200);

    // Connect to WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    // Initialize Firebase
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);
    if (Firebase.ready()) {
        Serial.println("Connected to Firebase");
    } else {
        Serial.println("Failed to connect to Firebase");
    }

    // Initialize LoRa
    if (!LoRa.begin(868E6)) {
        Serial.println("LoRa initialization failed!");
        while (1);
    }
    Serial.println("LoRa Initialized");

    // Initialize DHT sensor
    dht.begin();

    // Set soil moisture sensor pin
    pinMode(SOIL_MOISTURE_PIN, INPUT);
}

void loop() {
    // Read sensor data
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    int soilMoisture = analogRead(SOIL_MOISTURE_PIN);

    // Check if DHT sensor failed
    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Failed to read data from DHT sensor!");
        return;
    }

    // Prepare data to send via LoRa
    String sensorData = "Humidity: " + String(humidity) + "%, Temperature: " + String(temperature) + "C, Soil Moisture: " + String(soilMoisture);

    // Send data via LoRa
    LoRa.beginPacket();
    LoRa.print(sensorData);
    LoRa.endPacket();
    Serial.println("Data sent via LoRa: " + sensorData);

    // Upload data to Firebase
    String path = "/SensorData";
    if (Firebase.setFloat(firebaseData, path + "/Humidity", humidity)) {
        Serial.println("Humidity updated on Firebase");
    } else {
        Serial.println("Failed to update Humidity on Firebase: " + firebaseData.errorReason());
    }

    if (Firebase.setFloat(firebaseData, path + "/Temperature", temperature)) {
        Serial.println("Temperature updated on Firebase");
    } else {
        Serial.println("Failed to update Temperature on Firebase: " + firebaseData.errorReason());
    }

    if (Firebase.setInt(firebaseData, path + "/SoilMoisture", soilMoisture)) {
        Serial.println("Soil Moisture updated on Firebase");
    } else {
        Serial.println("Failed to update Soil Moisture on Firebase: " + firebaseData.errorReason());
    }

    // Wait for 2 seconds before the next reading
    delay(2000);
}

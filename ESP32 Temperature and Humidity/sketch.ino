// //Channel Id:2826753
// //Channel spi Key : 7G1VLFTUQDDGGZEF

#include <WiFi.h>
#include "DHTesp.h"
#include "ThingSpeak.h"

// تعريف المتغيرات والثوابت
const int DHT_PIN = 15;
const int LED_PIN = 13;
const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";
const int CHANNEL_NUMBER = 2826743;
const char* API_KEY = "7G1VLFTUQDDGGZEF";
const char* SERVER = "api.thingspeak.com";

DHTesp dhtSensor;
WiFiClient client;

void connectToWiFi() {
    Serial.print("Connecting to WiFi");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected!");
    Serial.println("Local IP: " + String(WiFi.localIP()));
}

void initializeHardware() {
    Serial.begin(115200);
    dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
    pinMode(LED_PIN, OUTPUT);
    connectToWiFi();
    ThingSpeak.begin(client);
}

void readAndSendSensorData() {
    TempAndHumidity data = dhtSensor.getTempAndHumidity();
    ThingSpeak.setField(1, data.temperature);
    ThingSpeak.setField(2, data.humidity);

    bool isAlert = (data.temperature > 35 || data.temperature < 12 || data.humidity > 70 || data.humidity < 40);
    digitalWrite(LED_PIN, isAlert ? HIGH : LOW);

    int response = ThingSpeak.writeFields(CHANNEL_NUMBER,API_KEY);
    Serial.println("Temp: " + String(data.temperature, 2) + "°C");
    Serial.println("Humidity: " + String(data.humidity, 1) + "%");
    Serial.println(response == 200 ? "Data pushed successfully" : "Push error: " + String(response));
    Serial.println("---");
}

void setup() {
    initializeHardware();
}

void loop() {
    readAndSendSensorData();
    delay(10000);
}

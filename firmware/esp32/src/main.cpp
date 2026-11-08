#include <WiFi.h>

#include "secrets.h"

void setup() {
    Serial.begin(115200);
    delay(2000);

    Serial.println();
    Serial.println("Connecting to Wi-Fi...");

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    unsigned long wifiStartTime = millis();

    while (WiFi.status() != WL_CONNECTED &&
           millis() - wifiStartTime < 10000) {
        Serial.println("Waiting for connection...");
        delay(500);
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Wi-Fi connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("Wi-Fi connection timed out.");
    }
}

void loop() {

    static unsigned long lastTelemetryTime = millis();
    
    if (millis() - lastTelemetryTime >= 5000) {
        Serial.printf("Device Uptime: %lu seconds\n", millis() / 1000);
        Serial.printf("Free Heap: %lu bytes\n", ESP.getFreeHeap());

        if (WiFi.status() == WL_CONNECTED) {
            Serial.printf("Wifi Signal: %d dBm\n", WiFi.RSSI());
        } else {
            Serial.println("Wifi Status: Disconnected");
        }

        lastTelemetryTime = millis();
    }
    
}
#include <HTTPClient.h>
#include <WiFi.h>
#include "ArduinoJson.h"

#include "config.h"
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

        String payload;
        JsonDocument doc;
        wl_status_t wifiStatus = WiFi.status();

        doc["uptime_seconds"] = millis() / 1000;
        doc["free_heap_bytes"] = ESP.getFreeHeap();
        doc["wifi_connected"] = (wifiStatus == WL_CONNECTED);

        if (wifiStatus == WL_CONNECTED) {
            doc["wifi_rssi_dbm"] = WiFi.RSSI();
        } else {
            doc["wifi_rssi_dbm"] = nullptr;
        }

        serializeJson(doc, payload);

        Serial.println(payload);
        Serial.println();

        if (wifiStatus == WL_CONNECTED) {

            HTTPClient client;

            client.begin(TELEMETRY_ENDPOINT);
            client.addHeader("Content-Type", "application/json");
            client.setConnectTimeout(3000);
            client.setTimeout(3000);
            int respStatus = client.POST(payload);
            client.end();

            Serial.printf("HTTP Response Code: %d\n", respStatus);

        }

        lastTelemetryTime = millis();
    }
    
}
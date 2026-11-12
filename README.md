# Sentientl - IoT Device Monitoring System

Sential is a personal software engineering project that
monitors EPS32 microcontrollers

## Hardware

- ESP32-WROOM-32

## Technologies

- C++  (Arduino framework)
- HTTP
- JSON
- Java 17
- PlatformIO
- Apache Maven

## Architecture

```text
ESP32-WROOM-32
    |
    | WiFi 
    | HTTP POST (JSON)
    V 
Java HTTP Server
    |
    V
/telemetry
    |
    V
Console Output
```

## Device Telemetry

The ESP32 currently reports:

- Device uptime in seconds
- Avilable heap memory in bytes
- WiFi connection status
- WiFi signal strength (RSSI) in dBm

Example JSON payload:
```json
{
    "uptime_seconds": 32,
    "free_heap_bytes": 125749,
    "wifi_connected": true,
    "wifi_rssi_dbm": -36
}

```
## Backend

The backend is currently implemented using Java 17 and the JDK built-in HttpServer API.

Apache Maven is used to compile and package the application into an executable JAR.

## Requirements

- Java Development Kit (JDK) 17
- Apache Maven

## Running the Backend

From the repository root, complile the Java source files:

```
cd backend
mvn clean package
```
Start the HTTP server:
```
java -jar target/sentinel-backend-0.1.0-SNAPSHOT.jar
```
The server listens on port 8080.

## API Endpoint

POST /telemetry

Accepts telemetry sernt as JSON in the HTTP request body.

Requests using unsupported HTTP methods receive HTTP 405 Method Not Allowed.

## Testing the Backend

With the server running execute:

```
curl -i http:/localhost:8080/telemetry \
    -H "Content-Type: application/json" \
    -d '{"uptime_seconds":32,"free_heap_bytes":125749,"wifi_connected":true,"wifi_rssi_dbm":-36}'
```

Expected response:

```
HTTP/1.1 200 OK

OK
```

The console should display the incoming JSON telemetry.

## ESP32 Firmware

The firmware is located in firmware/esp32/ and is built using the PlatformIO with the Arduino framework.

The ESP32 connects to WiFi collects telemetry every five seconds, serializes it into JSON and sends it to the backend using HTTP POST.

The telemetry destination is configured in:

```
firmware/esp32/include/config.h
```

Update the endpoint to use your computer's local network IP address and the /telemetry path.

The ESP32and backend computer must be able to communication over the local network.

## Current Limitations

Sentinel is under active development.

The backend currently receives JSON payloads as text and prints them to the console. It does not yet:

- Parse JSOn inJava objects
- Store telemetry in a database
- Provide historical telemetry queries
- Exposte a moinitoring dashboard



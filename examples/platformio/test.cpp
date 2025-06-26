#include <Arduino.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#else
#error "Not supported"
#endif  // ESP8266

#include "TimeNTP.h"

#define ID_SIZE 16

// passed constants
static const char *ssid = MY_SSID;
static const char *passwd = MY_PASSWD;
static const uint32_t baud = MY_BAUD;
static const char *ntpServer = MY_NTP_SERVER;
static const char *timeZone = MY_TIME_ZONE;

// global constants
static const uint16_t delayMedium = 250;
static const uint16_t delayLong = 1000;
static const uint32_t interval = 30000;

// major classes
TimeNTP timeNTP(ntpServer, timeZone);

// global variables
uint32_t currentMillis;
uint32_t previousMillis = 0;
uint16_t interval_count = 0;
bool ledStatus = false;

void wifi_setup(void) {
    IPAddress localIP;

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, passwd);

    Serial.println("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.println("Waiting to connect to WiFi");
        delay(delayMedium);
    }
    localIP = WiFi.localIP();
    Serial.print("WiFi connected local IP ");
    Serial.println(localIP);

    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);
}

void setup() {
    Serial.begin(baud);
    delay(5000);
    Serial.println("Starting");
    pinMode(LED_BUILTIN, OUTPUT);
    wifi_setup();
    timeNTP.wait();
    Serial.println(timeNTP.getTime());
    Serial.println("Setup done");
}

void blink(void) {
    Serial.println("Blink");
    ledStatus = !ledStatus;
    digitalWrite(LED_BUILTIN, ledStatus);
}

void loop() {
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        Serial.println("Loop check");
        Serial.print(timeNTP.getTime());
        blink();
        switch (WiFi.status()) {
            case WL_NO_SSID_AVAIL:
                Serial.println("Configured SSID cannot be reached");
                break;
            case WL_CONNECTED:
                Serial.print("Connected RSSI");
                Serial.println(WiFi.RSSI());
                break;
            case WL_CONNECT_FAILED:
                Serial.println("Connection failed");
                break;
            default:
                break;
        }
        previousMillis = currentMillis;
    }
}

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include "ChatSystem.h"

// Creates the ESP32 WiFi network, starts the captive portal system, and runs the local offline chat server for connected users.

const char* wifiName = "Free Open Chat WIFI";

const byte dnsPort = 53;

DNSServer dnsServer;
WebServer server(80);

ChatSystem chatSystem(server);

void setup()
{
    Serial.begin(115200);

    WiFi.mode(WIFI_AP);
    WiFi.softAP(wifiName);

    IPAddress ip = WiFi.softAPIP();

    dnsServer.start(dnsPort, "*", ip);

    chatSystem.SetupRoutes();

    server.begin();

    Serial.println("Open Chat started");
    Serial.print("IP: ");
    Serial.println(ip);
}

void loop()
{
    dnsServer.processNextRequest();
    server.handleClient();
}
#include <stdio.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include "config.h"
#include "wifi.h"
#include "request.h"

void setup(void)
{
	Serial.begin(115200);

	if (init_wifi() == WL_CONNECTED)
	{
		Serial.print("Connetted to ");
		Serial.print(wifi_ssid);
		Serial.print("--- IP: ");
		Serial.println(WiFi.localIP());
	}
	else
	{
		Serial.print("Error connecting to: ");
		Serial.println(wifi_ssid);
	}

	init_rest_server();
}

void loop(void)
{
	http_rest_server.handleClient();
}

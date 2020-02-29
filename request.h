ESP8266WebServer http_rest_server(HTTP_REST_PORT);

void config_rest_server_routing(void);
void init_rest_server(void);
void get_connect(void);
void get_move(void);
void get_serial_read(void);

void config_rest_server_routing(void)
{
    http_rest_server.on("/", HTTP_GET, []() {
        http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
        http_rest_server.send(200, "text/html", "Welcome to the ESP8266 REST Web Server");
    });

    http_rest_server.on("/connect", HTTP_GET, get_connect);
    http_rest_server.on("/move", HTTP_POST, get_move);
    http_rest_server.on("/serial_read", HTTP_GET, get_serial_read);

}

void init_rest_server(void)
{
    http_rest_server.begin();
 
    config_rest_server_routing();
    Serial.println("HTTP REST Server Started");
}

void get_connect(void)
{
    StaticJsonDocument<200> doc;
    char JSONmessageBuffer[200];

    doc["status"] = String(WiFi.status());
    doc["ip_address"] = String(ipToString(WiFi.localIP()));
    doc["ssid"] = wifi_ssid;
    doc["signal"] = String(WiFi.RSSI());
    doc["pass"] = wifi_passwd;

    serializeJsonPretty(doc, JSONmessageBuffer);

    http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
    http_rest_server.send(200, "application/json", JSONmessageBuffer);
}

void get_move(void)
{
    int move_id = http_rest_server.arg("move_id").toInt();
    int step =    http_rest_server.arg("step").toInt();

    switch (move_id)
    {
        case 1:  Serial.println("Stand");                                   break;
        case 2:  Serial.println("Sit");                                     break;
        case 3:  Serial.println("Forward with step " + String(step));       break;
        case 4:  Serial.println("Back with step " + String(step));          break;
        case 5:  Serial.println("Turn Left with step " + String(step));     break;
        case 6:  Serial.println("Turn Right with step " + String(step));    break;
        case 7:  Serial.println("Body Left with step " + String(step));     break;
        case 8:  Serial.println("Body Right with step " + String(step));    break;
        case 9:  Serial.println("Hand Wave with step " + String(step));     break;
        case 10: Serial.println("Hand Shake with step " + String(step));    break;
        default: break;     
    }
    http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
    http_rest_server.send(200, "text/html", "success");
}

void get_serial_read(void){

    String post_body = http_rest_server.arg("plain");
    Serial.println(post_body);

    http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
    if (Serial.available())
        http_rest_server.send(200, "application/json", Serial.readString());
    else 
        http_rest_server.send(200, "application/json", "#empty#"+post_body);

}
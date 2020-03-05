ESP8266WebServer http_rest_server(HTTP_REST_PORT);

void config_rest_server_routing(void);
void init_rest_server(void);

/** HTTP GET */
void get_connect(void);
void get_speeds(void);
void get_ultrasonic_distance(void);
void get_infrared_distance(void);
void get_infrared_line(void);
void get_thermal_image(void);
void get_serial_read(void);

/** HTTP POST */
void post_moves(void);
void post_speeds(void);
void post_leg_coordinates(void);




void init_rest_server(void)
{
    http_rest_server.begin();

    config_rest_server_routing();
    Serial.println("HTTP REST Server Started");
}

void config_rest_server_routing(void)
{
    http_rest_server.on("/", HTTP_GET, []() {
        http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
        http_rest_server.send(200, "text/html", "Welcome to the ESP8266 REST Web Server");
    });

    /** HTTP GET */
    http_rest_server.on("/connect",         HTTP_GET,  get_connect);
    http_rest_server.on("/speeds",          HTTP_GET,  get_speeds);
    http_rest_server.on("/us_dist",         HTTP_GET,  get_ultrasonic_distance);
    http_rest_server.on("/ir_dist",         HTTP_GET,  get_infrared_distance);
    http_rest_server.on("/ir_line",         HTTP_GET,  get_infrared_line);
    http_rest_server.on("/thermal_image",   HTTP_GET,  get_thermal_image);
    http_rest_server.on("/serial_read",     HTTP_GET,  get_serial_read);

    /** HTTP POST */
    http_rest_server.on("/moves",           HTTP_POST, post_moves);
    http_rest_server.on("/speeds",          HTTP_POST, post_speeds);
    http_rest_server.on("/leg_coordinates", HTTP_POST, post_leg_coordinates);
}




/** HTTP GET */

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

void get_speeds(void)
{
    StaticJsonDocument<200> doc;
    char JSONmessageBuffer[200];

    doc["move_speed_multiple"] = String(move_speed_multiple);
    doc["spot_turn_speed"] = String(spot_turn_speed);
    doc["leg_move_speed"] = String(leg_move_speed);
    doc["body_move_speed"] = String(body_move_speed);
    doc["stand_seat_speed"] = String(stand_seat_speed);

    serializeJsonPretty(doc, JSONmessageBuffer);

    http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
    http_rest_server.send(200, "application/json", JSONmessageBuffer);
}

void get_ultrasonic_distance(void)
{
    StaticJsonDocument<200> doc;
    char JSONmessageBuffer[200];

    doc["front"] = String(us_front);
    doc["front_left"] = String(us_front_left);
    doc["front_right"] = String(us_front_right);
    doc["left"] = String(us_left);
    doc["right"] = String(us_right);

    serializeJsonPretty(doc, JSONmessageBuffer);

    http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
    http_rest_server.send(200, "application/json", JSONmessageBuffer);
}

void get_infrared_distance(void)
{
    StaticJsonDocument<200> doc;
    char JSONmessageBuffer[200];

    doc["front"] = String(ir_dist_front);
    doc["left"] = String(ir_dist_left);
    doc["right"] = String(ir_dist_right);

    serializeJsonPretty(doc, JSONmessageBuffer);

    http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
    http_rest_server.send(200, "application/json", JSONmessageBuffer);
}

void get_infrared_line(void)
{
    StaticJsonDocument<200> doc;
    char JSONmessageBuffer[200];

    doc["front"] = String(ir_dist_front);
    doc["left"] = String(ir_dist_left);
    doc["right"] = String(ir_dist_right);

    serializeJsonPretty(doc, JSONmessageBuffer);

    http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
    http_rest_server.send(200, "application/json", JSONmessageBuffer);
}

void get_thermal_image(void)
{
    StaticJsonDocument<1047> doc;
    char JSONmessageBuffer[300];
    JsonArray arr = doc.createNestedArray("pixels");

    for (uint8_t i = 0; i < 64; i++)
        arr.add(pixels[i]);

    serializeJson(doc, JSONmessageBuffer);

    http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
    http_rest_server.send(200, "application/json", JSONmessageBuffer);
}


void get_serial_read(void)
{

    String post_body = http_rest_server.arg("plain");
    Serial.println(post_body);

    http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
    if (Serial.available())
        http_rest_server.send(200, "application/json", Serial.readString());
    else
        http_rest_server.send(200, "application/json", "#empty#" + post_body);
}





/** HTTP POST */

void post_moves(void)
{
    Serial.println("change move");
    
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
        default: Serial.println(http_rest_server.arg("move_id"));           break;
    }
    http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
    http_rest_server.send(200, "text/html", "success");
}

void post_speeds(void)
{
    move_speed_multiple = http_rest_server.arg("move_speed_multiple").toInt();
    spot_turn_speed     = http_rest_server.arg("spot_turn_speed").toInt();
    leg_move_speed      = http_rest_server.arg("leg_move_speed").toInt();
    body_move_speed     = http_rest_server.arg("body_move_speed").toInt();
    stand_seat_speed    = http_rest_server.arg("stand_seat_speed").toInt();

    Serial.println("move_speed_multiple :" + String(move_speed_multiple));
    Serial.println("spot_turn_speed :" + String(spot_turn_speed));
    Serial.println("leg_move_speed :" + String(leg_move_speed));
    Serial.println("body_move_speed :" + String(body_move_speed));
    Serial.println("stand_seat_speed :" + String(stand_seat_speed));

    http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
    http_rest_server.send(200, "text/html", "success");
}

void post_leg_coordinates(void)
{
    front_left_x = http_rest_server.arg("front_left_x").toFloat();
    front_left_y = http_rest_server.arg("front_left_y").toFloat();
    front_left_z = http_rest_server.arg("front_left_z").toFloat();

    front_right_x = http_rest_server.arg("front_right_x").toFloat();
    front_right_y = http_rest_server.arg("front_right_y").toFloat();
    front_right_z = http_rest_server.arg("front_right_z").toFloat();

    rear_left_x = http_rest_server.arg("rear_left_x").toFloat();
    rear_left_y = http_rest_server.arg("rear_left_y").toFloat();
    rear_left_z = http_rest_server.arg("rear_left_z").toFloat();

    rear_right_x = http_rest_server.arg("rear_right_x").toFloat();
    rear_right_y = http_rest_server.arg("rear_right_y").toFloat();
    rear_right_z = http_rest_server.arg("rear_right_z").toFloat();

    Serial.print("Front_left : ");
    Serial.print("X: " + String(front_left_x));
    Serial.print("Y: " + String(front_left_y));
    Serial.print("Z: " + String(front_left_z));
    Serial.println();

    Serial.print("Front_right : ");
    Serial.print("X: " + String(front_right_x));
    Serial.print("Y: " + String(front_right_y));
    Serial.print("Z: " + String(front_right_z));
    Serial.println();

    Serial.print("Rear_left : ");
    Serial.print("X: " + String(rear_left_x));
    Serial.print("Y: " + String(rear_left_y));
    Serial.print("Z: " + String(rear_left_z));
    Serial.println();

    Serial.print("Rear_right : ");
    Serial.print("X: " + String(rear_right_x));
    Serial.print("Y: " + String(rear_right_y));
    Serial.print("Z: " + String(rear_right_z));
    Serial.println();

    http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
    http_rest_server.send(200, "text/html", "success");
}

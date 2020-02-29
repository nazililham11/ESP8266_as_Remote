const char *wifi_ssid = DEFAULT_WIFI_SSID;
const char *wifi_passwd = DEFAULT_WIFI_PASS;

int init_wifi()
{
    uint16_t retries = 0;

    Serial.println("Connecting to WiFi AP..........");

    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi_ssid, wifi_passwd);
    
    while ((WiFi.status() != WL_CONNECTED) && (retries < MAX_WIFI_INIT_RETRY))
    {
        retries++;
        delay(WIFI_RETRY_DELAY);
        Serial.print("#");
    }

    return WiFi.status(); 
}

String ipToString(IPAddress ip)
{
    String s = "";
    for (uint8_t i = 0; i < 4; i++)
        s += i ? "." + String(ip[i]) : String(ip[i]);
    return s;
}
#include <ESP8266WiFi.h>

const char *ssid = "ESP32_Test";
const char *password = "12345678";

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

void loop()
{
  Serial.println("IP Address: " + WiFi.localIP().toString());
  delay(5000); // تأخير 5 ثواني قبل التكرار
}
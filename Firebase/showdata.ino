#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <FirebaseESP8266.h>

const char *ESP32_SSID = "Yosef";
const char *ESP32_PASSWORD = "28072004";

#define API_KEY "AIzaSyCCi6Yvyfh7zPY_DqczkMcBUFdkmmI8xTA"
#define DATABASE_URL "https://smart-cart-f9c56-default-rtdb.firebaseio.com/"
#define USER_EMAIL "yoseffarhod@gmail.com"
#define USER_PASSWORD "y28072004"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

String name = "";
float price = 0;
float weight = 0;
String serial = "";
String shelf = "";

void setup()
{
    Serial.begin(115200);

    WiFi.begin(ESP32_SSID, ESP32_PASSWORD);
    Serial.print("Connecting to ESP32 WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());

    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    config.database_url = DATABASE_URL;
    Firebase.reconnectNetwork(true);
    fbdo.setBSSLBufferSize(1024, 1024);
    fbdo.setResponseSize(1024);
    Firebase.begin(&config, &auth);
    Firebase.setDoubleDigits(5);
    config.timeout.serverResponse = 10 * 1000;

    if (Firebase.getString(fbdo, "/products/CyhYDpfJgNTcpQpMcfWK/name"))
        name = fbdo.stringData();
    if (Firebase.getFloat(fbdo, "/products/CyhYDpfJgNTcpQpMcfWK/price"))
        price = fbdo.floatData();
    if (Firebase.getFloat(fbdo, "/products/CyhYDpfJgNTcpQpMcfWK/weight"))
        weight = fbdo.floatData();
    if (Firebase.getString(fbdo, "/products/CyhYDpfJgNTcpQpMcfWK/serial"))
        serial = fbdo.stringData();
    if (Firebase.getString(fbdo, "/products/CyhYDpfJgNTcpQpMcfWK/shelf"))
        shelf = fbdo.stringData();

    for (int i = 0; i < 2; i++)
    {
        Serial.println("بيانات المنتج:");
        Serial.print("الاسم: ");
        Serial.println(name);
        Serial.print("السعر: ");
        Serial.println(price);
        Serial.print("الوزن: ");
        Serial.println(weight);
        Serial.print("الرقم التسلسلي: ");
        Serial.println(serial);
        Serial.print("الرف: ");
        Serial.println(shelf);
        Serial.println("----------------------");
    }
}

void loop()
{
    // لا يوجد أي معالجة في loop
}
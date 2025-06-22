//
//الكود الخاص بجلب البيانات من firebase وعرضها على الشاشة التسلسلية


#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

/* 1. Define WiFi credentials */
#define WIFI_SSID "Yosef"
#define WIFI_PASSWORD "28072004"

/* 2. Define Firebase API Key */
#define API_KEY "AIzaSyC2NAi_IKDllubxm7_WJ7RRfdT6Q9b_Haw"

/* 3. Define RTDB URL */
#define DATABASE_URL "https://test1-53894-default-rtdb.firebaseio.com/"

/* 4. Define user Email and Password */
#define USER_EMAIL "test1@gmail.com"
#define USER_PASSWORD "123456789"

// Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
const int ledPin = D4; // GPIO2 (D4) on ESP8266

void setup()
{
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW); // Initialize LED off

    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());

    /* Assign Firebase API Key and credentials */
    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    config.database_url = DATABASE_URL;

    /* Configure Firebase */
    Firebase.reconnectNetwork(true);
    fbdo.setBSSLBufferSize(1024, 1024); // Reduce buffer size for ESP8266
    fbdo.setResponseSize(1024);

    Firebase.begin(&config, &auth);
    Firebase.setDoubleDigits(5);
    config.timeout.serverResponse = 10 * 1000;
}

void loop()
{
    if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0))
    {
        sendDataPrevMillis = millis();

        // مثال: جلب بيانات منتج واحد من قاعدة البيانات
        String name = "";
        float price = 0;
        float weight = 0;
        String serial = "";

        if (Firebase.getString(fbdo, "/products/product1/name"))
        {
            name = fbdo.stringData();
        }
        if (Firebase.getFloat(fbdo, "/products/product1/price"))
        {
            price = fbdo.floatData();
        }
        if (Firebase.getFloat(fbdo, "/products/product1/weight"))
        {
            weight = fbdo.floatData();
        }
        if (Firebase.getString(fbdo, "/products/product1/serial"))
        {
            serial = fbdo.stringData();
        }

        Serial.println("----------------------");
        Serial.print("اسم المنتج: ");
        Serial.println(name);
        Serial.print("السعر: ");
        Serial.println(price);
        Serial.print("الوزن: ");
        Serial.println(weight);
        Serial.print("الرقم التسلسلي: ");
        Serial.println(serial);
        Serial.println("----------------------");
    }
}
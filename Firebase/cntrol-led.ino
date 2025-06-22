// File: esp8266-projects/Firebase/control-led.ino
// +// الكود الخاص بالتحكم في LED باستخدام Firebase و ESP8266
// +// هذا الكود يقوم بقراءة حالة LED من Firebase وتحديثه بناءً

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

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Initialize LED off

  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
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

void loop() {
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    int ledState;
    // Corrected: Use Firebase.getInt() instead of Firebase.RTDB.getInt()
    if (Firebase.getInt(fbdo, "/led/state", &ledState)) {
      digitalWrite(ledPin, ledState);
      Serial.print("LED state updated to: ");
      Serial.println(ledState);
    } else {
      Serial.println("Failed to read LED state: " + fbdo.errorReason());
    }
  }
}
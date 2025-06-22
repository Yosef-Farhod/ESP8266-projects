📡 ESP8266 Projects
A collection of experimental and practical projects using the ESP8266 microcontroller (e.g., NodeMCU, Wemos D1 mini).
This repo includes examples for connecting to WiFi, sending data to Firebase, reading sensors, and general IoT prototyping.

📁 Folder Structure
ESP8266-projects/
├── firebase-uploader/       # Send data to Firebase Realtime DB
├── wifi-manager/            # Auto WiFi connect with reconnection logic
├── http-get-example/        # HTTP GET request to a REST API
├── led-control-web/         # Control LED from web page
├── sensor-datalogger/       # Read from sensor and log data
└── README.md
Each folder contains:

.ino file (Arduino sketch)

Comments in English and/or Arabic

Wiring notes or README.txt if needed

📦 Common Libraries Used
ESP8266WiFi.h

FirebaseESP8266.h

ESPAsyncWebServer.h

DHT.h, Adafruit_Sensor.h (for DHT sensors)

ArduinoJson.h (for JSON formatting)

SoftwareSerial.h (if needed)

Install via Arduino Library Manager or use PlatformIO.

🚀 Sample Projects
Folder	Description
firebase-uploader	Connects ESP8266 to WiFi and uploads data to Firebase RTDB
wifi-manager	WiFi auto-reconnect and status monitor
http-get-example	Makes HTTP GET requests and parses responses
led-control-web	Simple web server to turn on/off LED using browser
sensor-datalogger	Reads temperature/humidity and sends values online

🧠 Goals
Learn core networking features of ESP8266.

Practice using Firebase and HTTP with microcontrollers.

Build small IoT blocks to integrate into bigger systems.

⚙️ Setup Instructions
Install Arduino IDE or PlatformIO.

Add ESP8266 board support (via Boards Manager).

Clone this repo:

git clone https://github.com/YOUR_USERNAME/ESP8266-projects.git
cd ESP8266-projects
Open any folder and upload to your ESP8266 board.

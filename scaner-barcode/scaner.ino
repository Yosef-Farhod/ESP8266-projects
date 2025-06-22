#include <SoftwareSerial.h>

// تعيين بنات الاتصال التسلسلي مع GM65
#define GM65_RX D5  // أي بنت رقمية متاحة
#define GM65_TX D6

SoftwareSerial barcodeSerial(GM65_RX, GM65_TX); // RX, TX

void setup() {
  Serial.begin(9600);             // الاتصال التسلسلي مع Serial Monitor
  barcodeSerial.begin(9600);      // الاتصال مع قارئ الباركود GM65
  Serial.println("Barcode scanner ready...");
}

void loop() {
  // التحقق من وصول بيانات من الماسح
  if (barcodeSerial.available()) {
    String barcode = "";
    while (barcodeSerial.available()) {
      char c = barcodeSerial.read();
      barcode += c;
      delay(5); // لتفادي فقد البيانات
    }
    Serial.print("Scanned barcode: ");
    Serial.println(barcode);
  }
}
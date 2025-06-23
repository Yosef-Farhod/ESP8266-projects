// expected libraries: HX711 library for weight sensor.

#include "HX711.h"

// الأرجل المناسبة لـ ESP8266 (مثال: NodeMCU)
#define DOUT D2  // GPIO4
#define CLK  D1  // GPIO5

HX711 scale;

float calibration_factor = 800; // يمكن تغييره حسب المعايرة

void setup() {
  Serial.begin(115200);
  scale.begin(DOUT, CLK);
  Serial.println("بدء الاتصال بحساس الوزن...");

  if (scale.is_ready()) {
    Serial.println("تم توصيل الحساس بنجاح");
    scale.set_scale(calibration_factor);
    scale.tare();
    Serial.println("تم تصفير الميزان. الرجاء وضع الوزن لبدء القراءة...");
  } else {
    Serial.println("فشل في الاتصال بالحساس");
    while (1);
  }
}

void loop() {
  float reading = scale.get_units(5); // متوسط 5 قراءات
  if (reading < 0)
    reading = 0;
    
  Serial.print("الوزن: ");
  Serial.print(reading, 2);
  Serial.println(" غرام");

  delay(1000);
}
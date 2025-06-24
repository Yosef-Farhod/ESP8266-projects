#include <Arduino.h>

const float product_weight = 500.0; // جم
const float threshold = 30.0;       // أقل فرق نعتبره تغيير حقيقي

const char *product_name = "Mango Juice";
const char *barcode = "445566";

void process_weight_change(float diff)
{
    int product_count = round(diff / product_weight);
    if (product_count > 0)
    {
        Serial.printf("✅ %d × %s taken\n", product_count, product_name);
        Serial.printf("📦 Barcode: %s\n\n", barcode);
    }
    else if (product_count < 0)
    {
        Serial.printf("🔄 %d × %s returned\n", abs(product_count), product_name);
        Serial.printf("📦 Barcode: %s\n\n", barcode);
    }
}

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
        delay(10);
    }
    Serial.println("Starting manual weight monitoring...\n");
    Serial.print("Enter initial weight (g): ");
}

float previous_weight = 0.0;
bool got_initial = false;

void loop()
{
    static String input = "";
    while (Serial.available())
    {
        char c = Serial.read();
        if (c == '\n' || c == '\r')
        {
            if (input.length() > 0)
            {
                float current_weight = input.toFloat();
                if (!got_initial)
                {
                    previous_weight = current_weight;
                    got_initial = true;
                    Serial.println();
                }
                else
                {
                    float diff = previous_weight - current_weight;
                    Serial.printf("Current weight: %.2f g | Difference: %.2f g\n", current_weight, diff);
                    if (abs(diff) >= threshold)
                    {
                        process_weight_change(diff);
                        previous_weight = current_weight;
                    }
                }
                Serial.print("Enter current weight (g): ");
                input = "";
            }
        }
        else if (isPrintable(c))
        {
            input += c;
        }
    }
    delay(10); // لتقليل استهلاك المعالج
}

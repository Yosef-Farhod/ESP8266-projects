import time

# الوزن المتوقع للمنتج الواحد
product_weight = 500  # جم
threshold = 30        # أقل فرق نعتبره تغيير حقيقي

# اسم المنتج
product_name = "Mango Juice"
barcode = "445566"

def process_weight_change(diff):
    product_count = round(diff / product_weight)
    if product_count > 0:
        print(f"✅ {product_count} × {product_name} taken")
        print(f"📦 Barcode: {barcode}\n")
    elif product_count < 0:
        print(f"🔄 {abs(product_count)} × {product_name} returned")
        print(f"📦 Barcode: {barcode}\n")

print("Starting manual weight monitoring...\n")
previous_weight = float(input("Enter initial weight (g): "))

while True:
    try:
        current_weight = float(input("Enter current weight (g): "))
    except ValueError:
        print("❌ Invalid input. Please enter a number.")
        continue

    diff = previous_weight - current_weight
    print(f"Current weight: {current_weight:.2f} g | Difference: {diff:.2f} g")

    if abs(diff) >= threshold:
        process_weight_change(diff)
        previous_weight = current_weight

    # يمكنك إزالة أو تعديل التأخير حسب الحاجة
    time.sleep(0.5)

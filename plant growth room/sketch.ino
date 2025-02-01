#include <Servo.h>  // مكتبة محرك السيرفو

// تعريف الثوابت للعتبات
const int TEMP_THRESHOLD_HIGH = 30;  // الحد الأعلى لدرجة الحرارة
const int TEMP_THRESHOLD_LOW = 20;   // الحد الأدنى لدرجة الحرارة
const int HUMIDITY_THRESHOLD = 512;  // عتبة الرطوبة (افتراض أن 512 تمثل 50%)
const int SOIL_MOISTURE_THRESHOLD = 307;  // عتبة رطوبة التربة (افتراض أن 307 تمثل 30%)

const int WATER_PUMP_DURATION = 10000;  // مدة تشغيل مضخة المياه بالميلي ثانية

// تعريف المستشعرات والمكونات
Servo ventServo;    // محرك السيرفو لفتح الفتحة
int tempSensorPin = A0; // مستشعر درجة الحرارة (مثال: LM35)
int humiditySensorPin = A1; // مستشعر الرطوبة
int soilMoisturePin = A2; // مستشعر رطوبة التربة
int heaterPin = 2;  // السخان
int waterPumpPin = 3; // مضخة المياه

void setup() {
  Serial.begin(9600); // تهيئة الشاشة التسلسلية
  ventServo.attach(9); // توصيل محرك السيرفو بالمنفذ 9
  pinMode(heaterPin, OUTPUT); // إعداد السخان كخرج
  pinMode(waterPumpPin, OUTPUT); // إعداد المضخة كخرج
  ventServo.write(0); // إغلاق الفتحة في البداية
}

void loop() {
  // قراءة المستشعرات
  int tempValue = analogRead(tempSensorPin); // قراءة درجة الحرارة
  int humidityValue = analogRead(humiditySensorPin); // قراءة الرطوبة
  int soilMoistureValue = analogRead(soilMoisturePin); // قراءة رطوبة التربة

  // تحويل درجة الحرارة (إذا كنت تستخدم LM35)
  float temperature = (tempValue * 5.0 / 1023.0) * 100;

  // 1. التحكم في درجة الحرارة
  if (temperature > TEMP_THRESHOLD_HIGH) {
    ventServo.write(90); // فتح الفتحة
    Serial.println("Vent opened: Temperature > 30°C");
  } else if (temperature < TEMP_THRESHOLD_LOW) {
    digitalWrite(heaterPin, HIGH); // تشغيل السخان
    Serial.println("Heater ON: Temperature < 20°C");
  } else {
    ventServo.write(0); // إغلاق الفتحة
    digitalWrite(heaterPin, LOW); // إيقاف السخان
  }

  // 2. التحكم في الرطوبة
  if (humidityValue < HUMIDITY_THRESHOLD) { // افتراض أن 512 هو 50% (يجب معايرة المستشعر)
    Serial.println("Warning: Humidity < 50%");
  }

  // 3. التحكم في رطوبة التربة
  if (soilMoistureValue < SOIL_MOISTURE_THRESHOLD) { // افتراض أن 307 هو 30% (يجب معايرة المستشعر)
    digitalWrite(waterPumpPin, HIGH); // تشغيل المضخة
    Serial.println("Water Pump ON: Soil Moisture < 30%");
    delay(WATER_PUMP_DURATION); // تشغيل المضخة لمدة 10 ثوانٍ
    digitalWrite(waterPumpPin, LOW); // إيقاف المضخة
  }

  delay(1000); // تأخير قبل الدورة التالية
}

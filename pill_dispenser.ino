#include <Wire.h>
#include <RTClib.h>
#include <Servo.h>

RTC_DS3231 rtc;
Servo pillServo;

const int buzzerPin = 8;
const int servoPin = 9;

int pillHours[] = {0, 0, 0};
int pillMinutes[] = {2, 4, 6};
int servoAngles[] = {30, 60, 90};

bool hasDispensed[3] = {false, false, false};

void setup() {
  Serial.begin(9600);
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // rtc.adjust(DateTime(2025, 5, 13, 20, 45, 0));

  pillServo.attach(servoPin);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  DateTime now = rtc.now();

  for (int i = 0; i < 3; i++) {
    if (now.hour() == pillHours[i] &&
        now.minute() == pillMinutes[i] &&
        !hasDispensed[i]) {

      digitalWrite(buzzerPin, HIGH);
      delay(3000);
      digitalWrite(buzzerPin, LOW);

      pillServo.write(servoAngles[i]);
      delay(20000);
      pillServo.write(0);

      hasDispensed[i] = true;
    }

    if (now.minute() != pillMinutes[i]) {
      hasDispensed[i] = false;
    }
  }
  delay(1000);
}

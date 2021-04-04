
#include <Arduino.h>

#include <PWM.h>
#define PWM_PIN 3
const int32_t pwmFrequency = 25000; // 25 kHz
int pwmLevel = 255; // Default to full speed

void setup(void) {
  // Enable serial communication over USB
  Serial.begin(9600);

  // Setup PWM output
  InitTimersSafe();
  SetPinFrequencySafe(PWM_PIN, pwmFrequency);
}

void loop(void) {
  // Read data from serial port and set desired PWM level
  while (Serial.available() > 0) {
    int incomingByte = Serial.read();
    Serial.print("Got byte ");
    Serial.print(incomingByte, DEC);
    if (incomingByte >= 48 && incomingByte <= 57) {
      pwmLevel = map(incomingByte, 48, 57, 0, 255);
      Serial.print(", Setting PWM level ");
      Serial.print(pwmLevel, DEC);
      Serial.print("/255");
    }
    Serial.println();
  }

  // Change the PWM output
  pwmWrite(PWM_PIN, pwmLevel);

  delay(100);
}

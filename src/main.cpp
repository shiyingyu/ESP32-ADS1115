#include <Arduino.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads; 
void setup() {
  Serial.begin(9600);
  Serial.println("Hello!");
  
  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }
  ads.setGain(GAIN_TWO);
}

void loop() {
  int16_t adc0, adc1;
  float volts0, volts1, v;
  adc0 = ads.readADC_SingleEnded(0);
  volts0 = ads.computeVolts(adc0);
  // 标定系数，每个板子不一样
  float k = 1.59064, b = 1.00513;
  v = (volts0 - b) / k - ((volts0 < 1.0052) ? 0.0012 : 0);

  Serial.print("AIN0: "); Serial.print(adc0); Serial.print("  "); Serial.print(volts0, 4); Serial.print("V   ");Serial.print(v, 4); Serial.println("V");

  delay(100);
}
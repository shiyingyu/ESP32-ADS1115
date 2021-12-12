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
  // 重要，设置为GAIN_TWO可得到较高的分辨率，不可乱改，跟电路设计有关，若超出范围，会导致读取值错误甚至烧坏芯片
  ads.setGain(GAIN_TWO);
}

void loop() {
  int16_t adc0;
  float volts0, v;
  // 读取第一个通道的采样值
  adc0 = ads.readADC_SingleEnded(0);
  // 转换为电压（单位V）
  volts0 = ads.computeVolts(adc0);

  // 根据电路板的体质各异进行标定，获取更为精准的电压值
  // 标定系数
  float k = 1.59064, b = 1.00513;

  // 标定公式，将ADC值转换为真实的电压值
  v = (volts0 - b) / k - ((volts0 < 1.0052) ? 0.0012 : 0);

  Serial.print(v, 4); Serial.println("V");

  delay(100);
}
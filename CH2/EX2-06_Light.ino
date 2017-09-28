#include <math.h>
const int ledPin=12;        //LED 連接腳位為Pin12
const int thresholdvalue=10;  // LED 點亮的門檻值 
float Rsensor; //Resistance of sensor in K
void setup() {
  Serial.begin(9600);               //設定與serial monitor溝通的鮑率
  pinMode(ledPin,OUTPUT);       //設定LED為output
}
void loop() {
  int sensorValue = analogRead(0); 
  Rsensor=(float)(1023-sensorValue)*10/sensorValue;
  if(Rsensor>thresholdvalue)
  {
    digitalWrite(ledPin,HIGH);
  }
  else
  {
  digitalWrite(ledPin,LOW);
  }
  Serial.println("the analog read data is ");
  Serial.println(sensorValue);
  Serial.println("the sensor resistance is ");
  Serial.println(Rsensor,DEC); //將光量顯示於序列監視器
  delay(1000);
}

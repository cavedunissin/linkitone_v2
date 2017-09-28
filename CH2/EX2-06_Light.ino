#include <math.h>
const int ledPin=12;        //LED �s���}�쬰Pin12
const int thresholdvalue=10;  // LED �I�G�����e�� 
float Rsensor; //Resistance of sensor in K
void setup() {
  Serial.begin(9600);               //�]�w�Pserial monitor���q���j�v
  pinMode(ledPin,OUTPUT);       //�]�wLED��output
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
  Serial.println(Rsensor,DEC); //�N���q��ܩ�ǦC�ʵ���
  delay(1000);
}

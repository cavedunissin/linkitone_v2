#include <LBT.h>
#include <LBTServer.h>

const int Motor_M1_1 = 4;   
const int Motor_M1_2 = 5;
const int Motor_M2_1 = 6;
const int Motor_M2_2 = 7;
char val;

void setup()  
{
  Serial.begin(115200);
  
  while(!LBTServer.accept(30));
  if(!LBTServer.begin((uint8_t*)"BTServer"))
  {
    Serial.println("Fail to start BT.");
    return;
  }
  Serial.println("BT server is started.");
  
  pinMode(Motor_M1_1, OUTPUT);
  pinMode(Motor_M1_2, OUTPUT);
  pinMode(Motor_M2_1, OUTPUT);
  pinMode(Motor_M2_2, OUTPUT);
}

void loop()
{
  if(LBTServer.available() > 0)
  {
    val = LBTServer.read();
    switch(val)
    {
      case 'f':   // car forward
                forward();
                break;
      case 'b':   // car backward
                backward();
                break;
      case 'l':   // car turn left
                left();
                break;
      case 'r':   // car turn right
                right();
                break;
      case 's':   // car stop
                motorstop();
                break;
    }
  }
}

void motorstop()
{
  digitalWrite(Motor_M1_1,LOW);
  digitalWrite(Motor_M1_2,LOW);
  digitalWrite(Motor_M2_1,LOW);
  digitalWrite(Motor_M2_2,LOW);
}

void forward()
{
  digitalWrite(Motor_M1_1,HIGH);
  digitalWrite(Motor_M1_2,LOW);
  digitalWrite(Motor_M2_1,HIGH);
  digitalWrite(Motor_M2_2,LOW);
}

void backward()
{
  digitalWrite(Motor_M1_1,LOW);
  digitalWrite(Motor_M1_2,HIGH);
  digitalWrite(Motor_M2_1,LOW);
  digitalWrite(Motor_M2_2,HIGH);
}

void right()
{
  digitalWrite(Motor_M1_1,HIGH);
  digitalWrite(Motor_M1_2,LOW);
  digitalWrite(Motor_M2_1,LOW);
  digitalWrite(Motor_M2_2,HIGH);
}

void left()
{
  digitalWrite(Motor_M1_1,LOW);
  digitalWrite(Motor_M1_2,HIGH);
  digitalWrite(Motor_M2_1,HIGH);
  digitalWrite(Motor_M2_2,LOW);
}

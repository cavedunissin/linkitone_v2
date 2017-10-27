//CAVEDU 2017
#include <LBT.h>
#include <LBTServer.h>

const int Motor_M1_1 = 4;  // digital pin 5 of Arduino (PWM)    
const int Motor_M1_2 = 5;  // digital pin 6 of Arduino (PWM)  
const int Motor_M2_1 = 6;  // digital pin 7 of Arduino
const int Motor_M2_2 = 7;  // digital pin 8 of Arduino
char val;                  // variable to receive data from the serial port(bluetooth)

const int Right_speed = 3; // digital pin 7 of Arduino
const int Left_speed = 9;  // digital pin 8 of Arduino
int wheelspeed;

byte cmmd[20];
int insize = 2;

void setup()  
{
  // Start serial communication at 9600
  Serial.begin(115200); 
  if(!LBTServer.begin((uint8_t*)"BTServer"))
  {
    Serial.println("Fail to start BT.");
    return;
  }
  Serial.println("BT server is started.");
  while(!LBTServer.accept(30));
  pinMode(Motor_M1_1, OUTPUT);
  pinMode(Motor_M1_2, OUTPUT);
  pinMode(Motor_M2_1, OUTPUT);
  pinMode(Motor_M2_2, OUTPUT);
}

void loop()
{
  if((insize = LBTServer.available())>0)  //check for incoming message
  {
    for(int i = 0; i < insize; i++)
    {
      cmmd[i] = LBTServer.read();
      if(insize-i-2 >= 0)
      {
        wheelspeed += cmmd[i]*pow(10,insize-i-2);
      }
      else
      {
        val = char(cmmd[i]);
      }
    }
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
    wheelspeed = 0;
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
  analogWrite(Left_speed,wheelspeed);
  analogWrite(Right_speed,wheelspeed);
}

void backward()
{
  digitalWrite(Motor_M1_1,LOW);
  digitalWrite(Motor_M1_2,HIGH);
  digitalWrite(Motor_M2_1,LOW);
  digitalWrite(Motor_M2_2,HIGH);
  analogWrite(Left_speed,wheelspeed);
  analogWrite(Right_speed,wheelspeed);
}

void right()
{
  digitalWrite(Motor_M1_1,HIGH);
  digitalWrite(Motor_M1_2,LOW);
  digitalWrite(Motor_M2_1,LOW);
  digitalWrite(Motor_M2_2,HIGH);
  analogWrite(Left_speed,wheelspeed);
  analogWrite(Right_speed,wheelspeed);
}

void left()
{
  digitalWrite(Motor_M1_1,LOW);
  digitalWrite(Motor_M1_2,HIGH);
  digitalWrite(Motor_M2_1,HIGH);
  digitalWrite(Motor_M2_2,LOW);
  analogWrite(Left_speed,wheelspeed);
  analogWrite(Right_speed,wheelspeed);
}

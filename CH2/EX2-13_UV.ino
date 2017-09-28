void setup(){
 
  Serial.begin(9600);
}
 
void loop()
{  
  int sensorValue;
  long  sum=0;
  for(int i=0;i<1024;i++)
   {  
      sensorValue=analogRead(A0);
      sum=sensorValue+sum;
      delay(2);
   }   
 sum = sum >> 10;
 Serial.print("The voltage value:");
 Serial.print(sum*4980.0/1023.0);
 Serial.println("mV");
 delay(20);
 Serial.print("\n");
 
}
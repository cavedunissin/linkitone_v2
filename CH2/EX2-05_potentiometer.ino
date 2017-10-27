const int led =3;
const int pot = A0;
   
void setup()
{
   //
}
   
void loop()
{
   int val = analogRead(pot);       // get analog pin data
   val = map(val, 0, 1023, 0, 255); // map analog data to 0～255
   analogWrite(led, val);           // set LED brightness by potentiometer status
   delay(10);                       // 10ms
}  

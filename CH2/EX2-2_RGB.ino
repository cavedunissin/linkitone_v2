  const int ledR = 2;
   const int ledB = 3;
   const int ledG = 4;
   
   const int buttonR = 5;
   const int buttonG = 6;
   const int buttonB = 7;
 
   void setup()
   {
       pinMode(ledR, OUTPUT);           // �]�w�Ҧ�LED�O�}���X
       pinMode(ledG, OUTPUT);
       pinMode(ledB, OUTPUT);
       
       pinMode(buttonR, INPUT);          // �]�w�Ҧ�LED�O�}���J
       pinMode(buttonG, INPUT);
       pinMode(buttonB, INPUT);
   }
   
   void loop()
   {
       int stateR = 1-digitalRead(buttonR);   // �]�w�Ҧ��u�����s�ܼ�
       int stateG = 1-digitalRead(buttonG);
       int stateB = 1-digitalRead(buttonB);
       
       digitalWrite(ledR, stateR);       // �]�w�P��۹������s��LED�C��
       digitalWrite(ledG, stateG);
       digitalWrite(ledB, stateB);
       
       delay(10);
   }

  const int led =3;
   const int pot = A0;
   
   void setup()
   {
       // ���ݭn�]�w����F��
   }
   
   void loop()
   {
       int val = analogRead(pot);          // ����i�ܹq������
       val = map(val, 0, 1023, 0, 255);    // �N�T������256�Ӥ�ҡ]0��255)
       analogWrite(led, val);           // �N�i�ܹq�����T���ǤJLED
       delay(10);                    // ����10�@��
   }  

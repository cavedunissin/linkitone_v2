  const int led =3;
   const int pot = A0;
   
   void setup()
   {
       // 不需要設定任何東西
   }
   
   void loop()
   {
       int val = analogRead(pot);          // 抓取可變電阻的值
       val = map(val, 0, 1023, 0, 255);    // 將訊號分成256個比例（0～255)
       analogWrite(led, val);           // 將可變電阻的訊號傳入LED
       delay(10);                    // 等待10毫秒
   }  

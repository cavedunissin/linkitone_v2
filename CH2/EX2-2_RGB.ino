  const int ledR = 2;
   const int ledB = 3;
   const int ledG = 4;
   
   const int buttonR = 5;
   const int buttonG = 6;
   const int buttonB = 7;
 
   void setup()
   {
       pinMode(ledR, OUTPUT);           // 設定所有LED燈腳位輸出
       pinMode(ledG, OUTPUT);
       pinMode(ledB, OUTPUT);
       
       pinMode(buttonR, INPUT);          // 設定所有LED燈腳位輸入
       pinMode(buttonG, INPUT);
       pinMode(buttonB, INPUT);
   }
   
   void loop()
   {
       int stateR = 1-digitalRead(buttonR);   // 設定所有彈跳按鈕變數
       int stateG = 1-digitalRead(buttonG);
       int stateB = 1-digitalRead(buttonB);
       
       digitalWrite(ledR, stateR);       // 設定與當相對應按鈕的LED顏色
       digitalWrite(ledG, stateG);
       digitalWrite(ledB, stateB);
       
       delay(10);
   }

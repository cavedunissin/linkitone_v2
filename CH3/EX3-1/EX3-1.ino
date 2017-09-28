#include <LGSM.h>
void setup() {
  Serial.begin(9600);

  while (!LSMS.ready())
    delay(1000);

  Serial.println("SIM ready for work!");
  LSMS.beginSMS("09XXXXXXXX"); //在此輸入收訊人的電話號碼
  LSMS.print("Hello from LinkIt");
  if (LSMS.endSMS())
  {
    Serial.println("SMS is sent");
  }
  else
  {
    Serial.println("SMS is not sent");
  }
}
void loop()
{
  // 無動作
}


#include <LGPRS.h>
#include <LGPRSClient.h>
#define SITE_URL "www.mediatek.com"
LGPRSClient client;
void setup()
{
  Serial.begin(9600);

  while (!LGPRS.attachGPRS()) //檢查 GPRS 是否可用
  {
    Serial.println("wait for SIM card ready");
    delay(1000);
  }
  Serial.print("Connecting to : " SITE_URL "...");
  if (!client.connect(SITE_URL, 80))
  {
    Serial.println("FAIL!");
    return;
  }
  Serial.println("done");
  Serial.print("Sending GET request...");
  client.println("GET / HTTP/1.1");
  client.println("Host: " SITE_URL ":80");
  client.println();
  Serial.println("done ");
}
void loop()
{
  int v;
  while (client.available())
  {
    v = client.read();
    if (v < 0)
      break;
    Serial.write(v);
  }
  delay(500);
}


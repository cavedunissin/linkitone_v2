#include <LGPRS.h>
#include <LGPRSClient.h>
#include <LGPRSServer.h>

#include <LGPS.h>
#include <HttpClient.h>
#include <LDateTime.h>

#define per 50
#define per1 3
#define DEVICEID "DUE6z588"
#define DEVICEKEY "QaY437J8EFV5p0Gs"
#define SITE_URL "api.mediatek.com"

gpsSentenceInfoStruct info;
char buff[256];
double latitude;
double longitude;

char buffer_latitude[8];
char buffer_longitude[8];

LGPRSClient c;
unsigned int rtc;
unsigned int lrtc;
unsigned int rtc1;
unsigned int lrtc1;
char port[4]={0};
char connection_info[21]={0};
char ip[15]={0}; 
int portnum;
int val = 0;
String tcpdata = String(DEVICEID) + "," + String(DEVICEKEY) + ",0";
String upload_led;

LGPRSClient c2;
HttpClient http(c2);

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  LGPS.powerOn();
  while(!Serial);
  
  Serial.print("GPRS attaching...");
  while (!LGPRS.attachGPRS())
  {
    Serial.print(".");
    delay(200);
  }
  Serial.println("Success!");
  getconnectInfo();
  connectTCP();
  Serial.println("==============================");
}

void loop()
{
  LDateTime.getRtc(&rtc);
  if ((rtc - lrtc) >= per) {
    heartBeat();
    lrtc = rtc;
  }
  //Check for report datapoint status interval
  LDateTime.getRtc(&rtc1);
  if ((rtc1 - lrtc1) >= per1) {
    //uploadstatus();
    GPS_receive();
    uploadstatus();
    lrtc1 = rtc1;
  }
}

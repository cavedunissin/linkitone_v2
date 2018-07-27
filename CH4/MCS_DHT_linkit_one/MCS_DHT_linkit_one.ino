//2017 CAVEDU
#include <LTask.h>
#include <LWiFi.h>
#include <LWiFiClient.h>
#include <Wire.h>
#include <math.h>
#include <LDateTime.h>
#include <HttpClient.h>
#include "LDHT.h"
#define DHTPIN 2          // what pin we're connected to
#define DHTTYPE DHT11     // using DHT11 sensor

LDHT dht(DHTPIN, DHTTYPE);
float tempC = 0.0, Humi = 0.0;

const unsigned char OSS = 0;  // Oversampling Setting
int state = 0;
int i = 0;

// b5 is calculated in bmp085GetTemperature(...), this variable is also used in bmp085GetPressure(...)
// so ...Temperature(...) must be called before ...Pressure(...).
long b5;
unsigned int rtc;
unsigned int lrtc;
unsigned int lrtc2;
unsigned int rtc2;
unsigned int rtc1;
unsigned int lrtc1;

#define WIFI_AP "cavedu"
#define WIFI_PASSWORD "12345678"
#define WIFI_AUTH LWIFI_WPA  // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP.
#define SITE_URL "api.mediatek.com"
#define per 5
#define per1 50
#define DEVICEID "D4trFIKD"
#define DEVICEKEY "D010YYBptER1dCfp"
LWiFiClient c;
LWiFiClient c2;
char port[5] = "    ";
char connection_info[21] = "                    ";
char ip[15] = "              ";
int portnum;
int val = 0;
String tcpdata = String(DEVICEID) + "," + String(DEVICEKEY) + ",0";
String upload_led;
HttpClient http(c2);

void setup() {
  LTask.begin();
  LWiFi.begin();
  Serial.begin(115200);
  while (!Serial) delay(1000); //mark this when ready for demo
  Serial.println("Connecting to AP");
  while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD)))
  {
    delay(1000);
  }

  delay(100);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  Serial.print("LED is set to LOW");
  //connection();
  LDateTime.getRtc(&lrtc);
  LDateTime.getRtc(&lrtc2);
  while (!c2.connect(SITE_URL, 80))
  {
    Serial.println("Re-Connecting to WebSite");
    delay(1000);
  }
  delay(100);
  getconnectInfo();
  connectTCP();
}

void loop() {
  if (LWiFi.status() == LWIFI_STATUS_DISCONNECTED) {
    Serial.println("Disconnected from AP");
    while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD)))
    {
      Serial.println("Connecting to AP");
      delay(1000);
    }
  }

  LDateTime.getRtc(&rtc);
  if ((rtc - lrtc) >= per) {
    Serial.println("Senddata");
    senddata();
    lrtc = rtc;
  }

  //Check for hearbeat interval
  LDateTime.getRtc(&rtc2);
  if ((rtc2 - lrtc2) >= per1) {
    heartBeat();
    lrtc2 = rtc2;
  }
}

void getconnectInfo() {
  //calling RESTful API to get TCP socket connection
  c2.print("GET /mcs/v2/devices/");
  c2.print(DEVICEID);
  c2.println("/connections.csv HTTP/1.1");
  c2.print("Host: ");
  c2.println(SITE_URL);
  c2.print("deviceKey: ");
  c2.println(DEVICEKEY);
  c2.println("Connection: close");
  c2.println();

  delay(500);

  int errorcount = 0;
  while (!c2.available())
  {
    Serial.println("waiting HTTP response: ");
    Serial.println(errorcount);
    errorcount += 1;
    if (errorcount > 10) {
      c2.stop();
      return;
    }
    delay(100);
  }
  int err = http.skipResponseHeaders();

  int bodyLen = http.contentLength();
  Serial.print("Content length is: ");
  Serial.println(bodyLen);
  Serial.println();
  char c;
  int ipcount = 0;
  int count = 0;
  int separater = 0;
  while (c2)
  {
    int v = c2.read();
    if (v != -1)
    {
      c = v;
      Serial.print(c);
      connection_info[ipcount] = c;
      if (c == ',')
        separater = ipcount;
      ipcount++;
    }
    else
    {
      Serial.println("no more content, disconnect");
      c2.stop();
    }
  }

  Serial.print("The connection info: ");
  Serial.println(connection_info);
  int i;
  for (i = 0; i < separater; i++)
  {
    ip[i] = connection_info[i];
  }
  int j = 0;
  separater++;
  for (i = separater; i < 21 && j < 4; i++)
  {
    port[j] = connection_info[i];
    j++;
  }
  Serial.println("The TCP Socket connection instructions:");
  Serial.print("IP: ");
  Serial.println(ip);
  Serial.print("Port: ");
  Serial.println(port);
  portnum = atoi (port);
} //getconnectInfo

void connectTCP() {
  //establish TCP connection with TCP Server with designate IP and Port
  c.stop();
  Serial.println("Connecting to TCP");
  while (0 == c.connect("54.255.209.252", 443))
  {
    Serial.println("Re-Connecting to TCP");
    delay(1000);
  }
  Serial.println("send TCP connect");
  c.println(tcpdata);
  c.println();
  Serial.println("waiting TCP response:");
} //connectTCP

void heartBeat() {
  Serial.println("send TCP heartBeat");
  c.println(tcpdata);
  c.println();
} //heartBeat

void senddata() {
  Serial.println("Begin of senddata");
  tempC = dht.readTemperature();
  Humi = dht.readHumidity();

  Serial.println("1");
  char buffert[5];
  char bufferh[5];
  char bufferp[10];
  Serial.println(tempC);
  Serial.println(Humi);
  Serial.println("2");

  String data = "temperature,," + String(tempC) + "\nhumidity,," + String(Humi);
  //String data = "temperature,,30.3\nhumidity,,28.9";

  Serial.println(data);
  int thisLength = data.length();
  LWiFiClient c2;
  unsigned long t1 = millis();
  while (0 == c2.connect(SITE_URL, 80))
  {
    Serial.println("Re-Connecting to WebSite");
    delay(1000);
  }

  delay(500);
  Serial.println("send POST request");

  c2.print("POST /mcs/v2/devices/");
  c2.print(DEVICEID);
  c2.println("/datapoints.csv HTTP/1.1");
  c2.print("Host: ");
  c2.println(SITE_URL);
  c2.print("deviceKey: ");
  c2.println(DEVICEKEY);
  c2.print("Content-Length: ");
  c2.println(thisLength);
  c2.println("Content-Type: text/csv");
  c2.println("Connection: close");
  c2.println();
  c2.println(data);

  String dataget = "";
  Serial.println("waiting HTTP response:");

  int errorcount = 0;
  while (!c2.available())
  {
    Serial.println("waiting HTTP response:");
    errorcount += 1;
    if (errorcount > 10) {
      c2.stop();
      return;
    }
    delay(100);
  }
  while (c2)
  {
    int v = c2.read();
    if (v != -1)
    {
      Serial.print(char(v));
      delay(1);
    }
    else
    {
      Serial.println("no more content, disconnect");
      c2.stop();
    }
  }
  Serial.println("upload successfully");
  delay(3000);
  unsigned long t2 = millis();
}//senddata

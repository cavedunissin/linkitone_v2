//2017 CAVEDU
#include <LAudio.h>

#define KEY 5
char buff[120];
unsigned char KEY_NUM = 0;

enum{Play,SetVolume,Pause,Resume,Stop};

unsigned char Status_Value = Play;

void Scan_KEY()
{
  if( digitalRead(KEY) == 0 )
  {
    delay(20);			  // 延遲20ms 以解按鈕彈跳	
    if( digitalRead(KEY) == 0 )   //檢查按鈕是否壓下
    {
  	KEY_NUM = 1;	
	while(digitalRead(KEY) == 0);		//放開按鈕
    }
  }
}

void setup()
{
  LAudio.begin();
  pinMode(KEY,INPUT_PULLUP);
  Serial.begin(115200);
  Change_Status(Play);
  pinMode(8, OUTPUT);
}

void Change_Status(unsigned char status)
{
  switch(status)
  {
    case Play:
      LAudio.playFile( storageFlash,(char*)"LS8Mo.wav");
      LAudio.setVolume(2);
      Serial.println("playOne");
      break;
    case SetVolume:
      LAudio.setVolume(6);
      Serial.println("setVolume");
      break;
    case Pause:
      LAudio.pause();
      Serial.println("pause");
      break;
    case Resume:
      LAudio.resume();
      Serial.println("resume");
      break;
    case Stop:
      LAudio.stop();
      Serial.println("stop");
      break;
    default:
      break;
  }
}
void loop()
{
   AudioStatus status;
   Scan_KEY();
   status = LAudio.getStatus();
   if(status == AudioEndOfFile) //檔案播放完畢
   {
     Status_Value = Play;
     Change_Status(Status_Value);
   }
   if(KEY_NUM == 1)
   {
	KEY_NUM = 0;
	Change_Status(Status_Value);
	Status_Value++;
	if(Status_Value == Stop+1)
	{
	  Status_Value = Play;
	}
   }
   delay(1000);
}

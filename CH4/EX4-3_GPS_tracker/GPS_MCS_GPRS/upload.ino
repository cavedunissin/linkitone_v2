void uploadstatus(){
  while (!c2.connect(SITE_URL, 80))
  {
    Serial.print("!");
    delay(300);
  }
  delay(100);
  
  //Serial.printf("latitude=%.4f\tlongitude=%.4f\n",latitude,longitude);
  if(latitude>-90 && latitude<90 && longitude>0 && longitude<360){
    sprintf(buffer_latitude, "%.4f", latitude);
    sprintf(buffer_longitude, "%.4f", longitude);
  }
    
  String upload_GPS = "GPS,,"+String(buffer_latitude)+","+String(buffer_longitude)+","+"0"+"\n"+"latitude,,"+buffer_latitude+"\n"+"longitude,,"+buffer_longitude;//null altitude
  
  int GPS_length = upload_GPS.length();
  HttpClient http(c2);
  c2.print("POST /mcs/v2/devices/");
  c2.print(DEVICEID);
  c2.println("/datapoints.csv HTTP/1.1");
  c2.print("Host: ");
  c2.println(SITE_URL);
  c2.print("deviceKey: ");
  c2.println(DEVICEKEY);
  c2.print("Content-Length: ");
  c2.println(GPS_length);
  c2.println("Content-Type: text/csv");
  c2.println("Connection: close");
  c2.println();
  c2.println(upload_GPS);
  delay(500);
  
  while (!c2.available())
  {
    Serial.print(".");
    delay(300);
  }
  int err = http.skipResponseHeaders();
  int bodyLen = http.contentLength();
  
  while (c2){
    int v = c2.read();
    if (v != -1){
      Serial.print(char(v));
    }
    else{
      Serial.println("no more content, disconnect");
      c2.stop();
    }
  }
  Serial.println();
}

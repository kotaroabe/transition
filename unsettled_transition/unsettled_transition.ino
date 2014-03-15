#include <Wire.h>
/* RTC module library from
https://code.google.com/p/arms22/downloads/detail?name=RTC8564-001.zip */
#include <RTC8564.h>
int null;
int sec;
int count;
boolean flag=true;
unsigned int setTime = 50;     //drive a coil for 50ms

void setup()
{
  Serial.begin(9600);
  Rtc.begin();
  
  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);        // conect coil thrugh 330Ω
  pinMode(10, OUTPUT);       // coil return
  pinMode(6, INPUT);         //geigercount
  
  digitalWrite(9, LOW);      // reset coil
  digitalWrite(10, LOW);     // reset coil
}

void loop()
{
  //the second hand goes everytime a geigercounter detects radiation
 Rtc.available();
 if(sec != Rtc.seconds()){
   count++;
   sec = Rtc.seconds();
 }
 
 if(digitalRead(6) == null){
   
   for(int i = 0; i < count; i++){
     digitalWrite(13,HIGH);     // LED flash
     flag = ! flag;
     if(flag == true) {
       digitalWrite(9, HIGH);    // coil drive foward
       delay(setTime);           // wait 
       digitalWrite(9, LOW);     // coil drive end
     }
     else {
       digitalWrite(10, HIGH);   // coil drive revers
       delay(setTime);           // wait
       digitalWrite(10, LOW);    // coil drive end
     }
     digitalWrite(13,LOW);       // LED flash end
   }
   count = 0;
 }
  
}

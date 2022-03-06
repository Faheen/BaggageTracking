#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

#include <SoftReset.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10 
#define RST_PIN 9 
MFRC522 mfrc522(SS_PIN, RST_PIN);        
MFRC522::MIFARE_Key key;
SoftwareSerial mySerial(3, 9);
int red=2;
int green=4;
int blue=7;
boolean done=false;
byte number[11];
String num;

void setup() {
        
        pinMode(blue,OUTPUT);
        pinMode(red,OUTPUT);
        pinMode(green,OUTPUT);
        digitalWrite(blue,HIGH);
        digitalWrite(red,LOW);
        digitalWrite(green,LOW);
        mySerial.begin(9600);
        Serial.begin(9600);        
        SPI.begin();               
        mfrc522.PCD_Init();        
        
        while(Serial.available()==0);
        num=Serial.readString();
        num.getBytes(number,11);
 
        for (byte i = 0; i < 6; i++) {
                key.keyByte[i] = 0xFF;
        }

}

int block=4;
byte blockcontent[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
byte readbackblock[18];

void loop()
{

        digitalWrite(blue,HIGH);
        digitalWrite(red,HIGH);
        digitalWrite(green,LOW);
   
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  done = true;
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

         int a=writeBlock(block, blockcontent);
         if(a!=0)
         {
          done = false;
         }
         int b=writeBlock(block, number);
         if(b!=0)
         {
          done = false;
         }
 
         
         if(done==true)
         {
          digitalWrite(red,LOW);
          digitalWrite(blue,LOW);
          digitalWrite(green,HIGH);
          Serial.println("Write success");
          sendmsg(num);
          soft_restart();
         }
         else
         {
          digitalWrite(green,LOW);
          digitalWrite(blue,LOW);
          digitalWrite(red,HIGH);
          Serial.println("Write failure");
          delay(3000);
          soft_restart();
         }
 
}


int writeBlock(int blockNumber, byte arrayAddress[]) 
{
  int largestModulo4Number=blockNumber/4*4;
  int trailerBlock=largestModulo4Number+3;
  if (blockNumber > 2 && (blockNumber+1)%4 == 0){return 2;}
  
  
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
         
         return 3;
  }
  status = mfrc522.MIFARE_Write(blockNumber, arrayAddress, 16);
  if (status != MFRC522::STATUS_OK) {
           
           return 4;
  }
  else
    return 0;
  
}

void sendmsg(String x)
{
  mySerial.println("AT+CMGF=1");
  delay(1000);
  mySerial.println("AT+CMGS=\"+91"+x+"\"\r");
  delay(1000);
  mySerial.println("Your number has been tagged");
  delay(100);
   mySerial.println((char)26);
  delay(1000);
}







#include <SoftReset.h>

#include <SPI.h>
#include <MFRC522.h>

#include <SoftwareSerial.h>
#define SS_PIN 10
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
SoftwareSerial mySerial(3, 9);
int red=2;
int green=4;
int blue=7;

String pass;
String right={"Your number has been removed"};
String wrong={"Your baggage is in reception"};
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
        pass = Serial.readString();
        for (byte i = 0; i < 6; i++) {
                key.keyByte[i] = 0xFF;
        }
}

int block=4;

byte readbackblock[18];

void loop()
{

        digitalWrite(blue,HIGH);
        digitalWrite(red,HIGH);
        digitalWrite(green,LOW);
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
         readBlock(block, readbackblock);
         
         num={readbackblock};
         
         if(num.equals(pass))
         {
          digitalWrite(red,LOW);
          digitalWrite(blue,LOW);
          digitalWrite(green,HIGH);
          Serial.println("Correct password");
          sendmsg(num,right);
          soft_restart();
         }
         else
         {
          digitalWrite(green,LOW);
          digitalWrite(blue,LOW);
          digitalWrite(red,HIGH);
          Serial.println("Wrong password");
          sendmsg(num,wrong);
          soft_restart();
         }
}

int readBlock(int blockNumber, byte arrayAddress[]) 
{
  int largestModulo4Number=blockNumber/4*4;
  int trailerBlock=largestModulo4Number+3;

  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  
  if (status != MFRC522::STATUS_OK) {
         return 3;
  }
  
  byte buffersize = 18;
  status = mfrc522.MIFARE_Read(blockNumber, arrayAddress, &buffersize);
  if (status != MFRC522::STATUS_OK) {
          return 4;
  }
}
void sendmsg(String x,String y)
{
  mySerial.println("AT+CMGF=1");
  delay(1000);
  mySerial.println("AT+CMGS=\"+91"+x+"\"\r");
  delay(1000);
  mySerial.println(y);
  delay(100);
   mySerial.println((char)26);
  delay(1000);
}

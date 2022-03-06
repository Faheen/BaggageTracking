#include <SoftReset.h>

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10 
#define RST_PIN 5 
#include <SoftwareSerial.h>//Tx - 3 rx - 9

SoftwareSerial mySerial(3, 9);

MFRC522 mfrc522(SS_PIN, RST_PIN);    
MFRC522::MIFARE_Key key;
String num;

void setup() {
        mySerial.begin(9600);   
        Serial.begin(9600);       
        SPI.begin();              
        mfrc522.PCD_Init();       
        Serial.println("Scan a MIFARE Classic card");
        for (byte i = 0; i < 6; i++) {
                key.keyByte[i] = 0xFF;
        }

}

int block=4;
byte readbackblock[18];

void loop()
{
        
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
           
         Serial.println("card selected");
         
         int a=readBlock(block, readbackblock);
         num={readbackblock};
         Serial.println(num);
         if(a==0)
         {
          SendMessage(num);
         }
         soft_restart();
 
}

void SendMessage(String x)
{
  mySerial.println("AT+CMGF=1");
  delay(200);
  mySerial.println("AT+CMGS=\"+91"+x+"\"\r");
  delay(200);
  mySerial.println("Your baggage will arrive within x mins");
  delay(100);
   mySerial.println((char)26);
  delay(200);
}

int readBlock(int blockNumber, byte arrayAddress[]) 
{
  int largestModulo4Number=blockNumber/4*4;
  int trailerBlock=largestModulo4Number+3;
  
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK) {
         Serial.print("PCD_Authenticate() failed (read): ");
         Serial.println(mfrc522.GetStatusCodeName(status));
         return 3;//return "3" as error message
  }
  
  byte buffersize = 18;
  status = mfrc522.MIFARE_Read(blockNumber, arrayAddress, &buffersize);
  if (status != MFRC522::STATUS_OK) {
          Serial.print("MIFARE_read() failed: ");
          Serial.println(mfrc522.GetStatusCodeName(status));
          return 4;
  }
  Serial.println("block was read");
  return 0;
}

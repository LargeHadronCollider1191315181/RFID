#include <SPI.h>
#include <MFRC522.h>
#include "LCDIC2.h"

#define RST_PIN D3
#define SDA_PIN D4

LCDIC2 lcd(0x27, 16, 2);
MFRC522 mfrc522(SDA_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Put your card to the reader...");
  lcd.begin();

    lcd.setCursor(0, 0);
    lcd.print("RFID KELOMPOK 05");
    delay(2000);

}

void loop() {
  if(!mfrc522.PICC_IsNewCardPresent()){
    return;
  }

  if(!mfrc522.PICC_ReadCardSerial()){
    return;
  }

  Serial.print("UID tag :");
  String content = "";
  byte letter;

  for(byte i = 0; i < mfrc522.uid.size; i++){
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.println();
  Serial.print("Pesan : ");
  content.toUpperCase();

  if(content.substring(1) == "AB F9 7C D0"){
    Serial.println("Kartu cocok");
    lcd.setCursor(0, 0);
    lcd.print("  Kartu Cocok   ");
    Serial.println();
    delay(1000);
  }

  else if(content.substring(1) == "1A 19 F6 72"){
    Serial.println("Kartu cocok     ");
    lcd.setCursor(0, 0);
    lcd.print("  Kartu Cocok   ");
    Serial.println();
    delay(1000);
  }

  else{
    Serial.println("Kartu Tidak cocok");
    lcd.setCursor(0, 0);
    lcd.print("Kartu Tak Cocok ");
    delay(1000);
  }

}
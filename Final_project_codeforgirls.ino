#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


#define RST_PIN 9
#define SS_PIN 10

byte readCard[4];
String MasterTag = "BC 14 21 23";  // REPLACE this Tag ID with your Tag ID!!!
String tagID = "";

// Create instances
MFRC522 mfrc522(SS_PIN, RST_PIN);
//LiquidCrystal lcd(7, 6, 5, 4, 3, 2); //Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal_I2C lcd(0x27,20,4); 

const int buzzer=6;
int LEDpin=9;



  void setup() 
{
  pinMode(LEDpin,OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  // Initiating
  SPI.begin(); // SPI bus
  mfrc522.PCD_Init(); // MFRC522
 // lcd.begin(16, 2); // LCD screen

  lcd.clear();
  //lcd.print(" Access Control ");
  lcd.setCursor(0, 1);
 // lcd.print("Scan Your Card>>");


  
   lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
   lcd.setCursor(0,2);
  lcd.print("Start");
}




  // put your main code here, to run repeatedly:
  void loop() 
{
  
  //Wait until new tag is available
  while (getID()) 
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    
    if (tagID == MasterTag) 
    {
      
      // You can write any code here like opening doors, switching on a relay, lighting up an LED, or anything else you can think of.
    }
    else
    {
       
        digitalWrite(buzzer, HIGH);
        digitalWrite(LEDpin,HIGH);// turn the LED on (HIGH is the voltage level)
         delay(1000);                       // wait for a second
         digitalWrite(buzzer, LOW );
         digitalWrite(LEDpin, LOW);// turn the LED off by making the voltage LOW
          delay(1000);

        
      lcd.setCursor(3,0);
      lcd.print("cat out!");
      lcd.setCursor(2,1);
      lcd.print("catch her!");
       
    }
    
      lcd.setCursor(0, 1);
     // lcd.print(" ID : ");
     // lcd.print(tagID);
      
    delay(2000);

    lcd.clear();
    lcd.print("  Cat inside");
    lcd.setCursor(0, 1);
   // lcd.print("Scan Your Card>>");
  }
}

//Read new tag if available
boolean getID() 
{
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
  return false;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
  return false;
  }
  tagID = "";
  for ( uint8_t i = 0; i < 4; i++) { // The MIFARE PICCs that we use have 4 byte UID
  //readCard[i] = mfrc522.uid.uidByte[i];
  tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); // Adds the 4 bytes in a single String variable
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); // Stop reading
  return true;
}

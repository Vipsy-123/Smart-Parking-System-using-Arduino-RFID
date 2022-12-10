/***********************************************************  SMART PARKING SYSTEM ****************************************************************** 
 *   
 *  ABOUT : 
 *      #SMART PARKING SYSTEM ENABLES YOU A SECURE PROCESS FOR PARKING OF OWNER'S VEHICLES WITHOUT ANY INTRUSION OF UNKNOWN VEHICLES.
 *      #RFID SENSOR WILL SENSE ONLY REGISTERED RFID TAGS AND REJECT THE UNKNOWN TAGS BY PLAYING BUZZER SOUND.
 *      #WHEN A TAG IS ACCEPTED, BARRIER ATTACHED TO SERVO MOTOR WILL OPEN AND VEHICLE WILL BE ALLOWED TO ENTER PARKING AREA. 
 *      #IF PARKING SLOTS ARE AVAILABLE  BARRIER WILL ALLOW THE VEHICLES IN ,ELSE IF PARKING SLOTS ARE NOT AVAILABLE BARRIER WILL STAY DOWN. 
 *      #LCD SCREEN WILL SHOW AVAILABLE PARKING SLOTS. 
 *      #IR SENSOR IS ATTACHED TO EACH PARKING SLOT.
 *      #WHEN ALL IR SENSORS ARE DETECTED THEN PARKING IS FULL AND LCD SCREEN WILL SHOW 'PARKING NOT AVAILABLE.' AND BARRIER WILL STAY DOWN.
 *         
 *         
 *   BY :VIPUL PARDESHI 
 *       SWAPNIL UMALKAR
 *       SAMYAK NAGRALE
 *       KUNAL SAIBOL
 *       
 *       SNEHAL SALAM
 *       
 *   COMPONENTS USED :
 *      RFID SENSOR RC522   X 1
 *      RFID TAGS           X 2
 *      IR SENSOR           X 2
 *      LCD SCREEN          X 1
 *      SERVO MOTOR         X 1
 *      ACTIVE BUZZER       X 1
 *      ARDUINO UNO         X 1
 *      ARDUINO USB CABLE   X 1
 *      JUMPER WIRES
 *      
 *      
 */
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

#define IR1 A0
#define IR2 A1
#define BUZZER A2
Servo myServo; //define servo name

//LCD
const int rs = 8, en = 7, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(6 , 7, 5, 4, 3, 2);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int slots = 2;
int pir1=0,pir2=0;
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  Serial.println("Put your card to the reader...");
  Serial.println();

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("WELCOME TO SMART");
  lcd.setCursor(1, 1);
  lcd.print("PARKING SYSTEM");
  delay(5000);
  lcd.clear();

  myServo.attach(6); //servo pin
  myServo.write(45); //servo start position

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
}

void loop() 
{  
//   Serial.println(analogRead(IR1));
//   Serial.println(analogRead(IR2));
   lcd.setCursor(0,0);
   lcd.print("Avail. slots = ");
   lcd.print(slots);
   lcd.setCursor(1,1);

 // IR Sensors
   if(analogRead(IR1)<=500 && analogRead(IR2)<=300){
    lcd.print("P1 P2 ");
    delay(500);
   }
   else if(analogRead(IR1)>=500 && analogRead(IR2)<=300){  //
    lcd.print("XX P2 ");
    delay(500);
   }
   else if(analogRead(IR1)<=500 && analogRead(IR2)>=300){
    lcd.print("P1 XX ");
    delay(500);
   }
   else if(analogRead(IR1)>=500 && analogRead(IR2)>=300){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PARKING FULL");
    delay(500);
    
    
   }
   
   //P1
   if(analogRead(IR1)>=500 && pir1==0){
     pir1=1;
     slots = slots - 1;
     }
   else if(analogRead(IR1)<=500 && pir1==1){
     pir1=0;
     slots = slots + 1;
     }

   //P2
   if(analogRead(IR2)>=300 && pir2==0){
     pir2=1;
     slots = slots - 1;
     }
   else if(analogRead(IR2)<=300 && pir2==1){
     pir2=0;
     slots = slots + 1;
     }
     
//----------------------------------------------------------------------------------------------------------------------------

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "FA EA A7 2D") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    myServo.write(135);
    delay(5000);
    myServo.write(45);
    

  }
 
 else   {
    Serial.println(" Access denied");
    myServo.write(45);
    tone(BUZZER, 1000);
    delay(500);
    noTone(BUZZER);
    delay(1);   
  }

} 

#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// -------------------- PINS --------------------
#define SS_PIN 10
#define RST_PIN 9
#define LED_PIN 6
#define BUZZER_PIN 7
#define BUTTON_PIN 2
#define RED_LED_PIN 5

MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27,16,2);

// -------------------- VARIABLES --------------------
bool registrationMode = true;  // start in registration mode
bool lastButtonState = LOW;

// Arrays for attendance (to be filled manually after registration)
       // Optional names
String studentUIDs[2] = {"739B7528" , "735F7213"};
String studentNames[2] = {"Student 1","Student 2"};
bool attendance[2] = {false,false};

// -------------------- SETUP --------------------
void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(5, OUTPUT);

  SPI.begin();
  mfrc522.PCD_Init();

  lcd.init();
  lcd.backlight();
  lcd.print("RFID Attendance");
  lcd.setCursor(0,1);
  lcd.print(registrationMode ? "REG MODE" : "ATT MODE");
  delay(2000);
  lcd.clear();
}

// -------------------- LOOP --------------------
void loop() {
  checkButton();  // Toggle between registration/attendance mode
  checkRFID();    // Scan card
}

// -------------------- BUTTON --------------------
void checkButton() {
  bool currentButton = digitalRead(BUTTON_PIN);
  if(currentButton == HIGH && lastButtonState == LOW){
    registrationMode = !registrationMode;
    lcd.clear();
    lcd.print(registrationMode ? "REG MODE" : "ATT MODE");
    beep(2);
  }
  lastButtonState = currentButton;
}
void errorAlert() {
  digitalWrite(LED_PIN, LOW);        // Green OFF
  digitalWrite(RED_LED_PIN, HIGH);   // Red ON

  digitalWrite(BUZZER_PIN, HIGH);    // Buzzer ON
  delay(1000);                       // LONG BEEP (1 second)
  digitalWrite(BUZZER_PIN, LOW);     // Buzzer OFF

  digitalWrite(RED_LED_PIN, LOW);    // Red OFF
}

// -------------------- RFID --------------------
void checkRFID() {
  if(!mfrc522.PICC_IsNewCardPresent()) return;
  if(!mfrc522.PICC_ReadCardSerial()) return;

  String uid = "";
  for(byte i=0; i<mfrc522.uid.size; i++){
    uid += String(mfrc522.uid.uidByte[i], HEX);
  }
  uid.toUpperCase();

  if(registrationMode){
    registerCard(uid);
  } else {
    markAttendance(uid);
  }

  mfrc522.PICC_HaltA();
}

// -------------------- REGISTER CARD --------------------
void registerCard(String uid){
  lcd.clear();
  lcd.print("Registered!");
  Serial.print("Registered UID: ");
  Serial.println(uid);   // Copy this to code manually
  beep(1);
  delay(500);
  lcd.clear();
}

// -------------------- MARK ATTENDANCE --------------------
void markAttendance(String uid){
  bool knownCard = false;

  for(int i=0;i<2;i++){
    if(studentUIDs[i] == uid){
      knownCard = true;
      attendance[i] = true;

      // Sequential PRESENT display
      lcd.clear();
      lcd.print(studentNames[i]);
      lcd.setCursor(0,1);
      lcd.print("PRESENT");

      digitalWrite(LED_PIN,HIGH);
      beep(1);
      delay(200);
      digitalWrite(LED_PIN,LOW);

      break;
    }
  }

  if(!knownCard){
    lcd.clear();
    lcd.print("Unknown Card");
    lcd.setCursor(0,1);
    lcd.print("Access Denied");
    errorAlert();

  }

  delay(1000);
  lcd.clear();
}

// -------------------- BEEP --------------------
void beep(int times){
  for(int i=0;i<times;i++){
    digitalWrite(BUZZER_PIN,HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN,LOW);
    delay(100);
  }
}

void longBeep(){
  digitalWrite(BUZZER_PIN,HIGH);
  delay(800);
  digitalWrite(BUZZER_PIN,LOW);
}
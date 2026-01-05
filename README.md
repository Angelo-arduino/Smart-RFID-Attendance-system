# Smart-RFID-Attendance-system
🔐 Smart RFID-based attendance system using Arduino, featuring registration and attendance modes with LCD, LEDs, and buzzer feedback.

## Project Overview
This project is a Smart RFID Attendance System designed to automatically register and record student attendance using RFID technology.
It reduces manual errors, prevents impersonation, and improves efficiency in classrooms, labs, and events.
The system works in two modes:
Registration Mode – registers new RFID cards
Attendance Mode – marks registered students as Present
This project demonstrates skills in embedded systems, hardware integration, and logical system design, making it suitable for scholarship and competition evaluation.
## Objectives
Automate attendance collection
Improve accuracy and security
Learn RFID communication and Arduino integration
Build a real-world, scalable system
## Components Used
Component
Quantity
Arduino Uno
1
MFRC522 RFID Reader
1
RFID Cards
2+
16×2 LCD (I2C or parallel)
1
Push Button
1
yellow LED (Access Granted)
1
Red LED (Access Denied)
1
Buzzer
1
Jumper Wires
Several
Breadboard
1
## code used:
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

 ## ⚙️ System Functionality
 
🔹 Registration Mode
User scans an RFID card
System displays “Registered”
UID is stored and later added to the code
 ### 🔹 Attendance Mode
Registered card → “Student Present”
Unknown card →
Red & Green LEDs blink together
Long buzzer sound
LCD shows “Unknown Card”
 ### 🔄 Project Workflow
Power on system
Select mode using push button
Scan RFID card
System checks UID
Displays result on LCD
Provides LED & buzzer feedback
#### watch the demo video on youtube : https://youtu.be/qHgr5DKHfdw?si=aA5lPTRoLuLduzeS

## 🛠️ Technical Challenges & Solutions
### 1️⃣ RFID Not Scanning
Problem: Reader powered but not detecting cards
Solution:
Checked SPI wiring
Confirmed MFRC522 library
Verified correct SS and RST pins
### 2️⃣ LCD Display Issues
Problem: LCD powered but no text
Solution:
Adjusted contrast
Verified I2C address
Tested with example code
### 3️⃣ Buzzer Not Working
Problem: No sound for unknown cards
Solution:
Discovered wrong buzzer pin assignment
Corrected pin in code
Tested with simple tone() function
### 4️⃣ Logic Errors (Wrong Attendance)
Problem: Cards not correctly identified
Solution:
Compared UID byte-by-byte
Separated registration and attendance logic
Used clear condition checks
### 🧪 Testing
Tested with multiple cards
Verified correct responses for:
Registered card
Unknown card
Mode switching
### 🚀 Future Improvements
Store attendance on SD card
Add RTC module for date & time
Connect to a web dashboard
Use EEPROM for dynamic UID storage
### 🏆 Applications
Schools & universities
Workshops & seminars
Office access control
Examination attendance
### 👤 Author
### Angelo
Arduino & Embedded Systems Enthusiast
Aspiring Engineer | Scholarship Candidate
📜 License
This project is open-source and available for learning and educational use.

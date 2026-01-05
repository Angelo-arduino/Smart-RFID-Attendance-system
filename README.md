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
## Circuit Diagram

https://github.com/Angelo-arduino/Smart-RFID-Attendance-system/blob/main/20260104_214639.jpg
## code used
https://github.com/Angelo-arduino/Smart-RFID-Attendance-system/blob/main/sketch_jan4a.ino
## Demo video
Here is a demo video showing how the RFID Attendance  system works:
[watch the demo on Youtube]( https://youtu.be/qHgr5DKHfdw?si=aA5lPTRoLuLduzeS)


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

# I2C-BitBanging
#### A software-implemented I2C master using GPIO on ESP8266 (bit-banging) with full protocol support and logic analyzer validation.
### 🧠 Software I2C (Bit-Banged) Implementation on ESP8266
This project implements an I2C master using bit-banging (software control) over GPIO pins of the ESP8266, written in the Arduino framework. It allows communication with I2C peripherals without using the hardware I2C peripheral, enabling full manual control and deep understanding of the protocol.
##
### 🔧 Features
- Software-based I2C Master Driver  
- Manual control of SDA and SCL lines (GPIO)  
- Support for:<br>
  Start/Stop conditions<br>
  Bit-wise data transfer (MSB first)<br>
  ACK/NACK detection<br>
  Read/write operations<br>
- Debug logging for every transaction  
- Tested and validated with a logic analyzer  
##
### 📦 Hardware Used
- ESP8266 (NodeMCU)  
- Logic Analyzer (for waveform verification)  
- Optional: EEPROM/Sensor with I2C interface  
##
### 🔌 Pin Configuration
#define SDA_PIN 4 // GPIO4 (D2)  
#define SCL_PIN 5 // GPIO5 (D1)
##
### 💡 Circuit Diagram
![image](https://github.com/user-attachments/assets/c76f2446-2784-4d2d-b883-7a13e4397347)
##
### 🔬 Logic Analyzer Output (Examples)
#### Write 111010101000000111011001111
![image](https://github.com/user-attachments/assets/9dd26e29-41f9-4247-a6b3-7029b9a8f845)
#### Read 101001111011100101111111111
![image](https://github.com/user-attachments/assets/3eb68780-0e7b-4b3f-9558-a663a98de7d6)
##
### 🏷️ Tags
• `#I2C` • `#BitBanging` • `#ESP8266` • `#Arduino`  • `#SoftwareI2C` • `#LowLevelI2C`  
• `#SoftwareI2C` • `#LogicAnalyzer` • `#Embedded` • `#Microcontroller` • `#GPIO`  
##
### 📢 Note
This software I2C driver has been tested and validated only on the ESP8266 platform.  
If you're using a different microcontroller (e.g. STM32, ATmega, RP2040), you will need to modify the code, including timing logic and pin control, to ensure compatibility with your board's architecture and behavior.  
The provided implementation may not work out of the box on other hardware.









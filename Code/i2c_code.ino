#include <Arduino.h>

// Define software I2C pins
#define SDA_PIN 4 //GPIO 4 data line
#define SCL_PIN 5 //GPIO 5 clock line

#define I2C_DELAYh 120  // Adjust timing as needed
#define I2C_DELAYl 120 // Adjust timing as needed


int I2C_DELAY_MODh = (I2C_DELAYh-2.333); //To counteract operational delay varies from board
int I2C_DELAY_MODl = (I2C_DELAYl-30); //To counteract operational delay varies from board

String debug_log = "";  // Buffer for debugging messages

void I2C_start() {
    pinMode(SDA_PIN, OUTPUT);
    pinMode(SCL_PIN, OUTPUT);

    digitalWrite(SDA_PIN, HIGH);
    digitalWrite(SCL_PIN, HIGH);
    delayMicroseconds(I2C_DELAY_MODh);
    // SDA goes LOW while SCL is HIGH -> START condition
    digitalWrite(SDA_PIN, LOW);
    delayMicroseconds(I2C_DELAY_MODh);
    // Then pull SCL LOW to start data transmission
    digitalWrite(SCL_PIN, LOW);

    debug_log += "I2C Start Condition\n";
}

void I2C_stop() {
    digitalWrite(SDA_PIN, LOW);
    delayMicroseconds(I2C_DELAY_MODh);
    digitalWrite(SCL_PIN, HIGH);
    delayMicroseconds(I2C_DELAY_MODh);
    // Then release SDA -> LOW to HIGH while SCL is HIGH = STOP condition
    digitalWrite(SDA_PIN, HIGH);

    debug_log += "I2C Stop Condition\n";
}

void I2C_write_bit(bool bit) {
    digitalWrite(SDA_PIN, bit); //Set data in SDA
    delayMicroseconds(I2C_DELAY_MODl);
    digitalWrite(SCL_PIN, HIGH); 
    delayMicroseconds(I2C_DELAY_MODh);
    digitalWrite(SCL_PIN, LOW);

    debug_log += "Writing bit: " + String(bit) + "\n";
}

bool I2C_read_bit() {
    pinMode(SDA_PIN, INPUT); // Set SDA as input to read acknowledgment
    delayMicroseconds(I2C_DELAY_MODl);
    digitalWrite(SCL_PIN, HIGH);
    delayMicroseconds(I2C_DELAY_MODh);
    bool bit = digitalRead(SDA_PIN); // Read the bit value(acknowledgement)
    digitalWrite(SCL_PIN, LOW);
    pinMode(SDA_PIN, OUTPUT); //Set SDA back to Output

    debug_log += "Read bit: " + String(bit) + "\n";
    return bit;
}

void I2C_write_byte(uint8_t data) {
    for (int i = 7; i >= 0; i--) {
         I2C_write_bit((data >> i) & 1); //Send bit by bit MSB first
    }

    bool ack = I2C_read_bit();
    debug_log += "ACK received: " + String(ack ? "NO" : "YES") + "\n"; // After byte is sent, read ACK/NACK bit from slave
}

uint8_t I2C_read_byte(bool ack) {
    uint8_t data = 0;
    for (int i = 7; i >= 0; i--) {
        data |= (I2C_read_bit() << i); //Receive MSB first
    }
    I2C_write_bit(!ack);  //Send ACK (0) or NACK (1) after reading
    return data;
}

// Function to print all debug messages after I2C communication
void print_line() {
    Serial.print(debug_log); // Output log to Serial Monitor
    debug_log = "";  // Clear the buffer after printing
}

void setup() {
    Serial.begin(115200); // Initialize serial communication
    pinMode(SDA_PIN, OUTPUT);
    pinMode(SCL_PIN, OUTPUT);
    digitalWrite(SDA_PIN, HIGH);
    digitalWrite(SCL_PIN, HIGH);
}

void loop() {
    debug_log = "";  // Reset debug buffer

    // WRITE sequence to I2C device
    debug_log += "Sending data over software I2C...\n";
    I2C_start();
    I2C_write_byte((0x75 << 1) | 0);  //Adress of slave 7 bit
    I2C_write_byte(0x03);  //Register address of slave 8 bit
    I2C_write_byte(0x67);  //Data to be written 8 bit
    I2C_stop();//(1110101)-Adress of slave 0-write 1-ack (00000011)-Register address of slave 1-ack (01100111)-Data to be written 1-ack

    print_line();  // Print debug output after I2C transaction
    delay(1000); //Delay between write and read

    debug_log += "Reading data over software I2C...\n";
    I2C_start();
    I2C_write_byte(0x53 << 1 | 1);  //Adress of slave 7 bit
    I2C_write_byte(0x72);  //Register address of slave 8 bit
    uint8_t data = I2C_read_byte(false);  
    I2C_stop(); //(1010011)-Adress of slave 1-read 1-ack (01110010)-Register address of slave 1-ack (11111111)-Dummy read 1-ack
    
    debug_log += "Final received data: 0x" + String(data, HEX) + " hex\n";

    print_line();  // Print debug output after I2C transaction
    delay(1000); //Delay between read and write
}
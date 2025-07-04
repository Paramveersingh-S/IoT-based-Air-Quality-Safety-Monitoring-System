#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>

// LCD display with I2C address 0x27, 16 columns and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin definitions
const int MQ2_PIN = A0;      // MQ2 gas sensor analog pin
const int BUZZER = 9;        // Buzzer pin
const int LED = 8;           // LED pin

File dataFile;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  // Configure I/O pins
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);

  // Initialize SD card
  if (!SD.begin(10)) {
    lcd.print("SD Card Error!");
    while (1); // Halt if SD card initialization fails
  }
}

void loop() {
  // Read gas level from MQ2 sensor
  int gasValue = analogRead(MQ2_PIN);

  // Display gas level on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gas Level: ");
  lcd.print(gasValue);

  // Log gas level to SD card
  dataFile = SD.open("log.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print(millis());     // Log timestamp
    dataFile.print(",");          
    dataFile.println(gasValue);   // Log gas value
    dataFile.close();
  }

  // Send gas value to Serial (for NodeMCU)
  Serial.println(gasValue);

  // Activate buzzer and LED if gas level is high
  if (gasValue > 1000) {
    digitalWrite(BUZZER, HIGH);
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(BUZZER, LOW);
    digitalWrite(LED, LOW);
  }

  // Wait for 2 seconds before next reading
  delay(2000);
}

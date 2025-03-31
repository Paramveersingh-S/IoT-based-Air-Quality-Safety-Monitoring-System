#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27
const int MQ2_PIN = A0;
const int BUZZER = 9;
const int LED = 8;
File dataFile;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);

  // Initialize SD card
  if (!SD.begin(10)) {
    lcd.print("SD Card Error!");
    while (1);
  }
}

void loop() {
  int gasValue = analogRead(MQ2_PIN);
  
  // Display on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gas Level: ");
  lcd.print(gasValue);
  
  // Log to SD card
  dataFile = SD.open("log.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print(millis());
    dataFile.print(",");
    dataFile.println(gasValue);
    dataFile.close();
  }

  // Send data to NodeMCU
  Serial.println(gasValue);

  // Trigger alerts
  if (gasValue > 1000) {
    digitalWrite(BUZZER, HIGH);
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(BUZZER, LOW);
    digitalWrite(LED, LOW);
  }
  
  delay(2000);
}

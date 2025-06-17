## IoT Air Quality & Safety Monitor 🌫️📡

A smart system that detects hazardous gases (LPG, CO, smoke) using an MQ-2 sensor, displays real-time data on an LCD, logs to an SD card, and sends alerts via Wi-Fi. Built with Arduino Uno, ESP8266 NodeMCU, and I2C LCD.

---

## 📌 Key Features
- **Real-Time Monitoring**: Gas levels shown on a 16x2 I2C LCD.
- **Cloud Alerts**: ESP8266 sends data to ThingSpeak/Blynk and triggers SMS/email alerts via IFTTT.
- **Data Logging**: Stores readings on a microSD card for analysis.
- **Safety Alarms**: Buzzer and LED activate when gas exceeds safe levels.
- **Automatic Ventilation**: *Optional* relay-controlled fan/exhaust system.

---

## 🛠️ Components
| Component               | Quantity |
|-------------------------|----------|
| Arduino Uno             | 1        |
| ESP8266 NodeMCU v3      | 1        |
| MQ-2 Gas Sensor         | 1        |
| 16x2 I2C LCD            | 1        |
| MicroSD Card Module     | 1        |
| Buzzer                  | 1        |
| LED & 220Ω Resistor     | 1 each   |
| Breadboard & Jumper Wires | As needed |
| *Optional* Relay Module | 1        |

---

### Key Connections:
#### **MQ-2 Sensor**
| MQ-2 Pin | Arduino Pin |
|----------|-------------|
| VCC      | 5V          |
| GND      | GND         |
| AO       | A0          |

#### **LCD I2C**
| LCD Pin | Arduino Pin |
|---------|-------------|
| SDA     | A4          |
| SCL     | A5          |

#### **Arduino ↔ NodeMCU**
| Arduino | NodeMCU     | Notes                     |
|---------|-------------|---------------------------|
| TX (D1) | RX (D3)     | Use voltage divider (5V→3.3V) |
| RX (D0) | TX (D1)     |                           |
| GND     | GND         | Common ground             |

---

## ⚙️ Installation
1. **Arduino IDE Setup**:
   - Install the `LiquidCrystal_I2C` and `SD` libraries via **Library Manager**.
   - Add ESP8266 board support:  
     `File → Preferences → Additional Boards Manager URL`:  
     `http://arduino.esp8266.com/stable/package_esp8266com_index.json`

2. **SD Card Prep**:
   - Format the SD card as FAT32.
   - Create a `log.txt` file for data storage.

3. **Upload Code**:
   - Upload the Arduino code to the Uno.
   - Upload the NodeMCU code to the ESP8266 (select "NodeMCU 1.0" board).

---

## 🚀 Usage
1. Power the Arduino and NodeMCU.
2. **Local Monitoring**:
   - Gas levels display on the LCD.
   - Buzzer/LED activate if gas > 1000ppm.
3. **Cloud Setup**:
   - Configure ThingSpeak/Blynk channels (update API keys in code).
   - Set up IFTTT applets for SMS/email alerts.
4. **Data Access**:
   - View real-time graphs on ThingSpeak.
   - Check `log.txt` on the SD card for historical data.

---

## 📉 Calibration
- Use the MQ-2 datasheet to convert analog values to ppm.  
  *Example formula*:  
  `ppm = (analogRead(A0) * 3.3 / 1024) * 1000`  
  Adjust based on sensor calibration.

---

## 🔧 Troubleshooting
| Issue                  | Solution                          |
|------------------------|-----------------------------------|
| LCD not displaying     | Check I2C address with scanner code |
| SD card errors         | Reformat card (FAT32)             |
| Wi-Fi fails to connect | Verify SSID/password in code      |
| Serial comms failure   | Check voltage divider on TX line  |

---

## 🌟 Future Enhancements
- Add temperature/humidity sensor (DHT11).
- Design a 3D-printed enclosure.
- Integrate a mobile app (Blynk/ThingSpeak).
- Implement low-power mode for battery use.

---

## 📜 License
MIT License. See [LICENSE](LICENSE) for details.

---

**Let’s breathe safer air!** 🍃  
*Feel free to contribute or adapt this project!*

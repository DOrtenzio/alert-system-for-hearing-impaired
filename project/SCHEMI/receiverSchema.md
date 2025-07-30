# 📡 RECEIVER Connection Diagram - ENG

## 🔌 Power Supply

- MB102 module powered by 9V DC (jack 2.1x5.5 mm)  
- MB102 lines:
  - +5V (positive breadboard line)
  - GND (negative breadboard line)
- ESP32 VIN (or 5V) → connect to +5V breadboard line (MB102)
- ESP32 GND → connect to GND line of the breadboard

## 🔧 Components

### 1) LED (with 220Ω resistor)
- LED Anode (+) → 220Ω resistor → GPIO 2 (`LED_PIN`) ESP32  
- LED Cathode (-) → GND breadboard

### 2) DC 3V Vibration Motor
- Motor VCC (+) → +5V or +3.3V (depending on motor, better use 3.3V or separate power via MB102)  
- Motor GND (-) → MOSFET drain (power channel)  
- Gate MOSFET → GPIO 4 (`VIBRATOR_PIN`) ESP32 via 100Ω resistor (optional but recommended)  
- Source MOSFET → GND breadboard  
- Protection diode (1N4007 or similar) in parallel with motor (anode to GND, cathode to VCC)

### 3) Reset Button
- One button terminal → GPIO 5 (`RESET_BUTTON_PIN`) ESP32  
- Other terminal → GND breadboard  
- Use `INPUT_PULLUP` in code — no external resistor needed

### 4) Ultrasonic Sensor HY-SRF05 (5 pin)
- VCC → +5V breadboard (MB102)  
- GND → GND breadboard  
- TRIG → GPIO 12 (`SRF05_TRIG_PIN`) ESP32  
- ECHO → 5V side of TXS0108E level converter  
- 3.3V side of converter → GPIO 13 (`SRF05_ECHO_PIN`) ESP32  
- RST (if present) → GND or leave unconnected

### 5) TXS0108E Logic Level Converter (8 channels)
- VCCA (low voltage) → +3.3V (ESP32 side)  
- VCCB (high voltage) → +5V (MB102 side)  
- GND → common GND  
- OE (output enable) → GND (to enable converter)  
- Channel 1:  
  - B1 (5V side) → ECHO pin from HY-SRF05  
  - A1 (3.3V side) → GPIO 13 ESP32

### 6) LCD 16x2 I2C (PCF8574)
- VCC → +5V breadboard (MB102)  
- GND → GND breadboard  
- SDA → GPIO 21 ESP32  
- SCL → GPIO 22 ESP32

---

# 📡 Schema di Collegamento RECEIVER - ITA

## 🔌 Alimentazione

- Modulo MB102 alimentato da 9V DC (jack 2.1x5.5 mm)  
- Linee MB102:
  - +5V (linea positiva breadboard)
  - GND (linea negativa breadboard)
- ESP32 VIN (o 5V) → collegare alla linea +5V della breadboard (MB102)  
- ESP32 GND → collegare alla linea GND della breadboard

## 🔧 Componenti

### 1) LED (con resistenza 220Ω)
- Anodo LED (+) → Resistenza 220Ω → GPIO 2 (`LED_PIN`) ESP32  
- Catodo LED (-) → GND breadboard

### 2) Motore Vibrazione DC 3V
- VCC motore (+) → +5V o +3.3V (meglio 3.3V o alimentazione separata MB102)  
- GND motore (-) → Drenatore MOSFET  
- Gate MOSFET → GPIO 4 (`VIBRATOR_PIN`) ESP32 tramite resistenza 100Ω (opzionale ma consigliata)  
- Source MOSFET → GND breadboard  
- Diodo di protezione (1N4007 o simile) in parallelo al motore (anodo su GND, catodo su VCC)

### 3) Pulsante Reset
- Un terminale → GPIO 5 (`RESET_BUTTON_PIN`) ESP32  
- Altro terminale → GND breadboard  
- Impostare GPIO 5 come `INPUT_PULLUP` nel codice (non serve resistenza esterna)

### 4) Sensore Ultrasuoni HY-SRF05 (5 pin)
- VCC → +5V breadboard (MB102)  
- GND → GND breadboard  
- TRIG → GPIO 12 (`SRF05_TRIG_PIN`) ESP32  
- ECHO → lato 5V del convertitore TXS0108E  
- Lato 3.3V del convertitore → GPIO 13 (`SRF05_ECHO_PIN`) ESP32  
- RST (se presente) → GND o non collegato

### 5) Convertitore Livello Logico TXS0108E (8 canali)
- VCCA (bassa tensione) → +3.3V breadboard (ESP32)  
- VCCB (alta tensione) → +5V breadboard (MB102)  
- GND → GND comune  
- OE (abilitazione) → GND (attiva il convertitore)  
- Canale 1:  
  - B1 (lato 5V) → pin ECHO HY-SRF05  
  - A1 (lato 3.3V) → GPIO 13 ESP32

### 6) LCD 16x2 I2C (PCF8574)
- VCC → +5V breadboard (MB102)  
- GND → GND breadboard  
- SDA → GPIO 21 ESP32  
- SCL → GPIO 22 ESP32

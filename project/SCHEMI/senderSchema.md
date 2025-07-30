# 📤 SENDER Diagram - ENG

## 🔌 Power Supply

| MB102 powered by 9V |
|---------------------|
| - Line + : 5V (for ESP32, microphone)  |
| - Line - : GND                         |

## 🔧 Connections

### **ESP32**
- `Vin` → 5V line from MB102  
- `GND` → GND line from MB102  
- `GPIO 34` → Microphone OUT  
- `GPIO 0` → REC Button → GND  
- `GPIO 1` → TEL Button → GND

### **GY-MAX4466 Microphone**
- `VCC` → 5V  
- `GND` → GND  
- `OUT` → GPIO 34 (ESP32)

---

# 📤 Schema SENDER - ITA

## 🔌 Alimentazione

| MB102 alimentato da 9V |
|------------------------|
| - Linea + : 5V (per ESP32, microfono) |
| - Linea - : GND                      |

## 🔧 Collegamenti

### **ESP32**
- `Vin` → linea 5V da MB102  
- `GND` → linea GND da MB102  
- `GPIO 34` → OUT microfono  
- `GPIO 0` → Pulsante REC → GND  
- `GPIO 1` → Pulsante TEL → GND

### **Microfono GY-MAX4466**
- `VCC` → 5V  
- `GND` → GND  
- `OUT` → GPIO 34 (ESP32)

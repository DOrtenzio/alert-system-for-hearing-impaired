#include <WiFi.h>
#include <esp_now.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LED_PIN 2
#define VIBRATOR_PIN 4
#define RESET_BUTTON_PIN 5

// HY-SRF05 Ultrasuoni
#define SRF05_TRIG_PIN 12
#define SRF05_ECHO_PIN 13
#define SRF05_HAND_DISTANCE_CM 10 // distanza massima per rilevare la mano

LiquidCrystal_I2C lcd(0x27, 16, 2); // indirizzo I2C e dimensioni display

typedef struct {
  bool dingDong;
  bool telephoneCall;
} Message;

Message incomingData;
bool notified = false;
unsigned long notifyMillis = 0;
String notifyType = "";

// Funzione lettura distanza HY-SRF05
long readDistanceCM() {
  digitalWrite(SRF05_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(SRF05_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SRF05_TRIG_PIN, LOW);
  long duration = pulseIn(SRF05_ECHO_PIN, HIGH, 30000); // timeout 30ms
  long distance = duration * 0.034 / 2;
  return distance;
}

void OnDataRecv(const uint8_t * mac, const uint8_t *data, int len) {
  memcpy(&incomingData, data, sizeof(incomingData));
  
  if (incomingData.dingDong) {
    notified = true;
    notifyMillis = millis();
    notifyType = "Campanello";
    Serial.println("🔔 Campanello rilevato!");
  } else if (incomingData.telephoneCall) {
    notified = true;
    notifyMillis = millis();
    notifyType = "Telefono";
    Serial.println("📞 Telefono rilevato!");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  pinMode(LED_PIN, OUTPUT);
  pinMode(VIBRATOR_PIN, OUTPUT);
  pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);

  pinMode(SRF05_TRIG_PIN, OUTPUT);
  pinMode(SRF05_ECHO_PIN, INPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(VIBRATOR_PIN, LOW);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Receiver pronto");

  if (esp_now_init() != ESP_OK) {
    Serial.println("Errore inizializzazione ESP-NOW");
    lcd.setCursor(0,1);
    lcd.print("Errore ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
  Serial.println("Receiver pronto");
}

void loop() {
  if (notified) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(VIBRATOR_PIN, HIGH);

    unsigned long elapsed = (millis() - notifyMillis) / 1000;
    lcd.setCursor(0,0);
    lcd.print("Arrivato:      ");
    lcd.setCursor(10,0);
    lcd.print(elapsed);
    lcd.print("s");
    lcd.setCursor(0,1);
    lcd.print("Tipo: ");
    lcd.print(notifyType);
    lcd.print("      ");
  } else {
    lcd.setCursor(0,0);
    lcd.print("Nessuna notif. ");
    lcd.setCursor(0,1);
    lcd.print("                ");
  }

  // Reset manuale con bottone o con mano davanti al sensore
  if ((digitalRead(RESET_BUTTON_PIN) == LOW || readDistanceCM() < SRF05_HAND_DISTANCE_CM) && notified) {
    Serial.println("🔕 Notifica resettata");
    notified = false;
    digitalWrite(LED_PIN, LOW);
    digitalWrite(VIBRATOR_PIN, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Nessun evento");
    delay(300); 
  }
  delay(100);
}
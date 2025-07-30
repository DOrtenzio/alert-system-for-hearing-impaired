#include <esp_now.h>
#include <arduinoFFT.h>
#include <SPIFFS.h>

// === CONFIGURAZIONE ===
#define MIC_PIN 34
#define SAMPLES 128
#define SAMPLING_FREQ 4000
#define SLEEP_TIME_SECONDS 2
#define BUTTON_PIN 0 // GPIO pulsante registrazione
#define BUTTON_TELEPHONE 1 // GPIO pulsante telefono

// === VARIABILI GLOBALI ===
double bellSignature[SAMPLES / 2]; // Firma spettrale campanello
double telephoneSignature[SAMPLES / 2]; // Firma spettrale campanello
uint8_t receiverAddress[] = {0x24, 0x6F, 0x28, 0xAB, 0xCD, 0xEF}; // Indirizzo MAC del ricevitore DA MODIFICARE
double vReal[SAMPLES];
double vImag[SAMPLES];
arduinoFFT FFT = arduinoFFT(vReal, vImag, SAMPLES, SAMPLING_FREQ);

typedef struct {
  bool dingDong;
  bool telephoneCall;
} Message;

Message dataToSend;

// Salva la firma su SPIFFS o meglio dire il suono del campanello
void saveSignature(double *signature,bool isRing) { //La firma è un array di double che rappresenta lo spettro del suono
  File file;
  if (isRing){
    file = SPIFFS.open("/bell.sig", FILE_WRITE);
  } else {
    file = SPIFFS.open("/phone.sig", FILE_WRITE);
  }
  if (!file) return;
  for (int i = 0; i < SAMPLES / 2; i++)
    file.write((uint8_t*)&signature[i], sizeof(double));
  file.close();
}

// Carica la firma da SPIFFS
bool loadSignature(double *signature, bool isRing) {
  File file;
  if (isRing){
    file = SPIFFS.open("/bell.sig", FILE_READ);
  } else {
    file = SPIFFS.open("/phone.sig", FILE_READ);
  }
  if (!file) return false;
  for (int i = 0; i < SAMPLES / 2; i++)
    file.read((uint8_t*)&signature[i], sizeof(double));
  file.close();
  return true;
}

// Confronta lo spettro acquisito con la firma
bool matchSignature(double *current, double *signature, double threshold) {
  double diff = 0;
  for (int i = 0; i < SAMPLES / 2; i++)
    diff += abs(current[i] - signature[i]);
  return diff < threshold;
}

// Invia segnale al ricevitore
void sendSignal(bool isDingDong, bool isTelephoneCall) {
  if(isDingDong) {
    dataToSend.dingDong = true;
    dataToSend.telephoneCall = false;
  } else if(isTelephoneCall) {
    dataToSend.dingDong = false;
    dataToSend.telephoneCall = true;
  }
  esp_now_send(receiverAddress, (uint8_t *)&dataToSend, sizeof(dataToSend));
  Serial.println("🔔 Segnale inviato!");
}

// Inizializza ESP-NOW
void initEspNow() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  if (esp_now_init() != ESP_OK) {
    Serial.println("Errore ESP-NOW");
    return;
  }
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (!esp_now_add_peer(&peerInfo)) {
    Serial.println("Peer aggiunto");
  }
}

void setup() {
  Serial.begin(115200); //seriale per debug
  delay(1000);

  pinMode(BUTTON_PIN, INPUT_PULLUP); // Pulsante per registrare la firma
  pinMode(BUTTON_TELEPHONE, INPUT_PULLUP); // Pulsante per registrare il telefono
  SPIFFS.begin(true); // Inizializza SPIFFS per memoria dati in ESP32
  initEspNow(); // Inizializza ESP-NOW per comunicazione

  // === CONFIGURAZIONE LETTURA MICROFONO ===
  pinMode(MIC_PIN, INPUT); // Pin del microfono
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);

  // === ACQUISIZIONE AUDIO ===
  for (int i = 0; i < SAMPLES; i++) {
    vReal[i] = analogRead(MIC_PIN);
    vImag[i] = 0;
    delayMicroseconds(1000000 / SAMPLING_FREQ);
  }

  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();

  // Se premi il pulsante, registra la firma o suono come vogliamo chiamarlo
  if (digitalRead(BUTTON_PIN) == LOW) {
    for (int i = 0; i < SAMPLES / 2; i++)
      bellSignature[i] = vReal[i];
    saveSignature(bellSignature,true);
    Serial.println("✅ Firma campanello registrata!");
  } else if (loadSignature(bellSignature,true)) {
    if (matchSignature(vReal, bellSignature, 5000)) {
      sendSignal(true, false);
    }
  } else {
    Serial.println("⚠️ Firma non trovata, registra prima!");
  }

  // Se premi il pulsante del telefono, registra la firma del telefono
  if (digitalRead(BUTTON_TELEPHONE) == LOW) {
    for (int i = 0; i < SAMPLES / 2; i++)
      telephoneSignature[i] = vReal[i];
    saveSignature(telephoneSignature,false);
    Serial.println("✅ Firma Telefono registrata!");
  } else if (loadSignature(telephoneSignature,false)) {
    if (matchSignature(vReal, telephoneSignature, 5000)) {
      sendSignal(false,true);
    }
  } else {
    Serial.println("⚠️ Firma non trovata, registra prima!");
  }

  // Metti il dispositivo in deep sleep per risparmiare energia
  esp_sleep_enable_timer_wakeup(SLEEP_TIME_SECONDS * 1000000ULL);
  esp_deep_sleep_start();
}

void loop() {
}
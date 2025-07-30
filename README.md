# Visual and Vibration Alert System for Hearing Impaired and Elderly

---

## Project Overview

This project is a **visual and vibration alert system** designed to assist hearing-impaired and elderly people by notifying them of prerecorded sounds from common household devices such as telephones and doorbells. The system detects these sounds and triggers a vibration motor along with visual feedback (LED and LCD display), ensuring important alerts are never missed.

### Key Features
- **Visual Alert:** LED and LCD display provide clear visual notification.
- **Vibration Alert:** Small vibration motor gives tactile feedback for alerts.
- **Gesture-based Reset:** Ultrasonic sensor detects hand gestures to reset notifications without physical contact.
- **Customizable Sound Recognition:** Use two buttons to record the clean ringing sound of your specific devices.
- **Plug and Play:** Easy to assemble and configure without complex setup.
- **Wireless Communication:** Based on ESP32 and ESP-NOW protocol for reliable message exchange.
- **Adaptable:** Compatible with various sound sources and environments.

---

## Hardware Components 
If you want there is a list in the section project.
- ESP32 Development Board  
- GY-MAX4466 Electret Microphone Amplifier Module  
- MB102 Power Supply Module (3.3V/5V)  
- Mini 3V Vibration Motor (coin type)  
- LCD 16x2 with I2C interface (PCF8574)  
- HY-SRF05 Ultrasonic Distance Sensor  
- TXS0108E Bidirectional Logic Level Converter (3.3V <-> 5V)  
- Push Buttons (at least 2)  
- LEDs and Resistors (e.g., 10kΩ for buttons, 220Ω for LEDs)  
- Breadboard and jumper wires  
- 9V Battery or DC Power Adapter

---

## Software Overview

- Written in Arduino C++ targeting the ESP32 platform.  
- Uses ESP-NOW protocol for wireless data transmission.  
- Manages vibration motor and LED notifications.  
- Reads ultrasonic sensor for non-contact reset functionality.  
- Controls LCD screen to display notification status and timer.  
- Handles button inputs for recording and resetting alerts.  

---

## How to Use

1. **Assemble Hardware:** Follow wiring diagram to connect all components properly.  
2. **Power Up:** Use MB102 module powered by a 9V battery or DC adapter.  
3. **Register Sounds:** Use the two push buttons to record clean sounds of your telephone and doorbell.  
4. **Receive Alerts:** When the system detects these sounds, it will vibrate and light the LED, displaying info on the LCD.  
5. **Reset Notifications:** Either press the reset button or wave your hand in front of the ultrasonic sensor to clear alerts.

---

## Contributions and Help Wanted

Contributions are welcome! Whether you want to improve the code, add new features, optimize hardware design, or help with documentation, your support is appreciated.  
Feel free to:  
- Submit pull requests  
- Open issues for bugs or feature requests  
- Suggest improvements  
- Share your use cases and feedback  

Let’s make this project accessible and useful for everyone!

---

## License

This project is open source and licensed under the **MIT License**.

---

## Contact

For questions, suggestions, or help, please open an issue on GitHub or contact me directly.

---

# Sistema di Avviso Visivo e Vibrazione per Meno Udenti e Anziani

---

## Descrizione del Progetto

Questo progetto è un **sistema di avviso visivo e con vibrazione** progettato per aiutare meno udenti e anziani notificando loro suoni preregistrati provenienti da apparecchi comuni come telefoni e campanelli. Il sistema rileva questi suoni e attiva un motore vibrante insieme a un feedback visivo (LED e display LCD), garantendo che le notifiche importanti non vengano mai perse.

### Caratteristiche principali
- **Avviso Visivo:** LED e display LCD per notifiche chiare e immediate.  
- **Avviso con Vibrazione:** Motore vibrante per avvisi tattili.  
- **Reset tramite Gesto:** Sensore a ultrasuoni per resettare le notifiche con un semplice gesto della mano.  
- **Riconoscimento Sonoro Personalizzabile:** Registra i suoni puliti con due pulsanti dedicati.  
- **Plug and Play:** Facile da assemblare e configurare senza settaggi complessi.  
- **Comunicazione Wireless:** Basato su ESP32 e protocollo ESP-NOW per scambio dati affidabile.  
- **Adattabile:** Compatibile con vari dispositivi sonori e ambienti diversi.

---

## Componenti Hardware
Se vuoi ci sono liste già preparate nella sezione progetto.
- Scheda di sviluppo ESP32  
- Modulo amplificatore microfonico GY-MAX4466  
- Modulo alimentazione MB102 (3.3V/5V)  
- Mini motore vibrante 3V (tipo moneta)  
- Display LCD 16x2 con interfaccia I2C (PCF8574)  
- Sensore a ultrasuoni HY-SRF05  
- Convertitore di livello logico bidirezionale TXS0108E (3.3V <-> 5V)  
- Pulsanti (almeno 2)  
- LED e resistenze (es. 10kΩ per pulsanti, 220Ω per LED)  
- Breadboard e cavetti jumper  
- Batteria 9V o alimentatore DC

---

## Software

- Scritto in C++ per Arduino su piattaforma ESP32.  
- Utilizza protocollo ESP-NOW per trasmissione dati wireless.  
- Gestisce motore vibrante e LED per notifiche.  
- Legge sensore ad ultrasuoni per funzionalità reset senza contatto.  
- Controlla il display LCD per mostrare stato e timer notifiche.  
- Gestisce pulsanti per registrazione e reset.

---

## Come Usare

1. **Assemblare Hardware:** Seguire lo schema di collegamento per connettere i componenti.  
2. **Alimentare:** Usare il modulo MB102 con batteria 9V o alimentatore DC.  
3. **Registrare Suoni:** Usare i due pulsanti per registrare i suoni puliti di telefono e campanello.  
4. **Ricevere Notifiche:** Quando il sistema rileva questi suoni, attiva vibrazione e LED e mostra info sul display LCD.  
5. **Resettare Notifiche:** Premere il pulsante reset oppure passare la mano davanti al sensore ad ultrasuoni.

---

## Contributi e Aiuti Richiesti

I contributi sono benvenuti! Se vuoi migliorare il codice, aggiungere funzionalità, ottimizzare il design hardware o aiutare con la documentazione, il tuo supporto è prezioso.  
Sentiti libero di:  
- Inviare pull request  
- Segnalare bug o richieste di funzionalità  
- Suggerire miglioramenti  
- Condividere esperienze e feedback  

Insieme possiamo rendere questo progetto accessibile e utile a tutti!

---

## Licenza

Questo progetto è open source e rilasciato sotto licenza **MIT**.

---

## Contatti

Per domande, suggerimenti o aiuto, apri una issue su GitHub o contattami direttamente.


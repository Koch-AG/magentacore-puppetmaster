#include <Magenta_lib.h>
#include <esp_now.h>
#include <WiFi.h>

// ======================
// Datenstruktur muss identisch zum Sender sein!
// ======================
typedef struct data_struct {
  int r, g, b;
  int BGC_r, BGC_g, BGC_b;
  int grad1, grad2;
  int button1, button2, button3, buttonC, buttonU, buttonR, buttonD, buttonL;
  char sa1, sa2, sa3, sa4;
  int sam;
} data_struct;

data_struct incomingData;

// ======================
// Callback für Empfang
// ======================
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingDataBytes, int len) {
  memcpy(&incomingData, incomingDataBytes, sizeof(incomingData));

  // printf("=== Neue Daten empfangen ===\n");
  // printf("Farbe: R=%d G=%d B=%d\n", incomingData.r, incomingData.g, incomingData.b);
  // printf("BG:    R=%d G=%d B=%d\n", incomingData.BGC_r, incomingData.BGC_g, incomingData.BGC_b);
  // printf("Servo: grad1=%d grad2=%d\n", incomingData.grad1, incomingData.grad2);
  // printf("Buttons: B1=%d B2=%d B3=%d\n", incomingData.button1, incomingData.button2, incomingData.button3);
  // printf("Joystick: U=%d R=%d D=%d L=%d C=%d\n", incomingData.buttonU, incomingData.buttonR, incomingData.buttonD, incomingData.buttonL, incomingData.buttonC);
  // printf("Sample: %d\n",incomingData.sam);
  // printf("============================\n");

  // === Werte auf die Magenta-Hardware anwenden ===
  magentaobj.setColor(incomingData.r,incomingData.g, incomingData.b, incomingData.BGC_r, incomingData.BGC_g, incomingData.BGC_b);

  magentaobj.sample(incomingData.sam);

  magentaobj.setServo1(incomingData.grad1);
  magentaobj.setServo2(incomingData.grad2);

  magentaobj.setSegmentAnzeige(incomingData.sa1, incomingData.sa2, incomingData.sa3, incomingData.sa4);
}

// ======================
// Setup
// ======================
void setup() {
  Serial.begin(115200);

  // Magenta-Hardware starten
  magentaobj.init();
  magentaobj.setSegmentAnzeige('R','E','C','V');

  // WiFi in STA-Modus
  WiFi.mode(WIFI_STA);

  // ESP-NOW initialisieren
  if (esp_now_init() != ESP_OK) {
    printf("Fehler bei ESP-NOW Init\n");
    return;
  }

  // Callback registrieren
  esp_now_register_recv_cb(OnDataRecv);

  printf("Empfänger bereit – wartet auf Daten...\n");
}

// ======================
// Loop
// ======================
void loop() {
  // Hier nichts nötig – alles passiert im Callback
}

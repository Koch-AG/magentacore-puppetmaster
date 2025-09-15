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
  int button1, button2, button3;
} data_struct;

data_struct incomingData;

// ======================
// Callback für Empfang
// ======================
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingDataBytes, int len) {
  memcpy(&incomingData, incomingDataBytes, sizeof(incomingData));

  printf("=== Neue Daten empfangen ===\n");
  printf("Farbe: R=%d G=%d B=%d\n", incomingData.r, incomingData.g, incomingData.b);
  printf("BG:    R=%d G=%d B=%d\n", incomingData.BGC_r, incomingData.BGC_g, incomingData.BGC_b);
  printf("Servo: grad1=%d grad2=%d\n", incomingData.grad1, incomingData.grad2);
  printf("Buttons: B1=%d B2=%d B3=%d\n", incomingData.button1, incomingData.button2, incomingData.button3);
  printf("============================\n");

  // === Werte auf die Magenta-Hardware anwenden ===
  magentaobj.setColor(
    incomingData.r,
    incomingData.g,
    incomingData.b,
    incomingData.BGC_r,
    incomingData.BGC_g,
    incomingData.BGC_b
  );

  magentaobj.setServo1(incomingData.grad1);
  magentaobj.setServo2(incomingData.grad2);

  // Beispiel: Button-Werte für Aktionen nutzen
  if (incomingData.button1 == 1) {
    magentaobj.setSegmentAnzeige('B','1','O','N'); // Anzeige "B1ON"
    magentaobj.Buzzer(0); // kurzer Pieper
  }
  if (incomingData.button2 == 1) {
    magentaobj.setSegmentAnzeige('B','2','O','N');
  }
  if (incomingData.button3 == 1) {
    magentaobj.setSegmentAnzeige('B','3','O','N');
  }
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

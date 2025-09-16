# Puppet Master  

## Timetable  
[Bild]  
Ich konnte mich nicht an den Zeitplan halten da ich Donnerstag bis Montag krank und Freitags den halben Tag Geschäftlich Abwesend war.  

## Eingesetzte Technologie  
### ESP-NOW  
**Wie ich zu ESP-NOW gekommen bin** 
Während meiner Recherche nach einer geeigneten Funktechnologie für mein Projekt bin ich auf *ESP-NOW* gestoßen. Es wurde mir im Internet 
als mögliche Lösung vorgeschlagen. Nach einer genaueren Auseinandersetzung mit den Eigenschaften stellte sich heraus, dass ESP-NOW sehr 
gut zu meinen Anforderungen passt: eine einfache, direkte und zuverlässige Datenübertragung zwischen zwei ESP32-Boards ohne zusätzliche Infrastruktur.  

**Funktionsweise**
ESP-NOW ist ein proprietäres Funkprotokoll von *Espressif*, das die WLAN-Hardware der ESP32- und ESP8266-Mikrocontroller nutzt. Anders als bei 
einer klassischen WLAN-Verbindung wird kein Router benötigt. Stattdessen tauschen die Geräte ihre *MAC-Adressen* aus und können anschließend direkt 
miteinander kommunizieren (Peer-to-Peer).
* Ein Gerät wird als *Peer* registriert.
* Datenpakete (maximal ~250 Bytes) werden direkt von einem ESP zum anderen gesendet.
* Die Übertragung erfolgt sehr schnell (Latenz im Millisekundenbereich).
* Der Empfänger ruft die Daten über ein Callback ab und kann sie sofort verarbeiten.
Damit eignet sich ESP-NOW vor allem für Anwendungen, bei denen kleine Datenmengen schnell und zuverlässig zwischen mehreren Geräten ausgetauscht werden müssen.

**Vorteile von ESP-NOW**
* *Direkte Kommunikation* ohne Router oder Internet
* *Sehr geringe Latenz* – Daten sind in Millisekunden beim Empfänger
* *Stromsparend* – gut geeignet für batteriebetriebene Systeme
* *Einfache Einrichtung* – nur einmalige Peer-Registrierung nötig
* *Mehrere Empfänger möglich* – ein Sender kann Daten an mehrere Geräte gleichzeitig schicken
* *Keine Zusatzhardware notwendig* – läuft direkt auf dem ESP32

**Nachteile von ESP-NOW**
* *Reichweite begrenzt* (ca. 30–60 m in Gebäuden, bis zu 200 m im Freien)
* *Maximal 250 Bytes pro Nachricht* – nur für kleine Datenpakete geeignet
* *Auf ESP-Geräte beschränkt* – keine direkte Kommunikation mit PCs oder Smartphones
* *Verschlüsselung vorhanden, aber eingeschränkt* im Vergleich zu normalem WLAN

**Vorteile im Vergleich zu anderen Systemen**
Im Vergleich zu anderen Funktechnologien bietet ESP-NOW einige entscheidende Vorteile:
* *Gegenüber WLAN*: deutlich geringere Latenz und kein Router erforderlich. WLAN ist besser für große Datenmengen, aber überdimensioniert für kleine Steuerdaten.
* *Gegenüber Bluetooth*: größere Reichweite und stabilere Übertragung, dafür benötigt Bluetooth meist eine aufwendigere Kopplung.
* *Gegenüber klassischen Funkmodulen (z. B. 433 MHz oder nRF24L01)*: keine zusätzliche Hardware erforderlich, da die ESPs ihre eingebaute WLAN-Antenne nutzen.

## Technische Hürden und Lösungsansätze  

## Format der Übertragbaren Daten  

## Resultat  
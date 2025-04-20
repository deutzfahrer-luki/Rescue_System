# RescuePackageHandler

## Methoden (Kurzbeschreibung)
- **begin()**  
  Initialisiert den Servo und setzt den Anfangszustand.

- **update()**  
  Führt die non‑blocking Logik (basierend auf `millis()`) zur Bewegung des Servos aus.

- **trigger(uint8_t len = 1)**  
  Plant das Auswerfen von `len` Paketen. Falls weniger Pakete vorhanden sind, wird die Anzahl entsprechend begrenzt.

- **clearAll()**  
  Aktiviert den Clear-All-Modus, sodass alle Pakete ausgegeben werden, bis keine mehr übrig sind.

- **resetPackages(uint8_t amount = 6)**  
  Setzt die Anzahl der RescuePackages (Standard: 6) zurück.

- **getPackageCount()**  
  Liefert die noch verfügbaren Pakete.

- **isBusy()**  
  Prüft, ob der Handler gerade aktiv ist (nicht im IDLE-Zustand oder mit ausstehenden Triggern).

- **stop()**  
  Stoppt den Servo sofort, setzt alle ausstehenden Vorgänge zurück und bringt ihn in die Standby-Position.

- **getStateName()**  
  Gibt den Namen des aktuellen Zustands als `const char*` zurück.

## Zustände (enum State)
- **IDLE**  
  Servo befindet sich in der Standby-Position.

- **MOVING_TO_WORKING**  
  Servo bewegt sich in die Arbeitsposition (Auswurf).

- **AT_WORKING**  
  Servo ist an der Arbeitsposition, um ein Paket auszuwerfen.

- **RETURNING**  
  Servo bewegt sich zurück in die Standby-Position.

---

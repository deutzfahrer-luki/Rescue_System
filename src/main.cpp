#include <Arduino.h>

// Pin für analoge Messung
const int analogPin = A7;

// Referenzspannung des Arduino (Standard: 5V bei Uno/Nano)
const float vRef = 5.0;

// Spannungsteiler-Verhältnis: 9V wird auf 4.5V geteilt
// Teilerfaktor: Vout = Vin * (R2 / (R1 + R2)) → hier: 0.5
const float voltageDividerFactor = 2.0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int adcValue = analogRead(analogPin); // 0 bis 1023
  float voltageAtPin = (adcValue / 1023.0) * vRef;  // Spannung nach dem Teiler (max. 4.5V)
  float originalVoltage = voltageAtPin * voltageDividerFactor; // Rückrechnung zur Originalspannung

  Serial.print("ADC-Wert: ");
  Serial.print(adcValue);
  Serial.print("  |  Gemessene Spannung: ");
  Serial.print(originalVoltage, 2); // Zwei Nachkommastellen
  Serial.println(" V");
  Serial.print("Batterie  ");
  Serial.println((originalVoltage>6)?"JA":"NEIN");
  Serial.println();

  delay(1000); // 1 Sekunde Pause
}
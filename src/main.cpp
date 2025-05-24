#include <Wire.h>
#include <Arduino.h>


int list[] = {37,39,41,32,34,36,30};
// 37 = 0 = HL
// 39 = 1 = Hinten
// 41 = 2 = HR
// 32 = 3 = VR
// 34 = 4 = Vorne Oben
// 36 = 5 = VL
// 30 = 6 = Vorne Unten

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial); // Warte auf serielle Verbindung
  int h = 6;
 for  (int i = 0; i<sizeof(list)/sizeof(int);i++)
 {
  pinMode(list[i], OUTPUT);
  digitalWrite(list[i], (h==i)?1:0);
}

}

void loop() {
yield();
}

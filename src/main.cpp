#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN            11
#define NUMPIXELS      5
#define PIXEL_TYPE     NEO_GRBW + NEO_KHZ800

Adafruit_NeoPixel strip(NUMPIXELS, PIN, PIXEL_TYPE);

void setup() {
  pinMode(PIN, OUTPUT);
  strip.begin();
  strip.show(); // Alle LEDs aus
}

void loop() {
  // Alle LEDs auf Weiß setzen
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0, 255)); // nur Weiß
  }
  strip.show();
  delay(1000);

  // Alle LEDs ausschalten
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0, 0)); // aus
  }
  strip.show();
  delay(1000);
}

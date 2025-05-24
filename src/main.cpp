#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN            11       // Datenpin
#define NUMPIXELS      8       // Anzahl der RGBW-LEDs
#define PIXEL_TYPE     NEO_GRBW + NEO_KHZ800  // Für RGBW

Adafruit_NeoPixel strip(NUMPIXELS, PIN, PIXEL_TYPE);

void setup() {
  strip.begin();
  strip.show(); // Alle LEDs aus
}

void loop() {
  // Beispiel: LED 0 auf reines Weiß setzen
  strip.setPixelColor(0, strip.Color(0, 0, 0, 255)); // (R,G,B,W)
  strip.show();
  delay(1000);

  // LED aus
  strip.setPixelColor(0, strip.Color(0, 0, 0, 0));
  strip.show();
  delay(1000);
}

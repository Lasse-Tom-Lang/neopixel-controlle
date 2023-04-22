#include <FastLED.h>

#define NUM_LEDS 37

#define ANIMATION_LENGTH 4

#define FPS 8

CRGB leds[NUM_LEDS];

int frame = 0;
int animation[ANIMATION_LENGTH][37] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1}
};

void setup() {
  FastLED.addLeds<NEOPIXEL, 13>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  Serial.begin(9600);
}

void loop() {

  for (int i = 0; i < NUM_LEDS; i++) {
    if (animation[frame][i] == 1) {
      leds[i].setRGB(255, 0, 0);
    }
    else {
      leds[i].setRGB(0, 0, 0);
    }
  }
  FastLED.show();
  delay(1000 / FPS);
  frame++;
  if (frame==ANIMATION_LENGTH){frame=0;}
}

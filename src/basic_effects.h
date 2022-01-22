#include <Arduino.h>
#include <U8g2lib.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

#define NUM1 597
#define NUM2 627
#define NUM 1224
#define LED_PIN1 5
#define LED_PIN2 23
#define DIAL 13
#define BUTTON 16

extern CRGB *leds[];
extern CRGB LEDs1[];
extern CRGB LEDs2[];

int flagsize = 35;
extern CRGB rasta[];

int b1 = 116;
int b2 = (345-115)/2+115;
int b3 = 345;
int b4 = (528-345)/2+345;
int b5 = 528;
int b6 = 853;
int b5h = (b6-b5)/2+b5;
int b7 = 1032;
int b6h = (b7-b6)/2+b6;
int b8 = 1118;
int b7h = (b8-b7)/2+b7;
int arr[] = {0, b1, b2, b3, b4, b5, b5h, b6, b6h, b7, b7h, b8, NUM};
uint8_t h = 0;
uint8_t r = 0;

void drawSolid(CRGB color) {
    for(int i = 0; i < NUM; i++) {
        *leds[i] = color;
    }
}

void drawSolid(CHSV color) {
  for(int i = 0; i < NUM; i++) {
        *leds[i] = color;
    }
}

void drawOutCorners(CRGBPalette256 pal) {
    for (int i = 0; i < 12; i++) {
        for (int j = arr[i]; j < arr[i+1]; j++) {
          if(i % 2 == 0) {
            *leds[j] = ColorFromPalette(pal, j-arr[i]+h);
          } else {
            *leds[j] = ColorFromPalette(pal, arr[i+1]-j+h);
          }
        }
      }

      EVERY_N_MILLIS(15) {
        h += 1;
        FastLED.show();
      }
}

void drawTrain(CRGBPalette256 pal) {
    for(int i = 0; i < NUM; i++) {
        *leds[i] = ColorFromPalette(pal, i+h);
      }
      EVERY_N_MILLIS(15) {
        h += 1;
        FastLED.show();
      }
}

void initTwinkle(CRGBPalette256 pal, uint8_t density) {
  for(int i = 0; i < NUM; i++) {
    if(random8() < density) {
      *leds[i] = ColorFromPalette(pal, random8());
      leds[i]->maximizeBrightness(random8(150));
    }
  }
  FastLED.show();
}

void drawTwinkle(CRGBPalette256 pal) {
    EVERY_N_MILLIS(15) {
        *leds[random(NUM)] = ColorFromPalette(pal, random8());
        FastLED.show();
      }
      fadeToBlackBy(LEDs1, NUM1, 1);
      fadeToBlackBy(LEDs2, NUM2, 1);
      FastLED.show();
}

void drawTwinkle2(CRGBPalette256 pal) {
    EVERY_N_MILLIS(75) {
      int led = random(NUM);
      uint8_t col = random8();
      *leds[led] = ColorFromPalette(pal, col);
      leds[led]->maximizeBrightness(5);
      FastLED.show();
      int time = millis();
      int reps = 0;
      uint8_t limit = 20;
      while(reps < 10) {
        if(millis() > time + 50) {
          leds[led]->maximizeBrightness(limit);
          limit += 20;
          time = millis();
          reps += 1;
          FastLED.show();
        }
      }
    }
    EVERY_N_MILLIS(600) {
      fadeToBlackBy(LEDs1, NUM1, 1);
      fadeToBlackBy(LEDs2, NUM2, 1);
      FastLED.show();
    }
}

void drawFade(CRGBPalette256 pal) {
    EVERY_N_MILLIS(200) {
      static CRGB currentColor = ColorFromPalette(pal, h);
      static CRGB lastColor = ColorFromPalette(pal, h);
      static CRGB targetColor = ColorFromPalette(pal, h+1);
      static uint8_t step = 0;
      
      currentColor = blend(lastColor, targetColor, 255/8*step++);
      if(step > 8)
      {
          step = 0;
          lastColor = targetColor;
          targetColor = ColorFromPalette(pal, h++);
      }
      for(int i = 0; i < NUM; i++) {
        *leds[i] = currentColor;
      }
      FastLED.show();
    }
}

void drawRainbowFade() {
  static CRGB currentColor = CRGB::Red;
    static CRGB lastColor = CRGB::Red;
    static CRGB targetColor = CRGB::Red;
    static uint8_t hue = 0;
    static uint8_t step = 0;
    
    currentColor = blend(lastColor, targetColor, 255/8*step++);
    if(step > 8)
    {
        step = 0;
        lastColor = targetColor;
        hsv2rgb_rainbow(CHSV(hue++, 255, 255), targetColor);
    }
    for(int i = 0; i < NUM; i++) {
        *leds[i] = currentColor;
      }
    FastLED.delay(10);
}

void drawRasta() {
  for(int i = 0; i < NUM; i++) {
        *leds[i] = rasta[(i+r)%(flagsize*3)];
  }
  EVERY_N_MILLIS(15) {
    r += 1;
    FastLED.show();
  }
}


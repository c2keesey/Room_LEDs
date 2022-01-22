#include <Arduino.h>
#include <U8g2lib.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#include <basic_effects.h>
#include <palettes.h>

/***************/
#define NUM_MODES 11
int mode = 8;
/***************/


U8G2_SSD1306_128X64_NONAME_F_HW_I2C g_OLED(U8G2_R2, 16, 15, 4);
int g_lineHeight = 0;


#define NUM1 597
#define NUM2 627
#define NUM 1224
#define LED_PIN1 5
#define LED_PIN2 23
#define DIAL 13
#define BUTTON 16

const int SHORT_PRESS_TIME = 1000;

CRGB LEDs1[NUM1] = {0};
CRGB LEDs2[NUM2] = {0};
CRGB *leds[NUM] = {0};
CRGB rasta[105] = {0};
uint8_t hue = 0;

int curr_state;
int last_state = LOW;
bool init_t = true;


// FramesPerSecond
//
// Tracks a weighted average to smooth out the values that it calcs as the simple reciprocal
// of the amount of time taken specified by the caller.  So 1/3 of a second is 3 fps, and it
// will take up to 10 frames or so to stabilize on that value.

double FramesPerSecond(double seconds)
{
  static double framesPerSecond; 
  framesPerSecond = (framesPerSecond * .9) + (1.0 / seconds * .1);
  return framesPerSecond;
}

void clear() {
  for(int i = 0; i < NUM; i ++) {
    *leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void setup() {
  //pinMode(LED_BUILTIN, OUTPUT);

  // g_OLED.begin();
  // g_OLED.clear();
  // g_OLED.setFont(u8g2_font_profont15_tf);
  // g_lineHeight = g_OLED.getFontAscent() - g_OLED.getFontDescent();
  // g_OLED.setCursor(40, g_OLED.getHeight()/2);
  // g_OLED.print("hey sexy");
  

  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(BUTTON, INPUT);
  
  FastLED.addLeds<WS2812, LED_PIN1, GRB>(LEDs1, NUM1);
  FastLED.addLeds<WS2812, LED_PIN2, GRB>(LEDs2, NUM2);

  for(int i = 0; i < NUM1; i++) {
    leds[i] = &LEDs1[i];
  }
  for(int i = 0; i < NUM2; i++) {
    leds[NUM1+i] = &LEDs2[NUM2-i];
  }
  for(int i = 0; i < flagsize; i++) {
  rasta[i] = CRGB(0, 255, 0);
  }
  for(int i = flagsize; i < flagsize*2; i++) {
   rasta[i] = CRGB(255, 224, 0);
  }
  for(int i = flagsize*2; i < flagsize*3; i++) {
    rasta[i] = CRGB(231, 0, 1);
  }

  FastLED.setBrightness(10);
  clear();
  FastLED.setMaxPowerInMilliWatts(8000);
  //Serial.begin(9600);
}

void loop() {
  // static bool bLED = LOW;
  // bLED = !bLED;
  // digitalWrite(LED_BUILTIN, bLED);


  // g_OLED.drawFrame(0, 0, g_OLED.getWidth(), g_OLED.getHeight());
  // g_OLED.setCursor(20, g_lineHeight *4 + 2);
  // g_OLED.printf("Framerate = %d", 0);
  // g_OLED.sendBuffer();


  curr_state = digitalRead(BUTTON);
  if(curr_state == HIGH && last_state == LOW) {
    FastLED.clear();
    mode = (mode + 1) % NUM_MODES;
    init_t = true;
    last_state = HIGH;
  } else if (curr_state == LOW && last_state == HIGH) {
    last_state = LOW;
  }

    if(mode == 0) {
      drawSolid(CRGB::White);

    } else if (mode == 1) {
      drawOutCorners(emerald_dragon);

    } else if (mode == 2) {
      drawTrain(emerald_dragon);
    
    } else if (mode == 3) {
      drawTrain(strong_watermellon);

    } else if (mode == 4) {
      clear();
    
    } else if (mode == 5) {
      drawSolid(CRGB::Red);
    
    } else if (mode == 6) {
      drawSolid(CHSV(187, 255, 255));
    
    } else if (mode == 7) {
      drawRainbowFade();
    
    } else if (mode == 8) {
      CRGBPalette256 pal = valentine;
      if(init_t) {
        initTwinkle(pal, 75);
        init_t = false;
      }
      drawTwinkle2(pal);
    
    } else if (mode == 9) {
      CRGBPalette256 pal = soft_watermellon;
      if(init_t) {
        initTwinkle(pal, 75);
        init_t = false;
      }
      drawTwinkle2(pal);
    
    } else if (mode == 10) {
      CRGBPalette256 pal = strong_watermellon;
      if(init_t) {
        initTwinkle(pal, 75);
        init_t = false;
      }
      drawTwinkle2(pal);
    }
    
  FastLED.show();

}
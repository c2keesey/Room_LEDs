#include <Arduino.h>
#include <U8g2lib.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C g_OLED(U8G2_R2, 16, 15, 4);
int g_lineHeight = 0;

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

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  g_OLED.begin();
  g_OLED.clear();
  g_OLED.setFont(u8g2_font_profont15_tf);
  g_lineHeight = g_OLED.getFontAscent() - g_OLED.getFontDescent();
  g_OLED.setCursor(40, g_OLED.getHeight()/2);
  g_OLED.print("hey sexy");
  
}

void loop() {
  static bool bLED = LOW;
  bLED = !bLED;
  digitalWrite(LED_BUILTIN, bLED);


  g_OLED.drawFrame(0, 0, g_OLED.getWidth(), g_OLED.getHeight());
  g_OLED.setCursor(20, g_lineHeight *4 + 2);
  g_OLED.printf("Framerate = %d", 0);
  g_OLED.sendBuffer();
}
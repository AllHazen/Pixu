#ifndef EYE_OLED_H
#define EYE_OLED_H

#include "Easing.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define screenWidth 128

class EyeCharacter {
  protected:
  Adafruit_SSD1306 &display; 
  const int eyeWidth = 25;
  const int eyeHeight = 25;
  const int spacing = 23;
  const int eyeY = 20;
  const int cornerRadius = 4;

  int centerX; 
  int leftEyeX;
  int rightEyeX;

  public: 
  EyeCharacter(Adafruit_SSD1306 &disp);

  void animationOpen() {};

  void animationBlinking() {};

  void animationSquint(){};

  void animationSleep(){};

  void animationLook(){};

  void animationShake(){};
};

#endif
#ifndef LOADING_OLED_H
#define LOADING_OLED_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Loading {
  private:  
  Adafruit_SSD1306 &display;
  int barHeight;
  int barWidth = 10;
  const int barMaxWidth = 99;
  const int barX = 14;
  int barY = 40;
  int rectX = barX ;
  int numBar; 
  int LoadingX = 43;
  int LoadingY = 25;

  public: 
  Loading(int barHeight, int Y, int spacing, Adafruit_SSD1306 &disp);  
  Loading(Adafruit_SSD1306 &disp);
    
  void displayBar() {}; // menampilkan bar loading di OLED 
  
};

#endif
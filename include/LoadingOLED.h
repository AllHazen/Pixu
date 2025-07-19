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
  int numBar = (barMaxWidth / barWidth); 
  int LoadingX = 43;
  int LoadingY = 25;

  public: 
  Loading(int barHeight, int Y, int spacing, Adafruit_SSD1306 &disp)
  : display(disp) {
      this->barHeight = barHeight;
      this->LoadingY = Y;
      this->barY = Y + spacing;
    }
    
    Loading(Adafruit_SSD1306 &disp) : Loading(10, 25, 40, disp) {}
    
  void displayBar() { // menampilkan bar loading di OLED
    LoadingX = 43;
    for (int i = 0; i < numBar; i++){
      display.clearDisplay();
      display.drawRect(barX, barY, barMaxWidth, barHeight, SSD1306_WHITE);
      
      display.setCursor(LoadingX,LoadingY);
      display.print("LOADING");
      for (int dot=0; dot < (i%4) ; dot++) {
        display.print(".");
        if (i%4 == 3) {
          LoadingX = 43;
        } 
      LoadingX -= 1;
      }

      for (int j = 0; j<= i ; j++){
        display.fillRect(rectX, barY, barWidth, barHeight, SSD1306_WHITE);
        rectX += (barWidth + 1);
      }
      rectX = barX;
      
      display.display();
      delay(1000);

      }
    } 
  
};

#endif
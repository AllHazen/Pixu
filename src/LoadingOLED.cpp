#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LoadingOLED.h>

Loading::Loading(int barHeight, int Y, int spacing, Adafruit_SSD1306 &disp) : display(disp) {
    this->LoadingY = Y;
    this->barY = Y + spacing;
    this->barHeight = barHeight;
    numBar = (barMaxWidth/barWidth);
}

Loading::Loading(Adafruit_SSD1306 &disp) : Loading(10,25,40, disp) {}

void Loading::displayBar() {
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
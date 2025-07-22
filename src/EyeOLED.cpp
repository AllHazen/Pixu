#include "Easing.h"
#include "EyeOLED.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define screenWidth 128

EyeCharacter::EyeCharacter(Adafruit_SSD1306 &disp) : display(disp) {
    centerX = screenWidth/2;
    leftEyeX = centerX - spacing - (eyeWidth / 2);
    rightEyeX = centerX + spacing - (eyeWidth / 2);
}

void EyeCharacter::animationOpen(){
    display.clearDisplay();

    // draw eye
    for (int step=0; step < 12; step++){
      float t = (float)step/11.0;
      float easeRatio = Easing::easeIn(t);
      int currentHeight = eyeHeight * easeRatio;
      int currentY = eyeY + ((eyeHeight - currentHeight)/2);

      display.clearDisplay();
      display.fillRoundRect(leftEyeX, currentY, eyeWidth, currentHeight, cornerRadius, SSD1306_WHITE);
      display.fillRoundRect(rightEyeX , currentY, eyeWidth, currentHeight, cornerRadius, SSD1306_WHITE);
      display.display();
      delay(5);
    }
}

void EyeCharacter::animationBlinking() {
    display.clearDisplay();

    // close eye 
    for (int step=0; step < 8; step++){
      float t = (float)step/7.0;
      float easeRatio = Easing::easeIn(t);
      int currentHeight = eyeHeight * (1 - easeRatio);
      int currentY = eyeY + (eyeHeight - currentHeight)/2;
      display.clearDisplay();
      display.fillRoundRect(leftEyeX, currentY, eyeWidth, currentHeight, cornerRadius, SSD1306_WHITE);
      display.fillRoundRect(rightEyeX, currentY, eyeWidth, currentHeight, cornerRadius, SSD1306_WHITE);
      display.display();
    }
    // open eye
    for (int step=0; step<8; step++){
      float t = (float)step/6.0;
      float easeRatio = Easing::easeOut(t);
      int currentHeight = eyeHeight * easeRatio; 
      int currentY = eyeY + (eyeHeight - currentHeight)/2;
      display.clearDisplay();
      display.fillRoundRect(leftEyeX, currentY, eyeWidth, currentHeight, cornerRadius, SSD1306_WHITE);
      display.fillRoundRect(rightEyeX , currentY, eyeWidth, currentHeight, cornerRadius, SSD1306_WHITE);
      display.display();
    }

}

void EyeCharacter::animationSquint() {
    display.clearDisplay();
    int endHeight = 13;
    for (int step=0; step<12; step++ ){
      display.clearDisplay();
      float t = step/11.0;
      float easeRatio = Easing::easeOut(t);
      int currentHeight = Easing::linearInter(eyeHeight, endHeight, easeRatio);
      display.fillRoundRect(leftEyeX, eyeY, eyeWidth, currentHeight, cornerRadius, SSD1306_WHITE);
      display.fillRoundRect(rightEyeX, eyeY, eyeWidth, currentHeight, cornerRadius, SSD1306_WHITE);
      display.display();
    }
    delay(500);
}

void EyeCharacter::animationSleep() {
    display.display();
    animationSquint();
    int endHeight = 13;
    int zY = 10;
    int zX = 90;
    delay(1500);
    for(int count = 0; count < 5; count++){
      display.fillRoundRect(leftEyeX, eyeY, eyeWidth, endHeight, cornerRadius, SSD1306_WHITE);
      display.fillRoundRect(rightEyeX, eyeY, eyeWidth, endHeight, cornerRadius, SSD1306_WHITE);
      for (int i=0; i <=3; i++){
        display.setTextSize(1 + i);
        display.setCursor(zX + (i*5), zY+(i*5));
        display.print("z");
        display.display(); 
        delay(700);
      }
      display.clearDisplay();
    }
    for (int step=0; step < 12; step++){
      display.clearDisplay();
      float t = step/11.0;
      float easeRatio = Easing::easeIn(t);
      int currentHeight = Easing::linearInter(endHeight, eyeHeight, easeRatio);
      display.fillRoundRect(leftEyeX, eyeY, eyeWidth, currentHeight, cornerRadius, SSD1306_WHITE);
      display.fillRoundRect(rightEyeX, eyeY, eyeWidth, currentHeight, cornerRadius, SSD1306_WHITE);
      display.display();
    }
}

void EyeCharacter::animationLook() {
    animationSquint();
    display.clearDisplay();
    int endHeight = 13;
    const int maxOffsetX = 13;
    for (int step=0; step<12; step++){
      display.clearDisplay();
      float t = step/11.0;
      float easeRatio = Easing::easeInOut(t);
      int offsetX = Easing::linearInter(0, maxOffsetX, easeRatio);
      int currentLeftX = leftEyeX - offsetX; 
      int currentRightX = rightEyeX - offsetX; 
      display.fillRoundRect(currentLeftX, eyeY, eyeWidth, endHeight, cornerRadius, SSD1306_WHITE);
      display.fillRoundRect(currentRightX, eyeY, eyeWidth, endHeight, cornerRadius, SSD1306_WHITE);
      display.display();
    }
    delay(500);
    for(int step=0; step<20; step++){
      display.clearDisplay();
      float t = step/19.0;
      float easeRatio = Easing::easeInOut(t);
      int offsetX = Easing::linearInter(maxOffsetX, -maxOffsetX, easeRatio);
      int currentLeftX = leftEyeX - offsetX; 
      int currentRightX = rightEyeX - offsetX; 
      display.fillRoundRect(currentLeftX, eyeY, eyeWidth, endHeight, cornerRadius, SSD1306_WHITE);
      display.fillRoundRect(currentRightX, eyeY, eyeWidth, endHeight, cornerRadius, SSD1306_WHITE);
      display.display();   
    }
    delay(1000);
    for (int step=0; step<18; step++){
      display.clearDisplay();
      float t = step/17.0;
      float easeRatio = Easing::easeOut(t);
      int centerX = Easing::linearInter(-maxOffsetX, 0, easeRatio);
      int currentHeight = Easing::linearInter(endHeight, eyeHeight, easeRatio);
      int currentLeftX = leftEyeX - centerX;
      int currentRightX = rightEyeX - centerX;
      display.fillRoundRect(currentLeftX, eyeY, eyeWidth, currentHeight, cornerRadius, SSD1306_WHITE);
      display.fillRoundRect(currentRightX, eyeY, eyeWidth, currentHeight, cornerRadius, SSD1306_WHITE);
      display.display();
    }
}

void EyeCharacter::animationShake() {
    display.clearDisplay();
    int endPoint = 6;
    int shake = 7;
    float decay = 0.8;
    //
    for (int i = 0; i<shake; i++){
      int direction = (random(0,2) == 0) ? -1 : +1;
      int amplitude = endPoint * pow(decay, i);
      for (int step=0;step<= 3; step++){
        display.clearDisplay();
        float t = (float)step/2.0;
        float easeRatio = Easing::easeOut(t);
        int offsetY = direction * amplitude * easeRatio;
        int currentY = eyeY + offsetY;
        display.fillRoundRect(leftEyeX, currentY, eyeWidth, eyeHeight, cornerRadius, SSD1306_WHITE);
        display.fillRoundRect(rightEyeX, currentY, eyeWidth, eyeHeight, cornerRadius, SSD1306_WHITE);
        display.display();
      }
    }
}
#include <Wire.h>
#include "EyeOLED.h"
#include "LoadingOLED.h"
#include <vector>
#include <functional>

#define screenWidth 128
#define screenHeight 64
#define oledReset -1

Adafruit_SSD1306 display(screenWidth, screenHeight, &Wire, oledReset);
EyeCharacter eyeCharacter(display);
Loading loading(display);

std::vector<std::function<void()>> animationList;

unsigned long previousMillis = 0;
const long interval = 4000;

void setup() {
  Serial.begin(115200);
  Wire.begin(21,22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.printf("OLED tidak ditemukan");
    Serial.println(" ");
    while (true);
  } else {
    Serial.println("OLED ditemukan");
  }

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  // display.clearDisplay();
  // display.display();
  loading.displayBar();
  display.clearDisplay();
  display.display();
  delay(3000);
  
  randomSeed(analogRead(2));
  animationList.push_back([]() { eyeCharacter.animationLook(); });
  animationList.push_back([]() {eyeCharacter.animationBlinking();});
  animationList.push_back([]() {eyeCharacter.animationShake();});
  animationList.push_back([]() {eyeCharacter.animationSleep();});

  eyeCharacter.animationOpen();
  delay(1500);
  eyeCharacter.animationLook();
  delay(300);
  eyeCharacter.animationShake();
  delay(5000);
}

void loop() {
  unsigned long currentMillis = millis();
  if ((unsigned long)currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    animationList[random(0, animationList.size())]();
  }
}

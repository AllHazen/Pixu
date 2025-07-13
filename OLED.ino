
#include <Wire.h> // komunikasi I2C
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <String>

// setup OLED
#define screenWidth 128
#define screenHeight 64
#define oledReset -1

// inisialisasi animasi OLED

// setting display (ukuran OLED, alamat memori I2C, dan reset OLED)
Adafruit_SSD1306 display(screenWidth, screenHeight, &Wire, oledReset);

class Loading {
  private:  
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
  Loading(){
    barHeight = 10;
    LoadingY = 25;
    barY = 40;

  }
  Loading (int barHeight, int Y, int spacing){
    this->barHeight = barHeight;
    this->LoadingY = Y;
    this->barY = Y + spacing;
  }

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

enum class EyeMode {
  NORMAL, 
  BLINKING,
  LOOKING_LEFT,
  LOOKING_RIGHT
};

class EyeCharacter {
  private : 
  EyeMode currentMode;

  protected: 
  const int eyeWidth = 25;
  const int eyeHeight = 25;
  const int centerX = screenWidth/2; 
  const int spacing = 23;
  const int leftEyeX = centerX - spacing - (eyeWidth/2);
  const int rightEyeX = centerX + spacing - (eyeWidth/2);
  const int eyeY = 20;
  const int cornerRadius = 4;

  public: 
  EyeCharacter() {
    currentMode = EyeMode::NORMAL;
    }
  void setMode(EyeMode mode) { 
    currentMode = mode;
    }
  float easeIn(float t){
    return t*t; // ketika t kecil maka return kecil, dan sebaliknya
  }

  float easeOut(float t) {
    return 1-pow(1-t,2);
  }

  float easeInOut(float t) {
    return t < 0.5 ? 2*t*t : 1- 2*pow(1-t,2);
  }

  float linearInter(float initial, float end, float t){
    return initial + (end - initial) * t;
  }
  void animationOpen() {
    display.clearDisplay();

    // draw eye
    for (int step=0; step < 12; step++){
      float t = (float)step/11.0;
      float easeRatio = easeIn(t);
      int currentHeight = eyeHeight * easeRatio;
      int currentY = eyeY + ((eyeHeight - currentHeight)/2);

      display.clearDisplay();
      display.fillRoundRect(leftEyeX, currentY, eyeWidth, currentHeight, cornerRadius, SSD1306_WHITE);
      display.fillRoundRect(rightEyeX , currentY, eyeWidth, currentHeight, cornerRadius, SSD1306_WHITE);
      display.display();
      delay(5);
    }


    // 
  }

  void animationBlinking() {
    display.clearDisplay();

    // close eye 
    for (int step=0; step < 12; step++){
      float t = (float)step/11.0;
      float easeRatio = easeIn(t);
      int currentHeight = eyeHeight * (1 - easeRatio);
      int currentY = eyeY + (eyeHeight - currentHeight)/2;
      display.clearDisplay();
      display.fillRoundRect(leftEyeX, currentY, eyeWidth, currentHeight, cornerRadius, SSD1306_WHITE);
      display.fillRoundRect(rightEyeX, currentY, eyeWidth, currentHeight, cornerRadius, SSD1306_WHITE);
      display.display();
    }
    // open eye
    for (int step=0; step<12; step++){
      float t = step/11.0;
      float easeRatio = easeOut(t);
      int currentHeight = eyeHeight * easeRatio; 
      int currentY = eyeY + (eyeHeight - currentHeight)/2;
      display.clearDisplay();
      display.fillRoundRect(leftEyeX, currentY, eyeWidth, currentHeight, cornerRadius, SSD1306_WHITE);
      display.fillRoundRect(rightEyeX , currentY, eyeWidth, currentHeight, cornerRadius, SSD1306_WHITE);
      display.display();
    }
  }

  void animationSquint(){
    display.clearDisplay();
    int endHeight = 13;
    for (int step=0; step<12; step++ ){
      display.clearDisplay();
      float t = step/11.0;
      float easeRatio = easeOut(t);
      int currentHeight = linearInter(eyeHeight, endHeight, easeRatio);
      display.fillRoundRect(leftEyeX, eyeY, eyeWidth, currentHeight, cornerRadius, SSD1306_WHITE);
      display.fillRoundRect(rightEyeX, eyeY, eyeWidth, currentHeight, cornerRadius, SSD1306_WHITE);
      display.display();
    }
    delay(500);
  }
  void animationLook(){
    animationSquint();
    display.clearDisplay();
    int endHeight = 13;
    const int maxOffsetX = 13;
    for (int step=0; step<12; step++){
      display.clearDisplay();
      float t = step/11.0;
      float easeRatio = easeInOut(t);
      int offsetX = linearInter(0, maxOffsetX, easeRatio);
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
      float easeRatio = easeInOut(t);
      int offsetX = linearInter(maxOffsetX, -maxOffsetX, easeRatio);
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
      float easeRatio = easeOut(t);
      int centerX = linearInter(-maxOffsetX, 0, easeRatio);
      int currentHeight = linearInter(endHeight, eyeHeight, easeRatio);
      int currentLeftX = leftEyeX - centerX;
      int currentRightX = rightEyeX - centerX;
      display.fillRoundRect(currentLeftX, eyeY, eyeWidth, currentHeight, cornerRadius, SSD1306_WHITE);
      display.fillRoundRect(currentRightX, eyeY, eyeWidth, currentHeight, cornerRadius, SSD1306_WHITE);
      display.display();
    }
  }
};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin(21,22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.printf("OLED tidak ditemukan");
    Serial.println(" ");
    while (true);
  } else {
    Serial.println("OLED ditemukan");
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();
  Loading loading;
  loading.displayBar();
  display.clearDisplay();
  display.display();
  delay(3000);
  EyeCharacter eyeCharacter;
  eyeCharacter.animationOpen();
  delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
  EyeCharacter eyeCharacter;
  eyeCharacter.animationLook();
  delay(5000);
  eyeCharacter.animationBlinking();
  eyeCharacter.animationBlinking();
  delay(3000);



}


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
}

void loop() {
  // put your main code here, to run repeatedly:
  Loading loading;
  loading.displayBar();
}

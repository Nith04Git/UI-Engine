/*
UI Engine [ST7735 Adafruit Edition]
*/

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <vector>
#include <string>

#define TFT_CS        10
#define TFT_DC         9
#define TFT_RST        8

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
std::vector<String> cmdmatrix;
String command;

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing ST7735 TFT via INITR_BLACKTAB.");

  uint8_t initstate = INITR_BLACKTAB;
  /*
  if this initialization doesn't work, try these alternatives. Comment out the initialization to try these alternatives.
  Use only one initialization at a time. Try each one until your TFT starts displaying.
  */
  //uint8_t initstate = INITR_GREENTAB;
  //uint8_t initstate = INITR_REDTAB;

  tft.initR(initstate);
  tft.fillScreen(ST77XX_BLACK);

  Serial.println("ST7735 TFT initialized.");
  Serial.println("UI Engine initialized. Please enter a command.");
}

void loop() {
  ask();

  if(command == "/help"){
    Serial.println("Type '/circle' to generate a circle.");
    Serial.println("Type '/square' to generate a square.");
    Serial.println("Type '/triangle' to generate a triangle.");
    return;
  }
  if(command == "/circle"){
    Serial.println("Please state x position of circle.");
    ask();
    uint8_t x = command.toInt();
    Serial.println("Please state y position of circle.");
    ask();
    uint8_t y = command.toInt();
    Serial.println("Please state radius of circle.");
    ask();
    uint8_t radius = command.toInt();

    circle(x, y, radius, 1);
    return;
  }

  command = "";
  cmdmatrix.clear();

  delay(10);

}

void ask(){
  while(Serial.available() == 0){
    delay(10);
  }

  String inputitem = Serial.readString();
  String currentWord = "";
  int tokenidx = 1;

  for (size_t i = 0; i < inputitem.length(); i++) {
    char c = inputitem.charAt(i);

    if (c == ' ' || c == '\n' || c == '\r' || c == '\t') {
      if (currentWord.length() > 0) {
        
        String cleanToken = "";
        for(size_t k = 0; k < currentWord.length(); k++) {
          char ch = currentWord.charAt(k);
          if(ch >= 32 && ch <= 126) cleanToken += ch;
        }
        cleanToken.trim();

        if (cleanToken.length() > 0) {
          cmdmatrix.push_back(cleanToken);
        }
        currentWord = "";
      }
    } 
    else {
      currentWord += c;
    }
  }

  for(size_t i = 0; i < cmdmatrix.size(); i++){
    if(i > 0){
      command = command + " " + cmdmatrix[i];
    }
    else{
      command = command + cmdmatrix[i];
    }
  }
}

void circle(uint8_t x, uint8_t y, uint8_t radius, uint8_t color){
  tft.drawCircle(x, y, radius, color);
}
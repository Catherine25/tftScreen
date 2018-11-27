#include <Adafruit_GFX.h>	// Core graphics library
#include <TftSpfd5408.h>	// Hardware-specific library

#define LCD_CS A3	// Chip Select goes to Analog 3
#define LCD_CD A2	// Command/Data goes to Analog 2
#define LCD_WR A1	// LCD Write goes to Analog 1
#define LCD_RD A0	// LCD Read goes to Analog 0

#define LCD_RESET A4	// Can alternately just connect to Arduino's reset pin

#define BLACK  0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//==========================================================================//

TftSpfd5408 tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

char outPut[25][25] = {
"0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0",
"0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0",
"0 1 0 0 0 1 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0 1 0 1 0",
"0 1 1 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1 0",
"0 1 0 1 0 0 0 1 0 1 0 1 0 1 0 1 0 0 0 1 0 0 0 1 0",
"0 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 1 0",
"0 1 0 0 0 1 0 0 0 1 0 1 0 0 0 0 0 1 0 0 0 0 0 0 0",
"0 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 0 1 1 1 1 1 1 1 0",
"0 1 0 1 0 1 0 0 0 0 0 0 0 1 0 1 0 1 0 1 0 1 0 1 0",
"0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 1 1 1 0 1 1 1 0",
"0 1 0 0 0 1 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 0 0",
"0 1 1 1 1 1 1 1 1 1 1 1 0 1 0 1 1 1 1 1 1 1 1 1 0",
"0 1 0 1 0 1 0 1 0 1 0 0 0 1 0 1 0 1 0 1 0 0 0 0 0",
"0 1 1 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1 0",
"0 1 0 1 0 0 0 1 0 0 0 1 0 1 0 0 0 0 0 1 0 0 0 1 0",
"0 1 0 1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1 1 1 0",
"0 1 0 0 0 1 0 0 0 0 0 1 0 0 0 1 0 0 0 1 0 1 0 1 0",
"0 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1 1 1 0",
"0 1 0 0 0 1 0 1 0 1 0 1 0 0 0 1 0 1 0 1 0 0 0 0 0",
"0 1 1 1 1 1 1 1 1 1 1 1 0 0 0 1 0 1 1 1 1 1 0 1 0",
"0 1 0 1 0 1 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 0 1 0",
"0 1 1 1 1 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 0",
"0 1 0 0 0 1 0 1 0 1 0 0 0 1 0 1 0 1 0 1 0 0 0 1 0",
"0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0",
"0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0" };

//==========================================================================//
void setup(void) {
  tft.reset();
  tft.begin(0x9341);

  Serial.println(testFillScreen());
  Serial.println(writeText());
  delay(500);
  Serial.println(testFillScreen());
  Serial.println(drawImage());
  delay(500);
}

void loop(void) { }
//==========================================================================//
unsigned long testFillScreen() {
  unsigned long start = micros();

  tft.fillScreen(BLACK);
  tft.fillScreen(RED);
  tft.fillScreen(GREEN);
  tft.fillScreen(BLUE);
  tft.fillScreen(BLACK);

  return micros() - start;
}
//--------------------------------------------------------------------------//
unsigned long writeText() {
  unsigned long start = micros();

  tft.setCursor(0, 0);
  tft.setTextSize(1);

  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {

      if (outPut[i][j] == '0') {
        tft.setTextColor(RED);
        tft.print('|');
      }
      else if (outPut[i][j] == '1') {
        tft.setTextColor(YELLOW);
        tft.print('_');
      }
      else {
        tft.setTextColor(YELLOW);
        tft.print('_');
      }
    }
    tft.println();
  }
  return micros() - start;
}
//--------------------------------------------------------------------------//
unsigned long drawImage() {
  unsigned long start = micros();
  
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {

      if (outPut[i][j] == '0') {
        tft.drawRect(9*i, 9*j, 9, 9, WHITE);
        tft.drawLine(9*i, 9*j, 9, 9, GREEN);
        tft.drawLine(9*i+9, 9*j-9, 9, 9 , GREEN);
      }
      else if (outPut[i][j] == '1') {
         tft.drawRect(9*i, 9*j, 9, 9, CYAN);
         tft.drawLine(9*i, 9*j, 9, 9, YELLOW);
         tft.drawLine(9*i+9, 9*j-9, 9, 9, YELLOW);
      }
      
    }
}
  return micros() - start;
}

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#include "FreqPeriod.h"

double lfrq;
long int pp;


void setup() {
  Serial.begin(115200);
  Serial.println("FreqPeriod Library Test");

  FreqPeriod::begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)

}

void loop() {

  pp=FreqPeriod::getPeriod();

  if (pp ){

    lfrq= 16000400.0 / pp;

    display.clearDisplay();
    display.setRotation(2);
  
    display.setCursor(0,0);
    display.setTextSize(4);
    display.setTextColor(WHITE);
    
    if (lfrq < 10) {
      display.print(String(lfrq, 4));
    } else if (lfrq < 100) {
      display.print(String(lfrq, 3));
    } else if (lfrq < 1000) {
      display.print(String(lfrq, 2));
    } else if (lfrq < 10000) {
      display.print(String(lfrq, 1));
    } else {
      display.print(int(lfrq + .5));
    }
  
    display.display();
  }

}

//***************************************************************************
void printDouble( double val, byte precision){
  // prints val with number of decimal places determine by precision
  // precision is a number from 0 to 6 indicating the desired decimial places
  // example: lcdPrintDouble( 3.1415, 2); // prints 3.14 (two decimal places)

  if(val < 0.0){
    Serial.print('-');
    val = -val;
  }

  Serial.print (int(val));  //prints the int part
  if( precision > 0) {
    Serial.print("."); // print the decimal point
    unsigned long frac;
    unsigned long mult = 1;
    byte padding = precision -1;
    while(precision--)
      mult *=10;

    if(val >= 0)
      frac = (val - int(val)) * mult;
    else
      frac = (int(val)- val ) * mult;
    unsigned long frac1 = frac;
    while( frac1 /= 10 )
      padding--;
    while(  padding--)
      Serial.print("0");
    Serial.print(frac,DEC) ;
  }
}

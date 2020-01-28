#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>

#define LCD_CS A3 
#define LCD_CD A2
#define LCD_WR A1 
#define LCD_RD A0 
#define LCD_RESET A4

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

void setup() {
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));
  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());
  tft.reset();
  uint16_t identifier = tft.readID();
  if(identifier==0x0101)
      identifier=0x9341;
  if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    return;
  }
  tft.begin(identifier);


}
  
void loop() {
  // put your main code here, to run repeatedly:
    testText();
    delay(4000);
}

unsigned long testText() {
  tft.setRotation(3);
  tft.fillScreen(BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(GREEN);  tft.setTextSize(1);
  tft.println("BYTEmark* Native Mode Benchmark ver. 2 (10/95)");
  tft.println("Index-split by Andrew D. Balsa (11/97)");
  tft.println("Linux/Unix* port by Uwe F. Mayer (12/96,11/97)");
  tft.println("");
  tft.print("TEST             : Iterations : Old Index : New Index");
  tft.print("                 :  per sec   : Pentium90 :AMD K6/233");
  tft.print("-----------------:------------:-----------:----------");
  tft.print("NUMERIC SORT     :       831  :    21.31  :      7.00");
  tft.print("STRING SORT      :    100.96  :    45.11  :      6.98");
  tft.print("BITFIELD         : 3.155e+08  :    54.12  :     11.31");  
  tft.print("FP EMULATION     :     109.4  :    52.50  :     12.11");
  tft.print("FOURIER          :     21070  :    23.96  :     13.46");
  tft.print("ASSIGNMENT       :    22.939  :    87.29  :     22.64");
  tft.print("IDEA             :    4590.5  :    70.21  :     20.85");
  tft.print("HUFFMAN          :    1594.3  :    44.21  :     14.12");
  tft.print("NEURAL NET       :    27.784  :    44.63  :     18.77");
  tft.print("LU DECOMPOSITION :    999.96  :    51.80  :     37.41");
  tft.print("==============ORIGINAL BYTEMARK RESULTS==============");
  tft.println("INTEGER INDEX       : 49.614");
  tft.println("FLOATING-POINT INDEX: 38.121");
  tft.println("Baseline (MSDOS*)   : Pentium* 90, 256 KB L2-cache");
  tft.print("===================LINUX DATA BELOW==================");
  tft.println("CPU                 : ATmega328 ");
  tft.println("C compiler          : gcc version 4.3.2");
  tft.println("MEMORY INDEX        : 12.135");
  tft.println("INTEGER INDEX       : 12.568");
  tft.println("FLOATING-POINT INDEX: 21.144");
  tft.println("Baseline (LINUX)    : AMD K6/233*, 512 KB L2-cache");
  int i;
  for (i=0;i<1;i+=1) {
    tft.print("Zeile ");
    tft.print(i);
    tft.println(" mit Inhalt");
  }
/*  tft.setTextSize(1);
  tft.println("einen tollen Text auf meinem neuen");
  tft.print("Arduino UNO R3 mit satten 10 MHz");
  tft.println("Taktfrequenz und unglaublichen 2 kByte");
  tft.println("RAM. Da hatte mein erster Computer,");
  tft.println("ein ZX81, mit der 16 kByte Erweiterung");
  tft.println("schon 1981 mehr. Aber was soll's.");
  tft.println("see if I don't!");
  */
  return micros() - start;
}

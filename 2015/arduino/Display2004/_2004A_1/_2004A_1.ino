#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd1(0x27,10,POSITIVE); // Display 1 mit 16 Spalten und 2 Zeilen an Adresse 20h
 
void setup()
{
    //lcd1.init(); // Display 1 initialisieren
 
    lcd1.setCursor(0,0);
    lcd1.print("DISPLAY 1");
 
    delay(1000);
 
    lcd1.clear();
}
 
void loop()
{
  lcd1.setCursor(0,0);
  lcd1.print("Sek. seit Start");
  lcd1.setCursor(0,1);
  lcd1.print(millis()/1000);
 
}


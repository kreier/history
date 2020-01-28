#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x27); // Display 1 mit 16 Spalten und 2 Zeilen an Adresse 20h
 
void setup()
{
    lcd.begin(20,4); // 20x4 Display initialisieren
    Serial.begin(9600);
    lcd.backlight();
    Serial.println("Los geht es");
 
    lcd.setCursor(0,0);
    lcd.print("DISPLAY 1");
 
    delay(1000);
 
    lcd.clear();
}
 
void loop()
{
  lcd.setCursor(0,0);
  lcd.print("Sek. seit Start");
  lcd.setCursor(0,1);
  lcd.print(millis()/1000);
}


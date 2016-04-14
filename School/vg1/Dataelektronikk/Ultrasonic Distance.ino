#include <NewPing.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
NewPing sonar(13,12);

void setup()
{
  lcd.begin(16,2);
  
  for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  
  lcd.backlight();
  
  lcd.setCursor(0,0);
  lcd.print("Distance in cm");
}

void loop()
{
  lcd.setCursor(0,1);
  lcd.print("   ");
  lcd.setCursor(0,1);
  lcd.print(sonar.ping_cm());
  delay(50);
}

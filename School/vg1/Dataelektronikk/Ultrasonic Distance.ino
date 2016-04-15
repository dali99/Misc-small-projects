#include <NewPing.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// Our LCD Screen uses 0x3F, but replace this for your LCD's adress
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
// Set the first number to the trigger pin, second to echo
NewPing sonar(12,11);

void setup()
{
  // Initializes LCD screen to a 16x2 screen
  lcd.begin(16,2);
  
  // Blinks LCD three times, leavig the screen on at the end, easy to see start/restart happened
  for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight();
  
  // Sets the cursor to top left
  lcd.setCursor(0,0);
  lcd.print("Distance in cm");
}

char cm[3];
void loop()
{
  lcd.setCursor(0,1);
  sprintf(cm, "%.3i", sonar.convert_cm(sonar.ping_median(5)));
  lcd.print(cm);
  delay(50);
}

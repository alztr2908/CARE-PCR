#include <Arduino.h>
#include "./Utils/LCDManager.h"
#include "./Utils/PageManager.h"
#include "./Utils/KeypadHandler.h"

// LCDManager lcdManager;   // Direct instantiation of LCDManager
PageManager pageManager; // Direct instantiation of PageManager

LiquidCrystal_I2C lcd = lcdManager.getLCD();

void displayWelcome()
{
  lcd.clear();
  String messages[3] = {"UP CARE", "CARE-PCR", "AQUINO MENDOZA"};
  byte numMessages = sizeof(messages) / sizeof(messages[0]);

  for (byte messageIndex = 0; messageIndex < numMessages; messageIndex++)
  {
    lcd.setCursor(0, messageIndex == numMessages - 1 ? 3 : messageIndex);
    String message = messages[messageIndex];

    for (byte letter = 0; letter < message.length(); letter++)
    {
      lcd.print(message[letter]);
      delay(50);
    }
  }

  delay(500);
}

void setup()
{
  lcdManager.init();
  displayWelcome();
  displayMenuPage(0, '\0');
  /*pageManager.displayCurrentPage(lcdManager.getLCD(), '\0');*/
}

void loop()
{
  handleKeypad();
}
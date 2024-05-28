#include <Arduino.h>
#include "./Utils/KeypadHandler.h"
#include "GlobalDeclarations.h"
// #include "./Thermocycler/Thermocycler.h"
// #include "./Thermocycler/ThermocyclerArray.h"

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
      lcd.printLetter(message[letter]);
      delay(50);
    }
  }

  delay(500);
}

void setup()
{
  lcd.begin();
  displayWelcome();
  displayMenuPage();
}

void loop()
{
  handleKeypad();
}
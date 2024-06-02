#include <Arduino.h>
#include "GlobalDeclarations.h"
#include "./Controller/KeypadHandler.h"
#include "./Pages/RunExperimentPage.h"

void displayWelcome()
{
  // Serial.begin(115200);
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
  // Initialize and add thermocyclers
  pageManager.ThermocyclerInitialTemp = 93.00;

  Thermocycler tc1;
  tc1.setProgName("CAB");
  tc1.setHeatedLid(110.0);
  tc1.setFinalHoldTemp(72.0);
  tc1.setNumCycles(2);
  tc1.setStep(0, Step::INITIAL, 95.0, 2);
  tc1.setStep(1, Step::DENATURATION, 94.0, 2);
  tc1.setStep(2, Step::ANNEALING, 95.0, 2);
  tc1.setStep(3, Step::EXTENDING, 94.0, 2);
  tc1.setStep(4, Step::FINAL, 95.0, 2);
  thermocyclerArray.addElement(0, tc1);

  Thermocycler tc2;
  // tc2.setProgName("Program2");
  thermocyclerArray.addElement(1, tc2);
  Thermocycler tc3;
  // tc3.setProgName("Program3");
  thermocyclerArray.addElement(2, tc3);

  lcd.begin();
  // displayWelcome();

  /* Debugging purposes */
  // lcd.clear();
  // lcd.printWord(thermocyclerArray.getElement(0).getProgName());
  // delay(1000);
  displayMenuPage();
}

void loop()
{
  switch (pageManager.getPageState())
  {
  case PageManager::RUN_EXPERIMENT_RUN:
    displayRunExperiment();
    break;
  default:
    handleKeypad();
    break;
  }
}
#include <Arduino.h>
#include "GlobalDeclarations.h"
#include "./Controller/KeypadHandler.h"
#include "./Pages/RunExperimentPage.h"
#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;               // CS pin for SD card module
unsigned long previousMillisLogging = 0; // Stores the last time the data was logged
const long interval = 1000;              // Interval at which to log data (milliseconds)

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
  Serial.begin(115200);
  // Initialize and add thermocyclers
  pageManager.ThermocyclerInitialTemp = 92.00;

  Thermocycler tc1;
  tc1.setProgName("CAB");
  tc1.setHeatedLid(110.0);
  tc1.setFinalHoldTemp(90.0);
  tc1.setNumCycles(1);
  tc1.setStep(0, Step::INITIAL, 95.0, 2);
  tc1.setStep(1, Step::DENATURATION, 93.0, 2);
  tc1.setStep(2, Step::ANNEALING, 95.0, 2);
  tc1.setStep(3, Step::EXTENDING, 93.0, 2);
  tc1.setStep(4, Step::FINAL, 96.0, 10);
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

  // Initialize the SD card
  // if (!SD.begin(chipSelect))
  // {
  //   lcd.printWord("Card failed, or not present");
  //   return;
  //   // don't do anything more:
  // }
  // else
  // {
  //   lcd.printWord("card initialized.");
  // }
  // lcd.delay(2000);
  // lcd.clear();

  displayMenuPage();
}

void loop()
{
  switch (pageManager.getPageState())
  {
  case PageManager::RUN_EXPERIMENT_RUN:
    // Data logging every 1s (separate millis)
    // File dataFile = SD.open("datalog.txt", FILE_WRITE);
    // unsigned long currentMillisLogging = millis();
    // if (currentMillisLogging - previousMillisLogging >= interval)
    // {
    //   if (dataFile)
    //   {
    //     dataFile.println(pageManager.currentBlockTempReading);
    //     dataFile.close();
    //   }
    // }

    displayRunExperiment();

    break;
  default:
    handleKeypad();
    break;
  }
}
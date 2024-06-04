#include <Arduino.h>
#include "GlobalDeclarations.h"
#include "./Controller/KeypadHandler.h"
#include "./Pages/RunExperimentPage.h"

// PID
#include "./Thermocycler/PID_v1.h"

/*
myPID(&currentBlockTempReading, &blockPWMOutput, &currentTargetSetpoint, PLATE_PID_INC_NORM_P, PLATE_PID_INC_NORM_I, PLATE_PID_INC_NORM_D, DIRECT)

PID::SetTunings(double Kp, double Ki, double Kd)
Loop -> PID::Compute()
PID::SetMode(int Mode)
PID::SetControllerDirection(int Direction)
*/

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

  /* Set pins for block thermistor */
  pinMode(A0, INPUT);

  // PID params initialization
  // double kP = 0;
  // double kI = 0;
  // double kD = 0;
  pageManager.currentBlockTempReading = analogRead(A0);
  pageManager.getMyPID().SetMode(AUTOMATIC);
  // SET PID constants BELOW <- programmer input
  // pageManager.getMyPID().SetTunings(kP,kI,kD);

  /* Set pins for Peltier */
  pinMode(5, OUTPUT); // INA, peltier
  pinMode(6, OUTPUT); // INB, peltier

  digitalWrite(5, 0);
  digitalWrite(6, 0);

  /* Set pins for heater */
  pinMode(10, OUTPUT); // heater
  digitalWrite(10, 0);

  // Initialize and add thermocyclers classes
  Thermocycler tc1;
  tc1.setProgName("CAB");
  tc1.setHeatedLid(110.0);
  tc1.setFinalHoldTemp(72.0);
  tc1.setNumCycles(2);
  tc1.setStep(0, Step::INITIAL, 95.0, 2);
  tc1.setStep(1, Step::DENATURATION, 95.0, 2);
  tc1.setStep(2, Step::ANNEALING, 55.0, 2);
  tc1.setStep(3, Step::EXTENDING, 72.0, 2);
  tc1.setStep(4, Step::FINAL, 85.0, 2);
  thermocyclerArray.addElement(0, tc1);
  Thermocycler tc2;
  thermocyclerArray.addElement(1, tc2);
  Thermocycler tc3;
  thermocyclerArray.addElement(2, tc3);

  // Display
  lcd.begin();
  // displayWelcome();
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
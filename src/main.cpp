#include <Arduino.h>
#include "GlobalDeclarations.h"
#include "./Controller/KeypadHandler.h"
#include "./Pages/RunExperimentPage.h"

// PID
// #include "./Thermocycler/PID_v1.h"
#include "./Thermocycler/ThermocyclerOperation.h"
/*
myPID(&currentBlockTempReading, &blockPWMOutput, &currentTargetSetpoint, PLATE_PID_INC_NORM_P, PLATE_PID_INC_NORM_I, PLATE_PID_INC_NORM_D, DIRECT)

PID::SetTunings(double Kp, double Ki, double Kd)
Loop -> PID::Compute()
PID::SetMode(int Mode)
PID::SetControllerDirection(int Direction)
*/

// double Setpoint, Input, Output, Kp, Ki, Kd;
// PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

unsigned long currentTime;
unsigned long previousTime = 0;

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
  // Serial.begin(115200);
  lcd.begin();

  /* Set pins for block thermistor */
  pinMode(A0, INPUT);

  // PID params initialization
  double kP = 100;
  double kI = 10;
  double kD = 40;
  pageManager.currentBlockTempReading = 0;
  pageManager.setPIDMode(AUTOMATIC);
  // pageManager.getMyPID();
  // SET PID constants BELOW <- programmer input
  pageManager.setPIDTunings(kP, kI, kD);

  /* Set pins for Peltier */
  pinMode(9, OUTPUT);  // INA, peltier
  pinMode(10, OUTPUT); // INB, peltier

  analogWrite(9, 0);
  analogWrite(10, 0);

  /* Set pins for heater */
  pinMode(11, OUTPUT); // heater
  digitalWrite(11, 0);

  // Initialize and add thermocyclers classes

  Thermocycler tc1;
  // tc1 = tc1.loadFromEEPROM(0);
  tc1.setProgName("CAB");
  tc1.setFinalHoldTemp(20.0);
  tc1.setNumCycles(2);
  tc1.setStep(0, Step::INITIAL, 100.0, 5);
  tc1.setStep(1, Step::DENATURATION, 100.0, 30);
  tc1.setStep(2, Step::ANNEALING, 200.0, 5);
  tc1.setStep(3, Step::EXTENDING, 300.0, 20);
  tc1.setStep(4, Step::FINAL, 400.0, 10);
  thermocyclerArray.addElement(0, tc1);

  Thermocycler tc2;
  // tc2.loadFromEEPROM(100);
  thermocyclerArray.addElement(1, tc2);
  Thermocycler tc3;
  // tc3.loadFromEEPROM(200);
  thermocyclerArray.addElement(2, tc3);

  // lcd.setCursor(0, 0);
  // lcd.printWord(String(sizeof(tc1)));
  // lcd.setCursor(0, 1);
  // lcd.printWord(String(sizeof(tc2)));
  // lcd.setCursor(0, 2);
  // lcd.printWord(String(sizeof(tc3)));
  // lcd.delay(3000);
  // lcd.clear();

  // Display
  displayWelcome();
  displayMenuPage();
}

// void foo()
// {
//   pageManager.currentBlockTempReading = ReadTemp();
//   displayRunExperiment();
// }

void loop()
{
  // pageManager.currentBlockTempReading = ReadTemp();
  // displayRunExperiment();

  // handleKeypad();
  switch (pageManager.getPageState())
  {
  case PageManager::RUN_EXPERIMENT_RUN:
    pageManager.currentBlockTempReading = ReadTemp();
    displayRunExperiment();
    // lcd.clear();

    break;
  default:
    handleKeypad();
    break;
  }
}

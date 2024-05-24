#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Wire.h>

/* DISPLAY */
LiquidCrystal_I2C lcd(0x27, 20, 4); // address, cols, rows

/* KEYPAD */
const byte KEYPAD_ROWS = 4; // four rows
const byte KEYPAD_COLS = 4; // four columns
// define the symbols on the buttons of the keypads
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'.', '0', '<', '>'}};
byte rowPins[KEYPAD_ROWS] = {11, 10, 9, 8}; // connect to the row pinouts of the keypad
byte colPins[KEYPAD_COLS] = {7, 6, 5, 4};   // connect to the column pinouts of the keypad
// initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

/* DEFINE GLOBALS */
enum State
{
  MENU,
  NEW_EXPERIMENT,
  SAVED_EXPERIMENT,
  RUN_EXPERIMENT,
  DEL_EXPERIMENT,
  EDIT_EXPERIMENT
};

String name = "";
String age = "";

// determine what screen in specific part of program
byte currentScreenIndex = 0;

// Experiment list
const String savedExperimentList[3] = {"AAA", "BAC", "CCC"};
byte numSavedExperiment = sizeof(savedExperimentList) / sizeof(savedExperimentList[0]);

/* INITIALIZATION */
State currentState = MENU;
char selectedKey = '\0';
String currentExperiment = "";

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

void displayMenu()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CARE-PCR");
  lcd.setCursor(15, 0);
  lcd.print("11:59");
  lcd.setCursor(0, 2);
  lcd.print("A-Add new experiment");
  lcd.setCursor(0, 3);
  lcd.print("B-Saved experiment");
}

void returnHomeScreen()
{
  currentState = MENU;
  currentScreenIndex = 0;
  lcd.clear();
  delay(500);
  displayMenu();
}

void displayNewExperiment(char key)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("New Experiment");

  switch (currentScreenIndex)
  {
  case 0:
    lcd.setCursor(2, 2);
    lcd.print("Name: ");
    if (key != '\0' && key != '<' && key != '>')
    {
      name += key;
    }
    lcd.setCursor(8, 2);
    lcd.print(name);
    break;
  case 1:
    lcd.setCursor(2, 2);
    lcd.print("Saved experiments");
    lcd.setCursor(4, 3);
    lcd.print("are full");
    break;
  default:
    returnHomeScreen();
  }
}

void displaySavedExperiment(char key)
{
  const String choiceLetterList[3] = {"A-", "B-", "C-"};
  const String choiceOperationList[3] = {"Run", "Edit", "Delete"};

  lcd.clear();
  lcd.setCursor(0, 0);

  switch (currentScreenIndex)
  {
  case 0:
    lcd.print("Saved experiments");
    for (byte i = 0; i < numSavedExperiment; i++)
    {
      lcd.setCursor(2, i + 1);
      lcd.print(choiceLetterList[i]);
      lcd.print(savedExperimentList[i]);
    }
    break;

  case 1:
    lcd.print(currentExperiment);
    for (byte i = 0; i < 3; i++)
    {
      lcd.setCursor(2, i + 1);
      lcd.print(choiceLetterList[i]);
      lcd.print(choiceOperationList[i]);
    }
    break;

  default:
    returnHomeScreen();
  }
}

void displayRunExperiment(char key)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(currentExperiment);

  switch (currentScreenIndex)
  {
  case 0:
    lcd.setCursor(12, 0);
    lcd.print("hh:mm:ss");
    lcd.setCursor(0, 1);
    lcd.print("Temp:95degC");
    lcd.setCursor(0, 2);
    lcd.print("Rem cycle:28");
    lcd.setCursor(0, 3);
    lcd.print("STEP: 1 >> 30s");
    break;
  case 1:
    lcd.setCursor(0, 1);
    lcd.print("SUCCESSFUL!!");
    lcd.setCursor(0, 2);
    lcd.print("hh:mm:ss");
    lcd.setCursor(0, 3);
    lcd.print("A-Save B-Home");
    break;
  case 2:
    lcd.setCursor(0, 1);
    lcd.print("NOT SUCCESSFUL!!");
    lcd.setCursor(0, 2);
    lcd.print("hh:mm:ss");
    lcd.setCursor(0, 3);
    lcd.print("A-Save B-Home");
    break;
  }
}

void displayDelExperiment(char key)
{
  const String choiceLetterList[2] = {"A-", "B-"};
  const String choiceOperationList[2] = {"Yes", "No"};

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Delete ");
  lcd.print(currentExperiment);
  lcd.print("?");

  for (byte i = 0; i < 2; i++)
  {
    lcd.setCursor(2, i + 1);
    lcd.print(choiceLetterList[i]);
    lcd.print(choiceOperationList[i]);
  }
}

void displayEditExperiment(char key)
{
  const String editOperationList[6] = {"Heated Lid", "Initial Step", "Cycles", "Step 1", "Step 2", "Step 3"};
  const String editOperationParams[2] = {"C-XXX", "T-XXX"};
  byte numEditOperationList = sizeof(editOperationList) / sizeof(editOperationList[0]);
  byte numEditOperationParams = sizeof(editOperationParams) / sizeof(editOperationParams[0]);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(currentExperiment);
  lcd.print(" (C-TEMP T-TIME)");
  lcd.setCursor(2, 1);
  lcd.print(editOperationList[currentScreenIndex]);

  for (byte j = 0; j < numEditOperationParams; j++)
  {
    lcd.setCursor(4, j + 2);
    lcd.print(editOperationParams[j]);
  }
}

void handleNewExperimentSelection(char key)
{
  if (key == '>')
  {
    currentScreenIndex++;
    if (currentScreenIndex > 1)
      currentScreenIndex = 0; // Wrap around if needed
    displayNewExperiment('\0');
  }
  else if (key == '<')
  {
    if (currentScreenIndex == 0)
    {
      returnHomeScreen();
    }
    else
    {
      currentScreenIndex--;
      displayNewExperiment('\0');
    }
  }
  else
  {
    displayNewExperiment(key);
  }
}

void handleSavedExperimentSelection(char key)
{
  if (key == '<')
  {
    if (currentScreenIndex == 0)
    {
      returnHomeScreen();
    }
    else
    {
      currentScreenIndex--;
      displaySavedExperiment('\0');
    }
  }
  else
  {
    if (currentScreenIndex == 0)
    {
      if (key == 'A' || key == 'B' || key == 'C')
      {
        currentExperiment = savedExperimentList[key - 'A'];
        currentScreenIndex++;
        displaySavedExperiment('\0');
      }
    }
    else if (currentScreenIndex == 1)
    {
      if (key == 'A')
      {
        currentState = RUN_EXPERIMENT;
        currentScreenIndex = 0;
        displayRunExperiment('\0');
      }
      else if (key == 'B')
      {
        currentState = EDIT_EXPERIMENT;
        currentScreenIndex = 0;
        displayEditExperiment('\0');
        // Implement Edit logic here
      }
      else if (key == 'C')
      {
        // Implement Delete logic here
        currentState = DEL_EXPERIMENT;
        currentScreenIndex = 0;
        displayDelExperiment('\0');
      }
    }
  }
}

void handleRunExperimentSelection(char key)
{
  if (key == '>' && currentScreenIndex == 0)
  {
    currentScreenIndex++;
    displayRunExperiment('\0');
  }
  else if (key == '<')
  {
    if (currentScreenIndex == 0)
    {
      returnHomeScreen();
    }
    else
    {
      currentScreenIndex--;
      displayRunExperiment('\0');
    }
  }
  else
  {
    if (currentScreenIndex == 1 || currentScreenIndex == 2)
    {
      if (key == 'A')
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(currentExperiment);
        lcd.setCursor(0, 1);
        lcd.print("Data saved");
        lcd.setCursor(0, 2);
        lcd.print("successfully");
        delay(2000);
        returnHomeScreen();
      }
      else if (key == 'B')
      {
        returnHomeScreen();
      }
    }
    else
    {
      displayRunExperiment(key);
    }
  }
}

void handleDelExperimentSelection(char key)
{
  if (key == '>' || key == 'A')
  {
    // Add delete function in saved experiment list
    returnHomeScreen();
  }
  else if (key == '<')
  {
    // Go back to saved experiment option
    currentState = SAVED_EXPERIMENT;
    currentScreenIndex = 1;
    displaySavedExperiment('\0');
  }
  else
  {
    if (key == 'B')
    {
      // Go back to saved experiment list
      currentState = SAVED_EXPERIMENT;
      currentScreenIndex = 0;
      displaySavedExperiment('\0');
    }
  }
}

void handleEditExperimentSelection(char key)
{
  if (key == '>')
  {
    if (currentScreenIndex == 5)
    {
      returnHomeScreen();
    }
    else
    {
      currentScreenIndex++;
      displayEditExperiment('\0');
    }

    // currentScreenIndex++;
    // if (currentScreenIndex > 1) currentScreenIndex = 0; // Wrap around if needed
    // displayEditExperiment('\0');
  }
  else if (key == '<')
  {
    if (currentScreenIndex == 0)
    {
      returnHomeScreen();
    }
    else
    {
      currentScreenIndex--;
      displayEditExperiment('\0');
    }
  }
  // else {
  //   displayNewExperiment(key);
  // }
}

void handleMenuSelection(char key)
{
  switch (key)
  {
  case 'A':
    currentState = NEW_EXPERIMENT;
    currentScreenIndex = 0;
    displayNewExperiment('\0');
    break;
  case 'B':
    currentState = SAVED_EXPERIMENT;
    currentScreenIndex = 0;
    displaySavedExperiment('\0');
    break;
  }
}

/* CODE LOGIC */
void setup()
{
  lcd.begin(20, 4);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  displayWelcome();
  lcd.clear();
  displayMenu();
}

void loop()
{
  char customKey = customKeypad.getKey();
  if (customKey)
  {
    switch (currentState)
    {
    case MENU:
      handleMenuSelection(customKey);
      break;

    case NEW_EXPERIMENT:
      handleNewExperimentSelection(customKey);
      break;

    case SAVED_EXPERIMENT:
      handleSavedExperimentSelection(customKey);
      break;

    case RUN_EXPERIMENT:
      handleRunExperimentSelection(customKey);
      break;

    case DEL_EXPERIMENT:
      handleDelExperimentSelection(customKey);
      break;

    case EDIT_EXPERIMENT:
      handleEditExperimentSelection(customKey);
      break;
    }
  }
}

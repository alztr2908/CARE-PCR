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

/* CODE LOGIC */
void setup()
{
  lcd.begin(20, 4);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  displayWelcome();
  lcd.clear();
}

void loop()
{
}

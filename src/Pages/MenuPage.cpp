#include "MenuPage.h"
#include "utils.h"
#include "../GlobalDeclarations.h"

// Define constant strings in PROGMEM
const char welcomeMsg[] PROGMEM = "CARE-PCR";
const char timeMsg[] PROGMEM = "11:59";
const char optionAMsg[] PROGMEM = "A-Add new experiment";
const char optionBMsg[] PROGMEM = "B-Saved experiment";

void displayMenuPage(char key)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.printWord(rps(welcomeMsg));
    lcd.setCursor(15, 0);
    lcd.printWord(rps(timeMsg));
    lcd.setCursor(0, 2);
    lcd.printWord(rps(optionAMsg));
    lcd.setCursor(0, 3);
    lcd.printWord(rps(optionBMsg));
}

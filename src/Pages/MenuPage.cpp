#include "MenuPage.h"
#include "../GlobalDeclarations.h"

void displayMenuPage(char key)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.printWord("CARE-PCR");
    lcd.setCursor(15, 0);
    lcd.printWord("11:59");
    lcd.setCursor(0, 2);
    lcd.printWord("A-Add new experiment");
    lcd.setCursor(0, 3);
    lcd.printWord("B-Saved experiment");
}

#include "HomePage.h"

void displayHomePage(LiquidCrystal_I2C &lcd, int subpage, const char *name, bool editing, char key)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Home Page");

    lcd.setCursor(0, 1);
    lcd.print("Name: ");
    lcd.print(name);

    if (editing)
    {
        if (key)
        {
            char newName[21];
            strncpy(newName, name, sizeof(newName));
            size_t len = strlen(newName);
            if (key == '<' && len > 0)
            {
                newName[len - 1] = '\0'; // Handle backspace
            }
            else if (key != '<' && len < sizeof(newName) - 1)
            {
                newName[len] = key;
                newName[len + 1] = '\0';
            }
            strncpy((char *)name, newName, sizeof(newName));
        }
        lcd.setCursor(0, 2);
        lcd.print("Editing...");
    }
    else
    {
        lcd.setCursor(0, 2);
        lcd.print("A: Run B: Edit");
        lcd.setCursor(0, 3);
        lcd.print("C: Delete");

        if (key == 'B')
        {
            editing = true;
        }
        // else if (key == 'C')
        // {
        //     name[0] = '\0';
        // }
    }
}

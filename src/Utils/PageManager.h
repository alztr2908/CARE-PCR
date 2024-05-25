#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include <LiquidCrystal_I2C.h>

class PageManager
{
public:
    PageManager() : currentPage("home"), currentSubpage(0) {}

    void setPage(const char *page);
    void nextSubpage();
    void previousSubpage();
    void displayCurrentPage(LiquidCrystal_I2C &lcd);

private:
    const char *currentPage;
    int currentSubpage;
};

#endif

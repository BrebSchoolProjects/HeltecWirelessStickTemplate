#include "testLcd.h"
#include <Wire.h>
#include "SSD1306Wire.h"

SSD1306Wire display(0x3c, 4, 15, GEOMETRY_64_32);

static void setupLcd(void);
static void testLcd(void);

void oledTask(void *arguments) {
    setupLcd();

    while(1) {
        testLcd();
    }
}

// Adapted from Adafruit_SSD1306
static void drawLines()
{
    for (int16_t i = 0; i < display.getWidth(); i += 4)
    {
        display.drawLine(0, 0, i, display.getHeight() - 1);
        display.display();
        delay(10);
    }
    for (int16_t i = 0; i < display.getHeight(); i += 4)
    {
        display.drawLine(0, 0, display.getWidth() - 1, i);
        display.display();
        delay(10);
    }
    delay(250);

    display.clear();
    for (int16_t i = 0; i < display.getWidth(); i += 4)
    {
        display.drawLine(0, display.getHeight() - 1, i, 0);
        display.display();
        delay(10);
    }
    for (int16_t i = display.getHeight() - 1; i >= 0; i -= 4)
    {
        display.drawLine(0, display.getHeight() - 1, display.getWidth() - 1, i);
        display.display();
        delay(10);
    }
    delay(250);

    display.clear();
    for (int16_t i = display.getWidth() - 1; i >= 0; i -= 4)
    {
        display.drawLine(display.getWidth() - 1, display.getHeight() - 1, i, 0);
        display.display();
        delay(10);
    }
    for (int16_t i = display.getHeight() - 1; i >= 0; i -= 4)
    {
        display.drawLine(display.getWidth() - 1, display.getHeight() - 1, 0, i);
        display.display();
        delay(10);
    }
    delay(250);
    display.clear();
    for (int16_t i = 0; i < display.getHeight(); i += 4)
    {
        display.drawLine(display.getWidth() - 1, 0, 0, i);
        display.display();
        delay(10);
    }
    for (int16_t i = 0; i < display.getWidth(); i += 4)
    {
        display.drawLine(display.getWidth() - 1, 0, i, display.getHeight() - 1);
        display.display();
        delay(10);
    }
    delay(250);
}

// Adapted from Adafruit_SSD1306
static void drawRect(void)
{
    for (int16_t i = 0; i < display.getHeight() / 2; i += 2)
    {
        display.drawRect(i, i, display.getWidth() - 2 * i, display.getHeight() - 2 * i);
        display.display();
        delay(10);
    }
}

// Adapted from Adafruit_SSD1306
static void fillRect(void)
{
    uint8_t color = 1;
    for (int16_t i = 0; i < display.getHeight() / 2; i += 3)
    {
        display.setColor((color % 2 == 0) ? BLACK : WHITE); // alternate colors
        display.fillRect(i, i, display.getWidth() - i * 2, display.getHeight() - i * 2);
        display.display();
        delay(10);
        color++;
    }
    // Reset back to WHITE
    display.setColor(WHITE);
}

// Adapted from Adafruit_SSD1306
static void drawCircle(void)
{
    for (int16_t i = 0; i < display.getHeight(); i += 2)
    {
        display.drawCircle(display.getWidth() / 2, display.getHeight() / 2, i);
        display.display();
        delay(10);
    }
    delay(1000);
    display.clear();

    // This will draw the part of the circel in quadrant 1
    // Quadrants are numberd like this:
    //   0010 | 0001
    //  ------|-----
    //   0100 | 1000
    //
    display.drawCircleQuads(display.getWidth() / 2, display.getHeight() / 2, display.getHeight() / 4, 0b00000001);
    display.display();
    delay(200);
    display.drawCircleQuads(display.getWidth() / 2, display.getHeight() / 2, display.getHeight() / 4, 0b00000011);
    display.display();
    delay(200);
    display.drawCircleQuads(display.getWidth() / 2, display.getHeight() / 2, display.getHeight() / 4, 0b00000111);
    display.display();
    delay(200);
    display.drawCircleQuads(display.getWidth() / 2, display.getHeight() / 2, display.getHeight() / 4, 0b00001111);
    display.display();
}

static void printBuffer(void)
{
    // Initialize the log buffer
    // allocate memory to store 8 lines of text and 30 chars per line.
    display.setLogBuffer(5, 30);

    // Some test data
    const char *test[] = {
        "Hello",
        "World",
        "----",
        "Show",
        "how",
        "the log buffer",
        "is",
        "working.",
        "Even",
        "scrolling is",
        "working"};

    for (uint8_t i = 0; i < 11; i++)
    {
        display.clear();
        // Print to the screen
        display.println(test[i]);
        // Draw it to the internal screen buffer
        display.drawLogBuffer(0, 0);
        // Display it on the screen
        display.display();
        delay(500);
    }
}

static void setupLcd(void)
{

    pinMode(16, OUTPUT);
    digitalWrite(16, LOW);
    delay(50);
    digitalWrite(16, HIGH);
    delay(50);

    display.init();
    display.flipScreenVertically();
}

static void testLcd(void)
{
 
    display.setContrast(255);

    drawLines();
    delay(1000);
    display.clear();

    drawRect();
    delay(1000);
    display.clear();

    fillRect();
    delay(1000);
    display.clear();

    drawCircle();
    delay(1000);
    display.clear();

    printBuffer();
    delay(1000);
    display.clear();
}

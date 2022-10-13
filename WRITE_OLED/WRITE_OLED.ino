#include<Wire.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>

#define SCREEN_ADDRESS 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4

Adafruit_SSD1306 my_display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
  if(!my_display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    for(;;);

  my_display.display();
  delay(1000);
  my_display.clearDisplay();
  delay(1000);
}

void loop()
{
  my_display.clearDisplay();
  my_display.setTextSize(1);
  my_display.setCursor(0, 0);
  my_display.setTextColor(WHITE);
  my_display.println("Hello World");
  my_display.println("i am deshrit");
  my_display.display();
  
  delay(2000);
}

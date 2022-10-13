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
  my_display.setTextColor(WHITE);
  my_display.setCursor(12, 0);
  my_display.println("DDA LINE ALGORITHM");
  my_display.display();
  
  int x1, y1, x2, y2;
  x1 = random(0, 30);
  y1 = random(20, 64);
  
  x2 = random(100, 128);
  y2 = random(20, 64);
  
  DDA(x1, y1, x2, y2);
  delay(1000);
}

void DDA(int x1, int y1, int x2, int y2)
{
  int dx, dy, steps;
  float x, y, xinc, yinc, m;

  dx = x2-x1;
  dy = y2-y1;

  m = ((float)dy)/((float)dx);
 
  xinc = 1;
  yinc = m;
  
  x = x1;
  y = y1;
  
  RENDER(round(x), round(y));

  while(x != x2) {
    x = x + xinc;
    y = y + yinc;
    RENDER(round(x), round(y));
  }
}

void RENDER(int x, int y)
{
  my_display.drawPixel(x, y, WHITE);
  my_display.display();
}

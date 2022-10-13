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
  my_display.setCursor(18, 0);
  my_display.println("MIDPOINT CIRCLE");
  my_display.display();
  
  // center a and b, radius r
  int a, b, r;
  a = random(40, 80);
  b = random(36, 48);
  r = random(8, 24);
  
  MIDPOINT_CIRCLE(a, b, r);
  delay(1000);
}

void MIDPOINT_CIRCLE(int a, int b, int r)
{
  int x, y;
  float p;

  x = 0;
  y = r;

  RENDER(a, b-r);
  RENDER(a, b+r);
  RENDER(a-r, b);
  RENDER(a+r, b);
  
  p = (5/4) - r;
  while(x <= y) {
    x++;
    if(p < 0) {
      p = p + 2*x + 3;
    }
    else {
      p = p + 2*x - 2*y + 5;
      y--;
    }

    RENDER(a+x, b+y);
    RENDER(a-x, b+y);

    RENDER(a+x, b-y);
    RENDER(a-x, b-y);

    RENDER(a+y, b+x);
    RENDER(a-y, b+x);

    RENDER(a+y, b-x);
    RENDER(a-y, b-x);
  }
}

void RENDER(int x, int y)
{
  my_display.drawPixel(x, y, WHITE);
  my_display.display();
}

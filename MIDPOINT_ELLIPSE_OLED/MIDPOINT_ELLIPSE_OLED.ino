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
  my_display.println("MIDPOINT ELLIPSE");
  my_display.display();
  
  // center a and b, radii r1 and r2
  int a, b, rx, ry;
  a = 32; b = 40;
  rx = 24; ry = 8;
 
  MIDPOINT_ELLIPSE(a, b, rx, ry);
  delay(1000);
}

void MIDPOINT_ELLIPSE(int a, int b, int rx, int ry)
{
  int x = 0, y = ry;
  float p1, p2, dx, dy;

  RENDER(a, b-y);
  RENDER(a, b+y);

  // Region one
  p1 = ry*ry + (rx*rx)/4 - ry*rx*rx;
  while((2*x*ry*ry) <= (2*y*rx*rx)) {
    x++;
    if(p1 <0) {
      p1 = p1 + ry*ry*(2*x + 1);
    }
    else {
      y--;
      p1 = p1 + 2*x*ry*ry + ry*ry - 2*y*rx*rx;
    }
    RENDER(a+x, b+y);
    RENDER(a+x, b-y);
    RENDER(a-x, b+y);
    RENDER(a-x, b-y);
  }

  // Region two
  p2 = ((ry*ry)*(x + 0.5)*(x+0.5))+ ((rx*rx)*(y - 1)*(y-1)) - (rx*rx*ry*ry);
  while(y > 0) {
    y--;
    if(p2 < 0) {
      x++;
      p2 = p2 + (2*ry*ry*x) - (2*y*rx*rx) + (rx*rx);
    }
    else {
      p2 = p2 - (2*y*rx*rx) + rx*rx;
    }
    
    RENDER(a+x, b+y);
    RENDER(a+x, b-y);
    RENDER(a-x, b+y);
    RENDER(a-x, b-y);
  }
}

void RENDER(int x, int y)
{
  my_display.drawPixel(x, y, WHITE);
  my_display.display();
}

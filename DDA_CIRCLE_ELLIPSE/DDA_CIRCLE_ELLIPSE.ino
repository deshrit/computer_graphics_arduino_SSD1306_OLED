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
  /// LINE
  INFO("DDA LINE");
  
  int x1, y1, x2, y2;
  x1 = random(0, 30);
  y1 = random(20, 64);
  
  x2 = random(100, 128);
  y2 = random(20, 64);
  
  DDA(x1, y1, x2, y2);
  delay(1000);


  /// CIRCLE
  INFO("MIDPOINT CIRCLE");
  
  // center a and b, radius r
  int a, b, r;
  a = random(40, 80);
  b = random(36, 48);
  r = random(8, 24);
  
  MIDPOINT_CIRCLE(a, b, r);
  delay(1000);


  /// ELLIPSE 
  INFO("MIDPOINT ELLIPSE");
  
  // center a and b, radii r1 and r2
  int rx, ry;
  a = random(26, 78);
  b = random(28, 54);
  rx = 24; ry = 8;
 
  MIDPOINT_ELLIPSE(a, b, rx, ry);
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

void INFO(const char* topic)
{
  my_display.clearDisplay();
  my_display.setTextSize(1);
  my_display.setTextColor(WHITE);
  my_display.setCursor(10, 0);
  my_display.println(topic);
  my_display.display();
}

void RENDER(int x, int y)
{
  my_display.drawPixel(x, y, WHITE);
  my_display.display();
}

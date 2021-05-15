#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define DISPLAY_PIN 8

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 128

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, DISPLAY_PIN, NEO_GRB + NEO_KHZ800);

int yOffset;
int xOffset;
bool maskX;
bool maskY;
int maskXMin;
int maskXMax;
int maskYMin;
int maskYMax;

void setup()
{
  pixels.begin(); // This initializes the NeoPixel library.
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
}

bool button_pressed[4];
bool button_downEvent[4];
bool button_upEvent[4];

int gameNr = 0;
byte resetCounter;
bool gameReset;

void loop()
{
  pixels.clear();
  xOffset = 0;
  yOffset = 0;

  readButton(0, 2);
  readButton(1, 3);
  readButton(2, 6);
  readButton(3, 7);

  if (button_pressed[0] && button_pressed[1] && button_pressed[2] && button_pressed[3])
  {
    resetCounter++;
    if (resetCounter == 20)
    {
      //Black screen warning
      pixels.show();
      delay(1000);
      readButton(0, 2);
      readButton(1, 3);
      readButton(2, 6);
      readButton(3, 7);
      if (button_pressed[0] && button_pressed[1] && button_pressed[2] && button_pressed[3])
      {
        gameNr = 0;
      }
    }
  }

  if (gameNr == 0)
    menu_update();
  else if (gameNr == 1)
    racer_gameUpdate();
  else if (gameNr == 2)
    pong_gameUpdate();
  else if (gameNr == 3)
    Andreas_gameUpdate();
  else if (gameNr == 4)
    beer_gameUpdate();

  // Tests Button Inputs of all buttons (isDown, pressed, released)
  /*testButton(0, 1, 2, 0, pixels.Color(150, 0, 0));
  testButton(15, 14, 13, 1, pixels.Color(150, 150, 0));
  testButton(16, 17, 18, 2, pixels.Color(0, 150, 0));
  testButton(31, 30, 29, 3, pixels.Color(0, 0, 150));
*/

  pixels.show(); // This sends the updated pixel color to the hardware.
  //delay(200);
}

void testButton(int LED_pressed, int LED_down, int LED_up, int buttonId, uint32_t color)
{

  if (button_pressed[buttonId])
  {
    pixels.setPixelColor(LED_pressed, color);
  }

  if (button_upEvent[buttonId])
  {
    pixels.setPixelColor(LED_up, color);
  }

  if (button_downEvent[buttonId])
  {
    pixels.setPixelColor(LED_down, color);
  }
}

void readButton(int buttonID, int pin)
{
  digitalWrite(pin, HIGH);
  bool wasPressed = button_pressed[buttonID];
  button_pressed[buttonID] = digitalRead(pin) != HIGH;
  button_upEvent[buttonID] = wasPressed && !button_pressed[buttonID];
  button_downEvent[buttonID] = !wasPressed && button_pressed[buttonID];
}

void ShowPixel(int X, int Y, uint32_t color)
{
  Y = Y + yOffset;
  X = X + xOffset;
/*
  Y = 15-Y;
  X = 7-X;
*/

  if (maskX && (X < maskXMin || X > maskXMax))
    return;
  if (maskY && (Y < maskYMin || Y > maskYMax))
    return;

  int pixelPos = 0;

  if (Y % 2 == 0) // EVEN
  {
    pixelPos = Y * 8 + X;
    Serial.print(pixelPos);
  }
  else
  {
    pixelPos = Y * 8 - (X + 1) + 8;
  }

  pixels.setPixelColor(pixelPos, color); // Moderately bright green color.
}

void draw5x4Number(int nr, int x, int y, uint32_t color)
{
  yOffset += y;
  xOffset += x;

  if (nr == 0)
  {
    ShowPixel(0, 1, color);
    ShowPixel(0, 2, color);
    ShowPixel(0, 3, color);
    ShowPixel(3, 1, color);
    ShowPixel(3, 2, color);
    ShowPixel(3, 3, color);
    ShowPixel(1, 0, color);
    ShowPixel(2, 0, color);
    ShowPixel(1, 4, color);
    ShowPixel(2, 4, color);
  }
  else if (nr == 1)
  {
    ShowPixel(2, 0, color);
    ShowPixel(2, 1, color);
    ShowPixel(2, 2, color);
    ShowPixel(2, 3, color);
    ShowPixel(2, 4, color);
    ShowPixel(1, 3, color);
    ShowPixel(0, 2, color);
  }else if (nr == 2)
  {
    ShowPixel(1, 0, color);
    ShowPixel(2, 0, color);
    ShowPixel(0, 1, color);
    ShowPixel(1, 2, color);
    ShowPixel(2, 2, color);
    ShowPixel(3, 3, color);
    ShowPixel(2, 4, color);
    ShowPixel(1, 4, color);
    ShowPixel(0, 4, color);
  }else if (nr == 3)
  {
    ShowPixel(0, 0, color);
    ShowPixel(1, 0, color);
    ShowPixel(2, 1, color);
    ShowPixel(1, 2, color);
    ShowPixel(2, 3, color);
    ShowPixel(1, 4, color);
    ShowPixel(0, 4, color);
  }else if (nr == 4)
  {
    ShowPixel(2, 0, color);
    ShowPixel(2, 1, color);
    ShowPixel(2, 2, color);
    ShowPixel(2, 3, color);
    ShowPixel(2, 4, color);
    ShowPixel(3, 2, color);
    ShowPixel(1, 2, color);
    ShowPixel(0, 2, color);
    ShowPixel(1, 3, color);
  }else if (nr == 5)
  {
    ShowPixel(0, 0, color);
    ShowPixel(1, 0, color);
    ShowPixel(2, 1, color);
    ShowPixel(1, 2, color);
    ShowPixel(0, 2, color);
    ShowPixel(0, 3, color);
    ShowPixel(0, 4, color);
    ShowPixel(1, 4, color);
    ShowPixel(2, 4, color);
  }else if (nr == 6)
  {
    ShowPixel(1, 0, color);
    ShowPixel(2, 0, color);
    ShowPixel(3, 1, color);
    ShowPixel(2, 2, color);
    ShowPixel(1, 1, color);
    ShowPixel(1, 2, color);
    ShowPixel(1, 3, color);
    ShowPixel(2, 4, color);
  }else if (nr == 7)
  {
    ShowPixel(1, 0, color);
    ShowPixel(1, 1, color);
    ShowPixel(1, 2, color);
    ShowPixel(2, 3, color);
    ShowPixel(2, 4, color);
    ShowPixel(1, 4, color);
    ShowPixel(0, 4, color);
  }else if (nr == 8)
  {
    ShowPixel(1, 0, color);
    ShowPixel(2, 0, color);
    ShowPixel(0, 1, color);
    ShowPixel(3, 1, color);
    ShowPixel(1, 2, color);
    ShowPixel(2, 2, color);
    ShowPixel(0, 3, color);
    ShowPixel(3, 3, color);
    ShowPixel(1, 4, color);
    ShowPixel(2, 4, color);
  }else if (nr == 9)
  {
    ShowPixel(1, 0, color);
    ShowPixel(2, 1, color);
    ShowPixel(1, 2, color);
    ShowPixel(2, 2, color);
    ShowPixel(0, 3, color);
    ShowPixel(2, 3, color);
    ShowPixel(1, 4, color);
    ShowPixel(2, 4, color);
  }

  yOffset -= y;
  xOffset -= x;
}

// interactive logic

void Andreas_loop()
{

  randomSeed(analogRead(0));

  Andreas_gameUpdate();
}

// input buttons
int RED = 0;
int YELLOW = 1;
int GREEN = 2;
int BLUE = 3;

// character data
int characterPosX = 4;
int characterPosY = 0;

// particle data
int ashParticlesX[8];
int ashParticlesY[8] = { -1, -1, -1, -1, -1, -1, -1, -1};
int ashParticlesYState[8] = { -1, -1, -1, -1, -1, -1, -1, -1};

// frame control
int seedOverTime = 0;
int skipFrameCount = 0;

// graphic aliases
const int COLOR_RED = 0;
const int COLOR_GREEN = 1;
const int COLOR_BLUE = 2;
const int COLOR_YELLOW = 3;
const int COLOR_ORANGE = 4;
const int COLOR_PURPLE = 5;
const int COLOR_CYAN = 6;
const int COLOR_WHITE = 7;
const int COLOR_BLACK = 8;

void Andreas_gameUpdate()
{


  Andreas_DrawSky();
  Andreas_DisplayCharacter();
  Andreas_Particles(skipFrameCount == 29);


  if (button_downEvent[GREEN])
  {
    characterPosX++;
    if (characterPosX > 8)
      characterPosX = 8;
  }

  if (button_downEvent[BLUE])
  {
    characterPosX--;
    if (characterPosX < 0)
      characterPosX = 0;
  }

  if (button_downEvent[RED] && characterPosY == 0)
  {
    characterPosY += 3;
  }


  if (skipFrameCount < 30) {
    skipFrameCount++;
    return;
  }
  else {
    skipFrameCount = 0;
  }

  if (characterPosY > 0)
    characterPosY--;


  seedOverTime++;

}

// In-game draw logic
void Andreas_Draw()
{
}

void Andreas_DrawSky()
{
  for (int y = 0; y < 16; y++)
  {
    for (int x = 0; x < 8; x++)
    {
      Andreas_ShowPixel(x, y, Andreas_getColor(COLOR_BLUE, 62 - (y * 4)));
    }
  }
}


void Andreas_Particles(bool action) {

  int rand = random(300);

  if (rand == 1) {
    int randPos = random(8);
    if (ashParticlesY[randPos] == -1) {
      ashParticlesY[randPos] = 15;
      ashParticlesX[randPos] = randPos;
      ashParticlesYState[randPos] = 5;
    }
  }

  for (int i = 0; i < 8; i++) {

    if (ashParticlesX[i] == characterPosX)
      if (ashParticlesY[i] == characterPosY || ashParticlesY[i] == characterPosY +1) {
        ashParticlesY[i] = -1;
        continue;
      }


    if (action && ashParticlesY[i] != -1) {

      if (ashParticlesYState[i] > 0)
        ashParticlesYState[i]--;
      else
      {
        ashParticlesYState[i] = 5;
        ashParticlesY[i]--;
      }
    }
    Andreas_ShowPixel(ashParticlesX[i], ashParticlesY[i], Andreas_getColor(COLOR_ORANGE, 100));
  }
}

void Andreas_DisplayCharacter()
{

  Andreas_ShowPixel(characterPosX, characterPosY, Andreas_getColor(COLOR_PURPLE, 100));
  Andreas_ShowPixel(characterPosX, characterPosY + 1, Andreas_getColor(COLOR_PURPLE, 100));
}

// Graphic functions


uint32_t Andreas_getColor(int colorID, int intensity)
{

  uint32_t color = 0;

  int R = 0;
  int G = 0;
  int B = 0;

  switch (colorID)
  {
    case COLOR_RED:
      R = 255;
      break;
    case COLOR_GREEN:
      G = 255;
      break;
    case COLOR_BLUE:
      B = 255;
      break;
    case COLOR_YELLOW:
      R = 255;
      B = 255;
      break;
    case COLOR_ORANGE:
      R = 255;
      G = 64;
      break;
    case COLOR_PURPLE:
      R = 255;
      B = 255;
      break;
    case COLOR_CYAN:
      G = 255;
      B = 255;
      break;
    case COLOR_WHITE:
      R = 255;
      G = 255;
      B = 255;
    case COLOR_BLACK:
      break;
  }
  return pixels.Color(R * intensity / 100, G * intensity / 100, B * intensity / 100);
}

// show a pixel : ShowPixel(X, Y, getColor(COLOR_X, INTENSITY 0 to 100 ));
void Andreas_ShowPixel(int X, int Y, uint32_t color)
{

  int pixelPos = 0;

  if (Y % 2 == 0) // EVEN
  {
    pixelPos = Y * 8 + X;
  }
  else
  {
    pixelPos = Y * 8 - (X + 1) + 8;
  }

  pixels.setPixelColor(pixelPos, color); // Moderately bright green color.
}

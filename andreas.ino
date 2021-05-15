
int ashParticles[8][16];

const int COLOR_RED = 0;
const int COLOR_GREEN = 1;
const int COLOR_BLUE = 2;
const int COLOR_YELLOW = 3;
const int COLOR_ORANGE = 4;
const int COLOR_PURPLE = 5;
const int COLOR_CYAN = 6;
const int COLOR_WHITE = 7;
const int COLOR_BLACK = 8;
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

int RED = 0;
int YELLOW = 1;
int GREEN = 2;
int BLUE = 3;

void Andreas_loop()
{

    randomSeed(analogRead(0));

    Andreas_gameUpdate();
}

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

int characterPosX = 4;
int characterPosY = 0;

int seedOverTime = 0;

int skipFrameCount = 0;
// show a pixel : ShowPixel(X, Y, getColor(COLOR_X, INTENSITY 0 to 100 ));
void Andreas_gameUpdate()
{

        Andreas_Draw();

    if(skipFrameCount < 30){
        skipFrameCount++;
        return;
    }
    else{
        skipFrameCount = 0;
    }


    seedOverTime++;

    Andreas_MakeAshRain();


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

    if (button_downEvent[RED])
    {
        characterPosY += 3;
    }
    else if (characterPosY > 0)
        characterPosY--;
}
void Andreas_Draw()
{

    Andreas_DrawSky();
    Andreas_DrawParticles();
    Andreas_DisplayCharacter();
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

void Andreas_MakeAshRain()
{

    for (int x = 0; x < 8; x++)
    {
        int randNumber = random(1000);
        if (randNumber == 1)
        {
            ashParticles[x][15] = 1;
        }
    }

    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if (ashParticles[x][y] == 1)
            {
                ashParticles[x][y] = 0;
                ashParticles[x][y - 1] = 1;
            }
        }
    }
}

void Andreas_DrawParticles()
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 8; x++)
        {

            if (ashParticles[x][y] == 1)
                Andreas_ShowPixel(x, y, Andreas_getColor(COLOR_ORANGE, 70));
        }
    }
}

void Andreas_DisplayCharacter()
{

    Andreas_ShowPixel(characterPosX, characterPosY, Andreas_getColor(COLOR_PURPLE, 100));
    Andreas_ShowPixel(characterPosX, characterPosY + 1, Andreas_getColor(COLOR_PURPLE, 100));
}

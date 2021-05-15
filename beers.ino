
byte aimX;
byte aimY;
int beer_decrease;
byte beer_enemyX[5] = {3, 7, 5, 12, 15};
byte beer_enemyY[5] = {2, 4, 3, 5, 3};

void beer_reset()
{
    //Reset game variables
    beer_decrease = 0;
    aimX = 0;
    aimY = 5;
}

void beer_gameUpdate()
{
    if (gameReset)
    {
        beer_reset();
        gameReset = false;
    }
    beer_handleInput();
    beer_draw();
}

void beer_draw()
{
    uint32_t wood = pixels.Color(18, 13, 1);   // wood brown
    uint32_t green = pixels.Color(10, 14, 4);  // wood brown
    uint32_t ground = pixels.Color(3, 3, 0);   // wood brown
    uint32_t sky = pixels.Color(0, 3, 3);      // wood brown
    uint32_t aimColor = pixels.Color(0, 0, 0); // wood brown
    uint32_t enemyColor = pixels.Color(180, 130, 1);

    byte xStart = aimX - 4;
    for (byte xT = 0; xT < 8; xT++)
    {
        for (byte y = 0; y < 6; y++)
        {
            ShowPixel(xT, y, ground);
        }
        for (byte y = 6; y < 16; y++)
        {
            ShowPixel(xT, y, sky);
        }

        byte x = (xT + xStart) % 16;

        if (x >= 0 && x <= 5 || (x >= 9 && x <= 11))
        {
            //Draw green
            ShowPixel(xT, 11, green);
            ShowPixel(xT, 12, green);
        }
        if (x >= 1 && x <= 4)
        {
            //Draw green
            ShowPixel(xT, 10, green);
            ShowPixel(xT, 13, green);
        }
        if (x >= 9 && x <= 11)
        {
            //Draw green
            ShowPixel(xT, 10, green);
        }
        if (x >= 5 && x <= 8 || (x >= 12 && x <= 15))
        {
            //Draw green
            ShowPixel(xT, 7, green);
        }
        if (x >= 6 && x <= 7 || (x >= 13 && x <= 14))
        {
            //Draw green
            ShowPixel(xT, 8, green);
            ShowPixel(xT, 6, green);
        }
        if (x >= 2 && x <= 3 || (x == 10))
        {
            //Draw wood
            ShowPixel(xT, 9, wood);
            ShowPixel(xT, 8, wood);
            ShowPixel(xT, 7, wood);
            ShowPixel(xT, 6, wood);
        }
        if (x >= 1 && x <= 4)
        {
            //Draw wood
            ShowPixel(xT, 5, wood);
        }
    }
/*
    for (byte enemy = 0; enemy < 5; enemy++)
    {
        byte enemyStartX = beer_enemyX[enemy];
        for (byte xD = 0; xD < 3; xD++)
        {
            byte curX = ((enemyStartX + xD)-aimX) % 16;
            if (curX >= 0 && curX <= 7)
            {
                //OnScreen
                if (xD == 0)
                {
                    ShowPixel(curX, beer_enemyY[enemy], enemyColor);
                    ShowPixel(curX, beer_enemyY[enemy] + 4, enemyColor);
                }
                else if (xD == 1)
                {
                    ShowPixel(curX, beer_enemyY[enemy], enemyColor);
                    ShowPixel(curX, beer_enemyY[enemy] + 1, enemyColor);
                    ShowPixel(curX, beer_enemyY[enemy] + 2, enemyColor);
                    ShowPixel(curX, beer_enemyY[enemy] + 3, enemyColor);
                    ShowPixel(curX, beer_enemyY[enemy] + 4, enemyColor);
                }
                else if (xD == 2)
                {
                    ShowPixel(curX, beer_enemyY[enemy] + 1, enemyColor);
                    ShowPixel(curX, beer_enemyY[enemy] + 2, enemyColor);
                }
            }
        }
    }
*/
    ShowPixel(4, aimY, aimColor);
    /*
    ShowPixel(3, aimY, aimColor);
    ShowPixel(4, aimY+1, aimColor);
    ShowPixel(4, aimY-1, aimColor);
    ShowPixel(5, aimY, aimColor);*/
}

void beer_handleInput()
{
    beer_decrease++;
    if (beer_decrease >= 100)
    {
        beer_decrease = 0;
        if (aimY > 3)
            aimY--;
    }
    if (button_downEvent[0])
    {
        aimX++;
    }
    if (button_downEvent[1])
    {
        aimX--;
    }
    if (aimY < 13 && button_downEvent[2])
    {
        aimY++;
    }
}

int menu_gameChoice;
int menu_blink;
void menu_update()
{

    if (menu_gameChoice == 0)
        menu_gameChoice = 1;

    yOffset = -4;
    maskY = true;
    maskYMax = 7;
    maskYMin = 0;
    if(menu_gameChoice == 1)
        racer_draw();
    else if(menu_gameChoice == 2)
        pong_draw();
    else if(menu_gameChoice == 3)
        Andreas_Draw();
    else if(menu_gameChoice == 4)
        beer_draw();
    maskY = false;
    yOffset = 0;

    drawJayOs();

    menu_blink++;
    if (menu_blink > 300)
        menu_blink = 0;

    if (menu_blink > 200)
    {
        drawMenuOverlay();
    }

    int maxGameNr = 4;
    if (button_downEvent[0])
    {
        menu_blink = 0;
        menu_gameChoice++;
        if (menu_gameChoice > maxGameNr)
            menu_gameChoice = 1;
    }

    if (button_downEvent[2])
    {
        menu_blink = 0;
        menu_gameChoice--;
        if (menu_gameChoice == 0)
            menu_gameChoice = maxGameNr;
    }

    if (button_downEvent[1])
    {
        gameNr = menu_gameChoice;
        gameReset = true;
    }
}

void drawMenuOverlay()
{

    uint32_t leftColor = pixels.Color(55, 148, 110);
    uint32_t playColor = pixels.Color(223, 113, 38);
    uint32_t rightColor = pixels.Color(172, 50, 50);
    uint32_t blackColor = pixels.Color(0, 0, 0);

    ShowPixel(0, 4, leftColor);
    ShowPixel(0, 3, leftColor);
    ShowPixel(1, 2, leftColor);
    ShowPixel(1, 5, leftColor);

    ShowPixel(0, 5, blackColor);
    ShowPixel(0, 2, blackColor);
    ShowPixel(2, 2, blackColor);
    ShowPixel(2, 5, blackColor);
    ShowPixel(2, 1, blackColor);
    ShowPixel(2, 6, blackColor);

    ShowPixel(3, 0, playColor);
    ShowPixel(3, 1, playColor);
    ShowPixel(4, 0, playColor);
    ShowPixel(4, 1, playColor);

    ShowPixel(2, 0, blackColor);
    ShowPixel(2, 1, blackColor);
    ShowPixel(3, 2, blackColor);
    ShowPixel(4, 2, blackColor);
    ShowPixel(5, 1, blackColor);
    ShowPixel(5, 0, blackColor);

    ShowPixel(7, 4, rightColor);
    ShowPixel(7, 3, rightColor);
    ShowPixel(6, 2, rightColor);
    ShowPixel(6, 5, rightColor);

    ShowPixel(7, 5, blackColor);
    ShowPixel(7, 2, blackColor);
    ShowPixel(5, 2, blackColor);
    ShowPixel(5, 5, blackColor);
    ShowPixel(5, 1, blackColor);
    ShowPixel(5, 6, blackColor);
}

void drawJayOs()
{

    uint32_t jColor = pixels.Color(55, 148, 110);
    uint32_t aColor = pixels.Color(223, 113, 38);
    uint32_t yColor = pixels.Color(172, 50, 50);
    uint32_t oColor = pixels.Color(5, 5, 5);
    uint32_t sColor = pixels.Color(10, 10, 10);

    ShowPixel(0, 15, jColor);
    ShowPixel(1, 15, jColor);
    ShowPixel(2, 15, jColor);
    ShowPixel(2, 14, jColor);
    ShowPixel(0, 13, jColor);
    ShowPixel(1, 13, jColor);
    ShowPixel(2, 13, jColor);
    ShowPixel(0, 12, jColor);
    ShowPixel(2, 12, jColor);
    ShowPixel(1, 11, jColor);

    ShowPixel(4, 15, aColor);
    ShowPixel(3, 14, aColor);
    ShowPixel(5, 14, aColor);
    ShowPixel(3, 13, aColor);
    ShowPixel(4, 13, aColor);
    ShowPixel(5, 13, aColor);
    ShowPixel(3, 12, aColor);
    ShowPixel(5, 12, aColor);

    ShowPixel(5, 15, yColor);
    ShowPixel(7, 15, yColor);
    ShowPixel(6, 14, yColor);
    ShowPixel(6, 13, yColor);
    ShowPixel(6, 12, yColor);

    ShowPixel(3, 11, oColor);
    ShowPixel(4, 12, oColor);
    ShowPixel(4, 10, oColor);
    ShowPixel(5, 11, oColor);

    ShowPixel(6, 9, sColor);
    ShowPixel(6, 11, sColor);
    ShowPixel(7, 10, sColor);
    ShowPixel(7, 12, sColor);
}
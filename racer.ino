

uint32_t racer_playerColorA = pixels.Color(251, 242, 54); // yellowish
uint32_t racer_playerColorB = pixels.Color(172, 50, 50);  // redish

byte racer_playerA_X[32] = {5, 5, 5, 5, 5, 5, 4, 3, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6};
byte racer_playerA_Y[32] = {8, 9, 10, 11, 12, 13, 13, 13, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7};

byte racer_playerB_X[32] = {6, 6, 6, 6, 6, 6, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 4, 5, 5, 5, 5, 5, 5};
byte racer_playerB_Y[32] = {8, 9, 10, 11, 12, 13, 14, 14, 14, 14, 14, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 2, 2, 2, 3, 4, 5, 6, 7};

byte racer_playerA_pos;
byte racer_playerB_pos;
bool racer_playerA_1key;
bool racer_playerB_1key;
byte racer_playerA_laps;
byte racer_playerB_laps;
byte racer_playerA_lapsPenalty;
byte racer_playerB_lapsPenalty;

void racer_reset()
{
    racer_playerA_pos = 0;
    racer_playerB_pos = 0;
    racer_playerA_1key = false;
    racer_playerB_1key = false;
    racer_playerA_laps = 0;
    racer_playerB_laps = 0;
    racer_playerA_lapsPenalty = 0;
    racer_playerB_lapsPenalty = 0;
}

void racer_gameUpdate()
{
    if(gameReset){
        racer_reset();
        gameReset = false;
    }
    racer_handleInput();
    racer_draw();
}

void racer_draw()
{

    // Map
    uint32_t frameColor = pixels.Color(10, 15, 24); // Blueish
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            if (y == 0 || y == 15 || x == 0 || x == 7 || ((x == 3 || x == 4) && (y >= 3 && y <= 12)))
                ShowPixel(x, y, frameColor);
        }
    }

    ShowPixel(racer_playerA_X[racer_playerA_pos], racer_playerA_Y[racer_playerA_pos], racer_playerColorA);

    ShowPixel(racer_playerB_X[racer_playerB_pos], racer_playerB_Y[racer_playerB_pos], racer_playerColorB);

    for (int i = 0; i < racer_playerA_laps; i++)
    {
        ShowPixel(0, i, racer_playerColorA);
    }
    for (int i = 0; i < racer_playerB_laps; i++)
    {
        ShowPixel(7, i, racer_playerColorB);
    }
}

void racer_handleInput()
{

    //Players
    if (!racer_playerA_1key && button_downEvent[0])
    { //Incorrect
        racer_playerA_pos--;
    }
    else if (racer_playerA_1key && button_downEvent[1])
    { //Incorrect
        racer_playerA_pos--;
    }
    else if (racer_playerA_1key && button_downEvent[0])
    { //Correct
        racer_playerA_pos++;
        racer_playerA_1key = !racer_playerA_1key;
    }
    else if (!racer_playerA_1key && button_downEvent[1])
    { //Correct
        racer_playerA_pos++;
        racer_playerA_1key = !racer_playerA_1key;
    }
    if (racer_playerA_pos > 32)
    {
        racer_playerA_pos = 31;
        racer_playerA_lapsPenalty++;
    }
    if (racer_playerA_pos == 32)
    {
        if (racer_playerA_lapsPenalty > 0)
            racer_playerA_lapsPenalty--;
        else
            racer_playerA_laps++;
        racer_playerA_pos = 0;
    }

    if (!racer_playerB_1key && button_downEvent[2])
    { //Incorrect
        racer_playerB_pos--;
    }
    else if (racer_playerB_1key && button_downEvent[3])
    { //Incorrect
        racer_playerB_pos--;
    }
    else if (racer_playerB_1key && button_downEvent[2])
    { //Correct
        racer_playerB_pos++;
        racer_playerB_1key = !racer_playerB_1key;
    }
    else if (!racer_playerB_1key && button_downEvent[3])
    { //Correct
        racer_playerB_pos++;
        racer_playerB_1key = !racer_playerB_1key;
    }
    if (racer_playerB_pos > 32)
    {
        racer_playerB_pos = 31;
        racer_playerB_lapsPenalty++;
    }
    if (racer_playerB_pos == 32)
    {

        if (racer_playerB_lapsPenalty > 0)
            racer_playerB_lapsPenalty--;
        else
            racer_playerB_laps++;
        racer_playerB_pos = 0;
    }
}

int pong_playerA_X = 3;
int pong_playerB_X = 3;
float pong_ballY = 8;
float pong_ballX = 3;
float pong_ballYD = 0.05;
float pong_ballXD = 0;
int pong_scoreA;
int pong_scoreB;
int playerHits;

void pong_reset()
{
    //Reset game variables
    pong_scoreA = 0;
    pong_scoreB = 0;
    pong_resetBall();
}
void pong_resetBall()
{
    pong_ballX = 3;
    pong_ballY = 8;
    pong_ballYD = 0.05;
    pong_ballXD = 0;
    pong_playerA_X = 3;
    pong_playerB_X = 3;
    playerHits = 0;
}

void pong_gameUpdate()
{
    if (gameReset)
    {
        pong_reset();
        gameReset = false;
    }
    pong_handleInput();
    pong_draw();
}

void pong_draw()
{

    //Score
    uint32_t lightGray = pixels.Color(2, 2, 2); // redish
    draw5x4Number(pong_scoreA, 2, 2, lightGray);
    draw5x4Number(pong_scoreB, 2, 9, lightGray);

    uint32_t white = pixels.Color(100, 100, 100); // redish

    //Ball
    ShowPixel(round(pong_ballX), round(pong_ballY), white);

    //PlayerA
    for (int i = -1; i <= 1; i++)
    {
        ShowPixel(pong_playerA_X + i, 0, white);
    }

    //PlayerB
    for (int i = -1; i <= 1; i++)
    {
        ShowPixel(pong_playerB_X + i, 15, white);
    }
}

void pong_handleInput()
{
    pong_ballY += pong_ballYD;
    pong_ballX += pong_ballXD;

    if (pong_ballX < 0)
    {
        pong_ballXD = -pong_ballXD;
        pong_ballX = pong_ballXD;
    }
    if (pong_ballX > 7)
    {
        pong_ballXD = -pong_ballXD;
        pong_ballX = 7 - pong_ballXD;
    }

    int ballX = round(pong_ballX);
    int ballY = round(pong_ballY);

    if (ballY == 0)
    {
        //At 0
        if (abs(ballX - pong_playerA_X) <= 1)
        {
            //Hit player
            pong_ballYD = -pong_ballYD;
            playerHits++;
            if(playerHits > 5 && pong_ballYD < 1)
                pong_ballYD += 0.01;
            pong_ballY = pong_ballY + 2 * pong_ballYD;
            pong_ballXD = (ballX - pong_playerA_X) * 0.01;
        }
        else
        {
            //Score B
            pong_scoreB++;
            pong_resetBall();
        }
    }

    if (ballY == 15)
    {
        //At 0
        if (abs(ballX - pong_playerB_X) <= 1)
        {
            //Hit player
            pong_ballYD = -pong_ballYD;
            playerHits++;
            if(playerHits > 5 && pong_ballYD > -1)
                pong_ballYD -= 0.01;
            pong_ballY = pong_ballY + 2 * pong_ballYD;
            pong_ballXD = (ballX - pong_playerB_X) * 0.01;
        }
        else
        {
            //Score A
            pong_scoreA++;
            pong_resetBall();
        }
    }

    if (button_downEvent[0])
    {
        if (pong_playerA_X > 1)
            pong_playerA_X--;
    }
    if (button_downEvent[1])
    {
        if (pong_playerA_X < 6)
            pong_playerA_X++;
    }
    if (button_downEvent[2])
    {
        if (pong_playerB_X > 1)
            pong_playerB_X--;
    }
    if (button_downEvent[3])
    {
        if (pong_playerB_X < 6)
            pong_playerB_X++;
    }
}
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <time.h>
#include <string>

using namespace sf;
using namespace std;

void traverseArray(Sprite grid[][8], int& scoreCount) 
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++) 
        {
            if (i + 2 < 8 && grid[i][j].getTexture() == grid[i + 1][j].getTexture() && grid[i][j].getTexture() == grid[i + 2][j].getTexture()) 
            {
                for (int k = i; k < 8; k++) 
                {
                    if (grid[i][j].getTexture() == grid[k][j].getTexture()) 
                    {
                        grid[k][j].setColor(Color::Blue);
                        scoreCount++;
                    }
                    else 
                    {
                        break;
                    }
                }
            }

            if (j + 2 < 8 && grid[i][j].getTexture() == grid[i][j + 1].getTexture() && grid[i][j].getTexture() == grid[i][j + 2].getTexture()) 
            {
                for (int k = j; k < 8; k++) {
                    if (grid[i][j].getTexture() == grid[i][k].getTexture()) 
                    {
                        grid[i][k].setColor(Color::Blue);
                        scoreCount++;
                    }
                    else 
                    {
                        break;
                    }
                }
            }
        }
    }
}

void deleteBlocks(Sprite grid[][8], Sprite animals[], int& scoreCount)
{
    bool repeat = true;
    while (repeat) 
    {
        repeat = false;
        for (int i = 7; i >= 0; i--) 
        {
            for (int j = 0; j < 8; j++) 
            {
                if (grid[j][i].getColor() == Color::Blue) 
                {
                    repeat = true;
                    int k = 0;
                    for (k = i; k >= 0; k--) 
                    {
                        if (grid[j][k].getColor() != Color::Blue) 
                        {
                            break;
                        }
                    }

                    if (k >= 0) 
                    {
                        Sprite Temp = grid[j][k];
                        Temp.move(0, grid[j][i].getPosition().y - grid[j][k].getPosition().y);
                        grid[j][i].move(0, grid[j][k].getPosition().y - grid[j][i].getPosition().y);
                        //grid[j][i].move(0, 500);
                        grid[j][k] = grid[j][i];
                        grid[j][i] = Temp;
                    }

                    if (grid[j][0].getColor() == Color::Blue) 
                    {
                        grid[j][0] = animals[rand() % 7];
                        grid[j][0].move(j * 57, 0);
                    }
                }
            }
        }
        if (repeat) {
            traverseArray(grid, scoreCount);
        }
    }
}

void getindex(int x,int y, int& index1, int& index2) 
{
    for (int i = 0; i < 8; i++) 
    {
        if (x >= i * (54 + 3) && x <= (i + 1) * (54 + 3) - 3) 
        {
            index1 = i;
            for (int j = 0; j < 8; j++) {
                if (y >= (j * (54 + 3)) && y <= (j + 1) * (54 + 3) - 3) 
                {
                    index2 = j;
                }
            }
        }
    }
}


int main(){
    srand(time(NULL));
    int ts = 54; //tile size
    Vector2i offset(48, 24);
    srand(time(0));
    RenderWindow app(VideoMode(740, 480), "Menagerie");
    app.setFramerateLimit(60);
    Texture t1, t2;
    t1.loadFromFile("sprites/back.jpg");
    t2.loadFromFile("sprites/gems.jpg");
    Sprite background(t1), gems(t2), menu, Bar,Pass, Fail, Won;   //Sprite is a Datatype
    Texture camel, cat, bull, deer, elephant, giraffe, goat, m, bar, barfill, pass, fail, won;
    Sprite animals[7];
    Sprite grid[8][8];


    Music music;

    music.openFromFile("sprites/song.wav");
    music.setVolume(50);
    music.play();


    camel.loadFromFile("sprites/camel.jpg");
    animals[0].setTexture(camel);
    bull.loadFromFile("sprites/tiger.jpg");
    animals[1].setTexture(bull);
    cat.loadFromFile("sprites/hippo.jpg");
    animals[2].setTexture(cat);
    deer.loadFromFile("sprites/deer.jpg");
    animals[3].setTexture(deer);
    elephant.loadFromFile("sprites/elephant.jpg");
    animals[4].setTexture(elephant);
    giraffe.loadFromFile("sprites/giraffe.jpg");
    animals[5].setTexture(giraffe);
    goat.loadFromFile("sprites/goat.jpg");
    animals[6].setTexture(goat);
    m.loadFromFile("sprites/menu.jpg");
    menu.setTexture(m);
    bar.loadFromFile("sprites/bar.png");
    Bar.setTexture(bar);
    Bar.setPosition(490, 10);
    barfill.loadFromFile("sprites/barFiller.png");
    pass.loadFromFile("sprites/pass.jpg");
    fail.loadFromFile("sprites/fail.jpg");
    Pass.setTexture(pass);
    Fail.setTexture(fail);
    won.loadFromFile("sprites/won.jpg");
    Won.setTexture(won);
    


    Sprite progressBar[8];   //Array size 8 hai because poray progress bar mai 8 bars hain 
    for (int i = 0; i < 8; i++) 
    {
        progressBar[i].setTexture(barfill);
        // barfill is a variable declared above which contains the pic of blue bar
        progressBar[i].setPosition(500 + (i * 25), 16);
    }

    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            grid[i][j] = animals[rand() % 7];
            grid[i][j].setPosition(i * (54 + 3), j * (54 + 3)); //3 is offset i.e. space b/w sprites
        }
    }



    Event e;
    int i1 = -1, i2 = -1, i3 = -1, i4 = -1;
    bool flag = false;
    bool gameStarted = false;
    bool menuShow = true;
    bool showLevelPass = false;
    bool showLevelFail = false;
    int progress = 0;
    int noOfTurns = 20;    //Changable
    bool sign;
    bool lvl1 = true;
    bool lvl2 = false;
    bool gameWon = false;
    int points = 0;
    bool isTimeTrial = false;
    Text scoreTitle, score, turns, multiplier, TimeLeft;
    Font font;
    font.loadFromFile("./arial.ttf");
    scoreTitle.setFont(font);
    scoreTitle.setString("Score: ");
    scoreTitle.setCharacterSize(24);
    scoreTitle.setPosition(500, 50);
    scoreTitle.setFillColor(Color::Black);
    scoreTitle.setStyle(Text::Bold);

    score.setFont(font);
    score.setString(to_string(points));
    score.setCharacterSize(40);
    score.setPosition(500, 80);
    score.setFillColor(Color::Black);
    score.setStyle(Text::Bold);

    turns.setFont(font);
    turns.setString("Turns Left: " + to_string(noOfTurns));
    turns.setCharacterSize(24);
    turns.setPosition(500, 140);
    turns.setFillColor(Color::Black);
    turns.setStyle(Text::Bold);

    multiplier.setFont(font);
    multiplier.setString("x" + to_string(1));
    multiplier.setCharacterSize(70);
    multiplier.setPosition(350, 220);
    multiplier.setFillColor(Color::Black);
    multiplier.setStyle(Text::Bold);

    int lvl2Time = 120;
    int scoreCount = 0;

    TimeLeft.setFont(font);
    TimeLeft.setString("Time Left: " + to_string(lvl2Time));
    TimeLeft.setCharacterSize(25);
    TimeLeft.setPosition(500, 190);
    TimeLeft.setFillColor(Color::Black);
    TimeLeft.setStyle(Text::Bold);

    time_t tim = time(NULL);

    time_t lvl2StartTime = time(NULL);


    while (app.isOpen()) 
    {
        if (gameWon) 
        {
            app.draw(Won);
            while (app.pollEvent(e))
            {
                if (e.type == Event::Closed)
                    app.close();

                if (e.type == Event::MouseButtonPressed || e.type == Event::MouseButtonReleased) 
                {
                    if (e.type == Event::MouseButtonPressed)
                        if (e.key.code == Mouse::Left) 
                        {
                            i1 = e.mouseButton.x; // x-coordinate
                            i2 = e.mouseButton.y; // y-coordinate
                            //coordinates^

                            if (i1 >= 50 && i1 <= 310 && i2 >= 225 && i2 <= 255) 
                            {
                                menuShow = true;  //Main menu shown
                                gameWon = false;  //Game won menu removed
                            }
                            else if (i1 >= 417 && i1 <= 720 && i2 >= 225 && i2 <= 255) 
                            {
                                lvl1 = true;
                                lvl2 = false;
                                gameWon = false;
                                gameStarted = true;
                                progress = 0;
                                if (isTimeTrial) 
                                {
                                    progress = 25;
                                }
                                noOfTurns = 20;
                                points = 0;
                            }
                            i1 = i2 = -1;   //To show that value is not stored..Not 0 because it is coordinate
                        }
                }
            }
        }
        if (showLevelFail)
        {
            app.draw(Fail);
            while (app.pollEvent(e))
            {
                if (e.type == Event::Closed)
                    app.close();

                if (e.type == Event::MouseButtonPressed || e.type == Event::MouseButtonReleased)
                {
                    if (e.type == Event::MouseButtonPressed)
                        if (e.key.code == Mouse::Left) 
                        {
                            i1 = e.mouseButton.x;
                            i2 = e.mouseButton.y;

                            if (i1 >= 50 && i1 <= 310 && i2 >= 225 && i2 <= 255)
                            {
                                menuShow = true;
                                showLevelFail = false;
                                lvl1 = true;
                                lvl2 = false;
                                lvl2Time = 120;
                                progress = 0;
                                points = 0;
                                noOfTurns = 20;
                            }
                            else if (i1 >= 488 && i1 <= 650 && i2 >= 225 && i2 <= 255)
                            {
                                showLevelFail = false;
                                gameStarted = true;
                                progress = 0;
                                if (isTimeTrial)
                                {
                                    progress = 25;
                                }
                                noOfTurns = 20;
                                points = 0;
                            }
                            i1 = i2 = -1;
                        }
                }
            }
        }

        if (showLevelPass)
        {
            app.draw(Pass);
            while (app.pollEvent(e)) 
            {
                if (e.type == Event::Closed)
                    app.close();

                if (e.type == Event::MouseButtonPressed || e.type == Event::MouseButtonReleased) 
                {
                    if (e.type == Event::MouseButtonPressed)
                        if (e.key.code == Mouse::Left)
                        {
                            i1 = e.mouseButton.x;
                            i2 = e.mouseButton.y;

                            if (i1 >= 51 && i1 <= 308 && i2 >= 224 && i2 <= 255)
                            {
                                menuShow = true;
                                showLevelPass = false;
                                lvl1 = true;
                                lvl2 = false;
                            }
                            else if (i1 >= 420 && i1 <= 718 && i2 >= 225 && i2 <= 255)
                            {
                                lvl1 = false;
                                lvl2 = true;
                                lvl2Time = 120;
                                lvl2StartTime = time(NULL);
                                showLevelPass = false;
                                gameStarted = true;
                                progress = 0;
                                if (isTimeTrial) 
                                {
                                    progress = 25;
                                }
                                noOfTurns = 20;
                            }
                            i1 = i2 = -1;
                        }
                }
            }
        }

        if (menuShow) 
        {
            app.draw(menu);

            while (app.pollEvent(e)) 
            {
                if (e.type == Event::Closed)
                    app.close();

                if (e.type == Event::MouseButtonPressed || e.type == Event::MouseButtonReleased) 
                {
                    if (e.type == Event::MouseButtonPressed)
                        if (e.key.code == Mouse::Left) 
                        {

                            //coordinates of mouse clicks
                            i1 = e.mouseButton.x;  //x-coordinates
                            i2 = e.mouseButton.y;  //y-coordinates


                            cout << i1 << i2 << endl;
                            if (i1 >= 38 && i1 <= 255 && i2 >= 218 && i2 <= 275) 
                            {
                                menuShow = false;
                                gameStarted = true;
                                showLevelPass = false;
                                showLevelFail = false;
                                progress = 0;
                                noOfTurns = 20;
                                lvl1 = true;
                                lvl2 = false;
                                gameWon = false;
                                points = 0;
                                isTimeTrial = false;
                                lvl2Time = 120;
                                scoreCount = 0;
                            }
                            else if (i1 >= 380 && i1 <= 670 && i2 >= 215 && i2 <= 270) 
                            {
                                menuShow = false;
                                gameStarted = true;
                                progress = 25;
                                isTimeTrial = true;
                                showLevelPass = false;
                                showLevelFail = false;
                                noOfTurns = 20;
                                lvl1 = true;
                                lvl2 = false;
                                gameWon = false;
                                points = 0;
                                lvl2Time = 120;
                                scoreCount = 0;
                            }
                            i1 = i2 = -1;
                            //Taa k i1 and i2 kee values kahee use na ho jaye tou iske value khtam kr dee humne
                        }
                }
            }
        }

        if (gameStarted) 
        {
            traverseArray(grid, scoreCount);
            deleteBlocks(grid, animals, scoreCount);
            scoreCount = 0;

            if (lvl2 && (difftime(time(NULL),lvl2StartTime)>=1)) 
            {
                lvl2StartTime = time(NULL);   //Lvl 2 time equal to System time
                lvl2Time--;
                TimeLeft.setString("Time Left: " + std::to_string(lvl2Time));
            }

            if (isTimeTrial && difftime(time(NULL), tim) >= 10)
            {
                tim = time(NULL);
                progress -= 6;
            }
            app.draw(background);
            app.draw(gems);
            app.draw(Bar);
            app.draw(scoreTitle);
            app.draw(score);
            app.draw(turns);
            if (lvl2) 
            {
                app.draw(TimeLeft);
            }
            int n = progress;
            for (int i = 0; i < 8; i++) 
            {
                if (n > 0) 
                {
                    app.draw(progressBar[i]);
                }
                n -= 6;
            }
            
            if (noOfTurns <= 0 || progress<0 || lvl2Time<0) 
            {
                showLevelFail = true;
                gameStarted = false;
            }

            if (lvl2) 
            {
                if (progress >= 50)    //length of progress bar is 50
                {
                    gameWon = true;
                    gameStarted = false;
                }
            }

            if (lvl1 == true ) 
            {
                if (progress >= 50) 
                {
                    showLevelPass = true;
                    gameStarted = false;
                }
            }

            for (int i = 0; i < 8; i++) 
            {
                for (int j = 0; j < 8; j++) 
                {
                    app.draw(grid[i][j]);
                }
            }
            // Grid drawn later taa k sprites oper draw ho jaye background k
            score.setString(to_string(points));
            turns.setString("Turns Left: " + to_string(noOfTurns));

            while (app.pollEvent(e)) 
            {
                if (e.type == Event::Closed)
                    app.close();

                if (e.type == Event::MouseButtonPressed || e.type == Event::MouseButtonReleased)
                {
                    if (e.type == Event::MouseButtonPressed)
                        if (e.key.code == Mouse::Left) 
                        {
                            //grid[0][0].move(0, 50);
                            //std::cout <<
                            getindex(e.mouseButton.x, e.mouseButton.y, i1, i2);
                            //<< std::endl;
                        }
                    if (e.type == Event::MouseButtonReleased)
                        if (e.key.code == Mouse::Left) 
                        {
                            /*std::cout << e.mouseButton.x << std::endl;
                            std::cout << e.mouseButton.y << std::endl;*/
                            getindex(e.mouseButton.x, e.mouseButton.y, i3, i4);
                        }

                    if (!(i1 == -1 || i2 == -1 || i3 == -1 || i4 == -1)) 
                    {
                        if (i3 == i1 && i2 != i4)    //Diagonal swapping avoid krne k liye
                        {
                            if (i2 == i4 + 1 || i2 == i4 - 1) 
                            {
                                flag = true;
                            }
                        }
                        if (i2 == i4 && i1 != i3) 
                        {
                            if (i3 == i1 + 1 || i3 == i1 - 1) 
                            {
                                flag = true;
                            }
                        }
                        if (flag) 
                        {
                            int x = grid[i3][i4].getPosition().x;
                            int y = grid[i3][i4].getPosition().y;
                            int x1 = grid[i1][i2].getPosition().x;
                            int y1 = grid[i1][i2].getPosition().y;
                            //store value of indexes after swapping
                            
                            grid[i1][i2].move(x - x1, y - y1);
                            grid[i3][i4].move(x1 - x, y1 - y);

                            // Movement ke direction show krne k liye

                            Sprite temp(grid[i1][i2]);
                            //temp.setColor(Color::Red);
                            grid[i1][i2] = grid[i3][i4];
                            grid[i3][i4] = temp;

                            noOfTurns--;

  
                            flag = false;
                            int num = 0;

                            sign = false;

                            for (int i = 0; i < 8; i++) 
                            {
                                for (int j = 0; j < 8; j++) 
                                {
                                    if (i + 2 < 8 && grid[i][j].getTexture() == grid[i + 1][j].getTexture() && grid[i][j].getTexture() == grid[i + 2][j].getTexture())
                                    {
                                        for (int k = i; k < 8; k++) 
                                        {
                                            if (grid[i][j].getTexture() == grid[k][j].getTexture())
                                            {
                                                grid[k][j].setColor(Color::Blue);
                                                scoreCount++;
                                            }
                                            else
                                            {
                                                break;
                                            }
                                        }
                                        sign = true;
                                    }
                                    if (j + 2 < 8 && grid[i][j].getTexture() == grid[i][j + 1].getTexture() && grid[i][j].getTexture() == grid[i][j + 2].getTexture()) {
                                        for (int k = j; k < 8; k++) {
                                            if (grid[i][j].getTexture() == grid[i][k].getTexture()) {
                                                grid[i][k].setColor(Color::Blue);
                                                scoreCount++;
                                            }
                                            else {
                                                break;
                                            }
                                        }
                                        sign = true;
                                    }
                                }
                            }

                            if (!sign) 
                            {

                                Sprite temp(grid[i1][i2]);
                                //temp.setColor(Color::Red);
                                grid[i1][i2] = grid[i3][i4];
                                grid[i3][i4] = temp;
                                // Match na honay ke wajah se swapping reverse krne k liye

                                noOfTurns++;

                                grid[i1][i2].move(x1 - x, y1 - y);
                                grid[i3][i4].move(x - x1, y - y1);
                                
                                i1 = i2 = i3 = i4 = -1;
                            }

                            if (sign) 
                            {
                                i1 = i2 = i3 = i4 = -1;
                                //std::cout << "Progress: " << progress << "\n";
                                if (scoreCount > 3) 
                                {
                                    progress += (scoreCount * 2);
                                    multiplier.setString("Hooray! x" + std::to_string(scoreCount - 2));
                                    app.draw(multiplier);
                                    points += scoreCount*(scoreCount-2);
                                }
                                else
                                {
                                    progress+=scoreCount;
                                    points += scoreCount;
                                }
                                scoreCount = 0;
                                // std::cout << "Progress: " << progress << "\n";
                                sign = false;

                                deleteBlocks(grid, animals, scoreCount);
                            }
                        }
                    }
                }
            }
        }
        
        app.display();
    }
    return 0;
}
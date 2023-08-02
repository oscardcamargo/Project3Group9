#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Maze.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

class MyWindow {
private:
    void drawBackground(sf::RenderWindow& window, bool door, bool left, bool right);
    void drawTitle(sf::RenderWindow &window);
    void drawOptions(sf::RenderWindow &window, std::vector<bool> selected_option, bool& music_on, std::vector<bool>& pressed);
    void drawDifficulty(sf::RenderWindow &window, std::vector<bool> selected_option,  std::vector<bool>& pressed);
    void gameWindow(sf::RenderWindow& window, std::vector<bool> difficulty);
    void settingsWindow(sf::RenderWindow& window, sf::Music& music, sf::Sound& sound);
    void gameSelectionWindow(sf::RenderWindow& window, sf::Sound& sound);
    bool mazeSolved(int& x, int& y, int size);

public:
    void welcomeWindow();
};

bool MyWindow::mazeSolved(int& x, int& y, int size)
{
    if (x > 2*size && y > size-1)
    {
        return true;
    }

    return false;
}

void MyWindow::drawDifficulty(sf::RenderWindow &window, std::vector<bool> selected_option, std::vector<bool> &pressed)
{
    std::string select = "CHOOSE ONE:";
    std::string easy = "EASY";
    std::string medium = "MEDIUM";
    std::string hard = "HARD";
    std::string nightmare = "NIGHTMARE";
    std::string cursor = "> ";

    sf::Text options;

    sf::Font font;

    font.loadFromFile("Ticketing.ttf");

    options.setFont(font);

    options.setFillColor(sf::Color::Yellow);

    options.setCharacterSize(39);

    options.setString(select);

    sf::FloatRect optionsRect = options.getLocalBounds();
    options.setOrigin(optionsRect.left + optionsRect.width/2.0f,optionsRect.top + optionsRect.height*4.5f);
    options.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));
    window.draw(options);

    if (selected_option[0])
    {
        options.setString(cursor + easy);
    }
    else
    {
        options.setString(easy);
    }

    if (pressed[0])
    {
        options.setFillColor({127, 127, 0});
    }
    else
    {
        options.setFillColor(sf::Color::Yellow);
    }

    optionsRect = options.getLocalBounds();
    options.setOrigin(optionsRect.left + optionsRect.width/2.0f,optionsRect.top + optionsRect.height*2.5f);
    options.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));

    window.draw(options);

    if (selected_option[1])
    {
        options.setString(cursor + medium);
    }
    else
    {
        options.setString(medium);
    }

    if (pressed[1])
    {
        options.setFillColor({127, 127, 0});
    }
    else
    {
        options.setFillColor(sf::Color::Yellow);
    }

    optionsRect = options.getLocalBounds();
    options.setOrigin(optionsRect.left + optionsRect.width/2.0f,optionsRect.top + optionsRect.height*0.5f);
    options.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));

    window.draw(options);

    if (selected_option[2])
    {
        options.setString(cursor + hard);
    }
    else
    {
        options.setString(hard);
    }

    if (pressed[2])
    {
        options.setFillColor({127, 127, 0});
    }
    else
    {
        options.setFillColor(sf::Color::Yellow);
    }

    optionsRect = options.getLocalBounds();
    options.setOrigin(optionsRect.left + optionsRect.width/2.0f,optionsRect.top - optionsRect.height*1.5f);
    options.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));

    window.draw(options);

    if (selected_option[3])
    {
        options.setString(cursor + nightmare);
    }
    else
    {
        options.setString(nightmare);
    }

    if (pressed[3])
    {
        options.setFillColor({127, 127, 0});
    }
    else
    {
        options.setFillColor(sf::Color::Yellow);
    }

    optionsRect = options.getLocalBounds();
    options.setOrigin(optionsRect.left + optionsRect.width/2.0f,optionsRect.top - optionsRect.height*3.5f);
    options.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));

    window.draw(options);
}

void MyWindow::gameSelectionWindow(sf::RenderWindow &window, sf::Sound& sound)
{
    std::vector<bool> selected_option = {true, false, false, false};
    std::vector<bool> pressed = {false, false, false, false};

    while(window.isOpen())
    {
        sf::Event event {};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Down)
                {
                    for (int i = 0; i < selected_option.size(); ++i)
                    {
                        if (selected_option[i] && i < selected_option.size() - 1 && !pressed[i])
                        {
                            selected_option[i] = false;
                            selected_option[i+1] = true;
                            break;
                        }
                    }
                }

                if (event.key.code == sf::Keyboard::Up)
                {
                    for (int i = 0; i < selected_option.size(); ++i)
                    {
                        if (selected_option[i] && i > 0 && !pressed[i])
                        {
                            selected_option[i] = false;
                            selected_option[i-1] = true;
                            break;
                        }
                    }
                }

                if (event.key.code == sf::Keyboard::Space)
                {
                    sound.play();
                    gameWindow(window, pressed);
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    for (int i = 0; i < selected_option.size(); ++i)
                    {
                        if (selected_option[i])
                        {
                            pressed[i] = true;
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::Black);

        drawBackground(window, false, false, true);
        drawTitle(window);
        drawDifficulty(window, selected_option, pressed);

        window.display();
    }
}

void MyWindow::drawOptions(sf::RenderWindow &window, std::vector<bool> selected_option, bool& music_on, std::vector<bool>& pressed)
{
    std::string start = "START";
    std::string exit = "QUIT";
        std::string instructions = "INSTRUCTIONS";
    std::string music = "MUSIC ";
    std::string music_status = "OFF";
    std::string cheats = "CHEATS";
    std::string cursor = "> ";

    sf::Text options;

    sf::Font font;

    font.loadFromFile("Ticketing.ttf");

    options.setFont(font);

    options.setFillColor(sf::Color::Yellow);

    options.setCharacterSize(39);

    sf::FloatRect optionsRect;

    if (selected_option[0])
    {
        options.setString(cursor + start);
    }
    else
    {
        options.setString(start);
    }

    if (pressed[0])
    {
        options.setFillColor({127, 127, 0});
    }
    else
    {
        options.setFillColor(sf::Color::Yellow);
    }

    optionsRect = options.getLocalBounds();
    options.setOrigin(optionsRect.left + optionsRect.width/2.0f,optionsRect.top + optionsRect.height*4.5f);
    options.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));

    window.draw(options);

    if (selected_option[1])
    {
        options.setString(cursor + instructions);
    }
    else
    {
        options.setString(instructions);
    }

    if (pressed[1])
    {
        options.setFillColor({127, 127, 0});
    }
    else
    {
        options.setFillColor(sf::Color::Yellow);
    }

    optionsRect = options.getLocalBounds();
    options.setOrigin(optionsRect.left + optionsRect.width/2.0f,optionsRect.top + optionsRect.height*2.5f);
    options.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));

    window.draw(options);

    if (!music_on)
    {
        music_status = "ON";
    }

    if (selected_option[2])
    {
        options.setString(cursor + music + music_status);
    }
    else
    {
        options.setString(music + music_status);
    }

    if (pressed[2])
    {
        options.setFillColor({127, 127, 0});
    }
    else
    {
        options.setFillColor(sf::Color::Yellow);
    }

    optionsRect = options.getLocalBounds();
    options.setOrigin(optionsRect.left + optionsRect.width/2.0f,optionsRect.top + optionsRect.height*0.5f);
    options.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));

    window.draw(options);

    if (selected_option[3])
    {
        options.setString(cursor + cheats);
    }
    else
    {
        options.setString(cheats);
    }

    if (pressed[3])
    {
        options.setFillColor({127, 127, 0});
    }
    else
    {
        options.setFillColor(sf::Color::Yellow);
    }

    optionsRect = options.getLocalBounds();
    options.setOrigin(optionsRect.left + optionsRect.width/2.0f,optionsRect.top - optionsRect.height*1.5f);
    options.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));

    window.draw(options);

    if (selected_option[4])
    {
        options.setString(cursor + exit);
    }
    else
    {
        options.setString(exit);
    }

    if (pressed[4])
    {
        options.setFillColor({127, 127, 0});
    }
    else
    {
        options.setFillColor(sf::Color::Yellow);
    }

    optionsRect = options.getLocalBounds();
    options.setOrigin(optionsRect.left + optionsRect.width/2.0f,optionsRect.top - optionsRect.height*3.5f);
    options.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));

    window.draw(options);
}

void MyWindow::settingsWindow(sf::RenderWindow& window, sf::Music& music, sf::Sound& sound)
{
    std::vector<bool> selected_option = {true, false, false, false, false};
    std::vector<bool> pressed = {false, false, false, false, false};
    bool music_on = true;

    while(window.isOpen())
    {
        sf::Event event {};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Down)
                {
                    for (int i = 0; i < selected_option.size(); ++i)
                    {
                        if (selected_option[i] && i < selected_option.size() - 1 && !pressed[i])
                        {
                            selected_option[i] = false;
                            selected_option[i+1] = true;
                            break;
                        }
                    }
                }

                if (event.key.code == sf::Keyboard::Up)
                {
                    for (int i = 0; i < selected_option.size(); ++i)
                    {
                        if (selected_option[i] && i > 0 && !pressed[i])
                        {
                            selected_option[i] = false;
                            selected_option[i-1] = true;
                            break;
                        }
                    }
                }

                if (event.key.code == sf::Keyboard::Space)
                {
                    if (selected_option[0])
                    {
                        sound.play();
                        pressed[0] = false;
                        gameSelectionWindow(window, sound);
                    }

                    if (selected_option[1])
                    {
                        pressed[1] = false;

                    }

                    if (selected_option[2])
                    {
                        music_on = !music_on;

                        if (music_on)
                        {
                            music.play();
                        }
                        else
                        {
                            music.pause();
                        }

                        pressed[2] = false;
                    }

                    if (selected_option[4])
                    {
                        window.close();
                    }

                    if (selected_option[3])
                    {
                        pressed[3] = false;
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    for (int i = 0; i < selected_option.size(); ++i)
                    {
                        if (selected_option[i])
                        {
                            pressed[i] = true;
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::Black);

        drawBackground(window, false, true, false);
        drawTitle(window);
        drawOptions(window, selected_option, music_on, pressed);

        window.display();
    }
}

void MyWindow::drawTitle(sf::RenderWindow& window)
{
    sf::Text title;
    title.setString("MAZE RUNNER");

    sf::Font fontTitle;
    fontTitle.loadFromFile("RUBBBB__.TTF");
    title.setFont(fontTitle);

    sf::FloatRect titleRect;

    title.setFillColor(sf::Color::Yellow);
    title.setCharacterSize(71);
    titleRect = title.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width/2.0f,titleRect.top + titleRect.height*4.5f);
    title.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));
    window.draw(title);
    title.setCharacterSize(70);
    titleRect = title.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width/2.0f,titleRect.top + titleRect.height*4.6f);
    title.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));
    title.setFillColor(sf::Color::Red);
    window.draw(title);
}

void MyWindow::drawBackground(sf::RenderWindow &window, bool front = true, bool left = false, bool right = false)
{
    sf::Vertex line[2] =
            {
                    sf::Vertex(sf::Vector2f(0, 0), sf::Color::Yellow),
                    sf::Vertex(sf::Vector2f(SCREEN_WIDTH/4.0f, SCREEN_HEIGHT/4.0f), sf::Color::Yellow)
            };
    window.draw(line , 2, sf::Lines);

    line[0] = sf::Vertex(sf::Vector2f(0, SCREEN_HEIGHT), sf::Color::Yellow);
    line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/4.0f, SCREEN_HEIGHT*0.75f), sf::Color::Yellow);
    window.draw(line , 2, sf::Lines);

    line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/4.0f, SCREEN_HEIGHT/4.0f), sf::Color::Yellow);
    line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/4.0f, SCREEN_HEIGHT*0.75f), sf::Color::Yellow);
    window.draw(line , 2, sf::Lines);

    line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH, 0), sf::Color::Yellow);
    line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.75f, SCREEN_HEIGHT/4.0f), sf::Color::Yellow);
    window.draw(line , 2, sf::Lines);

    line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT), sf::Color::Yellow);
    line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.75f, SCREEN_HEIGHT*0.75f), sf::Color::Yellow);
    window.draw(line , 2, sf::Lines);

    line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.75f, SCREEN_HEIGHT/4.0f), sf::Color::Yellow);
    line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.75f, SCREEN_HEIGHT*0.75f), sf::Color::Yellow);
    window.draw(line , 2, sf::Lines);

    line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/4.0f, SCREEN_HEIGHT*0.75f), sf::Color::Yellow);
    line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.75f, SCREEN_HEIGHT*0.75f), sf::Color::Yellow);
    window.draw(line , 2, sf::Lines);

    line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/4.0f, SCREEN_HEIGHT/4.0f), sf::Color::Yellow);
    line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.75f, SCREEN_HEIGHT/4.0f), sf::Color::Yellow);
    window.draw(line , 2, sf::Lines);

    if (front)
    {
        line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/2.5f, SCREEN_WIDTH*0.75f), sf::Color::Yellow);
        line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/2.5f, SCREEN_HEIGHT/2.5f), sf::Color::Yellow);
        window.draw(line , 2, sf::Lines);

        line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.6f, SCREEN_WIDTH/2.5f), sf::Color::Yellow);
        line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.6f, SCREEN_HEIGHT*0.75f), sf::Color::Yellow);
        window.draw(line , 2, sf::Lines);

        line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/2.5f, SCREEN_HEIGHT/2.5f), sf::Color::Yellow);
        line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.6f, SCREEN_WIDTH/2.5f), sf::Color::Yellow);
        window.draw(line , 2, sf::Lines);
    }

    if (left)
    {
        line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/16.0f, SCREEN_WIDTH*0.935f), sf::Color::Yellow);
        line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/16.0f, SCREEN_WIDTH/3.0f), sf::Color::Yellow);
        window.draw(line , 2, sf::Lines);

        line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/6.0f, SCREEN_WIDTH/2.5f), sf::Color::Yellow);
        line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/6.0f, SCREEN_HEIGHT*0.835f), sf::Color::Yellow);
        window.draw(line , 2, sf::Lines);

        line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/16.0f, SCREEN_WIDTH/3.0f), sf::Color::Yellow);
        line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/6.0f, SCREEN_WIDTH/2.5f), sf::Color::Yellow);
        window.draw(line , 2, sf::Lines);
    }

    if (right)
    {
        line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.935f, SCREEN_WIDTH*0.935f), sf::Color::Yellow);
        line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.935f, SCREEN_WIDTH/3.0f), sf::Color::Yellow);
        window.draw(line , 2, sf::Lines);

        line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.835f, SCREEN_WIDTH/2.5f), sf::Color::Yellow);
        line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.835f, SCREEN_HEIGHT*0.835f), sf::Color::Yellow);
        window.draw(line , 2, sf::Lines);

        line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.935f, SCREEN_WIDTH/3.0f), sf::Color::Yellow);
        line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.835f, SCREEN_WIDTH/2.5f), sf::Color::Yellow);
        window.draw(line , 2, sf::Lines);
    }
}

void MyWindow::welcomeWindow()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                            "Maze Runner", sf::Style::Close);

    sf::Font fontSubtitle;
    sf::Text subtitle;
    sf::Text footnote;

    sf::SoundBuffer buffer;
    buffer.loadFromFile("door-creak.wav");
    sf::Sound sound;
    sound.setBuffer(buffer);

    sf::Music music;
    music.openFromFile("ferambie.wav");
    music.setLoop(true);
    music.play();

    fontSubtitle.loadFromFile("Ticketing.ttf");

    subtitle.setFont(fontSubtitle);
    footnote.setFont(fontSubtitle);

    subtitle.setString("PUSH SPACE KEY TO CONTINUE");
    footnote.setString("2023 Maze Generation Games. All Rights Reserved");

    footnote.setFillColor(sf::Color::Yellow);
    subtitle.setFillColor(sf::Color::Yellow);

    subtitle.setCharacterSize(39);
    footnote.setCharacterSize(23);

    sf::FloatRect subtitleRect = subtitle.getLocalBounds();
    subtitle.setOrigin(subtitleRect.left + subtitleRect.width/2.0f,subtitleRect.top - subtitleRect.height*8.5f);
    subtitle.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));

    sf::FloatRect footnoteRect = footnote.getLocalBounds();
    footnote.setOrigin(footnoteRect.left + footnoteRect.width/2.0f,footnoteRect.top - footnoteRect.height*18.0f);
    footnote.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));

    while(window.isOpen())
    {
        sf::Event event {};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    subtitle.setColor({127, 127, 0});
                }
            }

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    sound.play();
                    sf::sleep(sf::milliseconds(200));
                    settingsWindow(window, music, sound);
                }
            }
        }

        window.clear(sf::Color::Black);

        drawBackground(window);
        drawTitle(window);

        window.draw(subtitle);
        window.draw(footnote);

        window.display();
    }
}

void MyWindow::gameWindow(sf::RenderWindow& window, std::vector<bool> difficulty)
{
    std::vector<int> sizes = {3, 10, 100, 317};
    int size = 0;

    Maze maze;

    for (int i = 0; i < difficulty.size(); ++i)
    {
        if (difficulty[i])
        {
            maze.setNewDimensions(sizes[i], sizes[i]);
            size = sizes[i];
        }
    }

    maze.binaryTree();

    std::vector<std::vector<bool>> world = maze.convertToBinaryMatrix();

    int playerX = 1;
    int playerY = 1;
    int playerDir = 2;

    std::vector<int> dx = {-1, 0, 1, 0};
    std::vector<int> dy = {0, 1, 0, -1};

    sf::Texture back_texture;
    back_texture.loadFromFile("./images/back.png");

    sf::Sprite back;
    back.setTexture(back_texture);
    back.setColor({255, 255, 0});

    std::vector<sf::Texture> left_textures(5);
    std::vector<sf::Sprite> left_sprites(5);

    std::vector<sf::Texture> right_textures(5);
    std::vector<sf::Sprite> right_sprites(5);

    std::vector<sf::Texture> mid_textures(5);
    std::vector<sf::Sprite> mid_sprites(5);

    for (int i = 0; i < 5; ++i)
    {
        left_textures[i].loadFromFile("./images/left" + std::to_string(i) + ".png");
        left_sprites[i].setTexture(left_textures[i]);
        left_sprites[i].setColor({255, 255, 0});

        right_textures[i].loadFromFile("./images/right" + std::to_string(i) + ".png");
        right_sprites[i].setTexture(right_textures[i]);
        right_sprites[i].setColor({255, 255, 0});

        mid_textures[i].loadFromFile("./images/mid" + std::to_string(i) + ".png");
        mid_sprites[i].setTexture(mid_textures[i]);
        mid_sprites[i].setColor({255, 255, 0});
    }

    while(window.isOpen())
    {
        sf::Event event {};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    int newX = playerX + dx[playerDir];
                    int newY = playerY + dy[playerDir];

                    if (mazeSolved(newX, newY, size))
                    {
                        playerX = 1;
                        playerY = 1;
                        maze.resetMaze();
                        maze.randomizedDFS();
                        world = maze.convertToBinaryMatrix();
                        sf::sleep(sf::milliseconds(300));
                    }
                    else
                    {
                        if (!world[newX][newY])
                        {
                            playerX = newX;
                            playerY = newY;
                        }
                    }
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    int newX = playerX - dx[playerDir];
                    int newY = playerY - dy[playerDir];

                    if (mazeSolved(playerX, playerY, size))
                    {
                        playerX = 1;
                        playerY = 1;
                        maze.resetMaze();
                        maze.randomizedDFS();
                        world = maze.convertToBinaryMatrix();
                        sf::sleep(sf::milliseconds(300));
                    }
                    else
                    {
                        if (!world[newX][newY])
                        {
                            playerX = newX;
                            playerY = newY;
                        }
                    }
                }
                if (event.key.code == sf::Keyboard::Left)
                {
                    --playerDir;

                    if (playerDir < 0)
                    {
                        playerDir = 3;
                    }
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    ++playerDir;

                    if (playerDir > 3)
                    {
                        playerDir = 0;
                    }
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(back);

        int dm = 1;

        if (playerDir == 1 || playerDir == 3)
        {
            dm = -1;
        }

        for (int i = 4; i > -1; --i)
        {
            int x = playerX + (i * dx[playerDir]);
            int y = playerY + (i * dy[playerDir]);

            if (x >= 0 && x < 2*size+1 && y >= 0 && y < 2*size+1)
            {
                int xl = x + (dy[playerDir] * dm);
                int yl = y + (dx[playerDir] * dm);

                if (world[xl][yl])
                {
                    window.draw(left_sprites[i]);
                }

                int xr = x - (dy[playerDir] * dm);
                int yr = y - (dx[playerDir] * dm);

                if (world[xr][yr])
                {
                    window.draw(right_sprites[i]);
                }

                if (world[x][y])
                {
                    window.draw(mid_sprites[i]);
                }
            }
        }

        window.display();
    }
}

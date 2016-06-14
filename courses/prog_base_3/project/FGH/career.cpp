#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "menu.h"
#include "game.h"
#include "career.h"
#define REQUIRED_POS_X 300
int choose_conc(RenderWindow &window, Sprite background, Sprite button_background, Font font, Player * player);
int career(RenderWindow &window, Sprite background, Sprite button_background, Font font, Keyboard::Key * keys, Player * player)
{
    Text button[3];
    int selected_button = -1;
    std::string str[3] = {"Play song", "Guitar shop", "Back"};
    Color selected_button_color = Color(123, 4 ,2);
    Color unselected_button_color = Color(198, 138, 72);
    for (int i = 0; i < 3; i++)
    {
        button[i].setColor(unselected_button_color);
        button[i].setString(str[i]);
        button[i].setPosition(BUTTON_FIRST_POS_X - str[i].length() * 10, BUTTON_FIRST_POS_Y + i * BUTTON_DELTA_POS);
        button[i].setCharacterSize(30);
        button[i].setFont(font);
    }
    Vector2i mouse_pos;
    Event event;
    while (window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                if (button[selected_button].getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
                {
                    switch (selected_button) {
                    case 0:
                        song_list(window, background, button_background, font, keys, player, true, choose_conc(window, background, button_background, font, player));
                        //player->update(game(window, keys, player, 0, true), 0);
                        break;
                    case 1:
                        shop(keys, window, background, button_background, font, player);
                        break;

                    case 2:
                        return 0;
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    selected_button = -1;
                }
            }
        }
        window.clear();
        window.draw(background);
        player->draw(window);
        mouse_pos = Mouse::getPosition(window);
        for (int i = 0; i < 3; i++)
        {
            if (button[i].getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
            {
                selected_button = i;
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (i == selected_button)
            {
                button[i].setColor(selected_button_color);
                button_background.setScale(button[i].getGlobalBounds().width + 10, button[i].getGlobalBounds().height + 10);
                button_background.setPosition(button[i].getGlobalBounds().left - 5, button[i].getGlobalBounds().top - 5);
                window.draw(button_background);
            }
            else
            {
                button[i].setColor(unselected_button_color);
            }

            window.draw(button[i]);
        }
        window.display();



    }
    return 0;
}

void shop(Keyboard::Key * keys, RenderWindow &window, Sprite background, Sprite button_background, Font font, Player * player)
{
    Text button[4];
    int selected_button = -1;
    int cost[5] = {300, 2000, 10000, 50000, 1000000};
    std::string str[4] = {"Buy", "Next", "Previous", "Back"};
    Color selected_button_color = Color(123, 4 ,2);
    Color unselected_button_color = Color(198, 138, 72);
    for (int i = 0; i < 4; i++)
    {
        button[i].setColor(unselected_button_color);
        button[i].setString(str[i]);
        button[i].setPosition(BUTTON_FIRST_POS_X - str[i].length() * 10, BUTTON_FIRST_POS_Y + i * BUTTON_DELTA_POS);
        button[i].setCharacterSize(30);
        button[i].setFont(font);
    }
    char buff[10];
    if (player->get_guitar() != 1)
    {
        sprintf(buff, ": %i", cost[0]);
        button[0].setString(str[0] + buff);
    }
    else
        button[0].setString(str[0] + ": seles");

    Vector2i mouse_pos;
    Image image;
    image.loadFromFile("guitar1.png");
    Texture guitars_texture[5];
    guitars_texture[3].loadFromImage(image);
    image.loadFromFile("guitar2.png");
    guitars_texture[2].loadFromImage(image);
    image.loadFromFile("guitar3.png");
    guitars_texture[4].loadFromImage(image);
    image.loadFromFile("guitar4.png");
    guitars_texture[1].loadFromImage(image);
    image.loadFromFile("guitar5.png");
    guitars_texture[0].loadFromImage(image);
    Sprite guitars[5];
    for (int i = 0; i < 5; i++)
    {
        guitars[i].setTexture(guitars_texture[i]);
        guitars[i].setPosition(425, 170);
    }
    int curr_guitar = 0;
    image.loadFromFile("frame.png");
    Texture frame_texture;
    frame_texture.loadFromImage(image);
    Sprite frame;
    frame.setTexture(frame_texture);
    frame.setPosition(400, 150);
    frame.setScale(550.0 / 300.0, 440.0 / 231.0);

    while (window.isOpen())
    {

        Event event;
        mouse_pos = Mouse::getPosition();
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                if (button[selected_button].getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
                {
                    switch (selected_button) {
                    case 0:
                        if (cost[curr_guitar] <= player->get_money() && curr_guitar >= player->get_guitar())
                        {
                            player->buy(curr_guitar, cost[curr_guitar]);
                            sprintf(buff, ": sales", cost[curr_guitar]);
                            button[0].setString(str[0] + buff);
                            player->update(0, 0);
                        }
                        break;
                    case 1:
                        curr_guitar++;
                        if (curr_guitar > 4)
                            curr_guitar = 0;
                        char buff[10];
                        if (player->get_guitar() <= curr_guitar)
                            sprintf(buff, ": %i$", cost[curr_guitar]);
                        else
                            sprintf(buff, ": sales", cost[curr_guitar]);
                        button[0].setString(str[0] + buff);
                        break;

                    case 2:
                        curr_guitar--;
                        if (curr_guitar < 0)
                            curr_guitar = 4;
                        sprintf(buff, ": %i", cost[curr_guitar]);
                        button[0].setString(str[0] + buff);
                        break;

                    case 3:
                        return;
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    selected_button = -1;

                }

            }
        }
        window.clear();
        window.draw(background);
        player->draw(window);
        mouse_pos = Mouse::getPosition(window);
        for (int i = 0; i < 4; i++)
        {
            if (button[i].getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
            {
                selected_button = i;
            }
        }
        for (int i = 0; i < 4; i++)
        {
            if (i == selected_button)
            {
                button[i].setColor(selected_button_color);
                button_background.setScale(button[i].getGlobalBounds().width + 10, button[i].getGlobalBounds().height + 10);
                button_background.setPosition(button[i].getGlobalBounds().left - 5, button[i].getGlobalBounds().top - 5);
                window.draw(button_background);
            }
            else
            {
                button[i].setColor(unselected_button_color);
            }

            window.draw(button[i]);
        }
        window.draw(guitars[curr_guitar]);
        window.draw(frame);
        window.display();
    }
}

int choose_conc(RenderWindow &window, Sprite background, Sprite button_background, Font font, Player * player)
{
    Text button[4];
    int selected_button = -1;
    int cost[5] = {0, 200, 1000, 5000, 100000};
    std::string str[4] = {"Lets rock", "Next", "Previous", "Back"};
    std::string name_conc[5] = {"Garage", "Cafe Merry Notes", "Bar Drunken Oyster", "Club STORM", "ZAXID Fest"};

    Color selected_button_color = Color(123, 4 ,2);
    Color unselected_button_color = Color(198, 138, 72);
    for (int i = 0; i < 4; i++)
    {
        button[i].setColor(unselected_button_color);
        button[i].setString(str[i]);
        button[i].setPosition(BUTTON_FIRST_POS_X - str[i].length() * 10, BUTTON_FIRST_POS_Y + i * BUTTON_DELTA_POS);
        button[i].setCharacterSize(30);
        button[i].setFont(font);
    }
    char buff[10];
    /*sprintf(buff, ": %i$", cost[0]);
    button[0].setString(str[0] + name_conc[0] + buff);*/
    Text required;
    required.setPosition(REQUIRED_POS_X, BUTTON_FIRST_POS_Y);
    required.setColor(unselected_button_color);
    required.setString(name_conc[0] + "\nRequired:\nMoney: 0\nLvl: 1");
    required.setCharacterSize(30);
    required.setFont(font);
    Vector2i mouse_pos;
    int curr_conc = 0;
    while (window.isOpen())
    {

        Event event;
        mouse_pos = Mouse::getPosition();
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                if (button[selected_button].getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
                {
                    switch (selected_button) {
                    case 0:
                        if (cost[curr_conc] <= player->get_money() && player->get_lvl() >= curr_conc * curr_conc + 1)
                            return curr_conc;
                        break;
                    case 1:
                        curr_conc++;
                        if (curr_conc > 4)
                            curr_conc = 0;
                        char buff[10];
                        sprintf(buff, "\nRequired:\nMoney: %i\nLvl: %i", cost[curr_conc], curr_conc * curr_conc + 1);
                        required.setString(name_conc[curr_conc] + buff);
                        break;

                    case 2:
                        curr_conc--;
                        if (curr_conc < 0)
                            curr_conc = 4;
                        sprintf(buff, "\nRequired:\nMoney: %i\nLvl: %i", cost[curr_conc], curr_conc * curr_conc + 1);
                        required.setString(name_conc[curr_conc] + buff);
                        break;

                    case 3:
                        return -1;
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    selected_button = -1;

                }

            }
        }
        window.clear();
        window.draw(background);
        player->draw(window);
        mouse_pos = Mouse::getPosition(window);
        for (int i = 0; i < 4; i++)
        {
            if (button[i].getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
            {
                selected_button = i;
            }
        }
        for (int i = 0; i < 4; i++)
        {
            if (i == selected_button)
            {
                button[i].setColor(selected_button_color);
                button_background.setScale(button[i].getGlobalBounds().width + 10, button[i].getGlobalBounds().height + 10);
                button_background.setPosition(button[i].getGlobalBounds().left - 5, button[i].getGlobalBounds().top - 5);
                window.draw(button_background);
            }
            else
            {
                button[i].setColor(unselected_button_color);
            }
            window.draw(required);
            window.draw(button[i]);
        }
        window.display();
    }
}

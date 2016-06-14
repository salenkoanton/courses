#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include "menu.h"
#include "game.h"
#include "career.h"


using namespace sf;
std::string fromKeyboardToChar(Keyboard::Key key);
void settings(Keyboard::Key * keys, RenderWindow &window, Sprite background, Sprite button_background, Font font);
int main()
{

    RenderWindow window(VideoMode(WINDOW_WIGHT, WINDOW_HIGHT), "Guitar Hero", Style::Fullscreen);    //create window
    window.setFramerateLimit(120);
    Keyboard::Key keys[6] = {Keyboard::Z, Keyboard::X, Keyboard::C, Keyboard::V, Keyboard::B, Keyboard::LShift};
    std::string str[4] = {"Career", "Quick game", "Settings", "Exit"};
    Image image;                                    //image for texture, i'll rename it later
    Texture background_texture;                 //textures for buttons
    Sprite background;                               //buttons
    image.loadFromFile("Rock-wallpapers-10.jpg");
    background_texture.loadFromImage(image);
    background_texture.setSmooth(true);
    background.setTexture(background_texture);
    background.setScale(WINDOW_WIGHT / float(background_texture.getSize().x), WINDOW_WIGHT / float(background_texture.getSize().x));
    Text button[5];
    Color selected_button_color = Color(123, 4 ,2);
    Color unselected_button_color = Color(198, 138, 72);
    Image b_image;
    b_image.create(1, 1, Color(254, 254, 204));
    Texture b_texture;
    b_texture.loadFromImage(b_image);
    Sprite button_background;
    button_background.setTexture(b_texture);
    int score;
    int selected_button = 0;
    Font font;
    font.loadFromFile("font/FIRESTARTER.ttf");
    Player player("career.txt", font);
    for (int i = 0; i < 4; i++)
    {
        button[i].setColor(unselected_button_color);
        button[i].setString(str[i]);
        button[i].setPosition(BUTTON_FIRST_POS_X - str[i].length() * 10, BUTTON_FIRST_POS_Y + i * BUTTON_DELTA_POS);
        button[i].setCharacterSize(30);
        button[i].setFont(font);
    }
    Vector2i mouse_pos;
    while (window.isOpen())
    {

        Event event;
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
                        career(window, background, button_background, font, keys, &player);
                        break;
                    case 1:
                        song_list(window, background, button_background, font, keys, &player, false, 0);
                        break;
                    case 2:
                        settings(keys, window, background, button_background, font);
                        break;

                    case 3:
                        window.close();
                        break;

                    default:
                        break;
                    }
                }
            }

        }
        window.clear();
        window.draw(background);
        player.draw(window);
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

        window.display();
    }
    return 0;
}

void settings(Keyboard::Key * keys, RenderWindow &window, Sprite background, Sprite button_background, Font font)
{
    Text button[7];
    int selected_button = -1;
    std::string str[7] = {"Green: ", "Red: ", "Yellow: ", "Blue: ", "Orange: ", "Rock power: ", "Back"};
    Color selected_button_color = Color(123, 4 ,2);
    Color unselected_button_color = Color(198, 138, 72);
    bool flag[6] = {false, false, false, false, false, false};
    for (int i = 0; i < 6; i++)
    {
        button[i].setColor(unselected_button_color);
        button[i].setString(str[i] + fromKeyboardToChar(keys[i]));
        button[i].setPosition(BUTTON_FIRST_POS_X - str[i].length() * 10, BUTTON_FIRST_POS_Y + i * BUTTON_DELTA_POS);
        button[i].setCharacterSize(30);
        button[i].setFont(font);
    }
    button[6].setColor(unselected_button_color);
    button[6].setString(str[6]);
    button[6].setPosition(BUTTON_FIRST_POS_X - str[6].length() * 10, BUTTON_FIRST_POS_Y + 6 * BUTTON_DELTA_POS);
    button[6].setCharacterSize(30);
    button[6].setFont(font);
    Vector2i mouse_pos;
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
                        break;
                    case 1:
                        break;

                    case 2:

                        break;

                    case 3:

                        break;

                    case 4:
                        break;
                    case 5:

                        break;
                    case 6:
                        return;
                        break;
                    default:
                        break;
                    }
                    flag[selected_button] = true;
                }
                else
                {
                    for (int i = 0; i < 6; i++)
                        flag[i] = false;
                    selected_button = -1;

                }

            }
            if (event.type == Event::KeyPressed && selected_button != -1 && flag[selected_button])
            {
                bool flag1 = true;
                for (int i = 0; i < 6; i++)
                    if (keys[i] == event.key.code)
                    {
                        flag1 = false;
                        break;
                    }
                if (flag1)
                {
                    button[selected_button].setString(str[selected_button] + fromKeyboardToChar(event.key.code));
                    keys[selected_button] = event.key.code;
                }
            }



        }
        window.clear();
        window.draw(background);
        mouse_pos = Mouse::getPosition(window);
        for (int i = 0; i < 7; i++)
        {
            if (button[i].getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
            {
                selected_button = i;
            }
        }
        for (int i = 0; i < 7; i++)
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
}

std::string fromKeyboardToChar(Keyboard::Key key)
{
    switch (key){
    case Keyboard::A: return "A";
        break;
    case Keyboard::S: return "S";
        break;
    case Keyboard::D: return "D";
        break;
    case Keyboard::F: return "F";
        break;
    case Keyboard::G: return "G";
        break;
    case Keyboard::H: return "H";
        break;
    case Keyboard::J: return "J";
        break;
    case Keyboard::K: return "K";
        break;
    case Keyboard::L: return "L";
        break;
    case Keyboard::Z: return "Z";
        break;
    case Keyboard::X: return "X";
        break;
    case Keyboard::C: return "C";
        break;
    case Keyboard::V: return "V";
        break;
    case Keyboard::B: return "B";
        break;
    case Keyboard::N: return "N";
        break;
    case Keyboard::M: return "M";
        break;
    case Keyboard::Q: return "Q";
        break;
    case Keyboard::W: return "W";
        break;
    case Keyboard::E: return "E";
        break;
    case Keyboard::R: return "R";
        break;
    case Keyboard::T: return "T";
        break;
    case Keyboard::Y: return "Y";
        break;
    case Keyboard::U: return "U";
        break;
    case Keyboard::I: return "I";
        break;
    case Keyboard::O: return "O";
        break;
    case Keyboard::P: return "P";
        break;
    case Keyboard::Num1: return "Num1";
        break;
    case Keyboard::Num2: return "Num2";
        break;
    case Keyboard::Num3: return "Num3";
        break;
    case Keyboard::Num4: return "Num4";
        break;
    case Keyboard::Num5: return "Num5";
        break;
    case Keyboard::Num6: return "Num6";
        break;
    case Keyboard::Num7: return "Num7";
        break;
    case Keyboard::Num8: return "Num8";
        break;
    case Keyboard::Num9: return "Num9";
        break;
    case Keyboard::Num0: return "Num0";
        break;
    case Keyboard::LShift: return "LShift";
        break;
    default:
        return "";
    }
}

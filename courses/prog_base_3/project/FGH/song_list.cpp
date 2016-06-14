#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "song_list.h"
#define BUTTON_LIST_POS_X 390
#define TEXT_BACKGROUND_POS_X 350
#define TEXT_BACKGROUND_POS_Y 150
#define MUSIC_START_POS 30
#define MUSIC_END_POS 50
using namespace sf;
int song_list(RenderWindow &window, Sprite background, Sprite button_background, Font font, Keyboard::Key * keys, Player * player, bool isCareer, int conc)
{
    if (conc == -1)
        return 0;
    int song_count = 6;
    char * filenames_music[song_count] = {"Scorpions.wav", "music3.ogg", "mozart.wav", "kapital.wav", "paranoid.wav", "bon_jovi.wav"};
    char * filenames_notes[song_count] = {"song0tmp16.ghfile", "song2tmp11.ghfile", "song5tmp3.ghfile", "song4tmp1.ghfile", "song6tmp2.ghfile", "song7tmp1.ghfile"};
    int pause_time[song_count] = {580, 650, 300, 560, 0, 0};
    Text button[song_count];
    int selected_button = -1;
    std::string str[song_count] = {"Scorpions - Rock you like a hurricane", "Avenged Sevenfold - Bat country", "Charlie Parra del Riego - Rondo alla turca", "Lyapis Trubetskoi - Kapital", "Black Sabbath - Paranoid", "Bon Jovi - Livi'n on a prayer"};
    for (int i = 0; i < song_count; i++)
    {
        char buff[20];
        sprintf(buff, "\t%i", player->get_score(i));
        str[i] += buff;
    }
    Color selected_button_color = Color(123, 4 ,2);
    Color unselected_button_color = Color(198, 138, 72);
    for (int i = 0; i < song_count; i++)
    {
        button[i].setColor(unselected_button_color);
        button[i].setString(str[i]);
        button[i].setPosition(BUTTON_LIST_POS_X, BUTTON_FIRST_POS_Y + i * BUTTON_DELTA_POS);
        button[i].setCharacterSize(20);
        button[i].setFont(font);
    }
    Image image;
    image.loadFromFile("text_background.png");
    Texture text_background_texture;
    text_background_texture.loadFromImage(image);
    Sprite text_background;
    text_background.setTexture(text_background_texture);
    text_background.setPosition(TEXT_BACKGROUND_POS_X, TEXT_BACKGROUND_POS_Y);
    text_background.setScale(700.0 / text_background_texture.getSize().x, 500.0 / text_background_texture.getSize().y);
    image.loadFromFile("frame.png");
    Texture frame_texture;
    frame_texture.loadFromImage(image);
    Sprite frame;
    frame.setTexture(frame_texture);
    frame.setPosition(TEXT_BACKGROUND_POS_X, TEXT_BACKGROUND_POS_Y);
    frame.setScale(700.0 / 300.0, 500.0 / 231.0);
    Text back_button;
    back_button.setCharacterSize(30);
    back_button.setColor(unselected_button_color);
    back_button.setFont(font);
    back_button.setPosition(390, 570);
    back_button.setString("Back");
    Music music;
    int selected_music = -1;
    int score;
    bool music_volume_flag = false;
    Vector2i mouse_pos;
    Event event;
    while (window.isOpen())
    {
        if (selected_button != -1)
        {
            if (selected_music != selected_button)
            {
                selected_music = selected_button;
                music.openFromFile(filenames_music[selected_button]);
                music.play();
                music.setPlayingOffset(seconds(MUSIC_START_POS));
                music_volume_flag = false;
            }
           // music.play();
        }
        else
            music.stop();
        if (!music_volume_flag)
        {
            float volume = float(music.getPlayingOffset().asSeconds() - MUSIC_START_POS + 1) / 10 * 100;
            if (volume < 100 && volume > 0)
                music.setVolume(volume);
            else
                music_volume_flag = true;
        }
        if (music.getPlayingOffset().asSeconds() > MUSIC_END_POS)
            music.setPlayingOffset(seconds(MUSIC_START_POS));
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
            {
                music.stop();
                window.close();
            }
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                if (selected_button != -1)
                    if (button[selected_button].getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
                    {
                        music.stop();
                        while (game(window, keys, player, selected_button, isCareer, filenames_music[selected_button], filenames_notes[selected_button], pause_time[selected_button], conc) == -1);
                    }
                    else
                    {
                        selected_button = -1;
                    }

                if (back_button.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
                {
                    return 0;
                }
            }
        }
        window.clear();
        window.draw(background);
        window.draw(text_background);
        window.draw(frame);
        mouse_pos = Mouse::getPosition(window);
        for (int i = 0; i < song_count; i++)
        {
            if (button[i].getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
            {
                selected_button = i;
            }
        }
        if (back_button.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
        {
            selected_button = -1;
            back_button.setColor(selected_button_color);
            button_background.setScale(back_button.getGlobalBounds().width + 10, back_button.getGlobalBounds().height + 10);
            button_background.setPosition(back_button.getGlobalBounds().left - 5, back_button.getGlobalBounds().top - 5);
            window.draw(button_background);
        }
        else
            back_button.setColor(unselected_button_color);
        for (int i = 0; i < song_count; i++)
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
        window.draw(back_button);
        window.display();



    }
    return 0;
}

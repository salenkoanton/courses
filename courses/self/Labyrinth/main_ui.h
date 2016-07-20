#ifndef MAIN_UI
#define MAIN_UI
#define WINDOW_WIGHT 640
#define WINDOW_HIGHT 480
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <windows.h>
#include "player.h"
#include "map.h"
#include "enums.h"
#include "dllmanager.h"
#include "list.h"
using namespace sf;
enum run_return_statemant{
    FAIL = -6,
    RELOAD_LIB,
    FAIL_IN_LOAD_LIB,
    FAIL_IN_LOAD_MAP,
    EXIT,
    LOADED
};

class Main_UI{
private:
    int MAX_LVL;
    //static const char BEGIN_STRING[8] = "Moves: ";
    char textString[3000];
    char ** map_files;
    char cur_work_dir[100];
    int cur_lvl;
    Map * map;
    Player * player;
    DLLManager * dll;
    Texture blocks, arrow, hero;
    Text text;
    Font font;
    Color textColor;
    bool load_dll(const wchar_t * dll_name)
    {
        if (dll != NULL)
            delete dll;
        dll = new DLLManager(dll_name);
        return dll->get_bot() == NULL;
    }
    int choose_lib(RenderWindow &window, char ** out_strings, int file_count)
    {
        int cur_lib = 0;
        Color cur_text_color = Color(200, 200, 200);
        Color text_color = Color(60, 40, 200);
        Text dll_text[file_count];
        Vector2i mouse_pos = Vector2i(0, 0);
        for (int i = 0; i < file_count; i++)
        {
            dll_text[i].setFont(font);
            dll_text[i].setPosition(0, i * (dll_text[0].getCharacterSize() + 2));
            dll_text[i].setColor(text_color);
            dll_text[i].setString(out_strings[i]);
        }
        dll_text[cur_lib].setColor(cur_text_color);
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::MouseWheelMoved)
                {
                    int delta_y = (float) event.mouseWheel.delta * 10;
                    if (!(delta_y > 0 && dll_text[0].getPosition().y >= 0) && !(delta_y < 0 && dll_text[file_count - 1].getPosition().y + dll_text[file_count - 1].getGlobalBounds().height < window.getSize().y))
                        for (int i = 0; i < file_count; i++)
                            dll_text[i].move(0, delta_y);
                }
                if (event.type == Event::MouseMoved)
                {
                    mouse_pos = Mouse::getPosition(window);
                    dll_text[cur_lib].setColor(text_color);
                    cur_lib = (mouse_pos.y - dll_text[0].getPosition().y) / (dll_text[0].getCharacterSize() + 2);
                    if (cur_lib >= file_count)
                        cur_lib = file_count - 1;
                    if (cur_lib < 0)
                        cur_lib = 0;
                    if (dll_text[cur_lib].getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
                        dll_text[cur_lib].setColor(cur_text_color);
                }
                if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && dll_text[cur_lib].getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
                    return cur_lib;

                if (event.type == Event::KeyReleased)
                {
                    switch (event.key.code)
                    {
                        case Keyboard::Return: return cur_lib;
                        default : break;
                    }
                }
                if (event.type == Event::Closed)
                    window.close();
            }
            window.clear();
            for(int i = 0; i < file_count; i++)
            {
                window.draw(dll_text[i]);
            }
            window.display();

        }
        return EXIT;
    }

    enum run_return_statemant setMap()
    {
        if (cur_lvl > MAX_LVL)
        {
            cur_lvl = MAX_LVL;
        }
        unsigned hight, wight, start_x, start_y;
        std::fstream file;
        char dir[strlen(map_files[cur_lvl]) + strlen(cur_work_dir) + 10];
        strcpy(dir, cur_work_dir);
        strcat(dir, "\\Maps\\");
        strcat(dir, map_files[cur_lvl]);
        file.open(dir, std::ios::in);
        if (file == NULL)
            return FAIL;
        file >> hight;
        file >> wight;
        file >> start_x;
        file >> start_y;
        enum block ** map_arr = new enum block * [hight];
        for (unsigned i = 0; i < hight; i++)
            map_arr[i] = new enum block [wight];
        for (unsigned i = 0; i < hight; i++)
            for (unsigned j = 0; j < wight; j++)
            {
                {
                    int info;
                    file >> info;
                    switch (info)
                    {
                        case 1: map_arr[i][j] = ROAD; break;
                        case 2: map_arr[i][j] = COMPLETED; break;
                        default: map_arr[i][j] = WALL; break;
                    }
                }
            }
        file.close();
        if (player != NULL)
            player->delMap();
        map->reset(hight, wight, map_arr, start_x, start_y);
        if (player != NULL)
            player->setMap(map);
        text.setPosition(map->get_wight() * BLOCK_WIGHT, 0);
        return LOADED;
    }
    void massage(const char * str)
    {
        MessageBoxA(0, str, "Message", MB_OK | MB_ICONINFORMATION);
    }

    char ** find_files(const char * expansion, const char * directory, int * count)
    {
        DIR *dp;
        struct dirent *ep;
        int files_count = 0;
        dp = opendir (directory);
        if (dp != NULL) {
            while ((ep = readdir (dp))) {
                if(32 == dp->dd_dta.attrib) {
                    if (strstr(dp->dd_dir.d_name, expansion) != NULL)
                        files_count++;
                }
            }
            (void) closedir (dp);
        }
        else return NULL;
        char ** out_str = new char * [files_count];
        dp = opendir (directory);
        if (dp != NULL) {
            int i = 0;
            while ((ep = readdir (dp))) {
                if(32 == dp->dd_dta.attrib) {
                    if (strstr(dp->dd_dir.d_name, expansion) != NULL)
                    {
                        out_str[i] = new char[strlen(dp->dd_dir.d_name) + 1];
                        strcpy(out_str[i++], dp->dd_dir.d_name);
                        if (i >= files_count)
                            break;
                    }
                }
            }

            (void) closedir (dp);

        }
        else return NULL;
        *count = files_count;
        return out_str;
    }
    enum run_return_statemant load_map_files()
    {
        char * dir = new char[strlen(cur_work_dir) + 10];
        strcpy(dir, cur_work_dir);
        strcat(dir, "\\Maps");
        map_files = find_files(".map", dir, &MAX_LVL);
        delete [] dir;
        if (map_files == NULL)
            return FAIL_IN_LOAD_MAP;
        return LOADED;
    }

    void bot(int count_moves)
    {
        switch(dll->get_bot()((dll->get_list())->get_list(), player->check_move(UP), player->check_move(RIGHT), player->check_move(DOWN), player->check_move(LEFT)))
        {
            case UP: player->move_up(); break;
            case DOWN: player->move_down(); break;
            case LEFT: player->move_left(); break;
            case RIGHT: player->move_right(); break;
            default: break;
        }
        sprintf(textString, "%s\nList size: %i\nMoves: %i", map_files[cur_lvl], dll->get_list()->size(), count_moves);
        text.setString(textString);
    }


public:
    Main_UI()
    {
        wchar_t buffer[100];
        map_files = NULL;
        GetCurrentDirectory(sizeof(buffer),buffer);
        wcstombs(cur_work_dir, buffer, 100 + 1);
        cur_work_dir[99] = '\0';
        if (load_map_files() == FAIL_IN_LOAD_MAP)
            exit(1);
        player = NULL;
        blocks.loadFromFile("Images/blocks.bmp");
        map = new Map(blocks);
        Image image;
        image.loadFromFile("Images/arrow.png");
        image.createMaskFromColor(image.getPixel(0, 0));
        arrow.loadFromImage(image);
        hero.loadFromFile("Images/hero.png");
        cur_lvl = 0;
        if (setMap() == FAIL)
            exit(1);
        player = new Player(arrow, hero, map);
        dll = NULL;
        font.loadFromFile("Fonts/KeepCalm-Medium.ttf");
        textColor = Color(255, 0, 0);
        text.setFont(font);
        sprintf(textString, "%s\nList size: 0\nMoves: 0", map_files[cur_lvl]);
        text.setString(textString);
        text.setColor(textColor);
    }

    enum run_return_statemant load_dll(RenderWindow &window)
    {
        char ** out_strings;
        int file_count;
        out_strings = find_files(".dll", cur_work_dir, &file_count);
        if (out_strings == NULL)
            return FAIL;
        wchar_t file_name[100];
        int chosen_lib = this->choose_lib(window, out_strings, file_count);
        if (chosen_lib == EXIT)
            return EXIT;
        swprintf(file_name, L"%hs", out_strings[chosen_lib]);
        for (int i = 0; i < file_count; i++)
            delete [] out_strings[i];
        delete [] out_strings;
        if (load_dll(file_name)) return FAIL_IN_LOAD_LIB;
        return LOADED;
    }

    enum run_return_statemant run(RenderWindow &window){
        Text button_text_choose_lib, button_text_run;
        button_text_run.setFont(font);
        button_text_run.setString("Run");
        button_text_run.setColor(textColor);
        button_text_run.setPosition(text.getPosition() + Vector2f(0, float(text.getGlobalBounds().height + 2.0)));
        button_text_choose_lib.setFont(font);
        button_text_choose_lib.setString("Choose lib");
        button_text_choose_lib.setColor(textColor);
        button_text_choose_lib.setPosition(button_text_run.getPosition() + Vector2f(0, float(button_text_run.getGlobalBounds().height + 2.0)));
        int count_moves = 0;
        Clock timer;
        timer.restart();
        const int timer_max_time = 100000;
        bool is_run = false;
        Vector2i mouse_pos;
        while (window.isOpen()){
            Event event;
            while (window.pollEvent(event))
            {
                mouse_pos = Mouse::getPosition(window);
                if (event.type == Event::KeyReleased)
                {
                    switch (event.key.code)
                    {
                        case Keyboard::W: player->move_up(); break;
                        case Keyboard::S: player->move_down(); break;
                        case Keyboard::A: player->move_left(); break;
                        case Keyboard::D: player->move_right(); break;
                        case Keyboard::Space: bot(++count_moves); break;
                        default : break;

                    }
                }
                if (event.type == Event::MouseButtonReleased)
                    if (event.mouseButton.button == Mouse::Left)
                    {
                        if (button_text_choose_lib.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
                        {
                            cur_lvl = 0;
                            window.clear();
                            if (setMap() == LOADED)
                                return RELOAD_LIB;
                            return FAIL;
                        }
                        if (button_text_run.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
                        {
                            if (is_run)
                            {
                                button_text_run.setString("Run");
                            }
                            else
                                button_text_run.setString("Stop");
                            is_run = !is_run;
                        }
                    }
                if (event.type == Event::Closed)
                    window.close();
            }
            if (timer.getElapsedTime().asMicroseconds() > timer_max_time && is_run)
            {
                timer.restart();
                bot(++count_moves);
            }
            if (player->get_cur_block() == COMPLETED)
            {
                massage("Sucsess");
                cur_lvl++;
                if (cur_lvl >= MAX_LVL)
                {
                    massage("Complited!!");
                    return EXIT;
                }
                if (setMap() == FAIL)
                    return FAIL;
                button_text_run.setPosition(text.getPosition() + Vector2f(0, float(text.getGlobalBounds().height + 2.0)));
                button_text_choose_lib.setPosition(button_text_run.getPosition() + Vector2f(0, float(button_text_run.getGlobalBounds().height + 2.0)));
            }
            window.clear();
            map->draw(window);
            player->draw(window);
            window.draw(text);
            window.draw(button_text_choose_lib);
            window.draw(button_text_run);
            window.display();
        }
        return EXIT;
    }
    ~Main_UI()
    {
        delete player;
        delete map;
    }
};

#endif // MAIN_UI


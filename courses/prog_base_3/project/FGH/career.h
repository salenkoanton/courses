#ifndef CAREER
#define CAREER
#include <iostream>
#include <fstream>
#include <string.h>
#include <SFML/Graphics.hpp>
//#include "song_list.h"
using namespace sf;
class Player
{
private:
    int guitar;
    int exp;
    int money;
    int lvl_exp;
    //std::string name;
    int lvl;
    int scores[6];
    char * filename;
    Text text;


public:
    Player(char * filename, Font &font)
    {
        std::fstream file;
        file.open(filename, std::ios::in);
        file >> guitar;
        file >> exp;
        file >> money;
        file >> lvl;
        file >> lvl_exp;
        for (int i = 0; i < 6; i++)
            file >> scores[i];
       // std::getline(file, name);
        file.close();
        this->filename = new char[strlen(filename)];
        strcpy(this->filename, filename);
        char buff[100];
        sprintf(buff, "Exp: %i\nMoney: %i\nLvl: %i\n%i exp left", exp, money, lvl, lvl_exp - exp);
        text = Text();
        text.setString(buff);
        text.setFont(font);
        text.setCharacterSize(30);
        text.setColor(Color(198, 138, 72));
        text.setPosition(1130, 50);
    }/*
    Player(std::string name)
    {
        this->name = name;
        guitar = 0;
        money = 0;
        exp = 0;
        lvl = 1;
        lvl_exp = 1000;
        for (int i = 0; i < 3; i++)
            scores[i] = 0;
    }*/
    void update(int score, int song){
        if (score > scores[song])
        {
            scores[song] = score;
            exp = 0;
            for (int i = 0; i < 6; i++)
                exp += scores[i];
            while (exp > lvl_exp)
            {
                lvl_exp *= 2;
                lvl++;
            }
        }
        std::fstream file;
        file.open(filename, std::ios::out);
        file << guitar << std::endl;
        file << exp << std::endl;
        file << money << std::endl;
        file << lvl << std::endl;
        file << lvl_exp << std::endl;
        for (int i = 0; i < 6; i++)
            file << scores[i] << std::endl;
        file.close();
        char buff[100];
        sprintf(buff, "Exp: %i\nMoney: %i\nLvl: %i\n%i exp left", exp, money, lvl, lvl_exp - exp);
        text.setString(buff);
    }
    int get_lvl(){
        return lvl;
    }
    int get_exp(){
        return exp;
    }
    int get_money(){
        return money;
    }
    int get_score(int song){
        return scores[song];
    }
    int get_guitar(){
        return guitar;
    }
    void buy(int guitar, int cost)
    {
        this->guitar = guitar + 1;
        money -= cost;
    }
    void earn_money(int mon)
    {
        money += mon;
    }
    void draw(RenderWindow &window )
    {
        window.draw(text);
    }
};


int career(RenderWindow &window, Sprite background, Sprite button_background, Font font, Keyboard::Key * keys, Player * player);
void shop(Keyboard::Key * keys, RenderWindow &window, Sprite background, Sprite button_background, Font font, Player * player);
#endif // CAREER


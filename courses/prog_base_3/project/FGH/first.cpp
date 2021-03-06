#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "menu.h"
#include "game.h"
using namespace sf;
int results(RenderWindow &window, int score, bool isCareer, float good_notes, int max_notes, Player * player, Font font, int conc);
int pause(Keyboard::Key * keys, RenderWindow &window, Font font);
struct key_data{                                        //struct for list
    Vector2f pos;
    int index;
    float time;
    float tail_time;
    bool isPressed;
    Vector2f pos_tail;
};

struct ListNode{
    key_data * data;
    struct ListNode * next;

};

class List{                                             //list

private: struct ListNode * tail, * head;
    int cnt;
    public:
    List(){
        tail = new struct ListNode;
        head = new struct ListNode;
        tail->data = NULL;
        tail->next = NULL;
        head->next = tail;
        head->data = NULL;
        cnt = 0;
    }
    int count(){
        return cnt;
    }

    void add(key_data * data)
    {
        struct ListNode * tmp = new struct ListNode, * cur;

        cur = head;
        for(int i = 0; i < cnt; i++)
            cur = cur->next;
        tmp->data = data;
        cur->next = tmp;
        cnt++;
    }
    struct key_data * get(int pos)
    {
        if (pos >= cnt)
            return NULL;
        struct ListNode * tmp = head->next;
        for(int i = 0; i < pos; i++)
            tmp = tmp->next;
        return tmp->data;
    }

    struct key_data * del(int pos)
    {
        struct ListNode * tmp = head;
        if (pos < cnt)
        for(int i = 0; i < pos; i++)
            tmp = tmp->next;
        else return NULL;
        struct key_data * data = tmp->next->data;
        tmp->next = tmp->next->next;
        cnt--;
        return data;
    }

};


int game(RenderWindow &window, Keyboard::Key * keys, Player * player, int song_id, bool isCareer, char * file_music, char * file_notes, int start_pause_time, int conc)
{
    srand(time(NULL));
    //int screen_h = 480;
    //int screen_w = 640;
    //float h_sc = float(screen_h) / 768;
    //float w_sc = float(screen_w) / 1366;
    int count = 0;

    List list = List();                             //list for sprites
    Vector2f * pos;                                 //temp sprite for including in list
    Clock clock_start;                              //clock for getElapsedTime
    Image buffer;                                   //new image for background (set the line)
    buffer.create(1366, 768, Color::Black);
    Vector2f vect[5];
    vect[0] = Vector2f(-0.32, 1);
    vect[1] = Vector2f(-0.16, 1);
    vect[2] = Vector2f(0, 1);
    vect[3] = Vector2f(0.16, 1);
    vect[4] = Vector2f(0.32, 1);

    for (int j = 80; j < 568; j++)
    {
        int alfa_tmp;
        if (j < 140)
            alfa_tmp = (j - 80) * 256 / 60;
        else
            alfa_tmp = 255;
        buffer.setPixel(413 - (j - 479) / 2.5, j + 200, Color(255, 255, 255, alfa_tmp));
        buffer.setPixel(412 - (j - 479) / 2.5, j + 200, Color(200, 200, 200, alfa_tmp));
        buffer.setPixel(414 - (j - 479) / 2.5, j + 200, Color(200, 200, 200, alfa_tmp));

        buffer.setPixel(411 - (j - 479) / 2.5, j + 200, Color(150, 150, 150, alfa_tmp));
        buffer.setPixel(415 - (j - 479) / 2.5, j + 200, Color(150, 150, 150, alfa_tmp));
        buffer.setPixel(953 + (j - 479) / 2.5, j + 200, Color(255, 255, 255, alfa_tmp));
        buffer.setPixel(952 + (j - 479) / 2.5, j + 200, Color(200, 200, 200, alfa_tmp));
        buffer.setPixel(954 + (j - 479) / 2.5, j + 200, Color(200, 200, 200, alfa_tmp));
        buffer.setPixel(951 + (j - 479) / 2.5, j + 200, Color(170, 170, 170, alfa_tmp));
        buffer.setPixel(955 + (j - 479) / 2.5, j + 200, Color(170, 170, 170, alfa_tmp));
/*
        buffer.setPixel(507 + (j - 479) * vect[0].x, j + 200, Color::White);
        buffer.setPixel(595 + (j - 479) * vect[1].x, j + 200, Color::White);
        buffer.setPixel(683 + (j - 479) * vect[2].x, j + 200, Color::White);
        buffer.setPixel(771 + (j - 479) * vect[3].x, j + 200, Color::White);
        buffer.setPixel(859 + (j - 479) * vect[4].x, j + 200, Color::White);
*/

    }                                           //end setting line
    /*for (int j = 280; j < 680; j++)
        for (int i = 465 + (679 - j) / 2.5; i < 903 - (679 - j)/2.5; i++)
            buffer.setPixel(i, j,  Color(20, 20, 20));*/
    buffer.createMaskFromColor(Color::Black);

    Image line_image;
    line_image.create(500, 4, Color::White);
    for (int i = 0; i < 500; i++)
    {

        line_image.setPixel(i, 2, Color(255, 255, 255, 150));
        line_image.setPixel(i, 3, Color(200, 200, 200, 150));
        line_image.setPixel(i, 1, Color(255, 255, 255, 150));
        line_image.setPixel(i, 0, Color(200, 200, 200, 150));
    }
    Texture line_texture;
    line_texture.loadFromImage(line_image);

    Vector2f lines_pos[20];
    for (int i = 0; i < 20; i++)
        lines_pos[i] = Vector2f(1366 / 2, 220);
    lines_pos[19].y += 1.0;
    Sprite line;
    line.setTexture(line_texture);

    Image image;                                    //image for texture, i'll rename it later
    Texture notesTexture, bufferTexture, buttonsTexture, backgroundTexture, fretDeckTexture;                 //textures for buttons
    Sprite button[5], notes[11], background, fretDeck[657];                               //buttons
    image.loadFromFile("fretdeck.png");
    fretDeckTexture.loadFromImage(image);
    fretDeckTexture.setSmooth(true);
    for (int i = 1; i < 658; i++)
    {
        fretDeck[i - 1].setTexture(fretDeckTexture);
        fretDeck[i - 1].setTextureRect(IntRect(0, i, 329, 1));
        fretDeck[i - 1].setScale(float(400) / 329 * (i + 150) / 495, 1);
        fretDeck[i - 1].setPosition(483 + (350 - i)/ 2.5, 280 + i);
    }
    image.loadFromFile("notes.bmp");          //load image
    notesTexture.loadFromImage(image);
    notesTexture.setSmooth(true);                        //set smooth
    image.loadFromFile("fretbuttons-3.png");          //load image
    buttonsTexture.loadFromImage(image);
    buttonsTexture.setSmooth(true);
    char buff[20];
    sprintf(buff, "background%i.jpg", rand() % 10);
    image.loadFromFile(buff);
    backgroundTexture.loadFromImage(image);
    backgroundTexture.setSmooth(true);
    background.setTexture(backgroundTexture);
    background.setScale(1366 / (float) 800, 768 / (float) 600);
    /*switch (rand() % 3) {
    case 0:
        image.loadFromFile("763.jpg");
        backgroundTexture.loadFromImage(image);
        backgroundTexture.setSmooth(true);
        background.setTexture(backgroundTexture);
        background.setScale(1366 / (float) 910, 768 / (float) 512);
        break;
    case 1:
        image.loadFromFile("background.jpg");
        backgroundTexture.loadFromImage(image);
        backgroundTexture.setSmooth(true);
        background.setTexture(backgroundTexture);
        background.setScale(1366 / (float) 1280, 768 / (float) 720);
        break;
    case 2:
        image.loadFromFile("background2.jpg");
        backgroundTexture.loadFromImage(image);
        backgroundTexture.setSmooth(true);
        background.setTexture(backgroundTexture);
        background.setScale(1366 / (float) 3888, 768 / (float) 2592);
        break;
    default:
        break;
    }*/
    //image.loadFromFile("background.jpg");

    for(int i = 0; i < 5; i++)
    {
        button[i].setTexture(buttonsTexture);
        button[i].setPosition(100 * i + 433, 410 + 200);
        button[i].setTextureRect(IntRect(i * 672 / 5, 0, 672 / 5, 81));
        button[i].setScale(500/float(672), 500/float(672));
        notes[i].setTexture(notesTexture);
        notes[i].setTextureRect(IntRect(i * 640 / 5, 0, 640 / 5, 640 / 5));
        notes[i].setScale(500/float(640), 500/float(640));
        notes[i].setOrigin(50, 50);
        notes[i + 5].setTexture(notesTexture);
        notes[i + 5].setTextureRect(IntRect(i * 640 / 5, 640 / 5 * 2, 640 / 5, 640 / 5));
        notes[i + 5].setScale(500/float(640), 500/float(640));
        notes[i + 5].setOrigin(50, 50);

    }                                               //creating of 5 buttons in the bottom
    notes[10].setTexture(notesTexture);
    notes[10].setTextureRect(IntRect(0 , 640 / 5 * 4, 640 / 5, 640 / 5));
    notes[10].setScale(500/float(640), 500/float(640));
    notes[10].setOrigin(50, 50);

    bufferTexture.loadFromImage(buffer);
    bufferTexture.setSmooth(true);
    Sprite bufferSprite;
    bufferSprite.setTexture(bufferTexture);         //set sprite (lines)

    image.loadFromFile("score_strick.png");
    image.createMaskFromColor(image.getPixel(0, 0));
    Texture scorecounter_texture;
    scorecounter_texture.loadFromImage(image);
    scorecounter_texture.setSmooth(true);
    Sprite scorecounter;
    scorecounter.setTexture(scorecounter_texture);
    scorecounter.setPosition(0, 484);

   /* image.loadFromFile("firetorch.jpg");
    image.createMaskFromColor(image.getPixel(0, 0));
    Texture fire1Texture;
    fire1Texture.loadFromImage(image);
    fire1Texture.setSmooth(true);
    Sprite fire1[36];
    for (int i = 0; i < 36; i++)
    {
        fire1[i].setTexture(fire1Texture);
        fire1[i].setTextureRect(IntRect(i % 6 * 3072 / 6, i / 6 * 3072 / 6, 3072 / 6, 3072 / 6));
        fire1[i].setScale(float(150) / 3072 * 6, float(150) / 3072 * 6);
    }*/

    image.loadFromFile("note_strick.png");
    image.createMaskFromColor(image.getPixel(0, 55));
    Texture note_strickcounter_texture;
    note_strickcounter_texture.loadFromImage(image);
    note_strickcounter_texture.setSmooth(true);
    Sprite note_strickcounter;
    note_strickcounter.setTexture(note_strickcounter_texture);
    note_strickcounter.setPosition(93, 660);

    image.loadFromFile("tail.png");
    Texture tailTexture;
    tailTexture.loadFromImage(image);
    Sprite tail[7];
    for (int i = 0; i < 7; i++)
    {
        tail[i].setTexture(tailTexture);
        tail[i].setTextureRect(IntRect(0, i, 18, 1));
        tail[i].setOrigin(9, 0);
        tail[i].setScale(2, 1);
    }

    image.loadFromFile("numbers.png");
    Texture numbers_texture;
    numbers_texture.loadFromImage(image);
    numbers_texture.setSmooth(true);
    Sprite numbers[3][10];
    for (int i = 0; i < 10; i++)
    {
        numbers[0][i].setTexture(numbers_texture);
        numbers[0][i].setTextureRect(IntRect(22 * i, 0, 22, 26));
    }

    image.loadFromFile("numbers1.png");
    Texture numbers_texture1;
    numbers_texture1.loadFromImage(image);
    numbers_texture1.setSmooth(true);
    for (int i = 0; i < 10; i++)
    {
        numbers[1][i].setTexture(numbers_texture1);
        numbers[1][i].setTextureRect(IntRect(26 * i, 0, 26, 34));
    }
    for (int i = 0; i < 10; i++)
    {
        numbers[2][i].setTexture(numbers_texture1);
        numbers[2][i].setTextureRect(IntRect(26 * i, 34, 26, 34));
    }

    image.loadFromFile("x12342468.png");
    Texture xScore_texture;
    xScore_texture.loadFromImage(image);
    xScore_texture.setSmooth(true);

    Sprite xScore[2][4];
    for (int i = 0; i < 4; i++)
    {
        xScore[1][i].setTexture(xScore_texture);
        xScore[1][i].setTextureRect(IntRect(64 * i, 85, 64, 85));
        xScore[1][i].setPosition(100, 575);

        xScore[0][i].setTexture(xScore_texture);
        xScore[0][i].setTextureRect(IntRect(64 * i, 0, 64, 85));
        xScore[0][i].setPosition(100, 575);
    }

    image.loadFromFile("thunder1.png");
    image.createMaskFromColor(image.getPixel(0, 0));
    Texture thunder_texture;
    thunder_texture.loadFromImage(image);
    thunder_texture.setSmooth(true);
    Sprite thunder[6];
    for (int i = 0; i < 6; i++)
    {
        thunder[i].setTexture(thunder_texture);
        thunder[i].setTextureRect(IntRect(thunder_texture.getSize().x / 6 * i, 0, thunder_texture.getSize().x / 6, thunder_texture.getSize().y));
        thunder[i].setPosition(0, 0);
    }

    image.loadFromFile("lamp.png");
    image.createMaskFromColor(image.getPixel(0, 0));
    Texture lamp_texture;
    lamp_texture.loadFromImage(image);
    lamp_texture.setSmooth(true);
    Sprite lamp[4];
    for (int i = 0; i < 4; i++)
    {
        lamp[i].setTexture(lamp_texture);
        lamp[i].setTextureRect(IntRect(0, 25 * i, 26, 25));
    }

    image.loadFromFile("rock_meter.png");
    image.createMaskFromColor(image.getPixel(0, 0));
    Texture rock_meter_texture;
    rock_meter_texture.loadFromImage(image);
    rock_meter_texture.setSmooth(true);
    Sprite rock_meter;
    rock_meter.setTexture(rock_meter_texture);
    rock_meter.setPosition(1096, 491);
    Texture rock_meters_texture[9];
    Sprite rock_meters[9];
    for (int i = 0; i < 9; i++)
    {
        String tmp;
        tmp = "meter_0.png";
        tmp[6] = i + '0';
        image.loadFromFile(tmp);
        image.createMaskFromColor(image.getPixel(0, 0));
        rock_meters_texture[i].loadFromImage(image);
        rock_meters_texture[i].setSmooth(true);
        rock_meters[i].setTexture(rock_meters_texture[i]);
        rock_meters[i].setPosition(1120, 560);
    }

    image.loadFromFile("lamp_1.png");
    image.createMaskFromColor(image.getPixel(0, 0));
    Texture rock_load_texture[8];
    rock_load_texture[0].loadFromImage(image);
    Sprite rock_load[8];
    image.loadFromFile("lamp_1_.png");
    image.createMaskFromColor(image.getPixel(0, 0));
    rock_load_texture[1].loadFromImage(image);
    image.loadFromFile("lamp_2_.png");
    image.createMaskFromColor(image.getPixel(0, 0));
    rock_load_texture[2].loadFromImage(image);
    image.loadFromFile("lamp_3_.png");
    image.createMaskFromColor(image.getPixel(0, 0));
    rock_load_texture[3].loadFromImage(image);
    image.loadFromFile("lamp_4_.png");
    image.createMaskFromColor(image.getPixel(0, 0));
    rock_load_texture[4].loadFromImage(image);
    image.loadFromFile("lamp_5_.png");
    image.createMaskFromColor(image.getPixel(0, 0));
    rock_load_texture[5].loadFromImage(image);
    image.loadFromFile("lamp_6_.png");
    image.createMaskFromColor(image.getPixel(0, 0));
    rock_load_texture[6].loadFromImage(image);
    image.loadFromFile("lamp_0.png");
    image.createMaskFromColor(image.getPixel(0, 0));
    rock_load_texture[7].loadFromImage(image);

    for (int i = 0; i < 4; i++)
    {
        rock_load_texture[i].setSmooth(true);
        rock_load[i].setTexture(rock_load_texture[i]);
        rock_load[i].setPosition(1100, 495);
    }
    for (int i = 4; i < 8; i++)
    {
        rock_load_texture[i].setSmooth(true);
        rock_load[i].setTexture(rock_load_texture[i]);
        rock_load[i].setPosition(1200, 470);
    }

    Image fireImage;
    fireImage.loadFromFile("fire_2.png");
    fireImage.createMaskFromColor(fireImage.getPixel(0,0));
    Texture fireTexture;
    fireTexture.loadFromImage(fireImage);
    fireTexture.setSmooth(true);
    Sprite fireSprite;
    fireSprite.setTexture(fireTexture);
    fireSprite.setTextureRect(IntRect(0, 0, 960, 768));
    fireSprite.setPosition(0, 0);

    //window.draw(fireSprite);
    //window.display();
    Music music0;
    if (!music0.openFromFile(file_music))
        return -1; // error
    music0.play();
    music0.pause();
    bool  music0_flag = true;
    struct key_data * tmpdata;                      // temp struct for list
    float speed = 0.4/800;                          //number of pixels that moves in 1 microsec
    /*bool flag0 = false, flag1 = false, flag2 = false, flag3 = false, flag4 = false; //flags for adding only one note per pressing
    while (!Keyboard::isKeyPressed(Keyboard::LShift))
    {
        Event event;
        while (window.pollEvent(event)) // for closing window
        {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
        }
    }
    float start = clock_start.getElapsedTime().asMicroseconds(); //get start
    while (!Keyboard::isKeyPressed(Keyboard::Space) && window.isOpen()) //scan pressings that will shows you later
    {
        Event event;
        while (window.pollEvent(event)) // for closing window
        {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
        }
        int index;
        if (Keyboard::isKeyPressed(Keyboard::A)){   //if pressed A creates sprite with spetical color and .x position
            if( !flag0)
        {
            index = 0;
            count++;
            tmpdata = new struct key_data;
            tmpdata->isPressed = false;
            tmpdata->index = index;
            tmpdata->time = clock_start.getElapsedTime().asMicroseconds() - start;
            pos = new Vector2f((float)index * 80 + 483, 0); // set position ~ time
            tmpdata->pos = *pos;
            flag0 = true;
            list.add(tmpdata);                      //add in list

        }
        }
        else
            flag0 = false;

        if (Keyboard::isKeyPressed(Keyboard::S))
    {
            if( !flag1)
        {
            index = 1;
             count++;

            flag1 = true;
            tmpdata = new struct key_data;
            tmpdata->isPressed = false;

            tmpdata->index = index;
            tmpdata->time = clock_start.getElapsedTime().asMicroseconds() - start;
            pos = new Vector2f((float)index * 80 + 483, 0);
            tmpdata->pos = *pos;
            list.add(tmpdata);
        }
        }
        else
            flag1 = false;

        if (Keyboard::isKeyPressed(Keyboard::D)){
            if( !flag2)
        {
            index = 2;
             count++;

            flag2 = true;
            tmpdata = new struct key_data;
            tmpdata->isPressed = false;

            tmpdata->index = index;
            tmpdata->time = clock_start.getElapsedTime().asMicroseconds() - start;
             pos = new Vector2f((float)index * 80 + 483, 0);
             tmpdata->pos = *pos;
            list.add(tmpdata);
        }
        }
        else
            flag2 = false;

        if (Keyboard::isKeyPressed(Keyboard::K)){
            if( !flag3)
        {
            index = 3;
             count++;

            flag3 = true;
            tmpdata = new struct key_data;
            tmpdata->isPressed = false;

            tmpdata->index = index;
            tmpdata->time = clock_start.getElapsedTime().asMicroseconds() - start;
            pos = new Vector2f((float)index * 80 + 483, 0);
             tmpdata->pos = *pos;
            list.add(tmpdata);
        }
        }
        else
            flag3 = false;

        if (Keyboard::isKeyPressed(Keyboard::L)){
            if( !flag4)
        {
            index = 4;
             count++;

            flag4 = true;
            tmpdata = new struct key_data;
            tmpdata->isPressed = false;

            tmpdata->index = index;
            tmpdata->time = clock_start.getElapsedTime().asMicroseconds() - start;
             pos = new Vector2f((float)index * 80 + 483, 0);
             tmpdata->pos = *pos;
            list.add(tmpdata);
        }
        }
        else
            flag4 = false;

    }*/
    //music0.stop();
    Font font;//шрифт
    font.loadFromFile("font/FIRESTARTER.ttf");//передаем нашему шрифту файл шрифта
    Text text("", font, 40);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
    text.setStyle(sf::Text::Bold);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
    /*std::fstream file;
    file.open("song5.ghfile", std::ios::out | std::ios::trunc);
    file << list.count() << std::endl;
    for (int i = 0; i < list.count(); i++)
    {
        file << list.get(i)->index << std::endl;
        file << list.get(i)->isPressed << std::endl;
        file << list.get(i)->pos.x << std::endl;
        file << list.get(i)->pos.y << std::endl;
        file << list.get(i)->time << std::endl;
        file << 0 << std::endl;
    }
    file.close();
}*/
    std::fstream file1;
    file1.open(file_notes, std::ios::in);
    file1 >> count;
    float pos_x, pos_y;
    for (int i = 0; i < count; i++)
    {
        tmpdata = new key_data;
        file1 >> tmpdata->index;
        file1 >> tmpdata->isPressed;
        file1 >> pos_x;
        file1 >> pos_y;
        file1 >> tmpdata->time;
        file1 >> tmpdata->tail_time;
        pos = new Vector2f(620 + tmpdata->index * 32   , pos_y + 200);
        tmpdata->pos = *pos;
        pos = new Vector2f(620 + tmpdata->index * 32   , pos_y + 200);
        tmpdata->pos_tail = *pos;
        list.add(tmpdata);
    }
    file1.close();
    float score = 0;
    float fretDeckPos = 0.0;
    int first_key = 0;      //first note what will check
    int one_note_score = 1;
    Clock clock;            //new clock for move
    std::string str;        //string for text
    char strtmp[50];        //temp string for text

    Text max_score("", font, 30);
    max_score.setColor(text.getColor());

    sprintf(strtmp, "%i:%i\n%i", int(music0.getDuration().asSeconds() - music0.getPlayingOffset().asSeconds()) / 60, int(music0.getDuration().asSeconds() - music0.getPlayingOffset().asSeconds()) % 60, player->get_score(song_id));
    max_score.setString(strtmp);
    max_score.setPosition(1260, 100);
    int fire1_count[5] = {0};
    int cur_thunder = 0;
    float thunder_time = 100000;
    float cur_thunder_time = 0;
    Vector2f tail_pos[5] = {Vector2f(0, 200), Vector2f(0, 200), Vector2f(0, 200), Vector2f(0, 200), Vector2f(0, 200)};
    bool tail_is_pressed[5] = {false, false, false, false, false};
    float rock_time[6] = { 1000000.0 , 1000000.0 , 1000000.0 , 1800000.0 , 2600000.0, 3600000.0};
    float cur_rock_time = 0;
    int notes_pleyed_count = 0;
    int rock_load_type = 0;
    int rock_load_notes = 70 + 20 * rock_load_type;
    int count_false = 0;
    float line_time = 483200.0;
    float line_time1 = line_time;
    Clock clock_line;
    int playing = 56;
    int good_notes = 0;
    int index;
    std::stringstream ss;   //stream for text
    int note_strick = 0;      //note strick
    bool flag[5] = {true, true, true, true, true}; //на всяк випадок
    int fire[5] = {0, 0, 0, 0, 0};
    float fire_time[5];
    bool is_good_note, isInRock = false; // is pressing correct
    //float bef_time;
    float time = 0.0;
    clock_start.restart();
    clock_line.restart();
    float pauseTime = 0;
    bool isGame = true;
    int max_notes = 0;
    //music0.pause();
    //start = clock_start.getElapsedTime().asMicroseconds(); //get new start
    while (window.isOpen() && isGame)     //start game
    {
        //bef_time = time;
        time = clock.getElapsedTime().asMicroseconds(); //get seconds per frame
       // while (Keyboard::isKeyPressed(Keyboard::Space));
        clock.restart();
        if (clock_start.getElapsedTime().asMicroseconds() + pauseTime > start_pause_time/speed / 0.5 / 1.7  && music0_flag) // 650/speed / 0.5 / 1.7 for bat 580/speed / 0.5 / 1.7 for scorp
        {
            music0.play();
            music0_flag = false;
        }
        time /= 1500 ; // set speed
        Event event;
        while (window.pollEvent(event)) // for closing window
        {
            if (event.type == Event::Closed)
                window.close();
        }
        for (int i = 0; i < 5; i++)
        if (!Keyboard::isKeyPressed(keys[i]))
        {
             button[i].setTextureRect(IntRect(672 / 5 * i, 0, 672/5, 81)); //animation
             flag[i]= true;
             tail_is_pressed[i] = false;
            // tail_pos[i].y = 200;
        }
        for (int i = 0; i < 5; i++)
            if (Keyboard::isKeyPressed(keys[i]) && tail_pos[i].y != 200)
                score += one_note_score * (1 + isInRock) * time / 1000 * (1 + isCareer * player->get_guitar());
        for (int i = 0; i < 5; i++)
        if (Keyboard::isKeyPressed(keys[i]) && flag[i])
        {
            button[i].setTextureRect(IntRect(672 / 5 * i, 164, 672/5, 81)); //animation
            //index = first_key; //get first note
            flag[i] = false;
            is_good_note = false;
            //if (list.get(index) == NULL) break;
            if (list.count() != 0)

            for (index = first_key; ; index++) //check all notes what is in area near bottom
                {
                    key_data * data = list.get(index);
                    if (data == NULL) break; // if last note - end
                    if (data->pos.y < 500) break;
                    if (data->index == i)  // if corect note
                    {
                        if (!data->isPressed){
                            if (tail_pos[data->index].y == 200 || !tail_is_pressed[data->index])
                            {
                                tail_pos[data->index] = data->pos_tail;
                                tail_is_pressed[data->index] = true;
                            }
                            if (tail_pos[data->index].y == 200)
                                tail_pos[data->index].y = 220;
                            if (tail_pos[data->index].y - data->pos.y > -5)
                            {
                                tail_is_pressed[data->index] = false;
                                tail_pos[data->index].y = 200;
                            }
                            data->tail_time = 0;
                            one_note_score = note_strick / 60 + 1;
                            if (one_note_score > 4)
                                one_note_score = 4;
                            score += one_note_score * (1 + isInRock) * (1 + isCareer * player->get_guitar()); //increase score
                            if (playing < 116)
                                playing++;
                            note_strick++; // increase note strick
                            if (note_strick > max_notes)
                                max_notes = note_strick;
                            rock_load_notes--;
                            if (rock_load_notes <= 0)
                            {
                                if (rock_load_type < 5)
                                    rock_load_type++;
                                rock_load_notes = rock_load_type * 20 + 70;
                            }
                            fire[i] = 1;
                            fire_time[i] = 0;
                        }
                        is_good_note = true;
                        music0.setVolume(100);
                        data->isPressed = true;
                    }



                }

            if (!is_good_note)
            {
                note_strick = 0; // else make it zero
                playing -= 3;
                rock_load_notes = rock_load_type * 20 + 70;
                button[i].setTextureRect(IntRect(672 / 5 * i, 81, 672/5, 81)); //animation
                music0.setVolume(50);
                one_note_score = 1;
            }
        }
        if (Keyboard::isKeyPressed(keys[5]))
            if (rock_load_type > 1 && !isInRock)
            {
                rock_load_type++;
                isInRock = true;
                cur_rock_time = clock_start.getElapsedTime().asMicroseconds() + pauseTime;

            }
        if (isInRock)
            if (clock_start.getElapsedTime().asMicroseconds() + pauseTime - cur_rock_time > rock_time[rock_load_type - 1])
                cur_rock_time += rock_time[--rock_load_type];
        if (rock_load_type == 0 && isInRock)
        {
            rock_load_notes = 70;
            isInRock = false;
        }

        if ( list.count() != 0)
        if ( list.get(first_key)->pos.y > 700) // if you haven't pressed note
        {
            if (!list.get(first_key)->isPressed)
            {
                count_false++;
                if (max_notes < note_strick)
                    max_notes = note_strick;
                note_strick = 0; //zero strick
                rock_load_notes = rock_load_type * 20 + 70;
                playing -= 3;
                music0.setVolume(50);
                one_note_score = 1;
                tail_pos[list.get(first_key)->index] = list.get(first_key)->pos_tail;
                good_notes++;
            }
            delete list.del(first_key);

        }
        for (int i = first_key; i <  list.count(); i++) // move all sprites
        {
            key_data * data = list.get(i);
            if (data->time > clock_start.getElapsedTime().asMicroseconds() + pauseTime) break;
            if (data == NULL) break;
            if (data->pos.y == 200)
               data->pos += (float)(clock_start.getElapsedTime().asMicroseconds() + pauseTime - data->time) / 1500 * vect[data->index] * ((data->pos.y - 180) / (float)430) * (float)1.3;
            data->pos += (time) * vect[data->index] * ((data->pos.y - 180) / (float)430) * (float)1.3;

        }

        for (int i = first_key; i <  list.count(); i++) // move all sprites
        {
            key_data * data = list.get(i);
            if (data->time + data->tail_time > clock_start.getElapsedTime().asMicroseconds() + pauseTime) break;
            if (data == NULL) break;
            if (data->pos_tail.y == 200)
                data->pos_tail += (float)(clock_start.getElapsedTime().asMicroseconds() + pauseTime - data->time - data->tail_time) / 1500 * vect[data->index] * ((data->pos_tail.y - 180) / (float)430) * (float)1.3;
            data->pos_tail += (time) * vect[data->index] * ((data->pos_tail.y - 180) / (float)430) * (float)1.3;

        }
        for (int i = 0; i < 5; i++) // move all sprites
        {
            if (tail_pos[i].y != 200)
            {
                if (tail_pos[i].y < 630)
                    tail_pos[i] += (time) * vect[i] * ((tail_pos[i].y - 180) / (float)430) * (float)1.3;
                else
                {
                    tail_pos[i].y = 200;
                    tail_is_pressed[i] = false;
                }
            }

        }

        for (int i = 0; i < 20; i++)
        {
            if (lines_pos[i].y > 768)
                lines_pos[i].y = 220;
            if (lines_pos[i].y != 220)
                lines_pos[i].y += (time)  * ((lines_pos[i].y - 180) / (float)430) * (float)1.3;
            else
            {
                if (clock_line.getElapsedTime().asMicroseconds() > line_time1)
                {
                    lines_pos[i].y += (clock_line.getElapsedTime().asMicroseconds() - line_time1) / 1500  * ((lines_pos[i].y - 180) / (float)430) * (float)1.3;
                    //clock_line.restart();
                    line_time1 += line_time;
                }
            }
        }




        fretDeckPos += time * 1.37 ;
        window.clear(); //clear window
        window.draw(background);
        window.draw(scorecounter);
        window.draw(note_strickcounter);
        for (int tmpscore = int(score), i = 0; tmpscore > 0; tmpscore /= 10)
        {
            int digit = tmpscore % 10; // 195 40
            numbers[0][digit].setPosition(195 - i * 22, 484 + 40);
            window.draw(numbers[0][digit]);
            i++;
        }

        for (int tmp_strick = note_strick, i = 0; i < 4; i++)
        {
            int digit = tmp_strick % 10;
            if (i == 0)
            {
                numbers[2][digit].setPosition(207, 668);
                window.draw(numbers[2][digit]);
            }
            else {
                numbers[1][digit].setPosition(205 - i * 26, 668);
                window.draw(numbers[1][digit]);
            }
            tmp_strick /= 10;
        }

        window.draw(rock_meter);
        if (playing > 0)
        {
            window.draw(rock_meters[playing / 13]);
        }
        else
        {
            window.draw(rock_meters[0]);
            text.setString("Looser!!!");
            text.setPosition(590, 200);
            if (isCareer)
            {
                while (clock.getElapsedTime().asMicroseconds() < 1000000);
                return 0;
            }
        }
        if (rock_load_type > 1 || isInRock)
            window.draw(rock_load[7]);
        if (rock_load_type != 0){
            if (rock_load_type == 1)
                window.draw(rock_load[0 + isInRock]);
            else
            {
                if (rock_load_type == 2 && isInRock)
                    window.draw(rock_load[2]);
                else
                    window.draw(rock_load[3]);
                if (rock_load_type != 2)
                    window.draw(rock_load[rock_load_type + !isInRock]);
            }
        }


        //if (one_note_score != 1)//____________________________________________________________________________
        window.draw(xScore[!isInRock][one_note_score - 1]);

        for (int i = 0; i < (note_strick % 60) / 10 || one_note_score == 4 || (note_strick % 60 == 0 && one_note_score != 1); i++)
        {
            if (i == 5) break;
            lamp[one_note_score - 1].setPosition(6, 666 - i * 25);
            window.draw(lamp[one_note_score - 1]);
        }

        for (int i = -30; i < 488; i++)
        {
            int k;
            k = abs((int((fretDeckPos +  0.84 * (400 - i) * (float(705) / (i + 305))) / 1.1 )) % 657);
            fretDeck[k].setScale(float(500) / 329 * (i + 268) / 615, 1);
            fretDeck[k].setPosition(433 + (350 - i)/ 2.5, 280 + i);

            if (i < 30)
            {
                Color col_s = fretDeck[k].getColor();
                col_s.a = (i + 30) * 256 / 60;
                fretDeck[k].setColor(col_s);

            }
            else
            {
                Color col_s = fretDeck[k].getColor();
                col_s.a = 255;
                fretDeck[k].setColor(col_s);

            }
            window.draw(fretDeck[k]);

        }
        window.draw(bufferSprite);
        for (int i = 0; i < 5; i++)
            if (tail_pos[i].y != 200)
            {
                for (int j = 645; j > (int)tail_pos[i].y; j--)
                {
                    int tmp_index;

                    if (isInRock)
                        tmp_index = 5;
                    else
                        tmp_index = i;
                    if (!tail_is_pressed[i])
                        tmp_index = 6;
                    tail[tmp_index].setPosition(tail_pos[i].x - (tail_pos[i].y - (float)j)  * vect[i].x, (float)j);
                    tail[tmp_index].setScale(((tail[tmp_index].getPosition().y - 5) / (float)625) * 2, 1);
                    if (tail[tmp_index].getPosition().y < 280)
                    {
                        Color col_s = tail[tmp_index].getColor();
                        col_s.a = (tail[tmp_index].getPosition().y - 220) * 256 / 60;
                        tail[tmp_index].setColor(col_s);

                    }

                    else
                    {
                        Color col_s = tail[tmp_index].getColor();
                        col_s.a = 255;
                        tail[tmp_index].setColor(col_s);

                    }
                    if (j - tail_pos[i].y < 30)
                    {
                        tail[tmp_index].setScale(tail[tmp_index].getScale().x * sqrt(1 - (30 - j + tail_pos[i].y) * (30 - j + tail_pos[i].y)/ 30/ 30)  , 1);
                        Color col_s = tail[i].getColor();
                        col_s.a = (j - tail_pos[i].y) * col_s.a / 30;
                        tail[i].setColor(col_s);

                    }

                    if (tail[tmp_index].getPosition().y > 220)
                    window.draw(tail[tmp_index]);
                }
            }
        for (int i = 0; i < 20; i++)
        {

            line.setOrigin(250, 2);
            line.setScale(((lines_pos[i].y - 5) / (float)625), ((lines_pos[i].y - 5) / (float)625));
           // line.setOrigin(250 * line.getScale().x, 2);
            line.setPosition(lines_pos[i].x , lines_pos[i].y);
           if (lines_pos[i].y < 280)
            {
                Color col_s = line.getColor();
                col_s.a = (lines_pos[i].y - 220) * 256 / 60;
                line.setColor(col_s);

            }
            else
            {
                Color col_s = line.getColor();
                col_s.a = 255;
                line.setColor(col_s);
            }
            window.draw(line);

        }
        //text.setPosition(200, 200);
       // window.draw(text);//рисую этот текст
        text.setColor(Color(200, 183, 107));
        text.setPosition(650, 150);
        window.draw(text);
        for (int i = 0; i < 5; i++) //drawing
             window.draw(button[i]);
        notes_pleyed_count = 0;
        for (int i = 0; i < list.count() && list.get(i)->pos.y > 220; i++)
            if (list.get(i)->isPressed)
                notes_pleyed_count++;

        for (int i = 0; i < list.count() ; i++)
        {
            int index_tmp;
            struct key_data * tmp_note = list.get(i);
            if (isInRock)
                index_tmp = 10;
            else
                index_tmp = tmp_note->index + 5 * (rock_load_notes - i + notes_pleyed_count < 20 && rock_load_notes - i + notes_pleyed_count > 0);
            if (tmp_note == NULL) break;
            if (tmp_note->pos.y < 220) //drow until the top
                break;
            if (!tmp_note->isPressed || tmp_note->pos.y < 655)
            {
                notes[index_tmp].setOrigin(64, 64);
                notes[index_tmp].setScale(((tmp_note->pos.y - 5) / (float)625) * 500/float(640), ((tmp_note->pos.y - 5) / (float)625) * 500/float(640));
                notes[index_tmp].setPosition(tmp_note->pos.x, tmp_note->pos.y);
                if (tmp_note->tail_time > 0)
                {

                    int pos_tail_y;

                    pos_tail_y = tmp_note->pos_tail.y;
                    for (int j = (int)tmp_note->pos.y; j > (int)pos_tail_y && j > 220; j--)
                    {
                        int index_tail = index_tmp %  5;
                        if (index_tmp == 10)
                            index_tail = 5;
                        tail[index_tail].setPosition(tmp_note->pos_tail.x - (pos_tail_y - (float)j)  * vect[tmp_note->index].x, (float)j);
                        tail[index_tail].setScale(((tail[index_tail].getPosition().y - 5) / (float)625) * 1.2, 1);
                        if (j < 280)
                        {
                            Color col_s = tail[index_tail].getColor();
                            col_s.a = (j - 220) * 256 / 60;
                            tail[index_tail].setColor(col_s);

                        }

                        else
                        {
                            Color col_s = tail[index_tail].getColor();
                            col_s.a = 255;
                            tail[index_tail].setColor(col_s);

                        }
                        if (j - pos_tail_y < 25)
                        {
                            tail[index_tail].setScale(tail[index_tail].getScale().x * sqrt(25 * 25 - (25 - j + pos_tail_y) * (25 - j + pos_tail_y)) / 25 , 1);
                            Color col_s = tail[index_tail].getColor();
                            col_s.a = (j - pos_tail_y) * col_s.a / 25;
                            tail[index_tail].setColor(col_s);

                        }
                        window.draw(tail[index_tail]);
                    }
                }

                if (notes[index_tmp].getPosition().y < 280)
                {
                    Color col_s = notes[index_tmp].getColor();
                    col_s.a = (notes[index_tmp].getPosition().y - 220) * 256 / 60;
                    notes[index_tmp].setColor(col_s);

                }
                else
                {
                    Color col_s = notes[index_tmp].getColor();
                    col_s.a = 255;
                    notes[index_tmp].setColor(col_s);

                }
                window.draw(notes[index_tmp]);
            }

        }




        for (int i = 0; i < 5; i++)
            if (fire[i] != 0)
            {
                if (fire_time[i] == 0)
                    fire_time[i] = clock_start.getElapsedTime().asMicroseconds() + pauseTime;
                fireSprite.setTextureRect(IntRect((fire[i] - 1) % 5 * 960 / 5, (fire[i] - 1) / 5 * 768 / 4, 960 / 5, 768 / 4));
                fireSprite.setScale(0.8, 0.8);
                fireSprite.setPosition(100 * i + 410, 517);
                Color col_s = fireSprite.getColor();
                col_s.a = 220;
                fireSprite.setColor(col_s);


                if (clock_start.getElapsedTime().asMicroseconds() + pauseTime - fire_time[i] > 15000.0 * fire[i])
                    fire[i]++;
                window.draw(fireSprite);
                if (fire[i] > 20)
                    fire[i] = 0;
            }
        for(int i = 0; i < 5; i++)
        {
            if (tail_is_pressed[i])
            {
                fire1_count[i]++;
                if (fire1_count[i] > 11)
                    fire1_count[i] = 6;
                fireSprite.setScale(0.8, 0.5);
                fireSprite.setTextureRect(IntRect((fire1_count[i] - 1) % 5 * 960 / 5, (fire1_count[i] - 1) / 5 * 768 / 4, 960 / 5, 768 / 4));
                fireSprite.setPosition(100 * i + 410, 517 + 40);

                window.draw(fireSprite);
            }
        }
        sprintf(strtmp, "%i:%i\n%i", int(music0.getDuration().asSeconds() - music0.getPlayingOffset().asSeconds()) / 60, int(music0.getDuration().asSeconds() - music0.getPlayingOffset().asSeconds()) % 60, player->get_score(song_id));
        max_score.setString(strtmp);
        window.draw(max_score);
        window.display();
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            pauseTime += clock_start.getElapsedTime().asMicroseconds() - 2006000;
            music0.pause();
            switch(pause(keys, window, font))
            {
            case 0:
                while (list.count() != 0)
                    list.del(0);
                return -1;
                break;
            case 1:
                while (list.count() != 0)
                    list.del(0);
                return 0;
                break;
            default:
                break;
            }

            int i = 0;
            //Time time = Time();
            music0.setPlayingOffset(music0.getPlayingOffset() - microseconds(2000000));
            while (list.get(i)->pos.y > 200)
            {
                key_data * tmpdata = list.get(i);
                tmpdata->pos = Vector2f(620 + tmpdata->index * 32   , pos_y + 200);
                tmpdata->pos_tail = Vector2f(620 + tmpdata->index * 32   , pos_y + 200);
                i++;
            }
            music0_flag = true;

            clock_start.restart();
        }
        if (music0.getStatus() == Music::Stopped)
        {
            if (max_notes == 0)
                max_notes = note_strick;
            player->update((int)round(score), song_id);
            //results(window, score, isCareer, float(count - good_notes) / float(count), max_notes, player, font);
            return results(window, score, isCareer, float(count - good_notes) / float(count), max_notes, player, font, conc);
        }
    }
    while (list.count() != 0)
        list.del(0);
    return int(round(score));
}

int pause(Keyboard::Key * keys, RenderWindow &window, Font font)
{

    Texture new_back_texture;
    new_back_texture.setSmooth(true);
    new_back_texture.loadFromImage(window.capture());
    Sprite new_back;
    new_back.setTexture(new_back_texture);
    new_back.setColor(Color(new_back.getColor().r * 0.6, new_back.getColor().g * 0.6, new_back.getColor().b * 0.6));
    Image b_image;
    b_image.create(1, 1, Color(254, 254, 204));
    Texture b_texture;
    b_texture.loadFromImage(b_image);
    Sprite button_background;
    button_background.setTexture(b_texture);
    Text button[4];
    int selected_button = -1;
    std::string str[4] = {"Restart", "New song", "Settings", "Back"};
    Color selected_button_color = Color(123, 4 ,2);
    Color unselected_button_color = Color(198, 138, 72);
    for (int i = 0; i < 4; i++)
    {
        button[i].setColor(unselected_button_color);
        button[i].setString(str[i]);
        button[i].setPosition(150 - str[i].length() * 10, 202 + i * 50);
        button[i].setCharacterSize(30);
        button[i].setFont(font);
    }
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
                        return 0;
                        break;
                    case 1:
                        return 1;
                        break;
                    case 2:
                        settings(keys, window, new_back, button_background, font);
                        break;
                    case 3:
                        return 2;
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
        window.draw(new_back);
       // window.draw(fret);
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
    return 2;
}

int results(RenderWindow &window, int score, bool isCareer, float good_notes, int max_notes, Player * player, Font font, int conc)
{
    int cost[5] = {0, 200, 1000, 5000, 100000};
    int earned_money = int((cost[conc] + 50) * (good_notes * 2 - 1));
    if (!isCareer)
        earned_money = 0;
    player->earn_money(earned_money);
    player->update(0, 0);
    Image image;
    image.loadFromFile("magazine.png");
    Texture magazine_texture;
    magazine_texture.loadFromImage(image);
    Sprite magazine;
    magazine.setTexture(magazine_texture);
    magazine.setScale(768.0 / magazine_texture.getSize().y, 768.0 / magazine_texture.getSize().y);
    magazine.setPosition(0, 0);
    image.loadFromFile("paper.png");
    Texture paper_texture;
    paper_texture.loadFromImage(image);
    Sprite paper;
    paper.setTexture(paper_texture);
    paper.setScale(768.0 / paper_texture.getSize().y, 768.0 / paper_texture.getSize().y);
    paper.setPosition(magazine.getGlobalBounds().width, 0);
    Text button[2];
    int selected_button = -1;
    std::string str[2] = {"New song", "Replay"};
    Color selected_button_color = Color(123, 4 ,2);
    Color unselected_button_color = Color(20, 30, 20);
    Color info_color =  Color(20, 30, 20);
    for (int i = 0; i < 2; i++)
    {
        button[i].setColor(unselected_button_color);
        button[i].setString(str[i]);
        button[i].setPosition(1200 - str[i].length() * 10, 102 + i * 50);
        button[i].setCharacterSize(30);
        button[i].setFont(font);
    }
    Text score_text, good_notes_text, max_notes_text, money;
    char buff[30];
    sprintf(buff, "Your score: %i", score);
    score_text.setString(buff);
    sprintf(buff, "%.1f%%", good_notes * 100);
    good_notes_text.setString(buff);
    sprintf(buff, "Note streak: %i", max_notes);
    max_notes_text.setString(buff);
    sprintf(buff, "Eaned money: %i$", earned_money);
    money.setString(buff);
    money.setFont(font);
    money.setCharacterSize(30);
    money.setPosition(730, 252);
    money.setColor(info_color);
    score_text.setFont(font);
    score_text.setCharacterSize(30);
    score_text.setPosition(730, 102);
    score_text.setColor(info_color);
    good_notes_text.setFont(font);
    good_notes_text.setCharacterSize(30);
    good_notes_text.setPosition(730, 152);
    good_notes_text.setColor(info_color);
    max_notes_text.setFont(font);
    max_notes_text.setCharacterSize(30);
    max_notes_text.setPosition(730, 202);
    max_notes_text.setColor(info_color);
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
                        return 0;
                        break;
                    case 1:
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
        //window.draw(background);
        window.draw(magazine);
        window.draw(paper);
        mouse_pos = Mouse::getPosition(window);
        for (int i = 0; i < 2; i++)
        {
            if (button[i].getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
            {
                selected_button = i;
            }
        }
        for (int i = 0; i < 2; i++)
        {
            if (i == selected_button)
            {
                button[i].setColor(selected_button_color);
            }
            else
            {
                button[i].setColor(unselected_button_color);
            }

            window.draw(button[i]);
        }
        window.draw(score_text);
        window.draw(good_notes_text);
        window.draw(max_notes_text);
        window.draw(money);
        window.display();



    }
    return 0;
}


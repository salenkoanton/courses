
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <SFML/Window/Event.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <math.h>
using namespace sf;
struct key_data{                                        //struct for list
    Vector2f pos;
    int index;
    float time;
    bool isPressed;
    float tail_time;
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

    bool add_pos(key_data * data, int pos)
    {
        struct ListNode * tmp = new struct ListNode, * cur;
        if (pos > cnt)
            return false;
        cur = head;
        for(int i = 0; i < pos; i++)
            cur = cur->next;
        tmp->data = data;
        tmp->next = cur->next;
        cur->next = tmp;
        cnt++;
        return true;
    }

};


int main(void)
{
    int count = 0;
    RenderWindow window(VideoMode(1366, 768), "Guitar Hero", Style::Fullscreen);    //create window
    window.setFramerateLimit(120);
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
        buffer.setPixel(433, j + 200, Color(255, 255, 255, alfa_tmp));
        buffer.setPixel(432 , j + 200, Color(200, 200, 200, alfa_tmp));
        buffer.setPixel(434, j + 200, Color(200, 200, 200, alfa_tmp));

        buffer.setPixel(431 , j + 200, Color(150, 150, 150, alfa_tmp));
        buffer.setPixel(435, j + 200, Color(150, 150, 150, alfa_tmp));
        buffer.setPixel(933, j + 200, Color(255, 255, 255, alfa_tmp));
        buffer.setPixel(932, j + 200, Color(200, 200, 200, alfa_tmp));
        buffer.setPixel(934, j + 200, Color(200, 200, 200, alfa_tmp));
        buffer.setPixel(931 , j + 200, Color(170, 170, 170, alfa_tmp));
        buffer.setPixel(935 , j + 200, Color(170, 170, 170, alfa_tmp));
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
    Image image;                                    //image for texture, i'll rename it later
    Texture notesTexture, bufferTexture, buttonsTexture, backgroundTexture, fretDeckTexture;                 //textures for buttons
    Sprite button[5], notes[6], background, fretDeck[658];                               //buttons
    image.loadFromFile("fretdeck.png");
    for (int i = 0; i < 329; i++)
    {
        image.setPixel(i, 1, Color(200, 200, 200));
        image.setPixel(i, 0, Color(200, 200, 200));
        image.setPixel(i, 2, Color(200, 200, 200));
        image.setPixel(i, 4, Color(200, 200, 200));
        image.setPixel(i, 3, Color(200, 200, 200));
        image.setPixel(i, 5, Color(200, 200, 200));
    }
    fretDeckTexture.loadFromImage(image);
    fretDeckTexture.setSmooth(true);
    for (int i = 0; i < 658; i++)
    {
        fretDeck[i].setTexture(fretDeckTexture);
        fretDeck[i].setTextureRect(IntRect(0, i, 329, 1));
        fretDeck[i].setScale(float(500) / 329, 1);
        fretDeck[i].setPosition(483 + (350 - i)/ 2.5, 280 + i);
    }
    image.loadFromFile("notes.bmp");          //load image
    notesTexture.loadFromImage(image);
    notesTexture.setSmooth(true);                        //set smooth
    image.loadFromFile("tail.png");
    Texture tailTexture;
    tailTexture.loadFromImage(image);
    Sprite tail[6];
    for (int i = 0; i < 6; i++)
    {
        tail[i].setTexture(tailTexture);
        tail[i].setTextureRect(IntRect(0, i, 18, 1));
        tail[i].setOrigin(9, 0);
        tail[i].setScale(2, 1);
    }
    image.loadFromFile("fretbuttons-3.png");          //load image
    buttonsTexture.loadFromImage(image);
    buttonsTexture.setSmooth(true);
    image.loadFromFile("background.jpg");
    backgroundTexture.loadFromImage(image);
    backgroundTexture.setSmooth(true);
    background.setTexture(backgroundTexture);
    background.setTextureRect(IntRect(0, 0, 1280, 720));
    background.setScale(1366 / (float) 1280, 768 / (float) 720);
    for(int i = 0; i < 5; i++)
    {
        button[i].setTexture(buttonsTexture);
        button[i].setPosition(100 * i + 433, 410 + 200);
        button[i].setTextureRect(IntRect(i * 672 / 5, 0, 672 / 5, 81));
        button[i].setScale(500/float(672), 500/float(672));
        for (int j = 0; j < 5; j++)
        {
            notes[i].setTexture(notesTexture);
            notes[i].setTextureRect(IntRect(i * 640 / 5, 0, 640 / 5, 640 / 5));
            notes[i].setScale(500/float(640), 500/float(640));
            notes[i].setOrigin(50, 50);
        }
    }                                               //creating of 5 buttons in the bottom
    notes[5].setTexture(notesTexture);
    notes[5].setTextureRect(IntRect(640 / 5, 4 * 640 / 5, 640 / 5, 640 / 5));
    notes[5].setScale(500/float(640), 500/float(640));
    notes[5].setOrigin(50, 50);

    image.loadFromFile("arrow.png");
    image.createMaskFromColor(image.getPixel(0, 0));
    Texture arrow_texture;
    arrow_texture.loadFromImage(image);
    Sprite arrow;
    arrow.setTexture(arrow_texture);
    arrow.setTextureRect(IntRect(0, 0, 48, 33));
    arrow.setOrigin(47, 16);

    bufferTexture.loadFromImage(buffer);
    bufferTexture.setSmooth(true);
    Sprite bufferSprite;
    bufferSprite.setTexture(bufferTexture);         //set sprite (lines)

    Image full_deck;
    full_deck.create(100, 1366, Color(0, 0, 0, 0));

    /*Image fireImage;
    fireImage.loadFromFile("fire_2.png");
    fireImage.createMaskFromColor(fireImage.getPixel(0,0));
    Texture fireTexture;
    fireTexture.loadFromImage(fireImage);
    fireTexture.setSmooth(true);
    Sprite fireSprite;
    fireSprite.setTexture(fireTexture);
    fireSprite.setTextureRect(IntRect(0, 0, 960, 768));
    fireSprite.setPosition(0, 0);*/

    //window.draw(fireSprite);
    //window.display();
    Music music0;
    if (!music0.openFromFile("music3.ogg"))
        return -1; // error
   // music0.play();
    bool  music0_flag = true;
    struct key_data * tmpdata;                      // temp struct for list
    float speed = 0.4/800;                          //number of pixels that moves in 1 microsec

    Font font;//шрифт
    font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
    Text text("", font, 40);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
    text.setColor(Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
    text.setStyle(sf::Text::Bold);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
    std::fstream file1;
    file1.open("song2tmp10.ghfile", std::ios::in);
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
        pos = new Vector2f(475 + tmpdata->index *  100  , pos_y - 100 - tmpdata->time / 1500);
        tmpdata->pos = *pos;
        list.add(tmpdata);
    }
    file1.close();
    Color color[5];
    color[0] = Color(0, 177, 13);
    color[1] = Color(171, 0, 0);
    color[2] = Color(215, 196, 26);
    color[3] = Color(19, 145, 206);
    color[4] = Color(218, 132, 31);
    for (int i = 0; i < list.count(); i++)
    {
        for (int j = 0; j < 20; j++)
            full_deck.setPixel(j + list.get(i)->index * 20, 765 - int(765 * list.get(i)->time / list.get(list.count() - 1)->time), color[list.get(i)->index]);
    }
    Texture full_deck_texture;
    full_deck_texture.loadFromImage(full_deck);
    Sprite full_deck_sprite;
    full_deck_sprite.setTexture(full_deck_texture);
    full_deck_sprite.setPosition(1000, 0);
    //int score = 0;
    float fretDeckPos = 0.0;
    int first_key = 0;      //first note what will check
    //int one_note_score = 1;
    Clock clock;            //new clock for move
    std::string str;        //string for text
    char strtmp[50];        //temp string for text
    int cur_note = first_key;
    float cur_note_time = list.get(cur_note)->time;
  //  int index;
    int selected_note = 0;
    bool is_selected = false;
    std::stringstream ss;   //stream for text
   // int note_strick = 0;      //note strick
    bool flag[5] = {true, true, true, true, true}; //на всяк випадок
    Keyboard::Key keys[5] = {Keyboard::A, Keyboard::S, Keyboard::D, Keyboard::K, Keyboard::L};
    int fire[5] = {0, 0, 0, 0, 0};
    float fire_time[5];
   // bool is_good_note; // is pressing correct
    bool flag_up, flag_down, flag_left, flag_right, flag_F3, flag_F4;
    float cur_time = 0;

    clock_start.restart();
    //start = clock_start.getElapsedTime().asMicroseconds(); //get new start
    while (window.isOpen())     //start game
    {

        float time = clock.getElapsedTime().asMicroseconds(); //get seconds per frame
        while (Keyboard::isKeyPressed(Keyboard::Space));
        clock.restart();
       /*if (clock_start.getElapsedTime().asMicroseconds() > 650/speed / 1.2 && music0_flag)        {
            music0.play();
            music0_flag = false;
        }*/
        time = time / 1500 ; // set speed
        Event event;
        while (window.pollEvent(event)) // for closing window
        {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
            if (event.type == Event::MouseWheelMoved)
                cur_time += (float) event.mouseWheel.delta * 100000;
        }

        if (Keyboard::isKeyPressed(Keyboard::Num9))
        {
            if (list.get(cur_note)->tail_time > 0)
                list.get(cur_note)->tail_time -= time * 150;
        }

        if (Keyboard::isKeyPressed(Keyboard::Num0))
        {
            list.get(cur_note)->tail_time += time * 150;
        }

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (IntRect(full_deck_sprite.getPosition().x, full_deck_sprite.getPosition().y, 100, 768).contains(Mouse::getPosition()))
            {
                for (int i = 0; i < list.count(); i++)
                    if (list.get(i)->time > list.get(list.count() - 1)->time / 768 * (768 - Mouse::getPosition().y))
                    {
                        cur_note = i;
                        cur_note_time = list.get(cur_note)->time;
                        cur_time = cur_note_time;
                        break;
                    }
            }
            else if (IntRect(483, 0, 500, 768).contains(Mouse::getPosition()))
            {
                int tmp;
                float tmp_time = (float)(-Mouse::getPosition().y + 384) * 1500.0 + cur_time;
                for (tmp = 0; list.get(tmp)->time < tmp_time && tmp < list.count(); tmp++);
                cur_note = tmp;
                cur_note_time = list.get(cur_note)->time;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Up) && flag_up)
        {
            if (cur_note < list.count())
                cur_note++;
            cur_note_time = list.get(cur_note)->time;
            flag_up = false;
        }
        if (!Keyboard::isKeyPressed(Keyboard::Up))
            flag_up = true;
        if (Keyboard::isKeyPressed(Keyboard::Down) && flag_down)
        {
            if (cur_note > 0)
                cur_note--;
            cur_note_time = list.get(cur_note)->time;
            flag_down = false;
        }
        if (!Keyboard::isKeyPressed(Keyboard::Down))
            flag_down = true;

        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            fretDeckPos += time;
            cur_time += time * 1500;
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            fretDeckPos -= time;
            cur_time -= time * 1500;
        }
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            selected_note = cur_note;
        }

        if (Keyboard::isKeyPressed(Keyboard::F1))
        {
            if (cur_note > selected_note)
                for (int i = selected_note + 1; i < cur_note; i++)
                    list.get(i)->time = (float)(i - selected_note) * (list.get(cur_note)->time - list.get(selected_note)->time) / float(cur_note - selected_note) + list.get(selected_note)->time;
            else
                for (int i = cur_note + 1; i < selected_note; i++)
                    list.get(i)->time = (float)(i - cur_note) * (list.get(selected_note)->time - list.get(cur_note)->time) / float(selected_note - cur_note) + list.get(cur_note)->time;

        }

        if (Keyboard::isKeyPressed(Keyboard::F2))
        {
            if (cur_note < list.count() - 1)
                list.get(cur_note + 1)->time = list.get(cur_note)->time;
        }

        if (Keyboard::isKeyPressed(Keyboard::F3) && flag_F3)
        {
            key_data * tmp = new struct key_data;
            tmp->index = list.get(cur_note)->index;
            tmp->pos = list.get(cur_note)->pos;
            tmp->isPressed = list.get(cur_note)->isPressed;
            tmp->time = (list.get(cur_note)->time + list.get(cur_note + 1)->time) / 2;
            list.add_pos(tmp, cur_note + 1);
            flag_F3 = false;
        }
        if (!Keyboard::isKeyPressed(Keyboard::F3))
            flag_F3 = true;


        if (Keyboard::isKeyPressed(Keyboard::F4) && flag_F4)
        {
            list.del(cur_note);
            flag_F4 = false;
        }
        if (!Keyboard::isKeyPressed(Keyboard::F4))
            flag_F4 = true;


        if (Keyboard::isKeyPressed(Keyboard::Left) && flag_left)
        {
            if (list.get(cur_note)->index > 0)
            {
                (list.get(cur_note)->index)--;
                list.get(cur_note)->pos.x -= 100;
            }
            flag_left = false;
        }
        if (!Keyboard::isKeyPressed(Keyboard::Left))
            flag_left = true;

        if (Keyboard::isKeyPressed(Keyboard::Right) && flag_right)
        {
            if (list.get(cur_note)->index < 4){
                (list.get(cur_note)->index)++;
                list.get(cur_note)->pos.x += 100;
            }
            flag_right = false;
        }
        if (!Keyboard::isKeyPressed(Keyboard::Right))
            flag_right = true;
        if (Keyboard::isKeyPressed(Keyboard::Tab))
        {
            cur_time = list.get(cur_note)->time;
        }
        if (Keyboard::isKeyPressed(Keyboard::Add))
        {
            if (list.get(cur_note)->time < list.get(cur_note + 1)->time)
                list.get(cur_note)->time += time * 150;
        }
        if (Keyboard::isKeyPressed(Keyboard::Subtract))
        {
            if (list.get(cur_note)->time > list.get(cur_note - 1)->time)
                list.get(cur_note)->time -= time * 150;
        }
        arrow.setPosition(1000, 766 - (int)round(766 * list.get(cur_note)->time / list.get(list.count() - 1)->time));
        sprintf(strtmp, "Selected note: %i\nCurrent note: %i\n dt: %lf", selected_note, cur_note, ((double)list.get(cur_note)->time/1000000 - (double)list.get(selected_note)->time/1000000)); // set text



        str = std::string(strtmp);
        text.setString(str);//задает строку тексту
        text.setPosition(50, 200);//задаем позицию текста, центр камеры


        window.clear(); //clear window
        window.draw(background);
        window.draw(full_deck_sprite);
        for (int i = -30; i < 738; i++)
        {
            int k;
            k = abs((int(fretDeckPos) - i) % 658);
            //fretDeck[k].setScale(float(500) / 329 * (i + 268) / 615, 1);
            fretDeck[k].setPosition(433, 30 + i);

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
        window.draw(text);//рисую этот текст
         for (int i = 0; i < 5; i++) //drawing
             window.draw(button[i]);

        for (int i = 0; i < list.count() ; i++)
        {
            if (list.get(i) == NULL) break;
            if (list.get(i)->time - cur_time > float(1500 * 384)) //drow until the top
                break;
            if (list.get(i)->time - cur_time > -float(1500 * 384))
                {
                int cur_tmp_note;
                if (i == cur_note)
                    cur_tmp_note = 5;
                else cur_tmp_note = list.get(i)->index;
                notes[cur_tmp_note].setPosition(list.get(i)->pos.x, (cur_time - list.get(i)->time ) / 1500 + 384);
                if (notes[cur_tmp_note].getPosition().y < 30)
                {
                    Color col_s = notes[cur_tmp_note].getColor();
                    col_s.a = (notes[cur_tmp_note].getPosition().y) * 256 / 30;
                    notes[cur_tmp_note].setColor(col_s);

                }
                else
                {
                    Color col_s = notes[cur_tmp_note].getColor();
                    col_s.a = 255;
                    notes[cur_tmp_note].setColor(col_s);

                }

                for (int j = 0; j < round(list.get(i)->tail_time / 1500); j++)
                {

                    tail[cur_tmp_note].setPosition(list.get(i)->pos.x + 11, (cur_time - list.get(i)->time ) / 1500 + 12 + 384 - j);
                    window.draw(tail[cur_tmp_note]);
                }
                window.draw(notes[cur_tmp_note]);
            }

        }
       /* for (int i = 0; i < 5; i++)
            if (fire[i] != 0)
            {
                if (fire_time[i] == 0)
                    fire_time[i] = clock_start.getElapsedTime().asMicroseconds();
                fireSprite.setTextureRect(IntRect((fire[i] - 1) % 5 * 960 / 5, (fire[i] - 1) / 5 * 768 / 4, 960 / 5, 768 / 4));
                fireSprite.setScale(0.8, 0.8);
                fireSprite.setPosition(100 * i + 410, 517);
                Color col_s = fireSprite.getColor();
                col_s.a = 220;
                fireSprite.setColor(col_s);


                if (clock_start.getElapsedTime().asMicroseconds() - fire_time[i] > 15000.0 * fire[i])
                    fire[i]++;
                window.draw(fireSprite);
                if (fire[i] > 20)
                    fire[i] = 0;
            }*/
        window.draw(arrow);

        window.display();
    }

    std::fstream file;
    file.open("song2tmp11.ghfile", std::ios::out | std::ios::trunc);
    file << list.count() << std::endl;
    for (int i = 0; i < list.count(); i++)
    {
        file << list.get(i)->index << std::endl;
        file << list.get(i)->isPressed << std::endl;
        file << list.get(i)->index * 80 + 483 << std::endl;
        file << 0 << std::endl;
        file << list.get(i)->time << std::endl;
        file << list.get(i)->tail_time << std::endl;
    }
    file.close();

    return 0;
}


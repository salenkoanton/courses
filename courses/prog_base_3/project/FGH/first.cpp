#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace sf;
struct key_data{                                        //struct for list
    Vector2f pos;
    int index;
    float time;
    bool isPressed;
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


int main(void)
{
    int count = 0;
    RenderWindow window(VideoMode(1366, 768), "Guitar Hero", Style::Fullscreen);    //create window
    List list = List();                             //list for sprites
    Vector2f * pos;                                 //temp sprite for including in list
    Clock clock_start;                              //clock for getElapsedTime
    Image buffer;                                   //new image for background (set the line)
    buffer.create(1366, 768, Color::Black);
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 480; j++)
        {
            buffer.setPixel( i * 80 + 40 + 483, j + 200, Color::White);
            buffer.setPixel( i * 80 + 39 + 483, j + 200, Color::White);
            buffer.setPixel( i * 80 + 41 + 483, j + 200, Color::White);
        }                                           //end setting line
    Image image;                                    //image for texture, i'll rename it later
    Texture notesTexture, bufferTexture, buttonsTexture;                 //textures for buttons
    Sprite button[5], notes[5];                               //buttons
    image.loadFromFile("RenameToNotes.png");          //load image
    notesTexture.loadFromImage(image);
    notesTexture.setSmooth(true);                        //set smooth
    image.loadFromFile("fretbuttons-3.png");          //load image
    buttonsTexture.loadFromImage(image);
    buttonsTexture.setSmooth(true);
    for(int i = 0; i < 5; i++)
    {
        button[i].setTexture(buttonsTexture);
        button[i].setPosition(80 * i + 483, 410 + 200);
        button[i].setTextureRect(IntRect(i * 672 / 5, 0, 672 / 5, 81));
        button[i].setScale(400/float(672), 400/float(672));
        notes[i].setTexture(notesTexture);
        notes[i].setTextureRect(IntRect(i * 664 / 5, 0, 664 / 5, 664 / 5));
        notes[i].setScale(400/float(664), 400/float(664));
    }                                               //creating of 5 buttons in the bottom
    bufferTexture.loadFromImage(buffer);
    Sprite bufferSprite;
    bufferSprite.setTexture(bufferTexture);         //set sprite (lines)
    Vector2f vect(0, 0.4);
    Image fireImage;
    fireImage.loadFromFile("fire_0.png");
    Texture fireTexture;
    fireTexture.loadFromImage(fireImage);
    fireTexture.setSmooth(true);
    Sprite fireSprite;
    fireSprite.setTexture(fireTexture);
    fireSprite.setTextureRect(IntRect(0, 0, 204, 204));
    fireSprite.setPosition(0, 0);

    window.draw(fireSprite);
    window.display();
    Music music0;
    if (!music0.openFromFile("music1.ogg"))
        return -1; // error
    //music0.play();
    struct key_data * tmpdata;                      // temp struct for list
    float speed = 0.4/800;                          //number of pixels that moves in 1 microsec
    bool flag0 = false, flag1 = false, flag2 = false, flag3 = false, flag4 = false, music0_flag = true; //flags for adding only one note per pressing
    float start = clock_start.getElapsedTime().asMicroseconds(); //get start
    /*while (!Keyboard::isKeyPressed(Keyboard::Space) && window.isOpen()) //scan pressings that will shows you later
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

    }
    music0.stop();*/
    Font font;//шрифт
    font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
    Text text("", font, 40);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
    text.setColor(Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
    /*std::fstream file;
    file.open("song.ghfile", std::ios::out | std::ios::trunc);
    file << list.count() << std::endl;
    for (int i = 0; i < list.count(); i++)
    {
        file << list.get(i)->index << std::endl;
        file << list.get(i)->isPressed << std::endl;
        file << list.get(i)->pos.x << std::endl;
        file << list.get(i)->pos.y << std::endl;
        file << list.get(i)->time << std::endl;
    }
    file.close();*/
    std::fstream file1;
    file1.open("song.ghfile", std::ios::in);
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
        pos = new Vector2f(pos_x, pos_y);
        tmpdata->pos = *pos;
        list.add(tmpdata);
    }
    file1.close();
    int score = 0;
    int first_key = 0;      //first note what will check
    int one_note_score = 1;
    Clock clock;            //new clock for move
    std::string str;        //string for text
    char strtmp[50];        //temp string for text

    int index;
    std::stringstream ss;   //stream for text
    int note_strick = 0;      //note strick
    bool flag[5] = {true, true, true, true, true}; //на всяк випадок
    Keyboard::Key keys[5] = {Keyboard::A, Keyboard::S, Keyboard::D, Keyboard::K, Keyboard::L};
    int fire[5] = {0, 0, 0, 0, 0};
    float fire_time[5];
    bool is_good_note; // is pressing correct
    clock_start.restart();
    start = clock_start.getElapsedTime().asMicroseconds(); //get new start
    while (window.isOpen())     //start game
    {

        float time = clock.getElapsedTime().asMicroseconds(); //get seconds per frame

        clock.restart();
        if (clock_start.getElapsedTime().asMicroseconds() > 650/speed && music0_flag)
        {
            music0.play();
            music0_flag = false;
        }
        time = time / 800; // set speed
        Event event;
        while (window.pollEvent(event)) // for closing window
        {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
        }
        for (int i = 0; i < 5; i++)
        if (!Keyboard::isKeyPressed(keys[i]))
        {
             button[i].setTextureRect(IntRect(672 / 5 * i, 0, 672/5, 81)); //animation
             flag[i]= true;
        }
        for (int i = 0; i < 5; i++)
        if (Keyboard::isKeyPressed(keys[i]) && flag[i])
        {
            button[i].setTextureRect(IntRect(672 / 5 * i, 164, 672/5, 81)); //animation
            index = first_key; //get first note
            flag[i] = false;
            is_good_note = false;
            if (list.count() != 0)
                while ( list.get(index)->pos.y > 560) //check all notes what is in area near bottom
                {
                    if (list.get(index)->index == i)  // if corect note
                    {
                        if (!list.get(index)->isPressed){
                            one_note_score = note_strick / 60 + 1;
                            if (one_note_score > 4)
                                one_note_score = 4;
                            score += one_note_score; //increase score
                            note_strick++; // increase note strick
                            fire[i] = 1;
                            fire_time[i] = 0;
                        }
                        is_good_note = true;

                        list.get(index)->isPressed = true;
                    }
                    index++;
                    if (index >= list.count()) break; // if last note - end

                }

            if (!is_good_note)
            {
                note_strick = 0; // else make it zero
                button[i].setTextureRect(IntRect(672 / 5 * i, 81, 672/5, 81)); //animation
            }
        }
        if ( list.count() != 0)
        if ( list.get(first_key)->pos.y > 700) // if you haven't pressed note
        {
            if (!list.get(first_key)->isPressed)
                note_strick = 0; //zero strick
            list.del(first_key);
        }
        for (int i = first_key; i <  list.count() && list.get(i)->time < clock_start.getElapsedTime().asMicroseconds(); i++) // move all sprites
            list.get(i)->pos += time * vect;


        sprintf(strtmp, "%i\nGood note:%i", score, note_strick); // set text
        str = std::string(strtmp);
        text.setString("Score:" + str);//задает строку тексту
        text.setPosition(200, 200);//задаем позицию текста, центр камеры


        window.clear(); //clear window
        //window.draw(bufferSprite);
         window.draw(text);//рисую этот текст
         for (int i = 0; i < 5; i++) //drawing
             window.draw(button[i]);
        for (int i = 0; i < list.count() ; i++)
        {
            if (list.get(i)->pos.y < 160 - speed * time) //drow until the top
                break;
            if (!list.get(i)->isPressed)
            {
                notes[list.get(i)->index].setPosition(list.get(i)->pos);
                window.draw(notes[list.get(i)->index]);
            }

        }
        for (int i = 0; i < 5; i++)
            if (fire[i] != 0)
            {
                if (fire_time[i] == 0)
                    fire_time[i] = clock_start.getElapsedTime().asMicroseconds();
                fireSprite.setTextureRect(IntRect((fire[i] - 1) * 51, 0, 51, 204));
                switch (fire[i]){
                    case 1 : fireSprite.setScale(1, 0.2); fireSprite.setPosition(80 * i + 497, 590); break;
                    case 2 : fireSprite.setScale(1, 0.4); fireSprite.setPosition(80 * i + 497, 550); break;
                    case 3 : fireSprite.setScale(1, 0.4); fireSprite.setPosition(80 * i + 497, 550); break;
                    case 4 : fireSprite.setScale(1, 0.2); fireSprite.setPosition(80 * i + 497, 590); break;
                }
                if (clock_start.getElapsedTime().asMicroseconds() - fire_time[i] > 30000.0 * fire[i])
                    fire[i]++;
                window.draw(fireSprite);
                if (fire[i] > 4)
                    fire[i] = 0;
            }

        window.display();
    }

    return 0;
}

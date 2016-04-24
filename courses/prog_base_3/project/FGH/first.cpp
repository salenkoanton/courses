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
    Image image;                                    //image for texture, i'll rename it later
    Texture notesTexture, bufferTexture, buttonsTexture, backgroundTexture, fretDeckTexture;                 //textures for buttons
    Sprite button[5], notes[5], background, fretDeck[658];                               //buttons
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
        fretDeck[i].setScale(float(400) / 329 * (i + 150) / 495, 1);
        fretDeck[i].setPosition(483 + (350 - i)/ 2.5, 280 + i);
    }
    image.loadFromFile("notes.bmp");          //load image
    //image.createMaskFromColor(image.getPixel(0,0));
    notesTexture.loadFromImage(image);
    notesTexture.setSmooth(true);                        //set smooth
    /*image.loadFromFile("notes90.psd");          //load image
    image.createMaskFromColor(image.getPixel(0,0));
    notesTexture[1].loadFromImage(image);
    notesTexture[1].setSmooth(true);
    image.loadFromFile("notes80.psd");          //load image
    image.createMaskFromColor(image.getPixel(0,0));
    notesTexture[2].loadFromImage(image);
    notesTexture[2].setSmooth(true);
    image.loadFromFile("notes60.psd");          //load image
    image.createMaskFromColor(image.getPixel(0,0));
    notesTexture[3].loadFromImage(image);
    notesTexture[3].setSmooth(true);
    image.loadFromFile("notes30.psd");          //load image
    image.createMaskFromColor(image.getPixel(0,0));
    notesTexture[4].loadFromImage(image);
    notesTexture[4].setSmooth(true);*/
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
    bufferTexture.loadFromImage(buffer);
    bufferTexture.setSmooth(true);
    Sprite bufferSprite;
    bufferSprite.setTexture(bufferTexture);         //set sprite (lines)

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

    window.draw(fireSprite);
    window.display();
    Music music0;
    if (!music0.openFromFile("music3.ogg"))
        return -1; // error
   // music0.play();
    bool  music0_flag = true;
    struct key_data * tmpdata;                      // temp struct for list
    float speed = 0.4/800;                          //number of pixels that moves in 1 microsec
    /*bool flag0 = false, flag1 = false, flag2 = false, flag3 = false, flag4 = false; //flags for adding only one note per pressing
    while (!Keyboard::isKeyPressed(Keyboard::Tab));
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
    font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
    Text text("", font, 40);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
    text.setColor(Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
   /* std::fstream file;
    file.open("song2.ghfile", std::ios::out | std::ios::trunc);
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
    file1.open("song2.ghfile", std::ios::in);
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
        pos = new Vector2f(600 + tmpdata->index * 35   , pos_y + 200);
        tmpdata->pos = *pos;
        list.add(tmpdata);
    }
    file1.close();
    int score = 0;
    float fretDeckPos = 0.0;
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
    //start = clock_start.getElapsedTime().asMicroseconds(); //get new start
    while (window.isOpen())     //start game
    {

        float time = clock.getElapsedTime().asMicroseconds(); //get seconds per frame
        while (Keyboard::isKeyPressed(Keyboard::Space));
        clock.restart();
        if (clock_start.getElapsedTime().asMicroseconds() > 650/speed / 0.5 / 1.3 && music0_flag)
        {
            music0.play();
            music0_flag = false;
        }
        time = time / 1500 ; // set speed
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
            //index = first_key; //get first note
            flag[i] = false;
            is_good_note = false;
            //if (list.get(index) == NULL) break;
            if (list.count() != 0)
            for (index = first_key; ; index++) //check all notes what is in area near bottom
                {
                    if (list.get(index) == NULL) break; // if last note - end
                    if (list.get(index)->pos.y < 540) break;
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
                        music0.setVolume(100);
                        list.get(index)->isPressed = true;
                    }



                }

            if (!is_good_note)
            {
                note_strick = 0; // else make it zero
                button[i].setTextureRect(IntRect(672 / 5 * i, 81, 672/5, 81)); //animation
                music0.setVolume(0);
            }
        }
        if ( list.count() != 0)
        if ( list.get(first_key)->pos.y > 700) // if you haven't pressed note
        {
            if (!list.get(first_key)->isPressed)
            {
                note_strick = 0; //zero strick
                music0.setVolume(0);
            }
            list.del(first_key);

        }
        for (int i = first_key; i <  list.count(); i++) // move all sprites
        {
            if (list.get(i)->time > clock_start.getElapsedTime().asMicroseconds()) break;
            if (list.get(i) == NULL) break;
            list.get(i)->pos += time * vect[list.get(i)->index] * ((list.get(i)->pos.y - 180) / (float)430) * (float)1.3;
        }

        sprintf(strtmp, "%i\nNote streak:%i", score, note_strick); // set text
        str = std::string(strtmp);
        text.setString("Score:" + str);//задает строку тексту
        text.setPosition(200, 200);//задаем позицию текста, центр камеры

        fretDeckPos += time * 1.37 ;
        window.clear(); //clear window
        window.draw(background);
        for (int i = -30; i < 488; i++)
        {
            int k;
            k = abs((int((fretDeckPos +  0.84 * (400 - i) * (float(705) / (i + 305))) / 1.1 )) % 658);
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
        window.draw(text);//рисую этот текст
         for (int i = 0; i < 5; i++) //drawing
             window.draw(button[i]);
        for (int i = 0; i < list.count() ; i++)
        {
            if (list.get(i) == NULL) break;
            if (list.get(i)->pos.y < 220) //drow until the top
                break;
            if (!list.get(i)->isPressed)
            {
                notes[list.get(i)->index].setOrigin(0, 0);
                notes[list.get(i)->index].setScale(((list.get(i)->pos.y - 5) / (float)625) * 500/float(640), ((list.get(i)->pos.y - 5) / (float)625) * 500/float(640));
                notes[list.get(i)->index].setOrigin(64 * notes[list.get(i)->index].getScale().x, 64 * notes[list.get(i)->index].getScale().x);
                notes[list.get(i)->index].setPosition(list.get(i)->pos.x /*+ (50 - notes[list.get(i)->index].getOrigin().x) / 7*/ , list.get(i)->pos.y /*+  (50 - notes[list.get(i)->index].getOrigin().x) / 2*/);
                if (notes[list.get(i)->index].getPosition().y < 280)
                {
                    Color col_s = notes[list.get(i)->index].getColor();
                    col_s.a = (notes[list.get(i)->index].getPosition().y - 220) * 256 / 60;
                    notes[list.get(i)->index].setColor(col_s);

                }
                else
                {
                    Color col_s = notes[list.get(i)->index].getColor();
                    col_s.a = 255;
                    notes[list.get(i)->index].setColor(col_s);

                }
                window.draw(notes[list.get(i)->index]);
            }

        }
        for (int i = 0; i < 5; i++)
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
            }
        window.display();
    }

    return 0;
}

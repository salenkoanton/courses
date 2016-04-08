#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <sstream>
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
    Texture texture, bufferTexture;                 //textures for buttons
    Sprite button[5], notes[5];                               //buttons
    image.loadFromFile("FretButtons.png");          //load image
    texture.loadFromImage(image);
    texture.setSmooth(true);                        //set smooth
    for(int i = 0; i < 5; i++)
    {
        button[i].setTexture(texture);
        button[i].setPosition(80 * i + 483, 410 + 200);
        button[i].setTextureRect(IntRect(i * 690 / 5, 0, 690 / 5, 81));
        button[i].setScale(400/float(690), 400/float(690));
        notes[i].setTexture(texture);
        notes[i].setTextureRect(IntRect(i * 690 / 5, 81, 690 / 5, 81));
        notes[i].setScale(400/float(690), 400/float(690));
    }                                               //creating of 5 buttons in the bottom
    bufferTexture.loadFromImage(buffer);
    Sprite bufferSprite;
    bufferSprite.setTexture(bufferTexture);         //set sprite (lines)
    Vector2f vect(0, 0.4);
    float speed = 0.4/800;                          //number of pixels that moves in 1 microsec
    bool flag0 = false, flag1 = false, flag2 = false, flag3 = false, flag4 = false; //flags for adding only one note per pressing
    float start = clock_start.getElapsedTime().asMicroseconds(); //get start
    while (!Keyboard::isKeyPressed(Keyboard::Space)) //scan pressings that will shows you later
    {
        int index;
        struct key_data * tmpdata;                  //temp struct for list
        if (Keyboard::isKeyPressed(Keyboard::A)){   //if pressed A creates sprite with spetical color and .x position
            if( !flag0)
        {
            index = 0;
            count++;
            tmpdata = new struct key_data;
            tmpdata->isPressed = false;
            tmpdata->index = index;
            tmpdata->time = clock_start.getElapsedTime().asMicroseconds() - start;
            pos = new Vector2f((float)index * 80 + 483, -speed * tmpdata->time); // set position ~ time
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
            pos = new Vector2f((float)index * 80 + 483, -speed * tmpdata->time);
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
             pos = new Vector2f((float)index * 80 + 483, -speed * tmpdata->time);
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
            pos = new Vector2f((float)index * 80 + 483, -speed * tmpdata->time);
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
             pos = new Vector2f((float)index * 80 + 483,  -speed * tmpdata->time);
             tmpdata->pos = *pos;
            list.add(tmpdata);
        }
        }
        else
            flag4 = false;

    }


    Font font;//шрифт
     font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
     Text text("", font, 40);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
     text.setColor(Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
     text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
    int score = 0;
    int first_key = 0;      //first note what will check
    Clock clock;            //new clock for move
    std::string str;        //string for text
    char strtmp[50];        //temp string for text
    clock_start.restart();
    start = clock_start.getElapsedTime().asMicroseconds(); //get new start
    int index;
    std::stringstream ss;   //stream for text
    int note_strick = 0;      //note strick
    //bool flag[5] = {true, true, true, true, true}; //на всяк випадок
    bool is_good_note; // is pressing correct
    flag0 = true;
    flag1 = true;
    flag2 = true;
    flag3 = true;
    flag4 = true; //flags for only one pressing
   /* Music music;
    if (!music.openFromFile("music.ogg"))
        return -1; // error*/
    Music music1;
    if (!music1.openFromFile("music1.ogg"))
        return -1; // error
    //music.play();
    music1.play();
    while (window.isOpen())     //start game
    {

        float time = clock.getElapsedTime().asMicroseconds(); //get seconds per frame
        clock.restart();
        time = time / 800; // set speed

        Event event;
        while (window.pollEvent(event)) // for closing window
        {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
        }
        if (!Keyboard::isKeyPressed(Keyboard::A))
        {
            button[0].setTextureRect(IntRect(0, 0, 690/5, 81)); //animation
             flag0 = true;
        }
        if (!Keyboard::isKeyPressed(Keyboard::S))
        {
            button[1].setTextureRect(IntRect(690/5, 0, 690/5, 81));
            flag1 = true;
        }
        if (!Keyboard::isKeyPressed(Keyboard::D))
        {
            button[2].setTextureRect(IntRect(690/5*2, 0, 690/5, 81));
            flag2 = true;
        }
        if (!Keyboard::isKeyPressed(Keyboard::K))
        {

            button[3].setTextureRect(IntRect(690/5*3, 0, 690/5, 81));
            flag3 = true;
        }
        if (!Keyboard::isKeyPressed(Keyboard::L))
        {
            button[4].setTextureRect(IntRect(690/5*4, 0, 690/5, 81));
            flag4 = true;
        }

        if (Keyboard::isKeyPressed(Keyboard::A) && flag0)
        {
            button[0].setTextureRect(IntRect(0, 164, 690/5, 81)); //animation
            index = first_key; //get first note
            flag0 = false;
            is_good_note = false;
            if (list.count() != 0)
                while ( list.get(index)->pos.y > 560) //check all notes what is in area near bottom
                {
                    if (list.get(index)->index == 0)  // if corect note
                    {
                        if (!list.get(index)->isPressed)
                            score++; //increase score
                        is_good_note = true;
                        list.get(index)->isPressed = true;
                        //list.del(index); //delete note
                    }
                    index++;
                    if (index >= list.count()) break; // if last note - end

                }
            if (is_good_note)
                note_strick++; // increase note strick
            else
                note_strick = 0; // else make it zero
        }

        if (Keyboard::isKeyPressed(Keyboard::S) && flag1)
        {
            button[1].setTextureRect(IntRect(690/5, 164, 690/5, 81));
            index = first_key;
            flag1 = false;
            is_good_note = false;
            if (list.count() != 0)
                while (list.get(index)->pos.y > 560)
                {
                    if (list.get(index)->index == 1)
                    {
                        if (!list.get(index)->isPressed)
                            score++;
                        is_good_note = true;
                        list.get(index)->isPressed = true;
                        //list.del(index);
                        //last_key--;

                    }
                    index++;
                    if (index >= list.count()) break;

                }
            if (is_good_note)
                note_strick++;
            else
                note_strick = 0;
        }

        if (Keyboard::isKeyPressed(Keyboard::D) && flag2)
        {
            button[2].setTextureRect(IntRect(2*690/5, 164, 690/5, 81));
            index = first_key;
            flag2 = false;
            is_good_note = false;
            if (list.count() != 0)
                while (list.get(index)->pos.y > 560)
                {
                    if (list.get(index)->index == 2)
                    {
                        if (!list.get(index)->isPressed)
                            score++;
                        is_good_note = true;
                        list.get(index)->isPressed = true;
                        //list.del(index);
                        //last_key--;
                    }
                    index++;
                    if (index >= list.count()) break;

                }
            if (is_good_note)
                note_strick++;
            else
                note_strick = 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::K) && flag3)
        {
            button[3].setTextureRect(IntRect(3 * 690 / 5, 164, 690/5, 81));
            index = first_key;
            flag3 = false;
            is_good_note = false;
            if (list.count() != 0)
                while (list.get(index)->pos.y > 560)
                {
                    if (list.get(index)->index == 3)
                    {
                        if (!list.get(index)->isPressed)
                            score++;
                        is_good_note = true;
                        list.get(index)->isPressed = true;
                        //list.del(index);
                        //last_key--;
                    }
                    index++;
                    if (index >= list.count()) break;

                }
            if (is_good_note)
                note_strick++;
            else
                note_strick = 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::L) && flag4)
        {
            button[4].setTextureRect(IntRect(4*690/5, 164, 690/5, 81));
            index = first_key;
            flag4 = false;
            is_good_note = false;
            if (list.count() != 0)
                while (list.get(index)->pos.y > 560)
                {
                    if (list.get(index)->index == 4)
                    {
                        if (!list.get(index)->isPressed)
                            score++;
                        is_good_note = true;
                        list.get(index)->isPressed = true;
                        //list.del(index);
                        //last_key--;

                    }
                    index++;
                    if (index >= list.count()) break;

                }
            if (is_good_note)
                note_strick++;
            else
                note_strick = 0;
        }
           //if (last_key == 0)
           // window.close();
        if ( list.count() != 0)
        if ( list.get(first_key)->pos.y > 700) // if you haven't pressed note
        {
            if (!list.get(first_key)->isPressed)
                note_strick = 0; //zero strick
            list.del(first_key);
           // first_key++; //increase first note will check
        }
        for (int i = first_key; i <  list.count(); i++) // move all sprites
            list.get(i)->pos += time * vect;

        //ss << score;
        sprintf(strtmp, "%i\nGood note:%i", score, note_strick); // set text
        str = std::string(strtmp);
        text.setString("Score:" + str);//задает строку тексту
        text.setPosition(200, 200);//задаем позицию текста, центр камеры

     //   window.setView(view);
        window.clear(); //clear window
        window.draw(bufferSprite);
         window.draw(text);//рисую этот текст
         for (int i = 0; i < 5; i++) //drawing
             window.draw(button[i]);
        for (int i = 0; i < list.count() ; i++)
        {
            if (!list.get(i)->isPressed)
            {
                notes[list.get(i)->index].setPosition(list.get(i)->pos);
                window.draw(notes[list.get(i)->index]);
            }
            if (list.get(i)->pos.y < 200) //drow until the top
                break;
        }

        window.display();

    }

    return 0;
}

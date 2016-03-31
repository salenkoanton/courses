#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iostream>
using namespace sf;
struct key_data{
    CircleShape * circle;
    int index;
    float time;
};

struct QueueNode{
    key_data * data;
    struct QueueNode * next;

};

class Queue{

private: struct QueueNode * tail, * head;
    int cnt;
    public:
    Queue(){
        tail = new struct QueueNode;
        head = new struct QueueNode;
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
        struct QueueNode * tmp = new struct QueueNode;
        tmp->next = head->next;
        tmp->data = data;
        head->next = tmp;
        cnt++;
    }
    struct key_data * get(int pos)
    {
        struct QueueNode * tmp = head;
        for(int i = 0; i < pos + 1; i++)
            tmp = tmp->next;
        return tmp->data;
    }

    struct key_data * del(int pos)
    {
        struct QueueNode * tmp = head;
        if (pos < cnt)
        for(int i = 0; i < pos; i++)
            tmp = tmp->next;
        struct key_data * data = tmp->next->data;
        tmp->next = tmp->next->next;
        cnt--;
        return data;
    }

};


int main(void)
{
            int count = 0;
    RenderWindow window(VideoMode(700, 680), "Lesson 19. kychka-pc.ru");
   // CircleShape ** shapes = (CircleShape **)malloc (sizeof(CircleShape *) * 5);
    Queue queue = Queue();
    CircleShape * shape;
    Clock clock_start;
    Image buffer;
    buffer.create(640, 480, Color::Black);

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 480; j++)
        {
            buffer.setPixel( i * 80 + 40, j, Color::White);
            buffer.setPixel( i * 80 + 39, j, Color::White);
            buffer.setPixel( i * 80 + 41, j, Color::White);
        }
    for (int i = 0; i < 400; i++)
        for (int j = 434; j < 440; j++)
            buffer.setPixel( i, j, Color::White);
    for (int k = 0; k < 5; k++)
    for (int i = 27 + k * 80; i < 53 + k * 80; i++)
        for (int j = 424; j < 450; j++)
            buffer.setPixel( i, j, Color::White);

    Texture bufferTexture;
    bufferTexture.loadFromImage(buffer);
    Sprite bufferSprite;
    bufferSprite.setTexture(bufferTexture);
    float speed = 0.25/800;
    bool flag0 = false, flag1 = false, flag2 = false, flag3 = false, flag4 = false;
    float start = clock_start.getElapsedTime().asMicroseconds();
    while (!Keyboard::isKeyPressed(Keyboard::Space))
    {
        int i;

        struct key_data * tmpdata;



        if (Keyboard::isKeyPressed(Keyboard::A)){
            if( !flag0)
        {
            i = 0;
             shape = new CircleShape(25.f);
             shape->setFillColor(Color::Green);
            count++;
            tmpdata = new struct key_data;
            tmpdata->circle = shape;
            tmpdata->index = i;
            tmpdata->time = clock_start.getElapsedTime().asMicroseconds() - start;
            flag0 = true;
            shape->setPosition(i * 80 + 15, int( -speed * tmpdata->time));
            queue.add(tmpdata);

        }
        }
        else
            flag0 = false;

        if (Keyboard::isKeyPressed(Keyboard::S))
    {
            if( !flag1)
        {
            i = 1;
             count++;
             shape = new CircleShape(25.f);
             shape->setFillColor(Color::Cyan);
            flag1 = true;
            tmpdata = new struct key_data;
            tmpdata->circle = shape;
            tmpdata->index = i;
            tmpdata->time = clock_start.getElapsedTime().asMicroseconds() - start;
            shape->setPosition(i * 80 + 15, int( -speed * tmpdata->time));
            queue.add(tmpdata);
        }
        }
        else
            flag1 = false;

        if (Keyboard::isKeyPressed(Keyboard::D)){
            if( !flag2)
        {
            i = 2;
             count++;
             shape = new CircleShape(25.f);
             shape->setFillColor(Color::Yellow);
            flag2 = true;
            tmpdata = new struct key_data;
            tmpdata->circle = shape;
            tmpdata->index = i;
            tmpdata->time = clock_start.getElapsedTime().asMicroseconds() - start;
            shape->setPosition(i * 80 + 15, int( -speed * tmpdata->time));
            queue.add(tmpdata);
        }
        }
        else
            flag2 = false;

        if (Keyboard::isKeyPressed(Keyboard::K)){
            if( !flag3)
        {
            i = 3;
             count++;
             shape = new CircleShape(25.f);
             shape->setFillColor(Color::Blue);
            flag3 = true;
            tmpdata = new struct key_data;
            tmpdata->circle = shape;
            tmpdata->index = i;
            tmpdata->time = clock_start.getElapsedTime().asMicroseconds() - start;
            shape->setPosition(i * 80 + 15, int( -speed * tmpdata->time));
            queue.add(tmpdata);
        }
        }
        else
            flag3 = false;

        if (Keyboard::isKeyPressed(Keyboard::L)){
            if( !flag4)
        {
            i = 4;
             count++;
             shape = new CircleShape(25.f);
             shape->setFillColor(Color::Red);
            flag4 = true;
            tmpdata = new struct key_data;
            tmpdata->circle = shape;
            tmpdata->index = i;
            tmpdata->time = clock_start.getElapsedTime().asMicroseconds() - start;
            shape->setPosition(i * 80 + 15, int( -speed * tmpdata->time));
            queue.add(tmpdata);
        }
        }
        else
            flag4 = false;

    }

    Image image;
    Texture texture;
    Sprite button[5];
    image.loadFromFile("FretButtons.png");
    texture.loadFromImage(image);
    for(int i = 0; i < 5; i++)
    {
        button[i].setTexture(texture);
        button[i].setPosition(80 * i, 410);
        button[i].setTextureRect(IntRect(i * 690 / 5, 0, 690 / 5, 81));
        button[i].setScale(400/float(690), 400/float(690));
    }
    Font font;//шрифт
     font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
     Text text("", font, 40);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
     text.setColor(Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
     text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
    int score = 0;
    int last_key = queue.count() - 1;
    Clock clock;
    std::string str;
    char strtmp[25];
   // image.loadFromFile("images/1.pgn");
   // texture.loadFromImage(image);
   // sprite.setTexture(texture);
    //sprite.setTextureRect(IntRect(0, 0, w, h));
    clock_start.restart();
    start = clock_start.getElapsedTime().asMicroseconds();
    int index;
    std::stringstream ss;
    int note_good = 0;
    //bool flag[5] = {true, true, true, true, true}; //на всяк випадок
    bool is_good_note;
    flag0 = true;
    flag1 = true;
    flag2 = true;
    flag3 = true;
    flag4 = true;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        if (!Keyboard::isKeyPressed(Keyboard::A))
        {
            button[0].setTextureRect(IntRect(0, 0, 690/5, 81));
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
            button[0].setTextureRect(IntRect(0, 164, 690/5, 81));
            index = last_key;
            flag0 = false;
            is_good_note = false;
            while ( ((*(queue.get(index)->circle)).getPosition().y > 380))
            {
                if (queue.get(index)->index == 0)
                {
                    score++;
                    is_good_note = true;
                    queue.del(index);
                    last_key--;

                }
                index--;
                if (index == 0) break;

            }
            if (is_good_note)
                note_good++;
            else
                note_good = 0;
        }

        if (Keyboard::isKeyPressed(Keyboard::S) && flag1)
        {
            button[1].setTextureRect(IntRect(690/5, 164, 690/5, 81));
            index = last_key;
            flag1 = false;
            is_good_note = false;
            while ( ((*(queue.get(index)->circle)).getPosition().y > 380))
            {
                if (queue.get(index)->index == 1)
                {
                    score++;
                    is_good_note = true;
                    queue.del(index);
                    last_key--;

                }
                index--;
                if (index == 0) break;

            }
            if (is_good_note)
                note_good++;
            else
                note_good = 0;
        }

        if (Keyboard::isKeyPressed(Keyboard::D) && flag2)
        {
            button[2].setTextureRect(IntRect(2*690/5, 164, 690/5, 81));
            index = last_key;
            flag2 = false;
            is_good_note = false;
            while ( ((*(queue.get(index)->circle)).getPosition().y > 380))
            {
                if (queue.get(index)->index == 2)
                {
                    score++;
                    is_good_note = true;
                    queue.del(index);
                    last_key--;
                }
                index--;
                if (index == 0) break;

            }
            if (is_good_note)
                note_good++;
            else
                note_good = 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::K) && flag3)
        {
            button[3].setTextureRect(IntRect(3 * 690 / 5, 164, 690/5, 81));
            index = last_key;
            flag3 = false;
            is_good_note = false;
            while ( ((*(queue.get(index)->circle)).getPosition().y > 380))
            {
                if (queue.get(index)->index == 3)
                {
                    score++;
                    is_good_note = true;
                    queue.del(index);
                    last_key--;
                }
                index--;
                if (index == 0) break;

            }
            if (is_good_note)
                note_good++;
            else
                note_good = 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::L) && flag4)
        {
            button[4].setTextureRect(IntRect(4*690/5, 164, 690/5, 81));
            index = last_key;
            flag4 = false;
            is_good_note = false;
            while ( ((*(queue.get(index)->circle)).getPosition().y > 380))
            {
                if (queue.get(index)->index == 4)
                {
                    score++;
                    is_good_note = true;
                    queue.del(index);
                    last_key--;

                }
                index--;
                if (index == 0) break;

            }
            if (is_good_note)
                note_good++;
            else
                note_good = 0;
        }
           if (last_key == 0)
            window.close();
        if ( queue.get(last_key)->circle->getPosition().y > 500)
        {
            note_good = 0;
            last_key--;
        }
        for (int i = 0; i <  queue.count(); i++)
            queue.get(i)->circle->move(0, time * 0.25);

        //ss << score;
        sprintf(strtmp, "%i\nGood note:%i", score, note_good);
        str = std::string(strtmp);
        text.setString("Score:" + str);//задает строку тексту
        text.setPosition(400, 200);//задаем позицию текста, центр камеры

     //   window.setView(view);
        window.clear();
        window.draw(bufferSprite);
         window.draw(text);//рисую этот текст
         for (int i = 0; i < 5; i++)
             window.draw(button[i]);
        for (int i = queue.count() - 1; i >= 0 ; i--)
        {

            window.draw(*(queue.get(i)->circle));
            if (queue.get(i)->circle->getPosition().y < 0)
                break;
        }

        window.display();

    }

    return 0;
}/*
int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Lesson 2. kychka-pc.ru");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}*/

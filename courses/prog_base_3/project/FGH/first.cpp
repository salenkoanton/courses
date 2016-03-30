#include <SFML/Graphics.hpp>
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
    public:
    Queue(){
        tail = new struct QueueNode;
        head = new struct QueueNode;
        tail->data = NULL;
        tail->next = NULL;
        head->next = tail;
        head->data = NULL;
    }
    void add(key_data * data)
    {
        struct QueueNode * tmp = new struct QueueNode;
        tmp->next = head->next;
        tmp->data = data;
        head->next = tmp;
    }
    struct key_data * get(int pos)
    {
        struct QueueNode * tmp = head;
        for(int i = 0; i < pos + 1; i++)
            tmp = tmp->next;
        return tmp->data;
    }

    struct key_data * del()
    {
        struct QueueNode * tmp = head;

        while(tmp->next->next != tail)
            tmp = tmp->next;
        struct key_data * data = tmp->next->data;
        tmp->next = tail;
        return data;
    }

};


int main(void)
{
            int count = 0;
    RenderWindow window(VideoMode(400, 480), "Lesson 19. kychka-pc.ru");
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
    float speed = 0.25/600;
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
             shape = new CircleShape(30.f);
             shape->setFillColor(Color::Green);
            count++;
            tmpdata = new struct key_data;
            tmpdata->circle = shape;
            tmpdata->index = i;
            tmpdata->time = clock_start.getElapsedTime().asMicroseconds() - start;
            flag0 = true;
            shape->setPosition(i * 80 + 10, int( -speed * tmpdata->time));
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
             shape = new CircleShape(30.f);
             shape->setFillColor(Color::Cyan);
            flag1 = true;
            tmpdata = new struct key_data;
            tmpdata->circle = shape;
            tmpdata->index = i;
            tmpdata->time = clock_start.getElapsedTime().asMicroseconds() - start;
            shape->setPosition(i * 80, int( -speed * tmpdata->time));
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
             shape = new CircleShape(30.f);
             shape->setFillColor(Color::Yellow);
            flag2 = true;
            tmpdata = new struct key_data;
            tmpdata->circle = shape;
            tmpdata->index = i;
            tmpdata->time = clock_start.getElapsedTime().asMicroseconds() - start;
            shape->setPosition(i * 80 + 10, int( -speed * tmpdata->time));
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
             shape = new CircleShape(30.f);
             shape->setFillColor(Color::Blue);
            flag3 = true;
            tmpdata = new struct key_data;
            tmpdata->circle = shape;
            tmpdata->index = i;
            tmpdata->time = clock_start.getElapsedTime().asMicroseconds() - start;
            shape->setPosition(i * 80 + 10, int( -speed * tmpdata->time));
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
             shape = new CircleShape(30.f);
             shape->setFillColor(Color::Red);
            flag4 = true;
            tmpdata = new struct key_data;
            tmpdata->circle = shape;
            tmpdata->index = i;
            tmpdata->time = clock_start.getElapsedTime().asMicroseconds() - start;
            shape->setPosition(i * 80 + 10, int( -speed * tmpdata->time));
            queue.add(tmpdata);
        }
        }
        else
            flag4 = false;

    }

    Image image;
    Texture texture;
    Sprite sprite;

    Clock clock;
   // image.loadFromFile("images/1.pgn");
   // texture.loadFromImage(image);
   // sprite.setTexture(texture);
    //sprite.setTextureRect(IntRect(0, 0, w, h));
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
        for (int i = 0; i <  count; i++)
            queue.get(i)->circle->move(0, time * 0.25);


     //   window.setView(view);
        window.clear();
        window.draw(bufferSprite);
        for (int i = 0; i <  count; i++)
            window.draw(*(queue.get(i)->circle));

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

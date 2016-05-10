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
    int screen_h = 480;
    int screen_w = 640;
    float h_sc = float(screen_h) / 768;
    float w_sc = float(screen_w) / 1366;
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

    image.loadFromFile("note_strick.png");
    image.createMaskFromColor(image.getPixel(0, 55));
    Texture note_strickcounter_texture;
    note_strickcounter_texture.loadFromImage(image);
    note_strickcounter_texture.setSmooth(true);
    Sprite note_strickcounter;
    note_strickcounter.setTexture(note_strickcounter_texture);
    note_strickcounter.setPosition(93, 660);

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
    font.loadFromFile("font/FIRESTARTER.ttf");//передаем нашему шрифту файл шрифта
    Text text("", font, 40);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
    text.setStyle(sf::Text::Bold);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
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
    file1.open("song2tmp7.ghfile", std::ios::in);
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
        pos = new Vector2f(620 + tmpdata->index * 32   , pos_y + 200);
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

    float rock_time[6] = { 1000000.0 , 1000000.0 , 1000000.0 , 1800000.0 , 2600000.0, 3600000.0};
    float cur_rock_time = 0;
    int notes_pleyed_count = 0;
    int rock_load_type = 0;
    int rock_load_notes = 70 + 20 * rock_load_type;
    int count_false = 0;
    float line_time = 483200.0;
    float line_time1 = line_time;
    Clock clock_line;
    int playing = 36;
    int index;
    std::stringstream ss;   //stream for text
    int note_strick = 0;      //note strick
    bool flag[5] = {true, true, true, true, true}; //на всяк випадок
    Keyboard::Key keys[5] = {Keyboard::A, Keyboard::S, Keyboard::D, Keyboard::K, Keyboard::L};
    int fire[5] = {0, 0, 0, 0, 0};
    float fire_time[5];
    bool is_good_note, isInRock = false; // is pressing correct
    //float bef_time;
    float time = 0.0;
    clock_start.restart();
    clock_line.restart();
    //start = clock_start.getElapsedTime().asMicroseconds(); //get new start
    while (window.isOpen())     //start game
    {
        //bef_time = time;
        time = clock.getElapsedTime().asMicroseconds(); //get seconds per frame
        while (Keyboard::isKeyPressed(Keyboard::Space));
        clock.restart();
        if (clock_start.getElapsedTime().asMicroseconds() > 650/speed / 0.5 / 1.7  && music0_flag)
        {
            music0.play();
            music0_flag = false;
        }
        time /= 1500 ; // set speed
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
                    if (list.get(index)->pos.y < 500) break;
                    if (list.get(index)->index == i)  // if corect note
                    {
                        if (!list.get(index)->isPressed){
                            one_note_score = note_strick / 60 + 1;
                            if (one_note_score > 4)
                                one_note_score = 4;
                            score += one_note_score * (1 + isInRock); //increase score
                            if (playing < 71)
                                playing++;
                            note_strick++; // increase note strick
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
                        list.get(index)->isPressed = true;
                    }



                }

            if (!is_good_note)
            {
                note_strick = 0; // else make it zero
                playing -= 3;
                rock_load_notes = rock_load_type * 20 + 70;
                button[i].setTextureRect(IntRect(672 / 5 * i, 81, 672/5, 81)); //animation
                music0.setVolume(50);
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::J))
            if (rock_load_type > 1 && !isInRock)
            {
                rock_load_type++;
                isInRock = true;
                cur_rock_time = clock_start.getElapsedTime().asMicroseconds();

            }
        if (isInRock)
            if (clock_start.getElapsedTime().asMicroseconds() - cur_rock_time > rock_time[rock_load_type - 1])
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
                note_strick = 0; //zero strick
                rock_load_notes = rock_load_type * 20 + 70;
                playing -= 3;
                music0.setVolume(50);
            }
            list.del(first_key);

        }
        for (int i = first_key; i <  list.count(); i++) // move all sprites
        {
            if (list.get(i)->time > clock_start.getElapsedTime().asMicroseconds()) break;
            if (list.get(i) == NULL) break;
            if (list.get(i)->pos.y == 200)
                list.get(i)->pos += (float)(clock_start.getElapsedTime().asMicroseconds() - list.get(i)->time) / 1500 * vect[list.get(i)->index] * ((list.get(i)->pos.y - 180) / (float)430) * (float)1.3;
            list.get(i)->pos += (time) * vect[list.get(i)->index] * ((list.get(i)->pos.y - 180) / (float)430) * (float)1.3;
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
        for (int tmpscore = score, i = 0; tmpscore > 0; tmpscore /= 10)
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
            window.draw(rock_meters[playing / 8]);
        }
        else
        {
            window.draw(rock_meters[0]);
            text.setString("Looser!!!");
            text.setPosition(610, 200);
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
        for (int i = 0; i < 20; i++)
        {

            line.setOrigin(250, 2);
            line.setScale(((lines_pos[i].y - 5) / (float)625), ((lines_pos[i].y - 5) / (float)625));
           // line.setOrigin(250 * line.getScale().x, 2);
            line.setPosition(lines_pos[i].x /*+ (50 - notes[list.get(i)->index].getOrigin().x) / 7*/ , lines_pos[i].y /*+  (50 - notes[list.get(i)->index].getOrigin().x) / 2*/);
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
            if (isInRock)
                index_tmp = 10;
            else
                index_tmp = list.get(i)->index + 5 * (rock_load_notes - i + notes_pleyed_count < 20 && rock_load_notes - i + notes_pleyed_count > 0);
            if (list.get(i) == NULL) break;
            if (list.get(i)->pos.y < 220) //drow until the top
                break;
            if (!list.get(i)->isPressed)
            {
                notes[index_tmp].setOrigin(64, 64);
                notes[index_tmp].setScale(((list.get(i)->pos.y - 5) / (float)625) * 500/float(640), ((list.get(i)->pos.y - 5) / (float)625) * 500/float(640));
                //notes[index_tmp].setOrigin(64 * notes[index_tmp].getScale().x, 64 * notes[index_tmp].getScale().x);
                notes[index_tmp].setPosition(list.get(i)->pos.x /*+ (50 - notes[list.get(i)->index].getOrigin().x) / 7*/ , list.get(i)->pos.y /*+  (50 - notes[list.get(i)->index].getOrigin().x) / 2*/);
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
/*
int check(bool in[5], bool out[5])
{
    bool flag = false;
    bool flag1 = false;
    for (int i = 0; i < 5; i++)
    {
        if (in[i] && out[i])
            flag = true;
        else
        {
            if (in[i] && !flag1)
                flag1 = true;
            else return false;
        }
    }
    return true;
}
*/

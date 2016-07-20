#ifndef PLAYER
#define PLAYER
#include "map.h"
#include "enums.h"
using namespace sf;

enum hero_move{
    HERO_DOWN = 0,
    HERO_LEFT,
    HERO_RIGHT,
    HERO_UP
};


class Player{
private:
    Sprite arrow, hero;
    Color arrow_color;
    moves ** way;
    Map * map;
    unsigned x, y;
public:
    Player(Texture &arrow_texture, Texture &hero_texture)
    {
        arrow_color = Color(250, 40, 50);
        arrow.setTexture(arrow_texture);
        arrow.setColor(arrow_color);
        arrow.setOrigin(BLOCK_WIGHT / 2, BLOCK_HIGHT / 2);
        hero.setTexture(hero_texture);
        hero.setScale((float(BLOCK_WIGHT) / hero_texture.getSize().x) * 4, (float(BLOCK_HIGHT) / hero_texture.getSize().y) * 4);
    }
    Player(Texture &arrow_texture, Texture &hero_texture, Map * map)
    {
        arrow_color = Color(250, 40, 50);
        arrow.setTexture(arrow_texture);
        arrow.setColor(arrow_color);
        arrow.setOrigin(BLOCK_WIGHT / 2, BLOCK_HIGHT / 2);
        hero.setTexture(hero_texture);
        hero.setScale((float(BLOCK_WIGHT) / hero_texture.getSize().x) * 4, (float(BLOCK_HIGHT) / hero_texture.getSize().y) * 4);
        this->map = map;
        way = new moves * [map->get_hight()];
        for (unsigned i = 0; i < map->get_hight(); i++)
            way[i] = new moves [map->get_wight()];
        for (unsigned i = 0; i < map->get_hight(); i++)
            for (unsigned j = 0; j < map->get_wight(); j++)
                way[i][j] = NO_MOVE;
        x = map->get_start_x();
        y = map->get_start_y();
        hero.setTextureRect(IntRect(0, HERO_RIGHT * hero.getTexture()->getSize().y / 4, hero.getTexture()->getSize().x / 4, hero.getTexture()->getSize().y / 4));
        hero.setPosition(BLOCK_WIGHT * x, BLOCK_HIGHT * y);
    }
    void delMap()
    {
        if (way != NULL)
        {
            for (unsigned i = 0; i < this->map->get_hight(); i++)
                delete [] way[i];
            delete [] way;
        }
    }
    void setMap(Map * map)
    {

        this->map = map;
        way = new moves * [map->get_hight()];
        for (unsigned i = 0; i < map->get_hight(); i++)
            way[i] = new moves [map->get_wight()];
        for (unsigned i = 0; i < map->get_hight(); i++)
            for (unsigned j = 0; j < map->get_wight(); j++)
                way[i][j] = NO_MOVE;
        x = map->get_start_x();
        y = map->get_start_y();
        hero.setPosition(BLOCK_WIGHT * x, BLOCK_HIGHT * y);
    }
    void restart()
    {
        for (unsigned i = 0; i < map->get_hight(); i++)
            for (unsigned j = 0; j < map->get_wight(); j++)
                way[i][j] = NO_MOVE;
        x = map->get_start_x();
        y = map->get_start_y();
        hero.setPosition(BLOCK_WIGHT * x, BLOCK_HIGHT * y);
    }

    void draw(RenderWindow &window)
    {
        for (unsigned i = 0; i < map->get_hight(); i++)
            for (unsigned j = 0; j < map->get_wight(); j++)
                if (way[i][j])
                {
                    arrow.setRotation(90 * (way[i][j] - 1));
                    arrow.setPosition(BLOCK_WIGHT / 2 + j * BLOCK_WIGHT, BLOCK_HIGHT / 2 + i * BLOCK_HIGHT);
                    window.draw(arrow);
                }
        window.draw(hero);
    }

    bool check_move(enum moves move)
    {
        bool result;
        switch (move) {
        case UP:
            result = map->get_block(x, y - 1);
            break;
        case DOWN:
            result = map->get_block(x, y + 1);
            break;
        case LEFT:
            result = map->get_block(x - 1, y);
            break;
        case RIGHT:
            result = map->get_block(x + 1, y);
            break;
        default:
            result = false;
            break;
        }
        return result;
    }

    int move_up()
    {
        int block = map->get_block(x, y - 1);
        if (block)
        {
            way[y][x] = UP;
            y--;
            hero.setTextureRect(IntRect(0, HERO_UP * hero.getTexture()->getSize().y / 4, hero.getTexture()->getSize().x / 4, hero.getTexture()->getSize().y / 4));
            hero.move(0, -BLOCK_HIGHT);
            return 1;
        }
        return 0;
    }
    int move_down()
    {
        int block = map->get_block(x, y + 1);
        if (block)
        {
            way[y][x] = DOWN;
            y++;
            hero.setTextureRect(IntRect(0, HERO_DOWN * hero.getTexture()->getSize().y / 4, hero.getTexture()->getSize().x / 4, hero.getTexture()->getSize().y / 4));
            hero.move(0, BLOCK_HIGHT);
            return 1;
        }
        return 0;
    }
    int move_right()
    {
        int block = map->get_block(x + 1, y);
        if (block)
        {
            way[y][x] = RIGHT;
            x++;
            hero.setTextureRect(IntRect(0, HERO_RIGHT * hero.getTexture()->getSize().y / 4, hero.getTexture()->getSize().x / 4, hero.getTexture()->getSize().y / 4));
            hero.move(BLOCK_WIGHT, 0);
            return 1;
        }
        return 0;
    }
    int move_left()
    {
        int block = map->get_block(x - 1, y);
        if (block)
        {
            way[y][x] = LEFT;
            x--;
            hero.setTextureRect(IntRect(0, HERO_LEFT * hero.getTexture()->getSize().y / 4, hero.getTexture()->getSize().x / 4, hero.getTexture()->getSize().y / 4));

            hero.move(-BLOCK_WIGHT, 0);
            return 1;
        }
        return 0;
    }

    ~Player()
    {
        if (way != NULL)
        {
            for (unsigned i = 0; i < map->get_hight(); i++)
                delete [] way[i];
            delete [] way;
        }
    }

    enum block get_cur_block()
    {
        return map->get_block(x, y);
    }


};

#endif // PLAYER


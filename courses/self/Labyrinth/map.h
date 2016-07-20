#ifndef MAP
#define MAP
#include <SFML/Graphics.hpp>
#define BLOCK_HIGHT 15
#define BLOCK_WIGHT 15
using namespace sf;

enum block{
    WALL = 0,
    ROAD,
    COMPLETED
};
class Map{
private:
    unsigned hight, wight;
    enum block ** map;
    Sprite stone, road, coin;
    unsigned start_x, start_y;
public:
    Map(Texture &blocks)
    {
        map = NULL;
        stone.setTexture(blocks);
        stone.setTextureRect(IntRect(3 * BLOCK_WIGHT, 2 * BLOCK_HIGHT, BLOCK_WIGHT, BLOCK_HIGHT));

        road.setTexture(blocks);
        road.setTextureRect(IntRect(0 * BLOCK_WIGHT, 2 * BLOCK_HIGHT, BLOCK_WIGHT, BLOCK_HIGHT));

        coin.setTexture(blocks);
        coin.setTextureRect(IntRect(1 * BLOCK_WIGHT, 3 * BLOCK_HIGHT, BLOCK_WIGHT, BLOCK_HIGHT));
    }

    void reset(unsigned hight, unsigned wight, enum block ** map, int x, int y)
    {
        if (this->map != NULL)
        {
            for (unsigned i = 0; i < this->hight; i++)
                delete [] this->map[i];
            delete [] this->map;
        }
        this->hight = hight;
        this->wight = wight;

        this->map = new enum  block* [hight];
        for (unsigned i = 0; i < hight; i++)
            this->map[i] = new enum block[wight];
        for (unsigned i = 0; i < hight; i++)
            for (unsigned j = 0; j < wight; j++)
                this->map[i][j] = map[i][j];
        start_x = x;
        start_y = y;
    }

    void draw(RenderWindow &window){
        for (unsigned i = 0; i < hight; i++)
            for (unsigned j = 0; j < wight; j++)
                switch (map[i][j]) {
                case ROAD:
                    road.setPosition(j * BLOCK_WIGHT, i * BLOCK_HIGHT);
                    window.draw(road);
                    break;
                case COMPLETED:
                    coin.setPosition(j * BLOCK_WIGHT, i * BLOCK_HIGHT);
                    window.draw(coin);
                    break;
                default:
                    stone.setPosition(j * BLOCK_WIGHT, i * BLOCK_HIGHT);
                    window.draw(stone);
                    break;
                }
    }
    unsigned get_hight()
    {
        return hight;
    }
    unsigned get_wight()
    {
        return wight;
    }

    unsigned get_start_x()
    {
        return start_x;
    }
    unsigned get_start_y()
    {
        return start_y;
    }

    enum block get_block(unsigned x, unsigned y)
    {
        if (x < wight && y < hight)
            return map[y][x];
        return WALL;
    }

    ~Map()
    {
        if (this->map != NULL)
        {
            for (unsigned i = 0; i < hight; i++)
                delete [] this->map[i];
            delete [] this->map;
        }
    }

};

#endif // MAP


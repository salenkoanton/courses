#ifndef SONG_LIST
#define SONG_LIST
#include <SFML/Graphics.hpp>
#include "career.h"
#include "game.h"
#include "menu.h"
using namespace sf;
int song_list(RenderWindow &window, Sprite background, Sprite button_background, Font font, Keyboard::Key * keys, Player * player, bool isCareer, int conc);
#endif // SONG_LIST


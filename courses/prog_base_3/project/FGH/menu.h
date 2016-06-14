#ifndef MENU
#define MENU
#include <fstream>
#include <iostream>
#include "career.h"
#include "song_list.h"
#define WINDOW_WIGHT 1366
#define WINDOW_HIGHT 768
#define BUTTON_FIRST_POS_X 150
#define BUTTON_FIRST_POS_Y 202
#define BUTTON_DELTA_POS 50
using namespace sf;
void settings(Keyboard::Key * keys, RenderWindow &window, Sprite background, Sprite button_background, Font font);
std::string fromKeyboardToChar(Keyboard::Key key);

#endif // MENU


#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "career.h"
using namespace sf;
int game(RenderWindow &window, Keyboard::Key * keys, Player * player, int song_id, bool isCareer, char * file_music, char * file_notes, int start_pause_time, int conc);
int pause(Keyboard::Key * keys, RenderWindow &window, Font font);
#endif // GAME_H


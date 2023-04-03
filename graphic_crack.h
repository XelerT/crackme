#ifndef GRAPHIC_CRACK_H
#define GRAPHIC_CRACK_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

int play_gif_progress_bar (char *gif_folder);
void print_i_frame        (char *gif_folder, char *frame_name, int frame_counter, sf::RenderWindow* window);

#endif /*GRAPHIC_CRACK_H*/

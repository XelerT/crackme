#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include "graphic_crack.h"

static const float MAX_PROGRESS_LENGTH = 600.f;

int play_gif_progress_bar (char *gif_folder)
{
        sf::RenderWindow window(sf::VideoMode(MAX_PROGRESS_LENGTH, 400), "Rewritting you...");
        sf::RectangleShape rectangle(sf::Vector2f(MAX_PROGRESS_LENGTH, 50.f));
        rectangle.setFillColor(sf::Color(200, 200, 200));

        window.clear();
        window.draw(rectangle);
        window.display();

        sf::SoundBuffer buffer;
        buffer.loadFromFile("sound.wav");

        sf::Sound sound;
        sound.setBuffer(buffer);
        sound.play();

        double progress_bar_length = 10;
        double progress_bar_y = 50;

        sf::Image Image;
        int n_frames = 39;
        int frame_counter = 0;
        char frame_name[30] = {'\0'};

        while (window.isOpen() && progress_bar_length / 10 <= MAX_PROGRESS_LENGTH) {
                sf::Event event;
                while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed || progress_bar_length > MAX_PROGRESS_LENGTH) {
                                window.close();
                                sound.stop();
                        }
                }

                sf::sleep(sf::seconds(0.1f));
                sf::RectangleShape progress_bar(sf::Vector2f(progress_bar_length / 10, progress_bar_y));

                progress_bar.setFillColor(sf::Color(200, 250, 50));
                window.draw(progress_bar);
                window.display();

                progress_bar_length += 50;

                print_i_frame(gif_folder, frame_name, frame_counter, &window);

                if (frame_counter < n_frames)
                        frame_counter++;
                else
                        frame_counter = 0;
        }

        return 0;
}

void print_i_frame (char *gif_folder, char *frame_name, int frame_counter, sf::RenderWindow* window)
{
        sf::Texture texture;
        sprintf(frame_name, "%s/%d.tga", gif_folder, frame_counter);
        texture.loadFromFile(frame_name);

        sf::Sprite sprite(texture);
        sf::Vector2u size = texture.getSize();
        sprite.setOrigin(-60, -100);
        sf::Vector2f increment(20.f, 20.f);
        window->draw(sprite);
}


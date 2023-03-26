#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
// #include <SFML/Sprite.hpp>
#include <vector>

class my_stream_c : public sf::SoundStream
{
        public:

        void load (const sf::SoundBuffer& buffer)
        {
                // extract the audio samples from the sound buffer to our own container
                m_samples.assign(buffer.getSamples(), buffer.getSamples() + buffer.getSampleCount());

                // reset the current playing position
                m_currentSample = 0;

                // initialize the base class
                initialize(buffer.getChannelCount(), buffer.getSampleRate());
        }

        private:

        virtual bool onGetData (Chunk& data)
        {
                // number of samples to stream every time the function is called;
                // in a more robust implementation, it should be a fixed
                // amount of time rather than an arbitrary number of samples
                const int samplesToStream = 50000;

                // set the pointer to the next audio samples to be played
                data.samples = &m_samples[m_currentSample];

                // have we reached the end of the sound?
                if (m_currentSample + samplesToStream <= m_samples.size())
                {
                // end not reached: stream the samples and continue
                data.sampleCount = samplesToStream;
                m_currentSample += samplesToStream;
                return true;
                }
                else
                {
                // end of stream reached: stream the remaining samples and stop playback
                data.sampleCount = m_samples.size() - m_currentSample;
                m_currentSample = m_samples.size();
                return false;
                }
        }

        virtual void onSeek(sf::Time timeOffset)
        {
                // compute the corresponding sample index according to the sample rate and channel count
                m_currentSample = static_cast<std::size_t>(timeOffset.asSeconds() * getSampleRate() * getChannelCount());
        }

        std::vector<sf::Int16> m_samples;
        std::size_t m_currentSample;
};

int main()
{
        sf::RenderWindow window(sf::VideoMode(600, 400), "SFML works!");
        sf::RectangleShape rectangle(sf::Vector2f(120.f, 50.f));
        rectangle.setFillColor(sf::Color(200, 200, 200));

        window.clear();
        window.draw(rectangle);
        window.display();

        sf::SoundBuffer buffer;
        buffer.loadFromFile("sound.wav");

        // initialize and play our custom stream
        my_stream_c stream;
        stream.load(buffer);
        stream.play();

        double progress_bar_length = 50;
        double progress_bar_y = 50;

        sf::Image Image;
        int n_frames = 39;
        int frame_counter = 0;
        char frame_name[30] = {'\0'};

        while (window.isOpen() && stream.getStatus() == my_stream_c::Playing) {
                sf::Event event;
                while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed)
                                window.close();
                }

                sf::sleep(sf::seconds(0.1f));
                sf::RectangleShape progress_bar(sf::Vector2f(progress_bar_length / 100, progress_bar_y));

                progress_bar.setFillColor(sf::Color(200, 250, 50));
                window.draw(progress_bar);
                window.display();

                progress_bar_length++;

                sf::Texture texture;
                sprintf(frame_name, "gif/%d.tga", frame_counter);
                texture.loadFromFile(frame_name);

                sf::Sprite sprite(texture);
                sf::Vector2u size = texture.getSize();
                sprite.setOrigin(-60, -100);
                sf::Vector2f increment(20.f, 20.f);
                window.draw(sprite);

                if (frame_counter < n_frames)
                        frame_counter++;
                else
                        frame_counter = 0;
        }

        return 0;
}


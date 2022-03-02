//#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stack>
#include <vector>
#include <iostream>
#include "source.hpp"
using namespace std;
int main(int, char const**)
{
    //creating and andjusting maze
    sf::Time seconds = sf::seconds(0.1);
    sf::Clock clock;
    sf::Time elapsed;
    Cell maze[height][width];
    vector<Path> path_to_end;
    initialize_maze(*maze);
    stack<Cell> path;
    create_maze(*maze, path);
    reset_maze(*maze,path_to_end);
    
    //creating window
    sf::RenderWindow window(sf::VideoMode(WIDTH  , HEIGHT), "Growing Tree");
    
    while (window.isOpen())
    {
        elapsed = clock.getElapsedTime(); //for timer
        find_way(elapsed, clock, *maze, path_to_end); //dynamic find of path
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        
        window.clear(sf::Color::White);
        draw_maze(*maze, window, path_to_end);
        window.display();
    }
    return EXIT_SUCCESS;
}

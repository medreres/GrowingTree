#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <stack>
#include <vector>
#include <iostream>
#include "source.hpp"
using namespace std;
int main(int, char const**)
{
    sf::RenderWindow window(sf::VideoMode(WIDTH  , HEIGHT), "Growing Tree");
//    srand(time(NULL));
    
    //initialize
    Cell maze[height][width];
    initialize(*maze);
    
    
    //starting from frist random cell
    srand(time(NULL));
    int startX = rand() % (width - 1);
    int startY = rand() % (height - 1);
    cout << "Starting point " << startX << " " << startY << endl;
    sf::Time seconds = sf::seconds(0.1);
    sf::Clock clock;
    maze[startY][startX].is_visited = true;
    
    
    stack<Cell> path;
    path.push(maze[startY][startX]);
    while (!path.empty())
    {
        Cell _cell = path.top();
        vector<Cell> nextStep;
        if (_cell.y > 0 && maze[_cell.y - 1][_cell.x].is_visited == false)
            nextStep.push_back(maze[_cell.y - 1][_cell.x]);
        if (_cell.y < height - 1 && maze[_cell.y + 1][_cell.x].is_visited == false)
            nextStep.push_back(maze[_cell.y + 1][_cell.x]);
        if (_cell.x > 0 && maze[_cell.y][_cell.x - 1].is_visited == false)
            nextStep.push_back(maze[_cell.y][_cell.x - 1]);
        if (_cell.x < width - 1 && maze[_cell.y][_cell.x + 1].is_visited == false)
            nextStep.push_back(maze[_cell.y][_cell.x + 1]);
        if (!nextStep.empty())
        {
            Cell next = nextStep[rand() % nextStep.size()];
            if (next.x != _cell.x)
            {
                if (_cell.x > next.x)
                {
                    maze[_cell.y][_cell.x].Left = Open;
                    maze[_cell.y][_cell.x].Leftl.setFillColor(sf::Color::White);
                    maze[next.y][next.x].Right = Open;
                    maze[next.y][next.x].Rightl.setFillColor(sf::Color::White);
                }
                else
                {
                    maze[_cell.y][_cell.x].Right = Open;
                    maze[_cell.y][_cell.x].Rightl.setFillColor(sf::Color::White);
                    maze[next.y][next.x].Left = Open;
                    maze[next.y][next.x].Leftl.setFillColor(sf::Color::White);
                }
            }
            if (next.y != _cell.y)
            {
                if (next.y > _cell.y)
                {
                    maze[next.y][next.x].Top = Open;
                    maze[next.y][next.x].Topl.setFillColor(sf::Color::White);
                    maze[_cell.y][_cell.x].Bottom = Open;
                    maze[_cell.y][_cell.x].Bottoml.setFillColor(sf::Color::White);
                }
                else
                {
                    maze[next.y][next.x].Bottom = Open;
                    maze[next.y][next.x].Bottoml.setFillColor(sf::Color::White);
                    maze[_cell.y][_cell.x].Top = Open;
                    maze[_cell.y][_cell.x].Topl.setFillColor(sf::Color::White);
                }
            }
            maze[next.y][next.x].is_visited = true;
            path.push(next);
        }
        else
            path.pop();
    }
    
    
    //finding way
    maze[height - 1][0].Leftl.setFillColor(sf::Color::White);
    maze[0][width-1].Rightl.setFillColor(sf::Color::White);
    maze[0][width-1].is_end = 1;
   // Path fork;
    
    
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x ++) {
            maze[y][x].is_visited = false;
        }
    }
    
    
    vector<Path> path_to_end;
    startX = 0;
    startY = height-1;
    maze[startY][startX].is_visited = true;
    path_to_end.push_back(Path(startX,startY));
    Cell fork;
    bool is_fork = 0;
    bool is_vertical = 0;
    
    
    // Start the game loop
    while (window.isOpen())
    {
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
        
        
        sf::Time elapsed = clock.getElapsedTime();
        if(elapsed.asSeconds() > 0.2)
        {
            clock.restart();
            if(maze[path_to_end.back().y][path_to_end.back().x].is_end == 0)
            {
                Cell _path = maze[path_to_end.back().y][path_to_end.back().x];
                vector<Cell> next_step;
                if(_path.x > 0 && maze[_path.y][_path.x ].Left == Open && maze[_path.y][_path.x - 1].is_visited == false )
                    next_step.push_back(maze[_path.y][_path.x - 1]);
                if(_path.x < width - 1 && maze[_path.y][_path.x].Right == Open && maze[_path.y][_path.x + 1].is_visited == false)
                    next_step.push_back(maze[_path.y][_path.x + 1]);
                if(_path.y > 0 && maze[_path.y - 1][_path.x].Bottom == Open && maze[_path.y - 1][_path.x ].is_visited == false)
                    next_step.push_back(maze[_path.y - 1][_path.x]);
                if(_path.y < height - 1 && maze[_path.y + 1][_path.x].Top == Open && maze[_path.y + 1][_path.x].is_visited == false)
                    next_step.push_back(maze[_path.y + 1][_path.x]);
                if(!next_step.empty())
                {
                    Cell next = next_step[rand() % next_step.size()];
                    maze[next.y][next.x].is_visited = true;
                    if(next.y != _path.y)
                        is_vertical = 1;
                    path_to_end.push_back(Path(next.x,next.y));
                    if(is_vertical)
                        is_vertical = 0;
                }
                else{
                    maze[path_to_end.back().y][path_to_end.back().x].is_visited = true;
                    path_to_end.pop_back();
                }
            }
        }
        
        
        
        // Clear screen
        window.clear(sf::Color::White);
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                window.draw(maze[y][x].Topl);
                window.draw(maze[y][x].Rightl);
                window.draw(maze[y][x].Bottoml);
                window.draw(maze[y][x].Leftl);
            }
        }
        for (int i = 0; i < path_to_end.size(); i++) {
            window.draw(path_to_end[i].line);
            
        }
       
        window.display();
    }
    
    return EXIT_SUCCESS;
}

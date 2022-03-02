#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <stack>
#include <vector>
#include <iostream>
using namespace std;
const int height = 11;
const int width = 11;
const int SIZE = 50;
const int MOVE = 200;
enum CellState
{
    Close,
    Open
};
class Cell
{
public:
    int x;
    int y;
    CellState Left = Close;
    CellState Right = Close;
    CellState Top = Close;
    CellState Bottom = Close;
    bool is_visited = false;
    sf::RectangleShape Topl;
    sf::RectangleShape Bottoml;
    sf::RectangleShape Rightl;
    sf::RectangleShape Leftl;
    Cell()
    {
        x = 0;
        y = 0;
        
        Topl.setFillColor(sf::Color::Black);
        Topl.setSize(sf::Vector2f(SIZE,2));
        
        
        
        Bottoml.setFillColor(sf::Color::Black);
        Bottoml.setSize(sf::Vector2f(SIZE,2));
        
        
        
        Leftl.setFillColor(sf::Color::Black);
        Leftl.setSize(sf::Vector2f(SIZE,2));
        
        
        
        Rightl.setFillColor(sf::Color::Black);
        Rightl.setSize(sf::Vector2f(SIZE,2));
        
        
        is_visited = false;
        Left = Right = Top = Bottom = Close;
        
    }
};
class Path
{
public:
    enum Rotation
    {
        HORIZONTAL,
        VERTICAL
    };
    int x;
    int y;
    sf::RectangleShape line;
    Path()
    {
        x = y = 0;
        line.setFillColor(sf::Color::Red);
        line.setSize(sf::Vector2f(SIZE,3));
        line.setPosition(x*SIZE+MOVE, y*SIZE+MOVE);
    }
    Path(int x, int y, Rotation rot = HORIZONTAL)
    {
        this->x = x;
        this->y = y;
        line.setFillColor(sf::Color::Red);
        line.setPosition(x*SIZE-SIZE/2+MOVE, y*SIZE-SIZE/2+MOVE);
        line.setSize(sf::Vector2f(SIZE,3));
        if(rot == VERTICAL)
        {
            line.rotate(90);
            line.setPosition(x*SIZE+SIZE/2+MOVE, y*SIZE-SIZE*1.5+MOVE);
            
        }
    }
    
};
int main(int, char const**)
{
    sf::RenderWindow window(sf::VideoMode(1366  , 768), "SFML window");
    
    
    Cell maze[height][width];
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            maze[y][x].x = x;
            maze[y][x].y = y;
            
            //                maze[y][x].Bottoml.setSize(sf::Vector2f(SIZE,3));
            //                maze[y][x].Bottoml.setFillColor(sf::Color::Black);
            maze[y][x].Bottoml.setPosition(maze[y][x].x*SIZE + MOVE, maze[y][x].y*SIZE+MOVE);
            
            
            
            
            maze[y][x].Topl.setPosition(maze[y][x].x*SIZE+MOVE, maze[y][x].y*SIZE-SIZE+MOVE);
            //                maze[y][x].Topl.setFillColor(sf::Color::Black);
            //                maze[y][x].Topl.setSize(sf::Vector2f(SIZE,3));
            
            
            
            maze[y][x].Leftl.setPosition(maze[y][x].x*SIZE+MOVE, maze[y][x].y*SIZE+MOVE);
            //                maze[y][x].Leftl.setFillColor(sf::Color::Black);
            //                maze[y][x].Leftl.setSize(sf::Vector2f(SIZE,3));
            maze[y][x].Leftl.rotate(-90);
            
            
            
            maze[y][x].Rightl.setPosition(maze[y][x].x*SIZE+SIZE+MOVE, maze[y][x].y*SIZE-SIZE+MOVE);
            //                maze[y][x].Rightl.setFillColor(sf::Color::Black);
            //                maze[y][x].Rightl.setSize(sf::Vector2f(SIZE,3));
            maze[y][x].Rightl.rotate(90);
            
            
            
        }
    
    //starting from frist random cell
    srand(time(NULL));
    int startX = rand() % (width - 1);
    int startY = rand() % (height - 1);
    cout << "Starting point " << startX << " " << startY << endl;
    
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
                    // maze[_cell.y][_cell.x].Leftl.rotate(90);
                    
                    
                    
                    maze[next.y][next.x].Right = Open;
                    maze[next.y][next.x].Rightl.setFillColor(sf::Color::White);
                    // maze[next.y][next.x].Rightl.rotate(90);
                    
                }
                else
                {
                    // maze[_cell.y][_cell.x].Leftl.rotate(90);
                    maze[_cell.y][_cell.x].Right = Open;
                    maze[_cell.y][_cell.x].Rightl.setFillColor(sf::Color::White);
                    
                    // maze[next.y][next.x].Leftl.rotate(90);
                    maze[next.y][next.x].Left = Open;
                    maze[next.y][next.x].Leftl.setFillColor(sf::Color::White);
                }
            }
            if (next.y != _cell.y)
            {
                if (next.y > _cell.y)
                {
                    maze[next.y][next.x].Bottom = Open;
                    maze[next.y][next.x].Topl.setFillColor(sf::Color::White);
                    
                    maze[_cell.y][_cell.x].Top = Open;
                    maze[_cell.y][_cell.x].Bottoml.setFillColor(sf::Color::White);
                }
                else
                {
                    maze[next.y][next.x].Top = Open;
                    maze[next.y][next.x].Bottoml.setFillColor(sf::Color::White);
                    
                    maze[_cell.y][_cell.x].Bottom = Open;
                    maze[_cell.y][_cell.x].Topl.setFillColor(sf::Color::White);
                }
            }
            maze[next.y][next.x].is_visited = true;
            path.push(next);
        }
        else
            path.pop();
    }
    
    
    maze[height - 1][0].Left = Open;
    maze[height - 1][0].Leftl.setFillColor(sf::Color::White);
    
    maze[height-1][width-1].Right = Open;
    maze[0][width-1].Rightl.setFillColor(sf::Color::White);
    
    
    //finding way
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            maze[y][x].is_visited = false;
        }
    }
    startX = 0;
    startY = height - 1;
    maze[startY][startX].is_visited = true;
    
    vector<Path> road;
    road.push_back(Path(startX,startY));
    
    vector<Cell> way;
    way.push_back(maze[startY][startX]);
    while(!(road.back().x == width - 1 && road.back().y == 0))
    {
        Cell _way = way.back();
        vector<Cell> nextStep;
        
        if(_way.y < height - 1 && maze[_way.y+1][_way.x].Bottom == Open && _way.Top == Open)
            nextStep.push_back(maze[_way.y+1][_way.x]);
        
        if(_way.y > 0 &&  maze[_way.y-1][_way.x].Top == Open && _way.Bottom == Open)
            nextStep.push_back(maze[_way.y-1][_way.x]);
        
        
        if(_way.x < width - 1 &&  _way.Right == Open && maze[_way.y][_way.x+1].Left == Open)
            nextStep.push_back(maze[_way.y][_way.x+1]);
        
        
        if(_way.x > 0 &&  _way.Left == Open && maze[_way.y][_way.x-1].Right == Open)
            nextStep.push_back(maze[_way.y][_way.x-1]);
        
        if (!nextStep.empty())
        {
            Cell next = nextStep[rand() % nextStep.size()];
            Path roadline = Path(next.x,next.y);
            if (next.y != _way.y && ((next.Bottom == Open && _way.Top == Open) || (next.Top == Open && _way.Bottom == Open)))
            {
                roadline = Path(next.x,next.y,Path::VERTICAL);
            }
            maze[next.y][next.x].is_visited = true;
            way.push_back(next);
            road.push_back(roadline);
        }
        else
        { way.pop_back();
            road.pop_back();}
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
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
        for (int i = 0; i < road.size(); i++) {
            window.draw(road[i].line);
        }
        
        
        
        
        
        window.display();
    }
    
    return EXIT_SUCCESS;
}

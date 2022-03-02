//
//  source.cpp
//  GrowingTree
//
//  Created by Максим Пригода on 02.03.2022.
//  Copyright © 2022 Максим Пригода. All rights reserved.
//

#include "source.hpp"
Cell::Cell()
{
    x = 0;
    y = 0;
    is_end = 0;
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
Path::Path()
{
    x = y = 0;
    line.setFillColor(sf::Color::Red);
    line.setSize(sf::Vector2f(SQUARE_SIZE,SQUARE_SIZE));
    line.setPosition(x*SIZE+MOVE, y*SIZE+MOVE);
}
Path::Path(int x, int y)
{
    this->x = x;
    this->y = y;
    line.setFillColor(sf::Color::Red);
    line.setPosition(x*SIZE+SIZE/2-SQUARE_SIZE/2+MOVE, y*SIZE-SIZE/2+MOVE);
    line.setSize(sf::Vector2f(SQUARE_SIZE,SQUARE_SIZE));
}
bool Path::operator!= (const Cell &p) const
{
    if( x==p.x && y == p.y )
       return 0;
    return 1;
}
void initialize_maze(Cell *maze)
{
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            (maze+y*width+x)->x = x;
            (maze+y*width+x)->y = y;
            (maze+y*width+x)->Bottoml.setFillColor(sf::Color::Black);
            (maze+y*width+x)->Bottoml.setPosition((maze+y*width+x)->x*SIZE + MOVE, (maze+y*width+x)->y*SIZE+MOVE);
            (maze+y*width+x)->Topl.setPosition((maze+y*width+x)->x*SIZE+MOVE, (maze+y*width+x)->y*SIZE-SIZE+MOVE);
            (maze+y*width+x)->Topl.setFillColor(sf::Color::Black);
            (maze+y*width+x)->Leftl.setPosition((maze+y*width+x)->x*SIZE+MOVE, (maze+y*width+x)->y*SIZE+MOVE);
            (maze+y*width+x)->Leftl.setFillColor(sf::Color::Black);
            (maze+y*width+x)->Leftl.rotate(-90);
            (maze+y*width+x)->Rightl.setPosition((maze+y*width+x)->x*SIZE+SIZE+MOVE, (maze+y*width+x)->y*SIZE-SIZE+MOVE);
            (maze+y*width+x)->Rightl.setFillColor(sf::Color::Black);
            (maze+y*width+x)->Rightl.rotate(90);
            (maze+y*width+x)->Bottom = (maze+y*width+x)->Top = (maze+y*width+x)->Left = (maze+y*width+x)->Right = Close;
        }
}
void create_maze(Cell *maze,stack<Cell> &path)
{
    srand(time(NULL));
    int startX = rand() % (width - 1);
    int startY = rand() % (height - 1);
    cout << "Starting point " << startX << " " << startY << endl;
//    maze[startY][startX].
    (maze+startY*width+startX)->is_visited = true;
    path.push(*(maze+startY*width+startX));
    while (!path.empty())
    {
        Cell _cell = path.top();
        vector<Cell> nextStep;
        if (_cell.y > 0 && (maze+(_cell.y - 1)*width+_cell.x)->is_visited == false)
            //(maze+(_cell.y - 1)*width+_cell.x)
            nextStep.push_back(*(maze+(_cell.y - 1)*width+_cell.x));
        //(maze+(_cell.y + 1)*width+_cell.x)->
        if (_cell.y < height - 1 && (maze+(_cell.y + 1)*width+_cell.x)->is_visited == false)
            nextStep.push_back(*(maze+(_cell.y + 1)*width+_cell.x));
        //(maze+_cell.y*width+_cell.x - 1)->
        if (_cell.x > 0 && (maze+_cell.y*width+_cell.x - 1)->is_visited == false)
            nextStep.push_back(*(maze+_cell.y*width+_cell.x - 1));
        //(maze+_cell.y*wdith+_cell.x+1)->
        if (_cell.x < width - 1 && (maze+_cell.y*width+_cell.x+1)->is_visited == false)
            nextStep.push_back(*(maze+_cell.y*width+_cell.x+1));
        if (!nextStep.empty())
        {
            Cell next = nextStep[rand() % nextStep.size()];
            if (next.x != _cell.x)
            {
                if (_cell.x > next.x)
                {
                    
                    //(maze+_cell.y*width+_cell.x)->
                    (maze+_cell.y*width+_cell.x)->Left = Open;
                    (maze+_cell.y*width+_cell.x)->Leftl.setFillColor(sf::Color::White);
                    (maze+next.y*width+next.x)->Right = Open;
                    (maze+next.y*width+next.x)->Rightl.setFillColor(sf::Color::White);
                }
                else
                {
                    (maze+_cell.y*width+_cell.x)->Right = Open;
                    (maze+_cell.y*width+_cell.x)->Rightl.setFillColor(sf::Color::White);
                    (maze+next.y*width+next.x)->Left = Open;
                    (maze+next.y*width+next.x)->Leftl.setFillColor(sf::Color::White);
                }
            }
            if (next.y != _cell.y)
            {
                if (next.y > _cell.y)
                {
                    (maze+next.y*width+next.x)->Top = Open;
                    (maze+next.y*width+next.x)->Topl.setFillColor(sf::Color::White);
                    (maze+_cell.y*width+_cell.x)->Bottom = Open;
                    (maze+_cell.y*width+_cell.x)->Bottoml.setFillColor(sf::Color::White);
                }
                else
                {
                    (maze+next.y*width+next.x)->Bottom = Open;
                    (maze+next.y*width+next.x)->Bottoml.setFillColor(sf::Color::White);
                    (maze+_cell.y*width+_cell.x)->Top = Open;
                    (maze+_cell.y*width+_cell.x)->Topl.setFillColor(sf::Color::White);
                }
            }
            (maze+next.y*width+next.x)->is_visited = true;
            path.push(next);
        }
        else
            path.pop();
    }
    
}
void find_way(sf::Time &elapsed,sf::Clock &clock, Cell *maze,vector<Path> &path_to_end)
{
    //(maze+(height-1)*width+0)->
    //maze[height - 1][0].
    (maze+(height-1)*width+0)->Leftl.setFillColor(sf::Color::White);
    //maze[0][width-1].
    (maze+width-1)->Rightl.setFillColor(sf::Color::White);
//    maze[0][width-1].
    (maze+width-1)->is_end = 1;
    if(elapsed.asSeconds() > 0.1)
    {
        clock.restart();
        //
//        maze[path_to_end.back().y][path_to_end.back().x].
        if((maze+path_to_end.back().y*width+path_to_end.back().x)->is_end == 0)
        {
            //(maze+path_to_end.back().y*width+path_to_end.back().x)
            Cell _path = *(maze+path_to_end.back().y*width+path_to_end.back().x);
            vector<Cell> next_step;
            //(maze+_path.y*width+_path.x)->
            //_path.x > 0 && maze[_path.y][_path.x ].
            if(_path.x > 0 && (maze+_path.y*width+_path.x)->Left == Open && (maze+_path.y*width+_path.x-1)->is_visited == false )
                next_step.push_back(*(maze+_path.y*width+_path.x-1));
            if(_path.x < width - 1 && (maze+_path.y*width+_path.x)->Right == Open && (maze+_path.y*width+_path.x+1)->is_visited == false)
                next_step.push_back(*(maze+_path.y*width+_path.x+1));
            
            
            
            if(_path.y > 0 && (maze+(_path.y-1)*width+_path.x)->Bottom == Open && (maze+(_path.y-1)*width+_path.x)->is_visited == false)
                next_step.push_back(*(maze+(_path.y-1)*width+_path.x));
            
            if(_path.y < height - 1 && (maze+(_path.y+1)*width+_path.x)->Top == Open && (maze+(_path.y+1)*width+_path.x)->is_visited == false)
                next_step.push_back(*(maze+(_path.y+1)*width+_path.x));
            
            
            if(!next_step.empty())
            {
                Cell next = next_step[rand() % next_step.size()];
                (maze+(_path.y)*width+_path.x)->is_visited = true;
//                if(next.y != _path.y)
//                    is_vertical = 1;
                path_to_end.push_back(Path(next.x,next.y));
//                if(is_vertical)
//                    is_vertical = 0;
            }
            else{
                (maze+path_to_end.back().y*width+path_to_end.back().x)->is_visited = true;
                //(maze+path_to_end.back().y*width+path_to_end.back().x)->
                path_to_end.pop_back();
            }
        }
    }
}
void reset_maze(Cell *maze,vector<Path> &path_to_end)
{
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x ++)
            (maze+y*width+x)->is_visited = false;
    int startX = 0;
    int startY = height-1;
    (maze+startY*width+startX)->is_visited = true;
    path_to_end.push_back(Path(startX,startY));
}
void draw_maze(Cell *maze,sf::RenderWindow &window,vector<Path> &path_to_end)
{
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            window.draw((maze+y*width+x)->Topl);
            window.draw((maze+y*width+x)->Rightl);
            window.draw((maze+y*width+x)->Bottoml);
            window.draw((maze+y*width+x)->Leftl);
        }
    }
    for (int i = 0; i < path_to_end.size(); i++) {
        window.draw(path_to_end[i].line);
        
    }
    
}

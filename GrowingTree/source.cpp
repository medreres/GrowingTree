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
void initialize(Cell *maze)
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


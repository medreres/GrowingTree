//
//  source.hpp
//  GrowingTree
//
//  Created by Максим Пригода on 02.03.2022.
//  Copyright © 2022 Максим Пригода. All rights reserved.
//

#ifndef source_hpp
#define source_hpp

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <stack>
#include <vector>
#include <iostream>
const int HEIGHT = 600;
const int WIDTH = 700;
const int height = 10;
const int width = 10;
const int SIZE = 50;
const int MOVE = 100 ;
const int SQUARE_SIZE = 10;
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
    bool is_visited = false;
    bool is_end = 0;
    Cell();
    CellState Left = Close;
    CellState Right = Close;
    CellState Top = Close;
    CellState Bottom = Close;
    sf::RectangleShape Topl;
    sf::RectangleShape Bottoml;
    sf::RectangleShape Rightl;
    sf::RectangleShape Leftl;
};
class Path
{
public:
    int x;
    int y;
    sf::RectangleShape line;
    Path();
    Path(int, int);
    bool operator!= (const Cell &p) const;
};
void initialize(Cell *);



#endif /* source_hpp */

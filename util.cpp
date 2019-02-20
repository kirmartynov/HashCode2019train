#pragma once

#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <time.h>
#include <utility>
#include <vector>

using namespace std;

//util classes
struct Input {
	int r, c, l, h;
	vector<vector<int> > grid;
    bool transposed;
};

struct Rect{
    int x1, y1, x2, y2;

    Rect() {}
    Rect(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {
    }
};

void readInput(Input& input, istream& in) {
	//TODO read input
    in >> input.r >> input.c >> input.l >> input.h;
    
    input.grid.resize(input.r);
    
    for (int i = 0; i < input.r; i++)
    {
        string row;
        in >> row;
        input.grid[i].resize(input.c);
        for (int j = 0; j < input.c; j++)
            if (row[j] == 'T')
                input.grid[i][j] = 1;
            else
                input.grid[i][j] = 0;
    }
    input.transposed = false;
}


void transposeGrid(Input &input)    {
    vector<vector<int> > grid;
    
    // transpose
    grid.resize(input.c);
    for (int i = 0; i < input.c; i++)
    {
        grid[i].resize(input.r);
        for (int j = 0; j < input.r; j++)
            grid[i][j] = input.grid[j][i];
    } 
    // update the grid and dimensions
    input.grid = grid;
    input.r = input.grid.size();
    input.c = input.grid[0].size();
    input.transposed = !input.transposed;
}


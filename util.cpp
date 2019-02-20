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
}

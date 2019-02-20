#pragma once
#include "util.cpp"
#include <vector>

using namespace std;

bool checkSlice(vector<vector<int>> &pizza, int l, int h, Rect &r) {
    if ((r.x1<0)||(r.y1<0)||(r.x2>=pizza.length)||(r.y2>=pizza[0].length)||(r.x1>r.x2)||(r.y1>r.r.y2)) return false;
    int s = (r.x2-r.x1)*(r.y2-r.y1);
    if (s>h) return false;
    int c = 0;
    for (int i=r.x1; i<=r.x2; i++){
        for (int j=r.y1; j<=r.y2; j++){
            if (pizza[i][j]==-1) return false;
            if (pizza[i][j]==1) c++;
        }
    }
    return (c>=l)&&((s-c)>=l);
}

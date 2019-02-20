#pragma once
#include "util.cpp"
#include <vector>

using namespace std;

vector<Rect> solve (Input &input) {
    vector<Rect> answer;

    int ci, cj;
    for (ci = 0; ci < input.r; ++ci) {
        for (cj = 0; cj < input.c; ++cj) {
            if (input.grid[ci][cj] == -1) {
                continue;
            }

            int found = 0;

            int ch = 1;
            while (ch <= input.h && ci + ch - 1 < input.r) {
                for (int cw = 1; cj + cw - 1 < input.c; ++cw) {
                    if (checkSlice(input.grid, input.l, input.h, Rect(ci, cj, ci+ch-1, cj+cw-1))) {
                        answer.push_back(Rect(ci, cj, ci+ch-1, cj+cw-1));

                        for (int i = ci; i <= ci + ch - 1; ++i) {
                            for (int j = cj; j <= cj + cw - 1; ++j) {
                                input.grid[i][j] = -1;
                            }
                        }

                        found = 1;
                        break;
                    }
                }
                if (found) {
                    break;
                }

                ++ch;
            }
        }
    }

    return answer;
}
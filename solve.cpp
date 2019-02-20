#pragma once
#include "util.cpp"
#include "checkpiece.cpp"
#include <vector>
#include <algorithm>

vector<Rect> solve (Input &input) {
    vector<Rect> answer;

    int ci, cj;

    vector<pair<int, int>> order;
    for (ci = 0; ci < input.r; ++ci) {
        for (cj = 0; cj < input.c; ++cj) {
            order.push_back(make_pair(ci, cj));
        }
    }

    srand(time(NULL));

    random_shuffle(order.begin(), order.end());

    for (int _ = 0; _ < order.size(); ++_) {
        ci = order[_].first;
        cj = order[_].second;

            if (input.grid[ci][cj] == -1) {
                continue;
            }

            int found = 0;

            int ch = 1;
            while (ch <= input.h && ci + ch - 1 < input.r) {
                for (int cw = 1; cj + cw - 1 < input.c; ++cw) {
                    Rect r = Rect(ci, cj, ci+ch-1, cj+cw-1);
                    if (input.grid[ci+ch-1][cj+cw-1] == -1) {
                        break;
                    }
                    if (checkSlice(input.grid, input.l, input.h, r)) {
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

    return answer;
}
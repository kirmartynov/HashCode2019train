#include "util.cpp"
#include "solve.cpp"
#include "checkpiece.cpp"

int main(int argc, char** argv)  {
    
	ios::sync_with_stdio(false);
	srand(time(NULL));
    
    Input input;
    
    readInput(input, cin);

    vector<Rect> ans = solve(input);
    
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i].x1 << ' ' << ans[i].y1 << ' ' << ans[i].x2 << ' ' << ans[i].y2 << endl;

    return 0;
}
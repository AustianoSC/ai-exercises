#include <iostream>
#include <vector>
using namespace std;

string nextMove(int n, int r, int c, vector <string> grid){
    // Find the princess
    unsigned int row, col;
    for (row = 0;  row < grid.size(); row++) {
        col = grid[row].find('p');
        if (col != string::npos) break;
    }

    // If princess above, move up
    if (r > row) return "UP";
    // If princess bellow, move down
    else if (r < row) return "DOWN"; 
    // If princess to right, move right
    else if (c < col) return "RIGHT";
    // Otherwise, move left
    return "LEFT";
}

int main(void) {

    int n, r, c;
    vector <string> grid;

    cin >> n;
    cin >> r;
    cin >> c;

    for(int i=0; i<n; i++) {
        string s; cin >> s;
        grid.push_back(s);
    }

    cout << nextMove(n, r, c, grid) << std::endl;
    return 0;
}
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class PathNode {
public:
    PathNode(unsigned int row, unsigned int col, bool isFood = false)
    : m_row(row), m_col(m_col), m_isFood(isFood) {

    }

    pair<unsigned int, unsigned int> getRowCol() {
        return pair<unsigned int, unsigned int>(m_row, m_col);
    }

    bool isFood() {
        return m_isFood;
    }

private:
    unsigned int m_row, m_col;
    bool m_isFood;
};

struct hash_pair { 
    template <class T1, class T2> 
    size_t operator()(const pair<T1, T2>& p) const
    { 
        auto hash1 = hash<T1>{}(p.first); 
        auto hash2 = hash<T2>{}(p.second); 
        return hash1 ^ hash2; 
    } 
};

typedef unordered_map<pair<unsigned int, unsigned int>, PathNode*, hash_pair> PathGraph;
void createGraph(PathGraph& graphMap) {
    
}

void nextMove( int r, int c, int pacman_r, int pacman_c, int food_r, int food_c, vector <string> grid) {
    //your logic here
}



int main(void) {

    int r,c, pacman_r, pacman_c, food_r, food_c;
    
    cin >> pacman_r >> pacman_c;
    cin >> food_r >> food_c;
    cin >> r >> c;
    vector <string> grid;

    for(int i=0; i<r; i++) {
        string s; cin >> s;
        grid.push_back(s);
    }

    // Create graph of space
    PathGraph graphMap;
    createGraph(graphMap);

    nextMove( r, c, pacman_r, pacman_c, food_r, food_c, grid);

    return 0;
}
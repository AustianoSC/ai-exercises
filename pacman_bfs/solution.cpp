#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

typedef pair<unsigned int, unsigned int> PathCoordinates;

class PathNode {
public:
    PathNode(unsigned int row, unsigned int col, bool isFood = false)
    : m_row(row), m_col(m_col), m_isFood(isFood) {
        m_neighbors.resize(4);
    }

    PathCoordinates getRowCol() {
        return PathCoordinates(m_row, m_col);
    }

    bool isFood() {
        return m_isFood;
    }

    void addNeighbor(PathNode* node) {
        m_neighbors.push_back(node);
    }

    const vector<PathNode*>& getNeighbors() {
        return m_neighbors;
    }

private:
    unsigned int m_row, m_col;
    bool m_isFood;
    vector<PathNode*> m_neighbors;
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

typedef unordered_map<pair<unsigned int, unsigned int>, PathNode*, hash_pair> PathNodeMap;

PathNodeMap* const createGraph(vector<string> grid) {
    // Create Path map
    PathNodeMap* const graphMap = new PathNodeMap();
    
    // Construct all nodes in the path map
    for (size_t row = 0; row < grid.size(); row++) {
        for (size_t col = 0; col < grid[row].size(); col++) {
            switch (grid[row][col])
            {
            case 'P':
            case '-':
                graphMap->emplace(PathCoordinates(row, col), new PathNode(row, col));
                break;
            case '.':
                graphMap->emplace(PathCoordinates(row, col), new PathNode(row, col, true));
            case '%':
            default:
                continue;
            }
        }
    }

    // Add each neighbor of each PathNode in the PathMap
    PathNodeMap::iterator it;
    for (it = graphMap->begin(); it != graphMap->end(); ++it) {
        // Get coordinates of curent node
        PathCoordinates coordinates = it->second->getRowCol();

        // Add above above node
        PathNodeMap::iterator neighbor;
        neighbor = graphMap->find(PathCoordinates(coordinates.first-1, coordinates.second));
        if (neighbor != graphMap->end()) it->second->addNeighbor(neighbor->second);
        
        // Add left node
        neighbor = graphMap->find(PathCoordinates(coordinates.first, coordinates.second-1));
        if (neighbor != graphMap->end()) it->second->addNeighbor(neighbor->second);
        
        // Add right node
        neighbor = graphMap->find(PathCoordinates(coordinates.first+1, coordinates.second));
        if (neighbor != graphMap->end()) it->second->addNeighbor(neighbor->second);
        
        //Add below node
        neighbor = graphMap->find(PathCoordinates(coordinates.first+1, coordinates.second));
        if (neighbor != graphMap->end()) it->second->addNeighbor(neighbor->second);
    }

    return graphMap;
}

void deleteGraph(PathNodeMap* const graphMap) {
    PathNodeMap::iterator it;
    for (it = graphMap->begin(); it != graphMap->end(); ++it) {
        delete it->second;
    }
    delete graphMap;
}

void nextMove( int r, int c, int pacman_r, int pacman_c, int food_r, int food_c, vector<string> grid) {
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
    PathNodeMap* graphMap = createGraph(grid);

    nextMove( r, c, pacman_r, pacman_c, food_r, food_c, grid);

    // Deallocate graph map
    deleteGraph(graphMap);

    return 0;
}
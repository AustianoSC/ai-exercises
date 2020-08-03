#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <set>
#include <cmath>
using namespace std;

typedef pair<unsigned int, unsigned int> PathCoordinates;

class PathNode {
public:
    PathNode(unsigned int row, unsigned int col, bool isFood = false)
    : m_row(row), m_col(col), m_isFood(isFood) {
        m_neighbors.reserve(4);
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

    unsigned int getRow() {
        return m_row;
    }
    
    unsigned int getCol() {
        return m_col;
    }

private:
    unsigned int m_row, m_col;
    bool m_isFood;
    vector<PathNode*> m_neighbors;
};

struct hash_pair { 
    template <class T1, class T2> 
    size_t operator()(const pair<T1, T2>& p) const { 
        auto hash1 = hash<T1>{}(p.first); 
        auto hash2 = hash<T2>{}(p.second); 
        return hash1 ^ hash2; 
    } 
};

class PathNodeInfo {
public:
    PathNodeInfo(PathNode* node, PathNode* const targetNode, PathNode* parent = nullptr)
    : m_node(node), m_parent(parent), m_g(0), m_closed(false) {
        setHeuristic(targetNode);
    }

    // Manhattan Distance Heuristic
    void setHeuristic(PathNode* const targetNode) {
        m_h = abs(m_node->getRow() - targetNode->getRow()) + abs(m_node->getCol() - targetNode->getCol());
    }

    unsigned int getHeurisitc() const {
        return m_h;
    }

    void setActualCost(unsigned int cost) {
        m_g = cost;
    }

    unsigned int getActualCost() const {
        return m_g;
    }

    unsigned int getDecisionValue() const {
        return m_g + m_h;
    }

    void close() {
        m_closed = true;
    }

    bool isClosed() const {
        return m_closed;
    }

private:
    PathNode* m_node, *m_parent;
    unsigned int m_g, m_h;
    bool m_closed;
};

struct PathNodeInfoComparator {
    bool operator()(const PathNodeInfo& lhs, const PathNodeInfo& rhs) {
        return lhs.getDecisionValue() > rhs.getDecisionValue();
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
                break;
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
        neighbor = graphMap->find(PathCoordinates(coordinates.first, coordinates.second+1));
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

stack<PathNode*> findFoodAStar(PathNode* startNode) {
    // If current node is the food, already found
    if (startNode->isFood()) return stack<PathNode*>();

    // Create open set. Closed set is implicitly in PathNodeInfos
    set<PathNodeInfo, PathNodeInfoComparator> openSet;

    stack<PathNode*> path;

    // Return the path
    return path;
}

void printPath(stack<PathNode*>& path) {
    cout << path.size()-1 << '\n';
    while (path.size()) {
        // Get next node in path
        PathNode* node = path.top();
        path.pop();

        // Print out the next node in the path
        cout << node->getRow() << ' ' << node->getCol() << '\n';
    }
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

    // Find the path to the food using BFS
    stack<PathNode*> path = findFoodAStar(graphMap->at(PathCoordinates(pacman_r, pacman_c)));

    // Print out the path to the food for hacker rank output
    printPath(path);

    // Deallocate graph map
    deleteGraph(graphMap);

    return 0;
}
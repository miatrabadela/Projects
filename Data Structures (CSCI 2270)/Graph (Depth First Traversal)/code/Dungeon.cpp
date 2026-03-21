#include "Dungeon.hpp"
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

Dungeon::Dungeon(int size){
    //Given - This functions initializes the matrix in the heap
    n = size;

    dungeon = new cell_type* [n];
    for (int i = 0; i < n; i++)
        dungeon[i] = new cell_type[n];   
    

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            dungeon[i][j] = END;
    }
}

/**
 * @brief This function should add a new vertex to the graph 
 * 
 * @param x x-cordinate of the cell
 * @param y y-cordinate of the cell
 * @param typeOfCell the type of the cell
 */
void Dungeon::addVertex(int x, int y, cell_type typeOfCell){
    vertex* v = new vertex;
    v->x = x;
    v->y = y;
    v->c = typeOfCell;
    v->visited = false;
    v->vertexNum = findVertexNumFromPosition(x, y);
    vertices.push_back(v);
}

/**
 * @brief Finds the vertex number from the position of the open path in the maze
 * 
 * @param x the x-cordinate of the cell
 * @param y the y-codinate of the cell
 * @return int the vertex number of the cell
 */
int Dungeon::findVertexNumFromPosition(int x, int y){
    return x * n + y;
    return -1;
}

/**
 * @brief Determine whether a cell is contaminated 
 */
bool Dungeon::isContaminated(int x, int y){
	if (dungeon[x][y] == radioactive){
        return true;
    }
    for(int dx = -1; dx <= 1; dx++){
        for(int dy = -1; dy<= 1; dy++){
            if(dx == 0 && dy == 0){
                continue;
            }
            int nx = x + dx;
            int ny = y + dy;
            if(nx >= 0 && nx < n && ny >= 0 && ny < n){
                if(dungeon[nx][ny] == radioactive){
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * @brief Given the x,y cordinates of a cell, find the vertex no.s of the cells that are adjacent and possible to visit.
 * 
 * @param x 
 * @param y 
 * @return vector<int> 
 */
vector<int> Dungeon::findOpenAdjacentPaths(int x, int y){
    vector<int> open_adj;
    
    for(int dx = -1; dx <= 1; dx++){
        for(int dy = -1; dy <= 1; dy++){
            if(dx == 0 && dy == 0){
                continue;
            }
            int nx = x + dx;
            int ny = y + dy;

            if(nx < 0 || nx >= n || ny < 0 || ny >= n){
                continue;
            }

            cell_type t = dungeon[nx][ny];

            if(t == wall || t == radioactive){
                continue;
            }

            if(isContaminated(nx,ny)){
                continue;
            }

            int vNum = findVertexNumFromPosition(nx,ny);
            open_adj.push_back(vNum);
        }
    }
    
    return open_adj;
}

/**
 * @brief For each cell, find and store its neighbors, essentially converting the matrix to an adjacency list representation. 
 * 
 */
void Dungeon::convertDungeonToAdjacencyListGraph(){
    for(auto v: vertices){
        v->adj.clear();
    }

    for(auto v : vertices){
        int x = v->x;
        int y = v->y;

        if(v->c == wall || v->c == radioactive || isContaminated(x,y)){
            continue;
        }

        vector<int> neighbors = findOpenAdjacentPaths(x,y);
        for(int vNum : neighbors){
            adjVertex av;
            av.v = vertices[vNum];
            v->adj.push_back(av);
        }
    }
}

static bool dfs(vertex* v){

    if(v->visited){
        return false;
    }
    v->visited = true;

    if(v->c == END){
        return true;
    }

    for(auto &adj : v->adj){
        if(!adj.v->visited){
            if(dfs(adj.v)){
                return true;
            }
        }
    }
    return false;
}
/**
 * This function is supposed to return true if the Dungeon is traversal is possible and false if not.
 */
bool Dungeon::isDungeonTraversable(){
    vertex* startVertex = nullptr;

    for(auto v : vertices){
        v->visited = false;
        if(v->c == start){
            startVertex = v;
        }
    }

    if (startVertex == nullptr){
        return false;
    }

    return dfs(startVertex);

    return false;
}


/**
 * @brief Destroy the Dungeon:: Dungeon object
 * 
 */
Dungeon::~Dungeon(){
    if(dungeon != nullptr){
        for(int i = 0; i < n; i++){
            delete [] dungeon [i];
        }
        delete [] dungeon;
        dungeon = nullptr;
    }

    for (auto v : vertices){
        delete v;
    }
    vertices.clear();
}

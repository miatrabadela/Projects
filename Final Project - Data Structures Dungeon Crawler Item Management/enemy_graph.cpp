#include "enemy_graph.hpp"
#include <iostream>

EnemyGraph::EnemyGraph() {
	return;
}

EnemyGraph::~EnemyGraph() {
    for (auto entry : vertices) {
        delete entry.second;
    }
    vertices.clear();
}

Vertex* EnemyGraph::addVertex(string id) {
    // Check for unique ID
    if (vertices.count(id) > 0) {
        cout << "ID already exists: " << id << endl;
        return nullptr;
    }
    Vertex* v = new Vertex();
    v->id = id;
	v->distance = 0;
	v->solved = false;
    vertices.insert({id, v});
    return v;
}

Vertex* EnemyGraph::searchVertex(string id) {

	Vertex* toReturn = nullptr;
	for (auto entry : vertices) {
		if (entry.first == id)
			return entry.second;
	}

    if (toReturn==nullptr) {
            throw std::invalid_argument("Vertex not found with provided id");
    }
	return toReturn;
}

/**
 * Adds an undirected edge between two vertices with specified IDs.
 */
void EnemyGraph::addEdge(string v1_id, string v2_id, string enemy_id) {
    // Verify that the IDs exist and are unique
    if (v1_id == v2_id) {
        cout << "v1_id and v2_id must be different!" << endl;
        return;
    }
    if (vertices.count(v1_id) == 0) {
        cout << "No Vertex with ID: " << v1_id << endl;

        return;
    }
    if (vertices.count(v2_id) == 0) {
        cout << "No Vertex with ID: " << v2_id << endl;
        return;
    }

    Vertex* v1 = vertices.at(v1_id);
    Vertex* v2 = vertices.at(v2_id);

    // Verify that edge doesn't already exist
    for (const auto &v : v1->adjacent) {
        if (v.v->id == v2_id) {
            cout << "There is already an edge between " << v1_id << " and " << v2_id << endl;
            return;
        }
    }
    for (const auto &v : v2->adjacent) {
        if (v.v->id == v1_id) {
            cout << "There is already an edge between " << v1_id << " and " << v2_id << endl;
            return;
        }
    }

    AdjacentVertex adj_v2;
    adj_v2.v = v2;
    adj_v2.enemy_id = enemy_id;
    v1->adjacent.push_back(adj_v2);

    AdjacentVertex adj_v1;
    adj_v1.v = v1;
    adj_v1.enemy_id = enemy_id;
    v2->adjacent.push_back(adj_v1);
}

/**
 *
 */
void EnemyGraph::buildGraphFromFile(string fname) 
{
    
    ifstream ifile;
    ifile.open(fname.c_str());
    if( !ifile.is_open())
    {
        cout<<"wrong file name or path"<<endl;
        return;
    }
    string line;
    while(getline(ifile,line))
    {
        stringstream s(line);
        string type; // vertex or edge
		string vertex_ID; // data for vertex
		string vertex1, vertex2, charName; // data for edges
        getline(s,type,';'); //cout<<movieName<<endl;
		if (type == "vertex") {
        	getline(s,vertex_ID,';'); 
			addVertex(vertex_ID);
		} else if (type == "edge") {
        	getline(s,vertex1,';');
        	getline(s,vertex2,';'); 
        	getline(s,charName,';'); 
			addEdge(vertex1, vertex2, charName);
		} else {
			cout << "line read error..." << endl;
		}
    }
    
}

/**
 *  Your implmentation should run a Dijkstra's search from the start vertext to the end
 *   - Edges are labeled with character names, 
 *   - Edge weights will be the character's highest damage item
 */


//
int EnemyGraph::findEasiestPath(HashTable ht) {

    //initialize all vertices before dijkstras
    //every room starts w:
    //distance = INT_MAX 
    //solved = false
    //entry.first = ID string (start, room1, etc)
    //entry.second = ptr to vertex obj (room)
    Vertex* start = searchVertex("start");
    Vertex* end = searchVertex("end");

    
    for (auto &entry : vertices){ //every pair in vertices hash map, & bc we need to change entry.second value
        Vertex* room = entry.second;
        
        room->distance = INT_MAX;
        room->solved = false;
    }
    start->distance = 0;

    //dijkstras w/out PQ
    //explore unsolved room w the shortest distance 
    //repeatedly until its solved (currentRoom), once solved the distance is final

    while (true){
        Vertex* currentRoom = nullptr;
        int smallestRoom = INT_MAX;

        //find the next unsolved vertex w the shortest distance
        //look thru entire vertex list (no PQ)

        for (auto &entry : vertices){
            Vertex* poten = entry.second;

            //set up 2 bool statements to check for 
            //the 2 necessary conditions for the 
            //room to be the shortest out of all the 
            //ones checked so far, is it unsolved and
            //is its distance less than the current 
            //shortest room
            bool potenIsUnsolved = (poten->solved == false);
            bool potenIsCloser = (poten->distance < smallestRoom);

            if (potenIsUnsolved && potenIsCloser){
                smallestRoom = poten->distance;
                currentRoom = poten;
            }
        }

        //if no unsolved vertex that is reachable is found,
        //dijkstras is finished

        if(currentRoom == nullptr){
            break;
        }
        //mark currentRoom as solved

        currentRoom->solved = true;

        if(currentRoom == end){
            break;
        }


        //must relax currentRoom's edges
        for(auto &adjacentInfo : currentRoom->adjacent){
            Vertex* adj = adjacentInfo.v;

            if(adj->solved){
                continue;
            }

            int edgeWeight = 0; //edge weight is the strongest items damage

            //search from enemy on this edge by enemy_id
            //in hash table, take its strongest item's
            //damage as the edge weight

            string enemyName = adjacentInfo.enemy_id;
            node* enemyNode = ht.searchCharacter(enemyName);

            if(enemyNode != nullptr){
                if(!enemyNode->pq.isEmpty()){
                    ItemInfo* strongest = enemyNode->pq.peek();
                    if(strongest != nullptr){
                        edgeWeight = strongest->damage;
                    }
                }
            }
            //relaxation part
            //if currentRoom is reachable, update neighbors distance

            if(currentRoom->distance != INT_MAX){
                int newDistance = currentRoom->distance + edgeWeight;
                if(newDistance < adj->distance){
                    adj->distance = newDistance;
                }
            }
        }
    }
    if(end->distance == INT_MAX){
            return -1; //unreachable
    }
    return end->distance;
}

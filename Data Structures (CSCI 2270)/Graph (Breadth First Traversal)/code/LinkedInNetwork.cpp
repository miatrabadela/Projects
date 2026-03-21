#include "LinkedInNetwork.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

void LinkedInNetwork::addProfessional(string name){
    for (auto p : professionals){
        if(p->name == name){
            cout << name << " found." << endl;
            return;
        }
    }
    Professional *newProf = new Professional;
    newProf->name = name;
    newProf->visited = false;
    newProf->connectionOrder = 0;
    professionals.push_back(newProf);

}
void LinkedInNetwork::addConnection(string v1, string v2){
    Professional *p1 = nullptr;
    Professional *p2 = nullptr;

    for (auto p : professionals){
        if(p->name == v1){
            p1 = p;
        }
        if(p->name == v2){
            p2 = p;
        }
    }

    if(p1 == nullptr || p2 == nullptr){
        return;
    }

    neighbor n1;
    n1.v = p2;
    p1->neighbors.push_back(n1);

    neighbor n2;
    n2.v = p1;
    p2->neighbors.push_back(n2);
    
}

void LinkedInNetwork::displayConnections(){
    for (auto p : professionals){
        cout << p->name << " --> ";
        for (auto &n : p->neighbors){
            cout << n.v->name << " ";
        }
        cout << endl;
    }
}

void LinkedInNetwork::breadthFirstTraverse(string sourceProfessional){
    Professional *src = nullptr;
    for(auto p : professionals){
        p->visited = false;
        p->connectionOrder = 0;
        if(p->name == sourceProfessional){
            src = p;
        }
    }

    if(src == nullptr){
        return;
    }

    cout << "Starting Professional (root): " << sourceProfessional << "-> ";

    queue<Professional*> q;
    src->visited = true;
    src->connectionOrder = 0;
    q.push(src);

    while(!q.empty()){
        Professional *current = q.front();
        q.pop();

        for(auto &adj : current->neighbors){
            Professional *v = adj.v;
            if(!v->visited){
                v->visited = true;
                v->connectionOrder = current->connectionOrder + 1;
                cout << v->name << "(" << v->connectionOrder << ") ";
                q.push(v);
            }
        }
    }
}

void bfs_helper(string source, vector<Professional*> &professionals) {
    Professional *src = nullptr;
    for (auto p : professionals){
        p->visited = false;
        p->connectionOrder = 0;
        if(p->name == source){
            src = p;
        }
    }
    queue<Professional*> q;
    src->visited = true;
    src->connectionOrder = 0;
    q.push(src);

    while(!q.empty()){
        Professional *current = q.front();
        q.pop();

        for(auto &adj : current->neighbors){
            Professional *v = adj.v;
            if(!v->visited){
                v->visited = true;
                v->connectionOrder = current->connectionOrder + 1;
                q.push(v);
            }
        }
    }
}

vector<string> LinkedInNetwork::suggestProfessionalsWithinKthOrder(string professionalName, int k){
    vector<string> professionalsWithink;

    if(k <= 0){
        return professionalsWithink;
    }

    bfs_helper(professionalName, professionals);

    for(auto p : professionals){
        if(p->name == professionalName){
            continue;
        }
        if(p->visited && p->connectionOrder > 0 && p->connectionOrder <= k){
            professionalsWithink.push_back(p->name);
        }
    }

    return professionalsWithink;
    
    vector<string> professionalsWithinK;
    return professionalsWithinK;
}
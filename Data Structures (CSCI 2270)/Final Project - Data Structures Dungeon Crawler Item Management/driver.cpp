#include<iostream>
#include <vector>
#include<fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "hash.hpp"
#include "PriorityQueue.hpp"
#include "enemy_graph.hpp"

using namespace std;
using namespace std::chrono;

void displayMenu()//keep it in starter code
{
    cout<<"------------------"<<endl;
    cout<<"1: Build the datastructure (call it only once)"<<endl;
    cout<<"2: Add a new item"<<endl;
    cout<<"3: Peek most powerful item from character"<<endl;
    cout<<"4: Pop most powerful item from character"<<endl;
    cout<<"5: Print all items for character"<<endl;
    cout<<"6: Get number of collisions"<<endl;
    cout<<"7: Print the table"<<endl;
	cout<<"8: Find easiest route through dungeon"<<endl;
    cout<<"9: Exit"<<endl;
    cout<<"------------------"<<endl;

}

int main(int argc, char* argv[])
{
    if (argc <3)
    {
        cout<<"need correct num of arg"<<endl;
    }
    string fname =argv[1];
    int tableSize = stoi(argv[2]);
    
    int ch = 0;
    string chs;
    HashTable ht(tableSize);
    bool built = false;
    while(ch!=9)
    {
        displayMenu();
        cout<<"Give your choice >> ";
        getline(cin, chs);
        ch =stoi(chs);
        switch (ch)
        {
            case 1:{ // bulk build (should only build on first call)
				if(built == false){
                    ht.buildBulk(fname);
                    built = true;
                    cout << "Data structure built from file: " << fname << endl;
                }
                else{
                    cout << "Data structure already built." << endl;
                }
                break;
            }
            //******************************************************************************* 
            case 2:{ // Insert new items from console
				ItemInfo item;
                cout << "Enter character name: ";
                getline(cin, item.characterName);

                cout << "Enter item name: ";
                getline(cin, item.itemName);

                int dmgValue = 0;
                bool validDamage = false;


                while(!validDamage){
                    cout << "Enter item damage (integer): ";
                    string dmgStr;
                    getline(cin, dmgStr);

                    bool allDigits = !dmgStr.empty();
                    for (char c : dmgStr){
                        if(!isdigit(c)){
                            allDigits = false;
                            break;
                        }
                    }

                    if(!allDigits){
                        cout << "invalid input" << endl;
                        continue; //ask again
                    }

                    dmgValue = stoi(dmgStr);

                    if(dmgValue < 0){
                        cout << "invalid input" << endl;
                        continue;
                    }

                    validDamage = true;
                }

                item.damage = dmgValue;
                cout << "Enter comment: ";
                getline(cin, item.comment);

                ht.insertItem(item);
                cout << "Item inserted." << endl;
                break;

            }
            case 3:{ // Peek 
				cout << "Character name: ";
                string charName;
                getline(cin, charName);

                node* cha = ht.searchCharacter(charName);

                if(cha == nullptr){
                    cout << "no record found" << endl;
                }
                else if(cha->pq.isEmpty()){
                    cout << "no record found" << endl;
                }

                else{
                    ItemInfo* top = cha->pq.peek();

                    if(top != nullptr){
                        cout << "Character: " << charName << endl;
                        cout << "Item: " << top->itemName << endl;
                        cout << "Damage: " << top->damage << endl;
                        cout << "Comment: " << top->comment << endl;
                    }
                }
                break;
			} //**************************************************************************** 
            case 4:{ // Pop
				cout << "Character name: ";
                string charName;
                getline(cin, charName);

                node* cha = ht.searchCharacter(charName);

                if (cha == nullptr){
                    cout << "no record found" << endl;
                }
                else if(cha->pq.isEmpty()){
                    cout << "no record found" << endl;
                }
                else{
                    cha->pq.pop();
                    //if this character has no more items, remove the hash table entry
                    if(cha->pq.isEmpty()){
                        ht.deleteEntry(charName);
                        cout << "PQ emptied..." << endl;
                    }
                }
                break;
            }
            case 5:{ // Print all items for character
				cout << "Enter the character's name to see their inventory: ";
                string charName;
                getline(cin,charName);

                node* cha = ht.searchCharacter(charName);

                if(cha == nullptr){
                    cout << "Character not found." << endl;
                }
                else if(cha->pq.isEmpty()){ //character exists but has no items
                    cout << "no record found" << endl;
                }
                else{
                    cout << "Items for " << charName << ":" << endl;
                    cha->pq.print(); //prints all items
                }
                break;
			}
            case 6: { // Display collisions
				cout << "Number of collisions: " << ht.getNumCollision() << endl;
                break;
			}
            case 7: { // Print table
				cout << "Hash table contents:" << endl;
                ht.printTable();
                break;
			}
			case 8:{ // Find easiest path through dungeon
				cout << "Input dungeon(file name): " << endl;
				string dungeonFile;
				getline(cin, dungeonFile);
				EnemyGraph G;
				G.buildGraphFromFile(dungeonFile);
				cout << G.findEasiestPath(ht) << endl;
				break;
			}
			case 9:
				cout << "Goodbye..." << endl;
				break;
       
            default:
                cout<<"Give a valid entry"<<endl;
                break;
        }
    }
}

// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"
#include<sstream>


using namespace std;


node* HashTable::createNode(string charName, node* nextNode)
{
	node* newNode = new node;
	newNode->characterName = charName;
	newNode->next = nextNode;
	return newNode;
}


HashTable::HashTable(int bsize)
{
	tableSize = bsize;
	table = new node*[tableSize]; //array of node pointers with that many buckets 
	for (int i = 0; i < tableSize; i++){
		table[i] = nullptr; //all start empty
	}
	numCollision = 0;
}


void HashTable::printTable()
{
	for(int i = 0; i < tableSize; i++){
		cout << i << " || ";
		node* temp = table[i];
		while (temp != nullptr){
			cout << temp->characterName;
			
			if(temp->next != nullptr){
				cout << " -> ";
			}

			temp = temp->next;
		}
		cout << endl;
	}
}

//************************************************************************** */
//function to calculate hash function
unsigned int HashTable::hashFunction(string charName)
{
	unsigned int hash = 0;

	for (char c : charName){
		hash = (hash * 7 + c) % tableSize;
	}
	return hash;
}



node* HashTable::searchCharacter(string charName)
{
	unsigned int index = hashFunction(charName);//find bucket index the character Name should be, call hashFunction 
	//so only one bucket is searched

	node* temp = table[index]; //start at head of LL in that bucket

	while (temp != nullptr){
		if (temp->characterName == charName){
			return temp; //found it
		}
		temp = temp->next;
	}
	return nullptr;
}


//***************************************************************************
//function to insert
void HashTable::insertItem(ItemInfo newItem)
{
	string charName = newItem.characterName;

	unsigned int index = hashFunction(charName);

	node* temp = table[index];
	while (temp!= nullptr){
		if(temp->characterName == charName){
			temp->pq.insertElement(newItem);
			return;
		}
		temp = temp->next;
	}

	if (table[index] != nullptr){
		numCollision++;
	}

	node* newNode = createNode(charName, table[index]); //create new node for character and put it at front
	//of the list
	newNode->pq.insertElement(newItem);//insert item into new node's priority queue

	table[index] = newNode;//make node head of linked list

}

//****************************************************************************
//reads file info into the table
void HashTable:: buildBulk(string fname)
{
    ifstream infile(fname);
	if (!infile.is_open()){
		cout << "Failed to open file: " << fname << endl;
		return;	
	}

	string line;
	while (getline(infile, line)){
		if(line.empty()){
		}
		else{
			stringstream ss(line);
			ItemInfo item;

			string damageStr;

			getline(ss, item.characterName, ';');
			getline(ss, item.itemName, ';');
			getline(ss, damageStr, ';');
			getline(ss, item.comment);

			item.damage = stoi(damageStr);

			insertItem(item);
		}
	}
	infile.close();
}
//**********************************************************************************
void HashTable::deleteEntry(string charName) {
	unsigned int index = hashFunction(charName);

	node* prev = nullptr;
	node* curr = table[index]; //points to head of LL at this bucket


	//find node that matches desired characterName to delete
	while (curr != nullptr && curr->characterName != charName){ 
		prev = curr;
		curr = curr->next;
	}
	if(curr == nullptr){
		cout << "no record found" << endl;
		return;
	}

	if(prev == nullptr){
		table[index] = curr->next;
	}
	else{
		prev->next = curr->next;
	}

	delete curr;
}

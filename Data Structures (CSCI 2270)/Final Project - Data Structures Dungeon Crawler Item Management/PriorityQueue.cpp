#include "PriorityQueue.hpp"
#include <limits.h>
using namespace std;

void swap(ItemInfo *a, ItemInfo *b) //helper function that organizes the heap by moving the items up and down
{
	ItemInfo temp = *a;
	*a = *b;
	*b = temp;
}

/*
Constructor for our MinHeap implementation
*/
PriorityQ::PriorityQ() //creates an empty priority queue
{
	capacity = 200;
	heapArr = new ItemInfo[capacity]; //takes items from ItemInfo and stores them in empty array for heap with more than enough room
	currentSize = 0; //empty 
}

PriorityQ::PriorityQ(int cap) //the same thing just allows for an argument (size of array) to be taken
{
	capacity = cap;
	heapArr = new ItemInfo[capacity];
	currentSize = 0;

}

/*
Finds the parent of a node, given its index.
*/
int PriorityQ::parent(int index)
{
	return (index - 1) / 2;
}

/*
Returns the left child of a node.
*/
int PriorityQ::leftChild(int index)
{
	return (2*index + 1);
}

/*
Returns the right child of a node.
*/
int PriorityQ::rightChild(int index)
{
	return (2*index + 2);

}

ItemInfo* PriorityQ::peek() //always returns the most powerful item, since the queue is organized on the damage subfield of ItemInfo
{
	if(currentSize == 0){
		cout << "Priority queue is empty." << endl;
		return nullptr;
	}
	return &heapArr[0]; //returns value at index 0 (max value)
}

void PriorityQ::heapify(int i) 
{
	int largest = i;
	int l = leftChild(i);
	int r = rightChild(i);

	if (l < currentSize && heapArr[l].damage > heapArr[largest].damage){
		largest = l;
	}
	if (r < currentSize && heapArr[r].damage > heapArr[largest].damage){
		largest = r;
	}
	if (largest != i){ //reset the current value to the actual largest then redo heapify w new value
		swap (&heapArr[i], &heapArr[largest]);
		heapify(largest);
	}
}

void PriorityQ::insertElement(ItemInfo item)
{
	if (currentSize == capacity){
		cout << "Priority queue is full." << endl;
		return;
	}
	//heaps are complete trees, last open position is always at currentSize
	int i = currentSize;
	heapArr[i] = item;
	currentSize++;

	//is parent smaller? yes? move parent down and child up, 
	while (i > 0 && heapArr[parent(i)].damage < heapArr[i].damage){
		swap(&heapArr[i], &heapArr[parent(i)]);
		i = parent(i); //reassigns indexes after values
	}
}

/*
Prints the elements in the heap
*/
void PriorityQ::print() 
{
	if (currentSize == 0){
		cout << "No items in the priority queue." << endl;
		return;
	}

	for (int i = 0; i < currentSize; i++){ //currentSize 
		cout << heapArr[i].characterName << " | " 
		<< heapArr[i].itemName << " | " << heapArr[i].damage << " | " 
		<< heapArr[i].comment << endl;
	}
}

// Optional function, use if you need to
void PriorityQ::popHelper(int i) {
	heapify(i);
}

// Method to remove minimum element (or root) from min heap
void PriorityQ::pop()
{
	if (currentSize == 0){
		cout << "Priority queue is empty." << endl;
		return;
	}

	heapArr[0] = heapArr[currentSize - 1];
	currentSize--;

	heapify(0);
}

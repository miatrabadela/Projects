
#include "MusicPlaylist.hpp"

MusicPlaylist::MusicPlaylist()
{
    // No changes needed
}

/*
 * Purpose: Has to detect if a loop is present in the linkedlist pointed by head
 * @param none
 * @return integer length of loop if one exists. If loop not present return -1
 */
int MusicPlaylist::findLoopInPlaylist(){
    Song *slow = head;
    Song *fast = head;
    Song *same = slow;
    Song *counter = same;
    int length = 0;
    while(fast && fast->next){
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow){
            int length = 0;
            same = slow->next;
            while (counter != slow){
                counter = counter->next;
                length++;
            }
            return length;
        }
    }
    return -1;
}

/*
 * Purpose: Has to remove all the Song nodes from [start, end] inclusive.
 * Has to print appropriate messages on cout like below if the linkedlist is empty
 * or if the values of start/ end are improper
 * follow the same order for couts in the writeup - check empty list first, then check wrong start/end values
 * @param integers start and end (1 based indexing not 0 based)
 * @return none
 */
void MusicPlaylist::removeSongs(int start, int end){
    if(this->head == nullptr){
        cout << "Playlist is Empty" << endl;
        return;
    }
    int length = 0;
    Song *p = this->head;
    while (p!=nullptr){
        length++;
        p = p->next;
    }
    if(start < 1 || end > length || start > end) {
        cout << "Invalid start or end values" << endl;
        return;
    }
    if(start == 1){
        for (int i = 0; i < end; i++){
            Song *nextNode = this->head->next;
            delete this->head;
            this->head = nextNode;
        }
        return;
    }
    Song *prev = head;
    for(int i = 1; i < start - 1; i++){
        prev = prev->next;
    }
    Song *curr = prev->next;
    int nodesToDelete = end - start + 1;
    for(int i = 0; i < nodesToDelete && curr != nullptr; i++){
        Song *nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
    prev->next = curr;
}



/*
 * Purpose: Interweave the webpages alternatively into a new linkedlist 
 * starting with the first webpage in the list one
 * Assign the head of the new interweaved list to the head of this BrowserHistory
 * DO NOT create new nodes and copy the data, just use the same nodes from one and two and change pointers
 * If one of them runs out of length append the remaining of the other one at end
 * @param two linkedlist heads one and two
 * @return none
 */
void MusicPlaylist::mergeTwoPlaylists(Song *headOne, Song * headTwo){
    if (headOne == nullptr && headTwo == nullptr){
       this->head = nullptr;
        return;
    }
    if (headOne != nullptr && headTwo == nullptr) {
        this->head = headOne;
    }
    if(headTwo != nullptr && headOne == nullptr){
        this->head = headTwo;
    }
    this->head = headOne;
    Song *p1 = headOne->next;
    Song *p2 = headTwo;
    Song *tail = headOne;

    while(p1 != nullptr || p2 != nullptr){
        if(p2 != nullptr){
            tail->next = p2;
            tail = p2;
            p2 = p2->next;
        }
        if(p1 != nullptr){
            tail->next = p1;
            tail = p1;
            p1 = p1->next;
        }
    }
}
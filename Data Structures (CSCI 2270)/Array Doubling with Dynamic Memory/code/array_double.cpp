#include "array_double.hpp"
#include <sstream>

/**
 * Reads the input file line by line, takes in the
 * query params along with reference of the passengers array
 */
void parseFile(ifstream& input, string queryParams[], AirlinePassenger *&passengers, int &arrCapacity, int &recordIdx, int &doublingCounter) {
    string line;

//reassigning query parms to variables in pareFile

    string queryLocation = queryParams[0];
    string queryAirline = queryParams[1];
    int startAge = stoi(queryParams[2]);
    int endAge = stoi(queryParams[3]);

    while (getline(input, line)){
        stringstream ss(line); 

        string name, airline, location, ageStr;
        getline(ss, name, ',');
        getline(ss, airline, ',');
        getline(ss, location, ',');
        getline(ss, ageStr, ',');

        int age = stoi(ageStr);

        AirlinePassenger p{name, airline, location, age};

       // cout << "Passenger: " << name << " " << airline << " " << location << " " << age << endl;

        if(isPassengerQueried(p, queryLocation, queryAirline, startAge, endAge) == true){

            addPassenger(passengers, p, arrCapacity, recordIdx, doublingCounter);
        }

    }
}

/**
 * Checks if the current passenger has their age in 
 * the queried age range, and their location and 
 * the airline matching with the queried ones.
 */
bool isPassengerQueried(AirlinePassenger passenger, string queryLocation, string queryAirline, int startAge, int endAge) { 
    if(passenger.location != queryLocation){
        return false;
    }
    if(passenger.airline != queryAirline){
        return false;
    }
    if(!(startAge <= passenger.age && passenger.age <= endAge)){
        return false;
    }
    return true;
}

/**
 * Takes in a reference to an array of structs (passengers) 
 * and the current arrayCapacity. It doubles the size 
 * of the array by making a new array of size the current
 * size and copying the elements of the old one. 
 */
void resizeArr(AirlinePassenger *&passengers, int *arraySize) {
   int oldCap = *arraySize;
   int newCap = oldCap * 2;

    //initialize new array
    AirlinePassenger *newArr = new AirlinePassenger[newCap];

   for(int i = 0; i < oldCap; i++){
        newArr[i] = passengers[i];
   }

delete[] passengers;

passengers = newArr;
*arraySize = newCap;
}

/**
 * Append the new record to the passengers array. Here we double the 
 * array capacity whenever it is full. Assuming that the passenger to
 * be added is already checked if it satisfies the query params.
 */
void addPassenger(AirlinePassenger *&passengers, AirlinePassenger airlinePassenger, int &arrCapacity, int &recordIdx, int &doublingCounter) {
   if(recordIdx >= arrCapacity){
        resizeArr(passengers, &arrCapacity);
        ++doublingCounter; 
   }
   passengers[recordIdx++] = airlinePassenger;
}

/**
 * Sorting the array of structs in descending order of age.
 * Tie breaker: Alphabetical order of names.
 */
void sortPassengers(AirlinePassenger *passengers, int length) {
    
    if (length <= 1) return; 

    bool swapped = true;

    while (swapped){
        swapped = false;

        for(int i = 0; i < length - 1; i++){
            bool needSwap = false;
            //sort by age (larger age comes first)
            if(passengers[i].age < passengers[i + 1].age){
                needSwap = true;
            }
            //if ages are equal, "break ties" ascending by name
            else if(passengers[i].age == passengers[i + 1].age && passengers[i].name > passengers[i + 1].name) {
                needSwap = true;
            }

            if(needSwap){
                AirlinePassenger temp = passengers[i]; //saves first passenger
                passengers[i] = passengers[i+1]; //moves 2nd passenger into 1st slot
                passengers[i+1] = temp; //sets 1st passenger into 2nd slot
                swapped = true; //says swap has been made
            }
        }
    }
}

/**
 * Call the sortPassenger function and print the name and the age of the passenger.
 */
void printQueriedPassengers(AirlinePassenger *passengers, int numOfRecords) {
    sortPassengers(passengers, numOfRecords);
    cout << "Queried Passengers\n---------------------------------------" << endl;
    for (int i = 0; i < numOfRecords; i++){
        cout << passengers[i].name << " " << passengers[i].age << endl;
    }
}

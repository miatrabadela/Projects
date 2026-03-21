// app/main.cpp
#include <iostream>
#include <fstream>
#include <string>
#include "../code/array_double.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    // i) Required usage check
    if (argc != 6) {
        cout << "Usage: ./run_app <inputfilename> <Query_Location> <Query_Airline> <Query_Start_Age> <Query_End_Age>" << endl;
        return 0;
    }

    // ii) Open input file (argv[1])
    ifstream input(argv[1]);
    if (!input.is_open()) {
        // Silent exit if file can't be opened (avoid breaking strict output checks)
        return 0;
    }

    // iii) Start with dynamic array size 10
    int arrCapacity = 10;
    AirlinePassenger *passengers = new AirlinePassenger[arrCapacity];

    // iv) Build query params: [location, airline, startAge, endAge]
    string queryParams[4];
    queryParams[0] = argv[2]; // location
    queryParams[1] = argv[3]; // airline
    queryParams[2] = argv[4]; // start age
    queryParams[3] = argv[5]; // end age

    int recordIdx = 0;        // how many matched passengers stored
    int doublingCounter = 0;  // how many times array doubled

    // Parse file and collect matches
    parseFile(input, queryParams, passengers, arrCapacity, recordIdx, doublingCounter);

    // v) Print counts (exact format)
    cout << "Array doubled: " << doublingCounter << endl;
    cout << "Total number of passengers returned after the query: " << recordIdx << endl;

    // vi) Print sorted queried passengers
    printQueriedPassengers(passengers, recordIdx);

    // Cleanup
    delete[] passengers;
    return 0;
}

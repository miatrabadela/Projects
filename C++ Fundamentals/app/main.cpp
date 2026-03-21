#include <iostream>
#include <fstream>
#include "../code/fundamentals.hpp"
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: ./run_app stock_1.csv output.csv" << endl;
        return 1;
    } 
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    stockInfo stocks[6];
    int count = 0;
    string line;
    
    while(count < 6 && getline(fin, line)){
        if (line.empty())
            continue;
        stringstream ss(line);

        string company;
        getline(ss, company, ',');

        double prices[5];
        for(int i = 0; i < 5; i++){
            string token;
            getline(ss, token, ',');
            prices[i] = stod(token);
        }
        insertStockInfo(stocks, company, prices, count);
        count++;
    }

    for(int i = 0; i < count; i++){
        displaySortedStocks(stocks[i], fout);
    }

    fin.close();
    fout.close();
    return 0;
}
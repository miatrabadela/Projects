#include "fundamentals.hpp"

void insertStockInfo(stockInfo stocks[], string company_name, double stock_prices_arr[], int index) {

    stockInfo s;
    s.company_name = company_name;


    double sum = 0.0;
    for(int i = 0; i < 5; i++) {
        s.stock_prices_arr[i] = stock_prices_arr[i];
        sum += stock_prices_arr[i];
    }

    s.average = sum / 5.0;

    stocks[index] = s;
}

void displaySortedStocks(stockInfo stock, ofstream& file){

    for(int i = 0; i < 5; i++){
        int minIndex = i;
        for(int j = i; j < 5; j++){
            if(stock.stock_prices_arr[j] < stock.stock_prices_arr[minIndex]){
                minIndex = j;
            }
        } 
        if(minIndex != i){
            double tempPrice = stock.stock_prices_arr[i];
            stock.stock_prices_arr[i] = stock.stock_prices_arr[minIndex];
            stock.stock_prices_arr[minIndex] = tempPrice;
        }
    }
    //stdout
    cout << stock.company_name << ',' << stock.average;
    for(int i = 0; i < 5; i++) cout<< ',' << stock.stock_prices_arr[i];
    cout << '\n';
    
    //file
    file << stock.company_name << ',' << stock.average;
    for (int i = 0; i< 5; i++) file << ',' << stock.stock_prices_arr[i];
    file << '\n';
}
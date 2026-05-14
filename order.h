#ifndef ORDER_H
#define ORDER_H

#include <string>
using namespace std;

struct Order {
    int id;
    int price;
    int quantity;
    bool isBuy;
    int timestamp;
    string symbol;
};

#endif
#ifndef ORDER_H
#define ORDER_H

struct Order {
    int id;
    int price;
    int quantity;
    bool isBuy;
    int timestamp;
};

#endif
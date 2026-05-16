#ifndef TRADE_H
#define TRADE_H

struct Trade {
    int buyId;
    int sellId;
    int price;
    int quantity;
    string timestamp;
};

#endif
#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include "engine.h"

class OrderBook {

public:

    priority_queue<
        Order,
        vector<Order>,
        BuyCompare
    > buyOrders;

    priority_queue<
        Order,
        vector<Order>,
        SellCompare
    > sellOrders;
};

#endif
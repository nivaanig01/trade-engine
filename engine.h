#ifndef ENGINE_H
#define ENGINE_H

#include <bits/stdc++.h>
#include "order.h"
#include "trade.h"

using namespace std;

struct BuyCompare {
    bool operator()(Order a, Order b);
};

struct SellCompare {
    bool operator()(Order a, Order b);
};

bool isValidOrder(Order order);

void matchOrders(
    priority_queue<Order, vector<Order>, BuyCompare>& buyOrders,
    priority_queue<Order, vector<Order>, SellCompare>& sellOrders,
    vector<Trade>& trades
);

#endif
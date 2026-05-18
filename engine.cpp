#include "engine.h"
#include <ctime>
extern map<string, vector<int>> priceHistory;

// Comparator for BUY (max heap)
bool BuyCompare::operator()(Order a, Order b) {

    if (a.price == b.price) {
        return a.timestamp > b.timestamp;
    }

    return a.price < b.price;
}

// Comparator for SELL (min heap)
bool SellCompare::operator()(Order a, Order b) {

    if (a.price == b.price) {
        return a.timestamp > b.timestamp;
    }

    return a.price > b.price;
}

bool isValidOrder(Order order) {

    if (order.price <= 0) {
        return false;
    }

    if (order.quantity <= 0) {
        return false;
    }

    return true;
}

void matchOrders(
    priority_queue<Order, vector<Order>, BuyCompare>& buyOrders,
    priority_queue<Order, vector<Order>, SellCompare>& sellOrders,
    vector<Trade>& trades
)
 {
    while (!buyOrders.empty() && !sellOrders.empty()) {

        Order buy = buyOrders.top();
        Order sell = sellOrders.top();

        if (buy.price < sell.price) {
            break; // no match possible
        }

        // Remove top orders
        buyOrders.pop();
        sellOrders.pop();

        int tradeQty = min(buy.quantity, sell.quantity);
        time_t now = time(0);

    string currentTime = ctime(&now);
    currentTime.pop_back();

Trade trade = {
    buy.id,
    sell.id,
    sell.price,
    tradeQty,
    currentTime,
    buy.symbol
};

priceHistory[buy.symbol]
    .push_back(sell.price);

trades.push_back(trade);

cout << "\nTrade executed between BUY ID "
     << buy.id
     << " and SELL ID "
     << sell.id
     << " for "
     << tradeQty
     << " units at price "
     << sell.price
     << endl;

        // Update remaining quantity
        buy.quantity -= tradeQty;
        sell.quantity -= tradeQty;

        // Put back remaining orders
        if (buy.quantity > 0) {
            buyOrders.push(buy);
        }

        if (sell.quantity > 0) {
            sellOrders.push(sell);
        }
    }
}
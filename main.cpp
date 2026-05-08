#include <bits/stdc++.h>
using namespace std;

struct Order {
    int id;
    int price;
    int quantity;
    bool isBuy;
    int timestamp;
};

// Comparator for BUY (max heap)
struct BuyCompare {
    bool operator()(Order a, Order b) {
        if (a.price == b.price) {
    return a.timestamp > b.timestamp;
}

return a.price < b.price;
    }
};

// Comparator for SELL (min heap)
struct SellCompare {
    bool operator()(Order a, Order b) {
        if (a.price == b.price) {
    return a.timestamp > b.timestamp;
}

return a.price > b.price;
    }
};

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
    priority_queue<Order, vector<Order>, SellCompare>& sellOrders
) {
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

             cout << "Trade executed between BUY ID "
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

void addBuyOrder(
    priority_queue<Order, vector<Order>, BuyCompare>& buyOrders,
    Order order
) {

    if (isValidOrder(order)) {
        buyOrders.push(order);
    }
    else {
        cout << "Invalid Buy Order" << endl;
    }
}

void addSellOrder(
    priority_queue<Order, vector<Order>, SellCompare>& sellOrders,
    Order order
) {

    if (isValidOrder(order)) {
        sellOrders.push(order);
    }
    else {
        cout << "Invalid Sell Order" << endl;
    }
}

int main() {

    priority_queue<Order, vector<Order>, BuyCompare> buyOrders;
    priority_queue<Order, vector<Order>, SellCompare> sellOrders;

    // Add some test orders
   // buyOrders.push({100, 5, true});
   // buyOrders.push({105, 2, true});

   // sellOrders.push({110, 3, false});
   // sellOrders.push({108, 4, false});

    //buyOrders.push({105, 5, true});
    //sellOrders.push({100, 3, false});
    
    Order b1 = {1, 105, 5, true, 1};
Order b2 = {2, 102, 4, true, 2};

Order s1 = {3, 99, 5, false, 3};
Order s2 = {4, 101, 3, false, 4};

Order bad1 = {5, -100, 5, true, 5};
Order bad2 = {6, 100, -3, false, 6};

addBuyOrder(buyOrders, b1);
addBuyOrder(buyOrders, b2);

addSellOrder(sellOrders, s1);
addSellOrder(sellOrders, s2);

addBuyOrder(buyOrders, bad1);
addSellOrder(sellOrders, bad2);

    matchOrders(buyOrders, sellOrders);

    cout << "\nRemaining Buy Orders: " << buyOrders.size() << endl;
    cout << "Remaining Sell Orders: " << sellOrders.size() << endl;


   // cout << "Top Buy: " << buyOrders.top().price << endl;
   // cout << "Top Sell: " << sellOrders.top().price << endl;

   if (buyOrders.empty()) {
    cout << "No remaining buy orders" << endl;
}

if (sellOrders.empty()) {
    cout << "No remaining sell orders" << endl;
}

    return 0;
}
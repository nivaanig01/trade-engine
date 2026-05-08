#include <bits/stdc++.h>
using namespace std;

struct Order {
    int price;
    int quantity;
    bool isBuy; // true = buy, false = sell
};

// Comparator for BUY (max heap)
struct BuyCompare {
    bool operator()(Order a, Order b) {
        return a.price < b.price;
    }
};

// Comparator for SELL (min heap)
struct SellCompare {
    bool operator()(Order a, Order b) {
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

        cout << "Trade executed: " << tradeQty 
             << " units at price " << sell.price << endl;

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
    
    Order b1 = {105, 5, true};
Order b2 = {102, 4, true};

Order s1 = {99, 5, false};
Order s2 = {101, 3, false};

Order bad1 = {-100, 5, true};
Order bad2 = {100, -3, false};

if (isValidOrder(b1)) {
    buyOrders.push(b1);
}
else {
    cout << "Invalid Buy Order" << endl;
}

if (isValidOrder(b2)) {
    buyOrders.push(b2);
}
else {
    cout << "Invalid Buy Order" << endl;
}

if (isValidOrder(s1)) {
    sellOrders.push(s1);
}
else {
    cout << "Invalid Sell Order" << endl;
}

if (isValidOrder(s2)) {
    sellOrders.push(s2);
}
else {
    cout << "Invalid Sell Order" << endl;
}

if (isValidOrder(bad1)) {
    buyOrders.push(bad1);
}
else {
    cout << "Invalid Buy Order" << endl;
}

if (isValidOrder(bad2)) {
    sellOrders.push(bad2);
}
else {
    cout << "Invalid Sell Order" << endl;
}

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
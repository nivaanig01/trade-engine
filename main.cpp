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

    buyOrders.push({105, 5, true});
    sellOrders.push({100, 3, false});

    matchOrders(buyOrders, sellOrders);


   // cout << "Top Buy: " << buyOrders.top().price << endl;
   // cout << "Top Sell: " << sellOrders.top().price << endl;

    return 0;
}
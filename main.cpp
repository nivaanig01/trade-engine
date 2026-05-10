#include <bits/stdc++.h>
#include <fstream>
using namespace std;

struct Order {
    int id;
    int price;
    int quantity;
    bool isBuy;
    int timestamp;
};

struct Trade {
    int buyId;
    int sellId;
    int price;
    int quantity;
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

Trade trade = {
    buy.id,
    sell.id,
    sell.price,
    tradeQty
};

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

void displayBuyOrders(
    priority_queue<Order, vector<Order>, BuyCompare> buyOrders
) {

    cout << "\nBuy Orders:\n";

    while (!buyOrders.empty()) {

        Order order = buyOrders.top();

        cout << "ID: " << order.id
             << " Price: " << order.price
             << " Qty: " << order.quantity
             << endl;

        buyOrders.pop();
    }
}

void displaySellOrders(
    priority_queue<Order, vector<Order>, SellCompare> sellOrders
) {

    cout << "\nSell Orders:\n";

    while (!sellOrders.empty()) {

        Order order = sellOrders.top();

        cout << "ID: " << order.id
             << " Price: " << order.price
             << " Qty: " << order.quantity
             << endl;

        sellOrders.pop();
    }
}

void cancelBuyOrder(
    priority_queue<Order, vector<Order>, BuyCompare>& buyOrders,
    int cancelId
) {

    priority_queue<Order, vector<Order>, BuyCompare> temp;

    while (!buyOrders.empty()) {

        Order order = buyOrders.top();
        buyOrders.pop();

        if (order.id != cancelId) {
            temp.push(order);
        }
    }

    buyOrders = temp;
}

void cancelSellOrder(
    priority_queue<Order, vector<Order>, SellCompare>& sellOrders,
    int cancelId
) {

    priority_queue<Order, vector<Order>, SellCompare> temp;

    while (!sellOrders.empty()) {

        Order order = sellOrders.top();
        sellOrders.pop();

        if (order.id != cancelId) {
            temp.push(order);
        }
    }

    sellOrders = temp;
}

int main() {

    priority_queue<Order, vector<Order>, BuyCompare> buyOrders;
    priority_queue<Order, vector<Order>, SellCompare> sellOrders;

    vector<Trade> trades;

    ofstream outFile("trades.txt");

    int n;
cout << "Enter number of orders: ";
cin >> n;

for (int i = 1; i <= n; i++) {

    char type;
    int price;
    int quantity;

    cout << "\nEnter order type (B/S): ";
    cin >> type;

    cout << "Enter price: ";
    cin >> price;

    cout << "Enter quantity: ";
    cin >> quantity;

    bool isBuy = (type == 'B' || type == 'b');

Order order = {i, price, quantity, isBuy, i};

    if (type == 'B' || type == 'b') {

    addBuyOrder(buyOrders, order);

}
else if (type == 'S' || type == 's') {

    addSellOrder(sellOrders, order);

}
else {

    cout << "Invalid Order Type" << endl;

}
    }

    int cancelId;

cout << "\nEnter order ID to cancel (-1 for none): ";
cin >> cancelId;

if (cancelId != -1) {

    cancelBuyOrder(buyOrders, cancelId);
    cancelSellOrder(sellOrders, cancelId);
}
    
    matchOrders(buyOrders, sellOrders, trades);

    displayBuyOrders(buyOrders);
    displaySellOrders(sellOrders);

   if (buyOrders.empty()) {
    cout << "\nNo remaining buy orders" << endl;
}

if (sellOrders.empty()) {
    cout << "No remaining sell orders" << endl;
}

cout << "\nTrade History:\n";

for (Trade trade : trades) {

    cout << "BUY ID: " << trade.buyId
         << " SELL ID: " << trade.sellId
         << " Price: " << trade.price
         << " Qty: " << trade.quantity
         << endl;

         outFile << "BUY ID: " << trade.buyId
        << " SELL ID: " << trade.sellId
        << " Price: " << trade.price
        << " Qty: " << trade.quantity
        << endl;
}

outFile.close();

    return 0;
}
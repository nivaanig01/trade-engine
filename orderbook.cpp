#include "orderbook.h"
using namespace std;

void OrderBook::displayBuyOrders() {

    auto temp = buyOrders;

    cout << "\nBuy Orders:\n";

    while (!temp.empty()) {

        Order order = temp.top();

        cout << "ID: " << order.id
             << " Price: " << order.price
             << " Qty: " << order.quantity
             << endl;

        temp.pop();
    }
}

void OrderBook::displaySellOrders() {

    auto temp = sellOrders;

    cout << "\nSell Orders:\n";

    while (!temp.empty()) {

        Order order = temp.top();

        cout << "ID: " << order.id
             << " Price: " << order.price
             << " Qty: " << order.quantity
             << endl;

        temp.pop();
    }
}

void OrderBook::displayMarketDepth() {

    auto buyTemp = buyOrders;
    auto sellTemp = sellOrders;

    map<int, int, greater<int>> buyLevels;
    map<int, int> sellLevels;

    while (!buyTemp.empty()) {

        Order order = buyTemp.top();
        buyTemp.pop();

        buyLevels[order.price] += order.quantity;
    }

    while (!sellTemp.empty()) {

        Order order = sellTemp.top();
        sellTemp.pop();

        sellLevels[order.price] += order.quantity;
    }

    cout << "\nMarket Depth:\n";

    cout << "\nBUY LEVELS:\n";

    for (auto level : buyLevels) {

        cout << "Price: "
             << level.first
             << " Total Qty: "
             << level.second
             << endl;
    }

    cout << "\nSELL LEVELS:\n";

    for (auto level : sellLevels) {

        cout << "Price: "
             << level.first
             << " Total Qty: "
             << level.second
             << endl;
    }
}

#include "engine.h"
#include "orderbook.h"
#include <fstream>


using namespace std;

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

void displayMarketDepth(
    priority_queue<Order, vector<Order>, BuyCompare> buyOrders,
    priority_queue<Order, vector<Order>, SellCompare> sellOrders
) {

    map<int, int, greater<int>> buyLevels;
    map<int, int> sellLevels;

    while (!buyOrders.empty()) {

        Order order = buyOrders.top();
        buyOrders.pop();

        buyLevels[order.price] += order.quantity;
    }

    while (!sellOrders.empty()) {

        Order order = sellOrders.top();
        sellOrders.pop();

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

void modifyBuyOrder(
    priority_queue<Order, vector<Order>, BuyCompare>& buyOrders,
    int modifyId,
    int newPrice,
    int newQuantity
) {

    priority_queue<Order, vector<Order>, BuyCompare> temp;

    while (!buyOrders.empty()) {

        Order order = buyOrders.top();
        buyOrders.pop();

        if (order.id == modifyId) {

            order.price = newPrice;
            order.quantity = newQuantity;
        }

        temp.push(order);
    }

    buyOrders = temp;
}

void modifySellOrder(
    priority_queue<Order, vector<Order>, SellCompare>& sellOrders,
    int modifyId,
    int newPrice,
    int newQuantity
) {

    priority_queue<Order, vector<Order>, SellCompare> temp;

    while (!sellOrders.empty()) {

        Order order = sellOrders.top();
        sellOrders.pop();

        if (order.id == modifyId) {

            order.price = newPrice;
            order.quantity = newQuantity;
        }

        temp.push(order);
    }

    sellOrders = temp;
}

int main() {
    
        OrderBook orderBook;

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

    addBuyOrder(orderBook.buyOrders, order);

}
else if (type == 'S' || type == 's') {

    addSellOrder(orderBook.sellOrders, order);

}
else {

    cout << "Invalid Order Type" << endl;

}
    }

    int cancelId;

cout << "\nEnter order ID to cancel (-1 for none): ";
cin >> cancelId;

if (cancelId != -1) {

    cancelBuyOrder(orderBook.buyOrders, cancelId);
    cancelSellOrder(orderBook.sellOrders, cancelId);
}

int modifyId;

cout << "\nEnter order ID to modify (-1 for none): ";
cin >> modifyId;

if (modifyId != -1) {

    int newPrice;
    int newQuantity;

    cout << "Enter new price: ";
    cin >> newPrice;

    cout << "Enter new quantity: ";
    cin >> newQuantity;

    modifyBuyOrder(
        orderBook.buyOrders,
        modifyId,
        newPrice,
        newQuantity
    );

    modifySellOrder(
        orderBook.sellOrders,
        modifyId,
        newPrice,
        newQuantity
    );
}
    
    matchOrders(
    orderBook.buyOrders,
    orderBook.sellOrders,
    trades
);

    displayBuyOrders(orderBook.buyOrders);
    displaySellOrders(orderBook.sellOrders);
    displayMarketDepth(
    orderBook.buyOrders,
    orderBook.sellOrders
);

   if (orderBook.buyOrders.empty()) {
    cout << "\nNo remaining buy orders" << endl;
}

   if (orderBook.sellOrders.empty()) { {
    cout << "No remaining sell orders" << endl;
}

int totalVolume = 0;
int highestPrice = 0;
int totalPriceQuantity = 0;

cout << "\nTrade History:\n";

for (Trade trade : trades) {

    cout << "BUY ID: " << trade.buyId
         << " SELL ID: " << trade.sellId
         << " Price: " << trade.price
         << " Qty: " << trade.quantity
         << endl;

    totalVolume += trade.quantity;

highestPrice = max(
    highestPrice,
    trade.price
);

totalPriceQuantity +=
    trade.price * trade.quantity;     

         outFile << "BUY ID: " << trade.buyId
        << " SELL ID: " << trade.sellId
        << " Price: " << trade.price
        << " Qty: " << trade.quantity
        << endl;
}

double averagePrice = 0;

if (!trades.empty()) {

    averagePrice =
        (double) totalPriceQuantity
        / totalVolume;
}

cout << "\nMarket Analytics:\n";

cout << "Total Volume: "
     << totalVolume
     << endl;

cout << "Highest Trade Price: "
     << highestPrice
     << endl;

cout << "Average Trade Price: "
     << averagePrice
     << endl;

outFile.close();

    return 0;
}
}
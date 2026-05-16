#include "engine.h"
#include "orderbook.h"
#include <algorithm>
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

void displayMarketSummary(
    map<string, OrderBook>& markets
) {

    cout << "\nMarket Summary:\n";

    for (auto& market : markets) {

        string symbol = market.first;

        OrderBook& orderBook =
            market.second;

        int buyCount =
            orderBook.buyOrders.size();

        int sellCount =
            orderBook.sellOrders.size();

        cout << symbol
             << " -> Buy Orders: "
             << buyCount
             << " Sell Orders: "
             << sellCount
             << endl;
    }
}

void saveMarketState(
    map<string, OrderBook>& markets
) {

    ofstream file("market_state.txt");

    for (auto& market : markets) {

        string symbol = market.first;

        OrderBook& orderBook =
            market.second;

        auto buyTemp =
    orderBook.buyOrders;

while (!buyTemp.empty()) {

    Order order = buyTemp.top();
    buyTemp.pop();

    file << order.symbol
         << " "
         << "B"
         << " "
         << order.price
         << " "
         << order.quantity
         << endl;
}

auto sellTemp =
    orderBook.sellOrders;

while (!sellTemp.empty()) {

    Order order = sellTemp.top();
    sellTemp.pop();

    file << order.symbol
         << " "
         << "S"
         << " "
         << order.price
         << " "
         << order.quantity
         << endl;
}
    }

    file.close();
}

void loadMarketState(
    map<string, OrderBook>& markets
) {

    ifstream file("market_state.txt");

    if (!file.is_open()) {
        return;
    }

    string symbol;
    char type;

    int price;
    int quantity;

    int id = 1000;

while (
    file >> symbol
         >> type
         >> price
         >> quantity
) {

        bool isBuy =
    (type == 'B');

Order order = {
    id++,
    price,
    quantity,
    isBuy,
    id,
    symbol
};

OrderBook& orderBook =
    markets[symbol];

if (isBuy) {
    orderBook.buyOrders.push(order);
}
else {
    orderBook.sellOrders.push(order);
}

cout << "Recovered Order: "
     << symbol
     << " "
     << type
     << " "
     << price
     << " "
     << quantity
     << endl;
    }

    file.close();
}

void saveTradesToCSV(
    vector<Trade>& trades
) {

    ofstream file("trades.csv",ios::app);

    for (Trade trade : trades) {

        file << trade.buyId
             << ","
             << trade.sellId
             << ","
             << trade.price
             << ","
             << trade.quantity
             << ","
             << trade.timestamp;
    }

    file.close();
}

int main() {
    
        map<string, OrderBook> markets;
        loadMarketState(markets);
        string currentSymbol;

        vector<Trade> trades;

    ofstream outFile("trades.txt");

    int n;
cout << "Enter number of orders: ";
cin >> n;

for (int i = 1; i <= n; i++) {

    string symbol;
    char type;
    int price;
    int quantity;

    cout << "\nEnter symbol: ";
    cin >> symbol;
    transform(symbol.begin(),symbol.end(),symbol.begin(),::toupper);
    currentSymbol = symbol;

    OrderBook& orderBook = markets[symbol];

    cout << "\nEnter order type (B/S): ";
    cin >> type;

    cout << "Enter price: ";
    cin >> price;

    cout << "Enter quantity: ";
    cin >> quantity;

    bool isBuy = (type == 'B' || type == 'b');

    Order order = {i,price,quantity,isBuy,i,symbol};

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

    OrderBook& orderBook = markets[currentSymbol];
    int cancelId;

cout << "\nEnter order ID to cancel (-1 for none): ";
cin >> cancelId;

if (cancelId != -1) {

    OrderBook& orderBook = markets[currentSymbol];
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

    orderBook.displayBuyOrders();
    orderBook.displaySellOrders();
    orderBook.displayMarketDepth();
    displayMarketSummary(markets);
    saveMarketState(markets);
    saveTradesToCSV(trades);

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
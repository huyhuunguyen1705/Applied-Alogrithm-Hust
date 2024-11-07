#include <bits/stdc++.h>

using namespace std;

// Struct to hold order information
struct Order {
    string customerID;
    string productID;
    int price;
    string shopID;
};

int main() {
    // Data storage
    map<string, int> shopRevenue; // Revenue by ShopID
    map<string, map<string, int>> customerShopSpending; // Spending by CustomerID and ShopID
    map<string, int> revenueAtTimePoint; // Revenue recorded at each time-point
    map<string, int> cumulativeRevenue; // Cumulative revenue by time-point (sorted by time)
    
    int totalOrders = 0;
    int totalRevenue = 0;

    // Input processing
    string line;
    while (getline(cin, line)) {
        if (line == "#") break;
        
        stringstream ss(line);
        Order order;
        string timePoint;
        ss >> order.customerID >> order.productID >> order.price >> order.shopID >> timePoint;
        
        totalOrders++;
        totalRevenue += order.price;
        
        // Update shop revenue
        shopRevenue[order.shopID] += order.price;
        
        // Update customer-shop spending
        customerShopSpending[order.customerID][order.shopID] += order.price;
        
        // Accumulate revenue at each specific time-point (not cumulative yet)
        revenueAtTimePoint[timePoint] += order.price;
    }
    
    // Calculate cumulative revenue
    int runningTotal = 0;
    for (const auto& entry : revenueAtTimePoint) {
        runningTotal += entry.second;
        cumulativeRevenue[entry.first] = runningTotal;
    }
    
    // Query processing
    while (getline(cin, line)) {
        if (line == "#") break;
        
        stringstream ss(line);
        string queryType;
        ss >> queryType;
        
        if (queryType == "?total_number_orders") {
            cout << totalOrders << endl;
        }
        else if (queryType == "?total_revenue") {
            cout << totalRevenue << endl;
        }
        else if (queryType == "?revenue_of_shop") {
            string shopID;
            ss >> shopID;
            cout << shopRevenue[shopID] << endl;
        }
        else if (queryType == "?total_consume_of_customer_shop") {
            string customerID, shopID;
            ss >> customerID >> shopID;
            cout << customerShopSpending[customerID][shopID] << endl;
        }
        else if (queryType == "?total_revenue_in_period") {
            string fromTime, toTime;
            ss >> fromTime >> toTime;
            
            int periodRevenue = 0;
            
            // Find cumulative revenue up to and including `toTime`
            auto toIt = cumulativeRevenue.upper_bound(toTime);
            if (toIt != cumulativeRevenue.begin()) {
                --toIt; // Move to the largest time <= toTime
                periodRevenue = toIt->second;
            }
            
            // Subtract cumulative revenue just before `fromTime`, if applicable
            auto fromIt = cumulativeRevenue.lower_bound(fromTime);
            if (fromIt != cumulativeRevenue.begin()) {
                --fromIt; // Move to the largest time < fromTime
                periodRevenue -= fromIt->second;
            }
            
            cout << periodRevenue << endl;
        }
    }
    
    return 0;
}
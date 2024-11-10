/*
Description
Data about sales in an e-commerce company (the e-commerce company has several shops) consists a sequence of lines, each line (represents an order) has the following information:
            <CustomerID> <ProductID> <Price> <ShopID> <TimePoint>
in which the customer <CustomerID> buys a product <ProductID> with price <Price> at the shop <ShopID> at the time-point <TimePoint>
<CustomerID>: string of length from 3 to 10
<ProductID>: string of length from 3 to 10
<Price>: a positive integer from 1 to 1000
<ShopID>: string of length from 3 to 10
<TimePoint>: string representing time-point with the format HH:MM:SS (for example, 09:45:20 means the time-point 9 hour 45 minutes 20 seconds)


Perform a sequence of queries of following types:
?total_number_orders: return the total number of orders
?total_revenue: return the total revenue the e-commerce company gets
?revenue_of_shop <ShopID>: return the total revenue the shop <ShopID> gets 
?total_consume_of_customer_shop <CustomerID> <ShopID>: return the total revenue the shop <ShopID> sells products to customer <CustomerID> 
?total_revenue_in_period <from_time> <to_time>: return the total revenue the e-commerce gets of the period from <from_time> to <to_time> (inclusive)

Input
The input consists of two blocks of data:
The first block is the operational data, which is a sequence of lines (number of lines can be upto 100000), each line contains the information of a submission with above format 
The first block is terminated with a line containing the character #
The second block is the query block, which is a sequence of lines (number of lines can be upto 100000), each line is a query described above
The second block is terminated with a line containing the character #

Output
Write in each line, the result of the corresponding query 

Example
Input
C001 P001 10 SHOP001 10:30:10
C001 P002 30 SHOP001 12:30:10
C003 P001 40 SHOP002 10:15:20
C001 P001 80 SHOP002 08:40:10
C002 P001 130 SHOP001 10:30:10
C002 P001 160 SHOP003 11:30:20
#
?total_number_orders
?total_revenue
?revenue_of_shop SHOP001
?total_consume_of_customer_shop C001 SHOP001 
?total_revenue_in_period 10:00:00 18:40:45
#


Output 
6
450
170
40
370
*/

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
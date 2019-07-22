#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <sstream>
#include <climits>

using namespace std;
/*
 * You are given the stock prices for a set of days .
 * Each day, you can either buy one unit of stock,
 * sell any number of stock units you have already bought, or do nothing.
 * What is the maximum profit you can obtain by planning your trading strategy optimally?
 *
 * Say you have an array for which the ith element is the price of a given stock on day i.
 *
 * If you were only permitted to complete at most one transaction
 * (i.e., buy one and sell one share of the stock),
 * design an algorithm to find the maximum profit.
 *
 * Note that you cannot sell a stock before you buy one.
 *
 * Example 1:
 * Input: [7,1,5,3,6,4]
 * Output: 5
 * Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
 * Not 7-1 = 6, as selling price needs to be larger than buying price.
 *
 * Example 2:
 * Input: [7,6,4,3,1]
 * Output: 0
 * Explanation: In this case, no transaction is done, i.e. max profit = 0.
 *
 */


class Solution {
public:
    int max_profit_bottom_up(vector<int> share_price) {
        int num_items = share_price.size();
        if (num_items == 0 || num_items ==1) return 0;

        vector<int> MinPriceTillDate(num_items);

        MinPriceTillDate[0] = share_price[0];
        int msf = 0;
        int maxProfitToday;
        int k = 0;
        for (int i = 1; i < num_items ; i++, k++) {
            // find out whats the min till date
            // which is same as min between today and yesterday
            MinPriceTillDate[i] = min (MinPriceTillDate[i-1], share_price[i]);

            // keep track of max profit so far
            maxProfitToday = share_price[k] - MinPriceTillDate[k];
            msf = max(msf, maxProfitToday);
        }

        //  one last iteration for item k = n-1, since k run still n- 2 in the above loop
        maxProfitToday = share_price[k] - MinPriceTillDate[k];
        msf = max(msf, maxProfitToday);

        return msf;
    }
};

class TestFixture {
    int test_count;
public:
    TestFixture() :test_count(0) {}

    bool Test(int expected, int actual) {
        bool ret_val = true;
        string err_str = "";
        test_count++;

        if (expected != actual) {
            err_str = "Expected: " + to_string(expected);
            err_str += ", Actual: " + to_string(actual);
            ret_val = false;
        }

        std::cout << "Test #" << test_count << (ret_val == true? ": passed " : ": failed ") << err_str << std::endl;
        return ret_val;
    }
};

int main() {

    auto *test = new TestFixture();

    test->Test(0, Solution().max_profit_bottom_up(vector<int> {}));
    test->Test(0, Solution().max_profit_bottom_up(vector<int> {1}));
    test->Test(1, Solution().max_profit_bottom_up(vector<int> {1, 2}));
    test->Test(5, Solution().max_profit_bottom_up(vector<int> {7,1,5,3,6,4}));
    test->Test(0, Solution().max_profit_bottom_up(vector<int> {7,6,4,3,1}));

    return 0;
}
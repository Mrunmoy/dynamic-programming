#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <sstream>
#include <climits>

using namespace std;

class Solution {
    int cut_rod_aux(vector<int>& costs, int L, vector<int>& memo ) {
        if (L == 0) return 0;
        if (memo[L] != 0) return memo[L];

        int msf = max(costs[L], memo[L]);
        for (int i = 1;i < L; i++) {
            msf = max(msf, cut_rod_aux(costs, L-i, memo) + max(costs[i], memo[i]));
        }
        memo[L] = msf;

        return memo[L];
    }

public:
    int cut_rod_memoized(vector<int> costs, int L) {
        if (L == 0) return 0;
        int num_items = costs.size();
        for (int i = 0; i <= (L - num_items + 1); i++) {
            costs.push_back(0);
        }

        vector<int> memo(L+1);
        for (int i = 0; i <= L; i++) {
            memo[i] = 0;
        }

        return cut_rod_aux(costs, L, memo);
    }


    int cut_rod_bottom_up(vector<int> costs, int L) {
        if (L == 0) return 0;

        int num_items = costs.size();
        for (int i = 0; i <= (L - num_items + 1); i++) {
            costs.push_back(0);
        }

        vector<int> memo(L+1);
        for (int i = 0; i <= L; i++) {
            memo[i] = 0;
        }

        for (int i = 1; i <= L; i++) {
            int msf = max(costs[i], memo[i]);
            for (int k = 0; k < i; k++) {
                msf = max(msf, max(costs[k], memo[k]) + memo[i - k]);
            }
            memo[i] = msf;
        }

        return memo[L];
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

    test->Test(9, Solution().cut_rod_memoized(vector<int> {0, 2, 4, 7, 8}, 4));
    test->Test(9, Solution().cut_rod_bottom_up(vector<int> {0, 2, 4, 7, 8}, 4));

    return 0;
}

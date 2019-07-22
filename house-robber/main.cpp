#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <sstream>
#include <climits>

using namespace std;
/*
 * You are a professional robber planning to rob houses along a street.
 * Each house has a certain amount of money stashed,
 * the only constraint stopping you from robbing each of them
 * is that adjacent houses have security system connected and
 * it will automatically contact the police if two
 * adjacent houses were broken into on the same night.
 *
 * Given a list of non-negative integers representing the amount of money of
 * each house, determine the maximum amount of money you can rob tonight
 * without alerting the police.
 *
 * Example 1:
 *
 * Input: [1,2,3,1]
 * Output: 4
 *
 * Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
 * Total amount you can rob = 1 + 3 = 4.
 *
 *
 * Example 2:
 *
 * Input: [2,7,9,3,1]
 * Output: 12
 * Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
 * Total amount you can rob = 2 + 9 + 1 = 12.
 *
 * */


class Solution {
    int rob_memoized_aux(vector<int> &nums, int index, vector<int> &memo) {
        if (index < 0) return 0;
        if (memo[index] > 0) return memo[index];

        printf("%s(%d)\n", __PRETTY_FUNCTION__, index);
        int msf = 0;
        for (int i = index; i >= 0; i--) {
            if (nums[i] == 0) continue;
            int choose = nums[i] + rob_memoized_aux(nums, i-2, memo);
            int skip   = rob_memoized_aux(nums, i-1, memo);
            int curr_max = max(choose, skip);
            msf = max(msf, curr_max);
        }

        memo[index] = msf;
        return memo[index];
    }

public:

    int rob_memoized(vector<int> nums) {
        int num_houses = nums.size();
        if (num_houses == 0) return 0;
        if (num_houses == 1) return nums[0];
        if (num_houses == 2) return max(nums[0], nums[1]);

        vector<int> memo(num_houses+1);
        for (int i = 0; i <= num_houses; i++)
            memo[i] = 0;

        memo[0] = nums[0];
        memo[1] = max(nums[1], nums[0]);
        return rob_memoized_aux(nums, num_houses-1, memo);
    }

    int rob_bottom_up(vector<int> nums) {
        int num_houses = nums.size();
        if (num_houses == 0) return 0;
        if (num_houses == 1) return nums[0];

        vector<int> memo(num_houses+1);

        memo[0] = nums[0];
        memo[1] = max(nums[1], nums[0]);
        for (int i = 2; i < num_houses; i++) {
            int skip = memo[i-1];
            int choose = nums[i] + memo[i-2];
            memo[i] = max(skip, choose);
        }
        return memo[num_houses-1];
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

    test->Test(4, Solution().rob_memoized(vector<int> {1,2,3,1}));
    test->Test(12, Solution().rob_memoized(vector<int> {2,7,9,3,1}));
    test->Test(0, Solution().rob_memoized(vector<int> {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}));
    test->Test(4, Solution().rob_bottom_up(vector<int> {1,2,3,1}));
    test->Test(12, Solution().rob_bottom_up(vector<int> {2,7,9,3,1}));
    test->Test(0, Solution().rob_bottom_up(vector<int> {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}));

    return 0;
}
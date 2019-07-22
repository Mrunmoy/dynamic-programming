#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <sstream>
#include <climits>

using namespace std;

class Solution {
    int num_ways_memoized_aux(int steps, vector<int>& memo ) {
        if (memo[steps] != 0) return memo[steps];

        printf("%s(%d)\n", __PRETTY_FUNCTION__, steps);
        memo[steps] = num_ways_memoized_aux(steps-1, memo) + num_ways_memoized_aux(steps-2, memo);

        return memo[steps];
    }

public:
    int num_ways_memoized(int steps) {
        if (steps == 0 || steps == 1) return 1;

        vector<int> memo(steps+1);
        for (int i = 0; i <= steps; i++) {
            memo[i] = 0;
        }
        memo[0] = memo[1] = 1;

        return num_ways_memoized_aux(steps, memo);
    }

    int num_ways_recursive(int steps) {
        if (steps == 0 || steps == 1) return 1;

        printf("%s(%d)\n", __PRETTY_FUNCTION__, steps);
        return num_ways_recursive(steps - 1) + num_ways_recursive(steps - 2);
    }

    int num_ways_bottom_up(int steps) {
        if (steps == 0 || steps == 1) return 1;

        int two_step = 1;
        int one_step = 1;
        int total_step = 0;
        for (int i = 1; i < steps; i++) {
            total_step = one_step + two_step;
            one_step = two_step;
            two_step = total_step;
            printf("%s(%d)\n", __PRETTY_FUNCTION__, i);
        }

        return total_step;
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

    test->Test(13, Solution().num_ways_recursive(6));
    test->Test(13, Solution().num_ways_memoized(6));
    test->Test(13, Solution().num_ways_bottom_up(6));

    return 0;
}
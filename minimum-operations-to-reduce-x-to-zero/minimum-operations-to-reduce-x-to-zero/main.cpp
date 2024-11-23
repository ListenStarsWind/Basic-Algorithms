#include<vector>

using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int sum = 0;
        for (auto e : nums)
            sum += e;

        int left = 0, right = 0, len = 0, target = sum - x, sz = nums.size();
        sum = 0;

        if (target == 0)
            return sz;

        while (right < sz) {
            sum += nums[right++];
            while (left < right && sum > target)
                sum -= nums[left++];
            if (sum == target)
                len = max(len, right - left);
        }

        if (len == 0)
            return -1;
        else
            return sz - len;
    }
};

int main()
{
    vector<int> v{ 8828,9581,49,9818,9974,9869,9991,10000,10000,10000,9999,9993,9904,8819,1231,6309 };
    Solution().minOperations(v, 134365);

    return 0;
}
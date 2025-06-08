#include<vector>

using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int left = 0;
        int right = 0;

        int sum = 0;
        int len = INT_MAX;

        int sz = nums.size();

        while (right < sz || left < right)
        {
            if (sum < target)
            {
                if (right >= sz)
                    break;
                sum += nums[right++];
            }
            else
            {
                while (sum >= target)
                {
                    if (len > right - left)
                        len = right - left;
                    sum -= nums[left++];
                }
                if (right >= sz)
                    break;
                sum += nums[right++];
            }
        }
        return len == INT_MAX ? 0 : len;
    }
};

int main()
{
    vector<int> v{ 5,1,3,5,10,7,4,9,2,8 };
    Solution().minSubArrayLen(15, v);
}
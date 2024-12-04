#include<vector>

using namespace std;


class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[right])
                left = mid + 1;
            else
                right = mid;
        }
        return nums[left];
    }
};

int main()
{
    vector<int> v = { 4,5,6,7,0,1,2 };
    Solution().findMin(v);
    return 0;
}
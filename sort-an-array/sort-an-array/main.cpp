#include<ctime>
#include<vector>

using namespace std;

class Solution {
    void _sort(vector<int>& nums, long long left, long long right)
    {
        if (left >= right)
            return;

        int key = nums[left + rand() % (right - left + 1)];
        long long start = left - 1, curr = left, end = right + 1;
        while (curr < end)
        {
            if (nums[curr] < key)
            {
                swap(nums[curr++], nums[++start]);
            }
            else if (nums[curr] > key)
            {
                swap(nums[curr], nums[--end]);
            }
            else
                curr++;
        }

        _sort(nums, left, start);
        _sort(nums, end, right);
    }

public:
    vector<int> sortArray(const vector<int>& nums) {
        vector<int> ret = nums;
        srand(time(nullptr));
        _sort(ret, 0, ret.size() - 1);
        return ret;
    }
};

int main()
{
    vector<int> arr = { 5,1,1,2,0,0 };
    Solution().sortArray(arr);
    return 0;
}
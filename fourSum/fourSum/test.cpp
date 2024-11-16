#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;

class Solution {
public:
    void twoSum(const vector<int>& nums, int begin, int end, long target,
        const vector<int> pass) {
        int start = begin;
        int edge = end - 1;
        vector<int> tmp = pass;
        while (start < edge) {
            int cur = nums[start];
            long key = target - cur;
            /*if (key < cur)
                break;*/
            int sum = nums[start] + nums[edge];
            if (sum > target) {
                edge--;
                while (start < edge && nums[edge + 1] == nums[edge])
                    edge--;
            }
            else if (sum < target) {
                start++;
                while (start < edge && nums[start - 1] == nums[start])
                    start++;
            }
            else {
                tmp.push_back(nums[start]);
                tmp.push_back(nums[edge]);
                _containers.push_back(tmp);
                tmp = pass;
                edge--;
                while (start < edge && nums[edge + 1] == nums[edge])
                    edge--;
                start++;
                while (start < edge && nums[start - 1] == nums[start])
                    start++;
            }
        }
    }

    void threeSum(const vector<int>& nums, int begin, int end, long target,
        const vector<int> pass) {
        int start = begin;
        int edge = end - 2;
        vector<int> tmp = pass;
        while (start < edge) {
            int cur = nums[start];
            long key = target - cur;
            /* if (key < cur)
                 break;*/
            tmp.push_back(cur);
            twoSum(nums, start + 1, nums.size(), key, tmp);
            tmp = pass;
            start++;
            while (start < edge && cur == nums[start])
                start++;
        }
    }

    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());

        int start = 0;
        int edge = nums.size() - 3;
        vector<int> pass;
        while (start < edge) {
            int cur = nums[start];
            long key = target - cur;
            /*if (key < cur)
                break;*/
            pass.push_back(cur);
            threeSum(nums, start + 1, nums.size(), key, pass);
            pass.clear();
            start++;
            while (start < edge && cur == nums[start])
                start++;
        }
        return _containers;
    }

private:
    vector<vector<int>> _containers;
};

int main()
{
    vector<int> v{ 1,-2,-5,-4,-3,3,3,5 };
    auto ret = Solution().fourSum(v, -11);
    for (auto e1 : ret)
    {
        for (auto e2 : e1)
        {
            cout << e2 << " ";
        }
        cout << endl;
    }
    return 0;
}
# [four-sum](https://leetcode.cn/problems/4sum)

![image-20241116133835853](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411161338984.png)

和三数之和一样，先固定一个数，然后去找三数和即可。下面是思路代码，分开写可以更好的理清思路。

```cpp
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
```

不过上面分开写效率有些低，所以真正提交的应该是这个

```cpp
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, long target) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ret;
        int sz = nums.size();
        int four_start = 0;
        int four_edge = sz - 3;

        while (four_start < four_edge) {
            int four_curr = nums[four_start];
            long four_pass = target - four_curr;
            /*if (four_pass < four_curr)
                break;*/

            int three_start = four_start + 1;
            int three_edge = sz - 2;
            while (three_start < three_edge) {
                int three_curr = nums[three_start];
                long three_pass = four_pass - three_curr;
               /* if (three_pass < three_curr)
                    break;*/

                int left = three_start + 1;
                int right = sz - 1;
                while (left < right) {
                    int curr = nums[left];
                    long key = three_pass - curr;
                    /*if (key < curr)
                        break;*/

                    int cmp = nums[right];
                    if (key < cmp) {
                        right--;
                        while (left < right && nums[right + 1] == nums[right])
                            right--;
                    }
                    else if (key > cmp) {
                        left++;
                        while (left < right && nums[left - 1] == nums[left])
                            left++;
                    }
                    else {
                        ret.push_back({ four_curr, three_curr, curr, cmp });
                        right--;
                        while (left < right && nums[right + 1] == nums[right])
                            right--;
                        left++;
                        while (left < right && nums[left - 1] == nums[left])
                            left++;
                    }
                }

                three_start++;
                while (three_start < three_edge &&
                    three_curr == nums[three_start])
                    three_start++;
            }

            four_start++;
            while (four_start < four_edge && four_curr == nums[four_start])
                four_start++;
        }
        return ret;
    }
};
```

有两个点需要注意，一是不要再`if break`了，就是代码中被注释的部分，三数和可以加这个的原因是它的`target`固定为0，不是负数，但四数和这里是可以为负数的，比如若`target`为`-11`，第一个找到的数是`-5`，得到的数是`-6`，`-6 < -5`成立，就会提前跳出循环。

二是某些数可能存在溢出风险，所以对这些数要用`long`类型。
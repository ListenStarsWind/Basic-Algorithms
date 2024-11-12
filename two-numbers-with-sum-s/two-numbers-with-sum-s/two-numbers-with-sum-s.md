# [two-numbers-with-sum-s](https://leetcode.cn/problems/he-wei-sde-liang-ge-shu-zi-lcof)

![image-20241112214553966](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411122145036.png)

我们仍旧采用经典的双指针法：

以[2, 7, 11, 15, 19, 21] s = 30为例。

首先我们直接把数组的两个极值加一下，也就是2 和 21，我们发现它的结果是23，既然2 + 21都小于目标了，那么2 + 19， 2 + 15， 2 + 11， 2 + 7更不可能，所以我们以后都完全不考虑2了。

那既然2太小了，那就换一个更大的呗，也就是7， 7 + 21结果为28，那还是一样，7以后也会被我们完全抛弃，以后也不考虑7了，接下来试一试11，结果是32，大于30，既然11 + 21 都大于30了，那15 + 21， 19 + 21更大于结果，这意味着21以后我们也不会完全考虑了，那就试试更小的，19，恰好11 + 19就是结果，那就返回。

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& price, int target) {
        auto min_iterator = price.begin();
        auto max_iterator = price.end();
        --max_iterator;
        while (*min_iterator + *max_iterator != target) {
            if (*min_iterator + *max_iterator < target)
                ++min_iterator;
            else
                --max_iterator;
        }
        vector<int> v;
        v.push_back(*min_iterator);
        v.push_back(*max_iterator);
        return v;
    }
};
```

虽然题目没有明说，但考虑到可能会有找不到的情况，更推荐使用下面的方法

![image-20241112222116867](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411122221927.png)

注意一下这个错误，它的意思是某些分支没有返回值，所以为了照顾编译器，要在最外层来个乱码兜底。

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& price, int target) {
        int left = 0;
        int right = price.size() - 1;
        while (left < right) {
            int sum = price[left] + price[right];
            if (sum < target)
                left++;
            else if (sum > target)
                right--;
            else
                return {price[left], price[right]};
        }
        return {-1, -1};
    }
};
```

对于vector\<int>，也可以这样传参，用{}把元素括起来，就像匿名对象一样传参。

# end
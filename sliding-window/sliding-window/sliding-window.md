# [sliding-window](https://leetcode.cn/problems/minimum-size-subarray-sum)

![image-20241117193606696](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411171936840.png)

## overview

还是老样子，让我们先来读一读题，理解题意。

有一个数组，这个数组含有的都是正整数，现在想让我们从这个数组中找到一个子数组，子数组中所有的元素之和需要大于或等于`target`，然后在所有满足需求的子数组中找到一个长度最小的就行了。

比如在示例一中，我们可以找到许多子数组`[2, 3, 1, 2]  [3, 1, 2]  [4, 3]`，它们都符合要求，但我们要的是长度最小的，所以我们最后返回的是`2`；

在示例二中，只要有`4`这一个元素就能满足要求，所以输出`1`

在示例三中，一个符合要求的子数组都找不到，那就返回`0`

## solution

我们首先看看暴力破解。

暴力破解就是穷举出所有子数组组合，选取满足要求长度最小的。它有三层循环，两层找到子数组的首尾，一层遍历子数组求和，所以复杂度是$O(N^3)$。

接下来把暴力破解再优化一下，我们可以定义一个`sum`用来求和，比如对于示例一，最开始`sum`就是0，`left`和`right`指向下标0，也就是2，但0不满足要求，那就把数组的区间扩大一下，让`right`向后移动一位，同时`sum`再加上之前`right`指向的数字，或者这样表示`sum += nums[right++]`，这样，就不用再走求和循环了，复杂度变成了$O(N^2)$。

如果`sum`不满足要求怎么办，很简单，由于数组中的元素都是正整数，而题目的要求是大于或等于某个正整数，这意味着，只要我们扩大子数组的区间，就会越来越接近我们的需求，`sum`是0，不满足需求，没关系，`sum += nums[right++]`，`sum`就变`2`了，离目标`7`又近了一些，然后再`sum += nums[right++]`，`sum`变成`5`了，又近了一些，再`sum += nums[right++]`，`sum`变成了`6`，马上就到目标了，`sum += nums[right++]`，`sum`变成`8`了，达到目标了，这时我们就不用尝试扩大数组区间了，因为题目想要的，是在满足需求的情况下，付出尽可能少的努力，实现最大的效率。所以我们就要把视线移到子数组内了，我们要缩小一下子数组的区间大小，让`left`往右移，再正式右移`left`之前，我们要先记录现在数组的长度，因为`left`右移可能会玩砸，导致子数组不再满足需求，用代码表示就是`sum -= nums[left++]`，结果这次就玩砸了，`sum`变成`6`了，没关系，之前我们已经记录过那个有效的数组长度了，如果后面找不到其它满足需求的子数组，那可以直接返回这个长度。想让`sum`靠近目标的方法也很简单，再次`sum += nums[right++]`，这样`sum`就变成了`10`，好的，又满足需求了，本来我想更新长度的，但发现现在数组长度和上次数组长度一样，那就不更新了，接下来我再次`sum -= nums[left++]`结果没作死成功，差一点就玩砸了，现在`sum`刚好是`7`，然后我又看了一下现在数组长度，发现现在长度是`3`，那就可以更新旧有数据，之后我再次缩小区间`sum -= nums[left++]`，`sum`为`6`了，那就扩大区间`sum += nums[right++]`，`sum`变成了`9`，满足要求，不过现在数组长度和`3`一样，那就不更新，那就再次缩小区间`sum -= nums[left++]`，`sum`为`7`，而且长度比`3`小，所以长度被更新为`2`，于是我再次缩小区间`sum -= nums[left++]`，`sum`变成了`4`，本来我想再次扩大区间，但`right`已经没有数据了，那就只能退出了。

有两个点要注意，一是边界控制，不能让两个指针越界，而是`len`初始值，只有子数组长度比旧数组长度小，`len`才会更新，因此我们把`len`的初始值为`int`最大值，当循环结束后`len`仍为最大值，则意味着没有找到一个满足需求的子数组，返回0即可。

这种方法的复杂度是$O(N)$级，最坏情况就是两指针都刚好越界，此时复杂度为$O(2N)$。

## code

```cpp
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
```

下面的代码更优雅：

```cpp
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int left = 0;
        int right = 0;

        int sz = nums.size();
        int len = INT_MAX;
        int sum = 0;

        while (right < sz) {
            sum += nums[right++];
            while (sum >= target) {
                len = min(len, right - left);
                sum -= nums[left++];
            }
        }
        return len == INT_MAX ? 0 : len;
    }
};
```

# end
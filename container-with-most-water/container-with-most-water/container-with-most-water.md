# [container-with-most-water](https://leetcode.cn/problems/container-with-most-water)

![image-20241112142206061](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411121422225.png)

题目看起来复杂，但不用担心，让我们直接看图。图中有9条垂线，我们要选两条组成一个“木桶”。木桶的宽度是两条垂线之间的距离（即下标差），高度是两条中较矮的那一条。

比如，图中选取两条红色的垂线，它们的宽度是7（8 - 1），高度是7，所以容积是49。

如果选1号和6号线（两条最长的线），则水的容积是5*8=40。

### 暴力解法与其局限性

一个简单的想法是穷举所有组合，找到最大值。然而，这样的效率是 $O(N^2)$，不可行。

### 使用双指针解法

水的容积由两因素决定：宽和高。

举例：[6, 2, 5, 4]

- 初始选择6和4，宽是3，高是4，容积为12。
- 之后，尝试用4和2或5组合。可以确定的是，无论4和2或者5中的哪个数字配对，容器的宽都会减小。如果用4和2，高和宽都下降，所以必然容积下降；如果用4和5，高还是4，但宽减小了，所以容积仍下降。也就是说，这些配对就不需要计算结果了。

因此，较短的那根垂线无法提高容积，需要移除。

### 双指针的流程

以 [1, 8, 6, 2, 5, 4, 8, 3, 7] 为例：

- 初始选1和7，容积为8。
- 移除较短的1，研究剩余区间。
- 选8和7，容积49，更新最大值。
- 移除7，选8和3，容积18，未超越49。
- 继续此过程，直到左右指针相遇。

这种算法相当于两个指针把数组合起来遍历了一遍，所以复杂度是$O(N)$。

```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int ret = 0;
        while (left < right) {
            int tmp = (right - left) * min(height[right], height[left]);
            ret = max(ret, tmp);
            if (height[left] < height[right])
                left++;
            else
                right--;
        }
        return ret;
    }
};
```

# end
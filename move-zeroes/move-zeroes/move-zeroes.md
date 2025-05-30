# [move-zeroes](https://leetcode.cn/problems/move-zeroes)

![image-20241109151101188](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411091511309.png)

这道题的思路是使用双指针法，将数组划分为多个层次。首先，指针`current`对数组进行了第一层划分，`current`左边的部分是已经访问过的元素，而`current`右边的部分则是未被访问过的元素。接下来，在`current`左边的部分，我们再进行进一步划分，指针`destination`的左边是非零元素，右边是零元素，`destination`充当非零部分的分界线。

初始化时，`destination`指向“无效位置”（用-1表示），而`current`从数组的起始位置开始。每次迭代时，检查`current`指向的元素：

- 如果元素不为0，就与`destination`的下一个位置（即非零部分的第一个0元素）进行交换，交换后`destination`指针向后扩展，指向新的非零元素的最后一个位置；
- 无论是否交换，`current`指针都向后移动，继续处理下一个元素。

当`current`遍历完所有元素后，数组中的非零元素被移动到数组的前面，零元素被移到数组的末尾。整个过程通过`current`和`destination`这两个指针，逐步对数组进行层次划分，确保非零元素排在前面，零元素排在后面。

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int destination = -1;
        int current = 0;
        while (current < nums.size()) {
            if (nums[current] != 0)
                swap(nums[++destination], nums[current]);

            ++current;
        }
    }
};
```

## 备注

第二次没有直接写出

相似题组[移除元素](https://leetcode.cn/problems/remove-element/)

![image-20250514171644733](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250514171644806.png)

```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int visited = 0;
        int NonValBack = -1;
        while(visited < nums.size())
        {
            if(nums[visited] != val)
                swap(nums[++NonValBack], nums[visited]);
            
            ++visited;
        }

        return NonValBack + 1;
    }
};
```

[对数组执行操作](https://leetcode.cn/problems/apply-operations-to-an-array/)

![image-20250514171743425](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250514171743485.png)

```cpp
lass Solution {
public:
    vector<int> applyOperations(vector<int>& nums) {
        int n = nums.size() - 1;
        for(int i = 0; i < n; ++i)
        {
            if(nums[i] == nums[i + 1])
            {
                nums[i] *= 2;
                nums[i+1] = 0;
            }
        }

        int visiting = 0;
        int NonZeroBack = -1;
        while(visiting <= n)
        {
            if(nums[visiting] != 0)
                swap(nums[++NonZeroBack], nums[visiting]);
            
            ++visiting;
        }

        return nums;
    }
};
```



# end
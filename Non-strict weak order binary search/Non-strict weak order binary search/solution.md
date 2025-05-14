# [Non-strict weak order binary search](https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array)

![image-20241130115337072](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411301153172.png)

## overview

所谓非严格弱序有三层含义，一是该序列中的元素之间具有可比性，或者说，它们中的两个个体具有大于，等于，小于关系；二是该序列中的元素关系可以不严格，即不明确，它们之间可以有大于等于，小于等于这种关系，三是这些序列按照这种相对关系进行了有序排列。

题目为我们提供一个非严格弱序的数组，并给出一个目标值，你需要依据该目标值找到其在数组中对应的起始和结尾位置，如果找不到，则二者皆返回-1。

## solution

首先仍然是暴力查找：按照一定的顺序，比如从前往后，对数组中的各个元素进行扫描比对。

第二个解法是狭义二分，狭义二分在此种场景下并不适用，因为我们要找的是目标值的首尾位置，而狭义二分只能查找到一个目标值，所以如果强行使用会和暴力查找的效率相同。

为此我们要对狭义二分进行修改，通过优化它的查找策略，将二分查找中最精髓的性质——二段性，重新构建，从而同样实现序列区域淘汰的行为。

----------------

首先我们先来尝试查找起始位置。假设现在的数组为`[1, 2, 3, 3, 3, 4, 5]`，`target == 3`，我们现在要找到第一个三，也就是下标为2的三，让我们看看，这个三是否可以把数组划分成两个部分，显然是可以的，起始三的下标为2，那么`[0, 1]`区间位置的元素就都是小于三的，而`[2, 6]`区间位置的元素都是大于等于三的。那我们就可以依据这种相对关系来作为二分查找的策略。

为方便起见，我们先假设这个数组是一定能找到目标值的。首先我们仍旧是先找到中间点，然后让该中间点与目标值进行比较，如果中间点小于目标值，就意味着现在的中间点是位于小于目标值的区间的，言外之意就是我们要找的起始目标值是在中间点右边的，所以就要修正`left`使之变为`mind + 1`，从而缩小后续的搜索范围。如果中间点大于等于目标值，则说明此时中间点是位于大于等于目标值区间中的，言外之意就是我们要查找的起始位置可能在中间点左边，也可能就是中间点（因为起始目标值就是大于等于区间的左端点），反正`[mid + 1, right]`区间中的数组元素肯定不是起始目标值，所以就可以淘汰，也就是让`right = mid`，

接着我们需要考虑一些细节。首先我们要考虑循环条件，现在有两个备选选项`left <= right`以及`left < right`，这里一定要选择第二种，也就是`left < right`，也就是说当`left == right`的时候循环就要停下，我们分三种情况分析。

第一种情况，这个数组中确实是有目标值的。从上面的`left`和`right`迭代机制可以看到，`right`一直安分守己，不越雷池一步，因为`right`即使迭代，它也是等于`mid`的，而在此时，`mid`是大于等于目标值的，所以说`right`一直都在大于等于区间里，并逐步接近起始目标值，但对于`left`不是这样，因为它的迭代机制是`left = mid + 1`，我们并不知道新的`left`到底位于哪个区间，或者说，`left`扮演者开拓者的角色，一直在探索未知，实际上`left`也必须不断探索，因为起始目标值在大于等于区间里，而`left`基本位于小于目标区间，所以只有不断探索未知才能突破自己原有的圈子，来到大于等于区间里，从而找到起始目标值，对`left`来说，目标就是未知的一部分。当`left`和`right`相等后，就已经找到了起始目标值，所以不需要继续循环了。我们再退一步说，如果允许`left`和`right`相等后继续循环，就会出现死循环，很明显，当`left == right`时，下一次`mid`还是`left`或者说`right`，因为该此场景下能找到目标值，所以此时`mid`就等于目标值，于是就会触发`right`的迭代机制，也就是`right = mid`，由于`right`墨守成规，只在自己的舒适圈内，所以尽管之后它看上去很努力，一直在迭代，但每次都迭代到上一次位置上，所以就会永无止境，不停循环，直至消亡。

第二种情况，这个数组里全是大于目标的元素，在此种场景下，`right`就会一路向前狂飙，直到遇到`left`，此时也不需要再进行循环了，因为此时就相当于`right`一个指针遍历了整个数组，既然整个数组的所有元素都被检查过了，那就没必要检查了，找不到就是找不到。所以此时就要停止循环。

第三种情况，这个数组里全是小于目标的元素，在此种场景下，`left`就会一路向后狂飙，直到遇到`right`，此时也不需要再进行循环了，`left`已经遍历了整个数组了，没找到就是没找到。

然后让我们考虑以何种方式寻找中间点。还是有两个备选选项，`mid = left + (right - left) / 2`，以及`mid = left + (right - left + 1) / 2`，它们两个的区别无非就是向下取整还是向上取整，计算机在进行除法运算时，默认向下取整，加了一个一就变成向上取整了，就比如三和四，三和四向下取整结果是三，向上取整结果是四。那么，现在考虑这种情况，现在`left` 和`right`已经是连续的两个数了，如果我们选取向上取整，得到的`mid`就是`right`，当遇到第一种情况，也就是中间值小于目标值，`left = mid + 1`时，由于`left`的开拓性，`left`就会变成`right + 1`，从而跳出循环，但由于跳出循环后`right`和`left`的值不一样，所以后续处理就很麻烦，如果遇到第二种情况，也就是中间值大于等于目标值，`right = mid`时，就会进入死循环，因为`right`具有闭守性，所以就会一直等于`mid`，而向上取整又会使得`mid`一直等于`right`，所以就停不下来了。而当使用向下取整时，还是当`left`和`right`为连续值的时候，此时`mid`就会等于`left`，如果是中间值小于目标值，就会`left = right`，从而停下循环，如果是中间值大于等于目标值，就会`right = left`，也会跳出循环。

-------------

接下来我们查找末尾目标值的位置。

还是`[1, 2, 3, 3, 3, 4, 5]`，`target == 3`，末尾目标值就是下标为4的三，通过它，我们可以把数组分成两部分，一是`[0， 4]`范围，是小于等于目标值的区间，二是`[5，6]`范围，是大于目标值的区间，因此当中间值小于等于目标值的时候，`left = mid`，而当中间值大于目标值的时候，`right = mid -1`。也就是说，`left`和`right`互换了身份。

循环条件仍旧是`left < right`，这点不受身份互换的影响。求中点的操作要变成向上取整，也就是`mid = left + (right - left + 1) / 2`，还是当`left`和`right`连续时，向上取整得到的`mid`是`right`，当中间值小于等于目标值时，`left = right`，跳出循环，当中间值大于目标值时，`right = left`，也跳出循环。

## code

```cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid;
        }

        // 处理空数组
        if (nums.empty() || nums[left] != target)
            return {-1, -1};

        int begin = left;

        left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left + 1) / 2;
            if (nums[mid] <= target)
                left = mid;
            else
                right = mid - 1;
        }

        int end = left;
        return {begin, end};
    }
};
```

这里可以再优化一下，在已经找到起始目标值之后，对末尾目标值的查找可以直接从现在`left`和数组最后中查找，也就是说，可以不把`left`置0。

```cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid;
        }

        if (nums.empty() || nums[left] != target)
            return {-1, -1};

        int begin = left;

        right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left + 1) / 2;
            if (nums[mid] <= target)
                left = mid;
            else
                right = mid - 1;
        }

        int end = left;
        return {begin, end};
    }
};
```

## template

左端点模版：

```cpp
while (left < right) {
    int mid = left + (right - left) / 2;
    if (······)
        left = mid + 1;	
    else
        right = mid;
}
```

右断点模版：

```cpp
while (left < right) {
    int mid = left + (right - left + 1) / 2;
    if (······)
        left = mid;
    else
        right = mid - 1;
}
```

只要分得清谁是开拓者，谁是守成者就行了。

守成者：指在已有基础上维持现状或守护既有成果的人，与“开拓者”强调开创新领域形成对比。

# end
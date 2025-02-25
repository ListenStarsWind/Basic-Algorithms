# [reverse-nodes-in-k-group](https://leetcode.cn/problems/reverse-nodes-in-k-group)

![image-20250225190728162](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250225190728327.png)

## overview

这道题并不难, "困难"是虚标的.

题目给我们一个链表, 我们需要把这个链表分成若干个小组, 在每个小组里对节点进行翻转.   比如对于示例一来说, `[1, 2, 3, 4, 5]`可以分成两个小组, `[1, 2]`一组, `[3, 4]`一组, 每组节点内部翻转, 就变成了`[2, 1]`, `[4, 3]`, 而组与组之间保持原有位置, 所以最后的链表就是`[2, 1, 4, 3, 5]`.

## solution

这是道模拟题.   有若干种模拟思路, 我们这里只说一种.

 我们首先可以把链表分成若干组, 像末尾不足一组的就不进行操作.   首先我们先遍历链表, 从而得到链表的节点个数, 有了节点个数就知道多少组了.然后建立两层循环, 外层迭代每一组, 内层组内翻转.

![image-20250225192817666](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250225192817735.png)

![image-20250225193009697](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250225193009756.png)

![image-20250225193307815](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250225193307890.png)

![image-20250225194218093](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250225194218161.png)

![image-20250225194403964](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250225194404019.png) 

## code

```cpp
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) 
    {
        // 计算链表长度
        ListNode* current = head;
        int length = 0;
        while (current)
        {
            ++length;
            current = current->next;
        }
        int groupCount = length / k;

        // 开始反转每一组
        ListNode* nextNode = nullptr;
        ListNode* dummyNode = new ListNode();
        ListNode* prevGroupEnd = dummyNode;
        ListNode* groupStart = head;
        current = groupStart;

        for (int i = 0; i < groupCount; ++i)
        {
            groupStart = current;
            for (int j = 0; j < k; ++j)
            {
                nextNode = current->next;
                current->next = prevGroupEnd->next;
                prevGroupEnd->next = current;
                current = nextNode;
            }
            prevGroupEnd = groupStart;
        }
        prevGroupEnd->next = current;

        ListNode* result = dummyNode->next;
        delete dummyNode;
        return result;
    }
};
```

# end
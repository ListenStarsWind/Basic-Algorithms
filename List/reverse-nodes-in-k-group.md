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

## 后记

这道题我不喜欢用模拟, 细节太多了, 所以这里还可以用递归.我们定义`dfs`完成这样的事, 输入一个链表, 返回翻转过后的, 那么首先需要看链表的节点数目够不够`k`, 不够就直接返回, 够的话, 首先把第`k`个节点的下一节点断开, 然后把它扔到链表翻转里面, 然后再用之前的头结点, 现在的尾节点接收剩下链表的`dfs`

```cpp
class Solution {
    int k;

    ListNode* reverse(ListNode* root)
    {
        ListNode* prev = nullptr;
        while(root)
        {
            ListNode* next = root->next;
            root->next = prev;
            prev = root;
            root = next;
        }

        return prev;
    }

    ListNode* dfs(ListNode* root)
    {
        int count = k;
        ListNode* head = root;
        ListNode* prev = nullptr;
        while(root && count--)
        {
            prev = root;
            root = root->next;
        }

        if(count > 0)
            return head;
        
        ListNode* next = prev->next;
        prev->next = nullptr;
        prev = reverse(head);
        head->next = dfs(next);

        head = prev;

        return head;
    }


public:
    ListNode* reverseKGroup(ListNode* head, int _k) {
        k = _k;
        return dfs(head);
    }
};
```

# end
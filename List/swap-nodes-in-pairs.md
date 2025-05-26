# [swap-nodes-in-pairs](https://leetcode.cn/problems/swap-nodes-in-pairs)

![image-20250222205123747](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250222205123804.png)

## overview

这是一道很容易在面试时遇到的题目, 为什么呢? 首先它难度不是太大, 所以不会花费太多时间, 另一方面, 这是一道多解题, 有两种主要的解题思路, 面试就喜欢一题多解, 考察我们对于问题有多角度的解决思路.

题目说的很简单, 但我觉得英文说的更好,即`swap-nodes-in-pairs`, 一对一对地交换节点, 并且需要注意的是, 这种交换是基于节点实体的真实交换, 而不是交换数值域.

比如`[1, 2, 3, 4]`, 先看第一对, 是`(1), <2>`, 交换之后就是`<2>, (1)`,  第二对是`(3), <4>`, 交换之后就是`<4>, (3)`, 所以最后的结果就是`[2, 1, 3, 4]`

## solution

这道题有两条解题思路, 分别是模拟和递归, 先看更简单的模拟思路.

对于模拟思路来说, 实际上就是模拟节点交换的具体过程, 其实这在上面的概述环节就已经模拟过了.

![image-20250222211812800](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250222211812834.png)

首先我们需要引入哨兵位, 模拟本来就需要考虑很多东西, 如果再不带哨兵位, 就更难考虑边界情况了. 当然, 注意最后要释放掉, 不要内存泄露了.

![image-20250222212047197](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250222212047235.png)

再交换过程中, 会涉及到四个节点.

![image-20250222212445161](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250222212445201.png)

具体的交换过程很简单, 一个一个连就行了, `prev->next = second; second->next = first; first->next = next`, 之后, 再对它们进行调整, 应对下一次循环, 

然后我们需要考虑循环条件.   对于偶数节点来说, 终止情况是这样的, 其实就是`first`为空了

![image-20250222212825392](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250222212825429.png)

对于奇数来说, 则是`second`为空

 ![image-20250222212940156](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250222212940189.png)

## code

```cpp
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummy = new ListNode(0, head);  
        ListNode* prev = dummy;
        ListNode* first = nullptr;
        ListNode* second = nullptr;
        ListNode* next = nullptr;

        while ((first = prev->next) != nullptr && (second = first->next) != nullptr) {
            next = second->next;

            prev->next = second;    
            second->next = first;   
            first->next = next;     

            prev = first;           
        }

        ListNode* result = dummy->next;  
        delete dummy;                    
        return result;
    }
};
```

## 后记

这题怎么之前没写递归, 递归很简单, 没有模拟那么多弯弯绕, 我们定义`dfs`, 输入一个链表, 输出该链表交换之后的头结点, 这样的话, 当链表节点个数小于2时, 直接返回头结点, 大于等于2, 就交换, 并接收以第三个节点为头结点的链表`dfs`

```cpp
class Solution {
    ListNode* dfs(ListNode* root)
    {
        if(!root || !root->next)
            return root;
        
        ListNode* first = root;
        ListNode* second = root->next;

        first->next = dfs(second->next);
        second->next = first;

        return second;
    }


public:
    ListNode* swapPairs(ListNode* head) {
        return dfs(head);
    }
};
```

# 完


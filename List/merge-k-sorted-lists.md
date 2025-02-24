# [merge-k-sorted-lists](https://leetcode.cn/problems/merge-k-sorted-lists)

![image-20250224113230259](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250224113230410.png)

## overview

这道题是一道面试题, 其实就单纯解答来说, 它并不难. 否则也不会常在面试环节遇到.  由于题目已经说的很清楚了, 所以我们就不复述了, 直接看示例.

首先有三个链表`[1,4,5],[1,3,4],[2,6]`, 它们都是升序的, 我们要把这些链表中的节点按照升序合并成一个链表.

## solution

这道题有三种解法, 分别是"暴力破解", "最小堆", "分治", 我们按照先后顺序分别来谈.

------------------------------

暴力破解

之前我们已经写过合并两个有序链表的函数了, 直接使用该函数对前两个链表进行合并, 得到一个新的链表, 之后再让这个新的链表与第三个链表相合并, 依次类推, 最终得到一个链表, 在这里, 我们就不细谈代码细节了, 而是要计算一下时间复杂度.

我们假设每个链表的平均长度是`n`, 一共有`k`个链表. 对于第一个链表中的节点来说, 它相当于每次合并都要进行一次比较, 从第一个链表开始, 要合并`k -1`次, 所以单就它一个链表来说, 其时间复杂度就是`n(k-1)`, 同理, 对于第二个链表而言, 其时间复杂度就是`n(k-2)`, 第三个是`n(k-3)`.... 最后一个就是`n*1`, 总的时间复杂度就是把它们加起来.
$$
O(n) = n(k-1) + n(k-2)+n(k-3)+...+n = n * \frac{k(k-1)}{2}
$$
即$nk^2$级别

-------------------

最小堆

我们可以对上面的暴力破解进行优化.

![image-20250224123231490](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250224123231580.png)

假设我们现在有三个链表, 我们可以安排三个指针分别指向这三个链表中的节点, 最开始, 三指针都指向三链表的头结点, 然后我们找到值最小的那个节点, 把它链接到新链表上, 然后让与之对应的指针指向下一个节点.  如果不考虑寻找最小值的过程, 一共有$n*k$个节点, 所以复杂度就是$n*k$

现在我们要想一个办法找到值最小的节点, 为此我们可以使用小根堆. 我们把`k`个指针扔到小根堆里, 之后再把堆顶元素取出, 将其链接到新链表上, 再让这个指针向后迭代, 重新插入堆中, 直到其变为空.

此时, 对于堆来说, 每次修改的复杂度都是$log_2k$, 所以总的复杂度就是$log_2k * nk$,  总的复杂度就是$nk(log_2k + 1)$, 在级别上就是$nk * log_2k$.

----------------

 分治

![image-20250224125517322](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250224125517378.png)

如上图我们现在有六个方框, 其中的每个方框都代表着一个链表, 为了能把它们合并成两个链表, 我们可以把这六个链表分成两组, 第一组是`1, 2, 3`, 第二组是`4, 5, 6`, 每一组都要合并成一个链表, 这样, 我们把这新的两个链表进行合并就能得到一个链表

![image-20250224125957474](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250224125957539.png)

现在为了将第一组中的链表合并成一个, 我们需要堆第一组进行更细的划分, 把它分成两组, 第一组是`1, 2`, 第二组是`3`; `1, 2`可以合并成一个链表, 然后再和`3`合并, 这样我们就得到了`first`;  `4, 5, 6`同理可以得到`second`.

下面我们算一算分治的时间复杂度.

如果把上面那张图画完的话, 会发现整个逻辑实际上是个树结构, 对于某个节点来说, 每过一层, 它就需要进行一次比较, 因为链表的个数为$k$, 所以层数就是$log_2k$, 一共有$nk$个节点, 所以总的时间复杂度就是$nk * log_2k$.

## code

```cpp
class Solution {
    struct greater
    {
        bool operator()(ListNode* node1, ListNode* node2)
        {
            return node1->val > node2->val;
        }
    };

public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, greater> heap;
        for(auto e : lists)
        {
            if(e != nullptr)
            heap.push(e);
        }
        
         ListNode* dummy = new ListNode();
         ListNode* tail = dummy;
         while(!heap.empty())
         {
            tail->next = heap.top();
            tail = tail->next;
            heap.pop();
            ListNode* node = tail->next;
            if(node != nullptr)
                heap.push(node);    
         }
         ListNode* result = dummy->next;
         delete dummy;
         return result;
    }
};


class Solution {
    ListNode* mergeList(ListNode* list1, ListNode* list2)
    {
        ListNode* dummy = new ListNode();
        ListNode* tail = dummy;
        while(list1 && list2)
        {
            if(list1->val < list2->val)
            {
                tail->next = list1;
                list1 = list1->next;
            }
            else
            {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }

        if(list1)
            tail->next = list1;
        if(list2)
            tail->next = list2;

        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }

    ListNode* divide_and_conquer(vector<ListNode*>& lists, int left, int right)
    {
        if(left >= right)
            return lists[left];
        
        int mid = left + (right - left) / 2;
        ListNode* list1 = divide_and_conquer(lists, left, mid);
        ListNode* list2 = divide_and_conquer(lists, mid + 1, right);
        return mergeList(list1, list2);
    }

public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.size() == 0)
            return nullptr;
        return divide_and_conquer(lists, 0, lists.size() - 1);
    }
};
```

# end
# [reorder-list](https://leetcode.cn/problems/reorder-list)

![image-20250224082957022](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250224082957160.png)

## overview

题目要求我们按照它给的要求对链表进行重排: 比如对于`[1, 2, 3, 4, 5]`来说, 先排第一个, 再排倒数第二个, 然后是第二个, 倒数第二个, 于是最后就变成了`[1, 5, 2, 4, 3]`, 由于重排之后头结点还是之前的, 所以并没有要求我们传返回值.

## solution

这道题的思路就是模拟. 因为重排后的链表就像是把原来的链表从头和尾开始, 交替排列形成的. 所以我们可以先找到链表的中间节点, 然后从中间节点那里把链表一分为二, 之后把后面的链表进行逆序排列, 再对这两个链表交替排列新链表即可.

我们先拿`[1, 2, 3, 4, 5]`来举例. 首先找到它们的中间节点, 也就是`[3]`, 于是就可以把链表分成两个子链表, `[1, 2]`, `[3, 4, 5]`, 再把后面的链表进行逆序排列, `[5, 4, 3]`, 

这样我们就得到了两个可以直接排列的子链表`[1, 2], [5, 4, 3]`.  `1, 5, 2, 4`然后前一个链表就排完了, 所以要跳出循环, 但我们也不需要再把`3`给链接上, 因为`4`本身就链接这`3`.

再举一个例子`[1, 2, 3, 4]`, 此时找到的中间节点就是`[3]`, 于是就可以把它们分成`[1, 2]`, `[3, 4]`,  对后一个链表进行逆序, `[4, 3]`, 再交替链接, 就形成了`[1, 3, 2, 4]`, 因为两个子链表节点个数相同, 所以会同时结束, 跳出循环就不需要进行考虑.

下面, 我们简略说一下模拟的子过程, 首先是找到中间节点, 使用的是快慢指针法, 慢指针迭代步长是`1`, 快指针迭代步长是`2`, 等到快直接无法迭代时, 慢指针指向的就是中间节点, 需要注意的是, 由于这里的链表是单链表, 所以为了让两个链表能够分开, 我们真正要找到的是中间节点的前一个节点. 

接着说如何对链表进行逆序, 有两种方法, 一是三指针法, 二是头插法.

我们先说头插法, 头插法就是新建一个链表, 然后每读一个原链表的节点, 就把这个节点头插到新链表中, 因为是头插, 所以就自然而言是逆序了.                      第二种方法在做法上很简单, 但需要一定的理解.  对于链表逆序而言, 第一个节点就应该是新链表的最后一个节点, 这最后一个节点应该指向空, 我们可以认为, 因为它是第一个节点, 前面没有节点, 所以第一个节点前的一个节点就是空, 对于第二个节点来说, 它在新链表中的位置应该是倒数第二, 它会指向原来的第一个节点, 也就是在上次迭代我们操作的那个节点, 所以我们在上次迭代节点操作完成后, 应该记录一下当前节点, 供下一次迭代使用.          不过它在具体操作上很简单, 就是准备三个指针, 一个指针记录上次迭代的操作节点(或者说当前节点在原链表中的前一个节点), 一个记录当前节点, 一个记录下一次迭代的操作节点(或者说当前节点在原链表中的下一个节点).

链表合并就不说了, 那很简单.

## code

```cpp
class Solution {
private:
    ListNode* findMiddleNode(ListNode* head)
    {
        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* prev = nullptr;
        
        while (fast && fast->next)
        {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        return prev;
    }

    // ListNode* reverseList(ListNode* head)
    // {
    //     if (head == nullptr)
    //     {
    //         return nullptr;
    //     }
        
    //     ListNode* dummy = new ListNode();
    //     ListNode* prev = nullptr;
        
    //     while (head)
    //     {
    //         dummy->next = head;
    //         head = head->next;
    //         dummy->next->next = prev;
    //         prev = dummy->next;
    //     }
        
    //     ListNode* result = dummy->next;
    //     delete dummy;
    //     return result;
    // }

     ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = nullptr;
        ListNode* next = nullptr;
        while((curr = head) != nullptr)
        {
            head = head->next;
            next = curr->next;
            curr->next = prev;
            prev = curr;
        }
        return prev;
    }

public:
    void reorderList(ListNode* head) 
    {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
        {
            return;
        }

        ListNode* midPrev = findMiddleNode(head);
        ListNode* mid = midPrev->next;
        midPrev->next = nullptr;
        
        ListNode* list1 = head;
        ListNode* list2 = reverseList(mid);
        
        ListNode* dummy = new ListNode();
        ListNode* tail = dummy;
        
        while (list1 && list2)
        {
            tail->next = list1;
            tail = tail->next;
            list1 = list1->next;
            
            tail->next = list2;
            tail = tail->next;
            list2 = list2->next;
        }

        delete dummy;
    }
};
```



 
# [maximum-width-of-binary-tree](https://leetcode.cn/problems/maximum-width-of-binary-tree)

![image-20250312212546930](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250312212547136.png)

## overview

定义, 每一层的 宽度 被定义为该层最左和最右的非空节点（即，两个端点）之间的长度。且左右端点间的空节点是不可以忽略的. 比如, 对于示例一来说, 它的第三层的节点序列是`[5, 3, null, 9]`, 所以宽度为四.

## solution

题目强调, 本题中的二叉树与满叉树的结构相同, 我们在学习满二叉树的时候, 在物理层使用数组模拟出了二叉树的组织形式. 

![image-20240815110919830](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408151109977.png)

对于上图来说, 假设根节点从零下标开始, 那么, 如果父节点的下标是`x`, 则左子节点的下标是`x * 2 + 1`, 右子节点的下标是`x * 2 + 1`, 不过我们这里为了减少计算次数, 可以假设根节点从一下标开始, 那么, 如果父节点的下标是`x`, 则左子节点的下标是`x * 2`, 右子节点的下标是`x * 2 + 1`

好的, 现在我们可以将每个节点用一个`pair`来表示, 这个`pair`的`first`是节点的地址, `second`就是与之相对的数组下标. 我们可以将每层的节点以从左往右的顺序存入容器中, 此时容器的第一个元素就是最左的节点, 最后一个元素就是最右的节点.  我们可以把它们对应的下标拿出来, 相减再加一, 就能得到这层的宽度, 

![image-20250312214443687](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250312214443729.png)

比如对于上图的第二层来说, 它的宽度是3- 2 + 1 = 2, 对于左右节点之间的那些空节点来说, 它们此时的状态就类似于, 虚拟内存那些为0 的区域, 没有对应的物理内存, 它们只在逻辑上是存在的, 但实际上并不存在.

需要注意的是, 越往下, 空节点的数量就会越多, 而且, 它还是树状结构, 所以下标容易溢出, 理应用能容纳更多数据的类型. 另外, 我们在实际代码上, 可以使用两个容器, 一个表示上一层的状态, 一个表示这一层的状态, 当这一层一个节点都没有时, 那就意味着这棵树已经遍历完了. 

另外, 可能存在一种情况, 就是使用`int`存储下标, 即使即使下标溢出了, 也能得到正确的结果, 这是因为数据溢出的形式是环状的, 只要左右两个下标之间的差距不超过整个环, 其相减的结果还是相同的.

![img](https://i-blog.csdnimg.cn/blog_migrate/cef59f9884f5257e2405a0a05fe92ae5.png)

## code

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    typedef unsigned long long idx;
    typedef pair<TreeNode*, idx> pair;

public:
    int widthOfBinaryTree(TreeNode* root) {
        int result = 0;
        vector<pair> each_layer;
        each_layer.emplace_back(root, 1);
        while(!each_layer.empty())
        {
            vector<pair> next_layer;
            for(const auto&[node, sub] : each_layer)
            {
                if(node->left) next_layer.emplace_back(node->left, sub * 2);
                if(node->right) next_layer.emplace_back(node->right, sub * 2 + 1);
            }
            result = max(result, static_cast<int>(each_layer.back().second - each_layer.front().second + 1));
            each_layer = move(next_layer);
        }
        return result;
    }
};
```

# end
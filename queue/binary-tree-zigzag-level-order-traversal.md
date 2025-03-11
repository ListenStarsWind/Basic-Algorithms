# [binary-tree-zigzag-level-order-traversal](https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal)

![image-20250311105948762](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250311105948898.png)

## overview

这也是层序遍历, 只不过略有不同, 不同之处在于, 我们之前每一层的遍历都是从左往右的, 但在这里, 遍历的方向是在发生变化的, 第一层是从左往右, 第二层是从右往左, 从而产生锯齿状的效果.   比如对于示例一来说, 在之前的层序遍历中, 我们对于第二层是先`9`再`20`, 现在要逆置, 变成`20`再`9`.

## solution

我们其实已经在概述那里谈过思路了, 就是在每次遍历完后, 看看这是第几层, 是奇数层就按原来的从左往右顺序, 是偶数层, 就把数组逆序一样, 这样就变成从右往左了. 如何判断此时是第几层? 很简单, 看看最后返回的二维数组里有多少个元素就行了.

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
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if(root == nullptr)  return result;

        queue<TreeNode*> q;
        q.emplace(root);
        while(!q.empty())
        {
            int size = q.size();
            vector<int> v;
            for(int i = 0; i < size; ++i)
            {
                TreeNode* curr = q.front();
                if(curr->left) q.emplace(curr->left);
                if(curr->right) q.emplace(curr->right);
                q.pop();
                v.emplace_back(curr->val);
            }
            if(result.size() % 2 != 0)
                reverse(v.begin(), v.end());
            result.emplace_back(move(v));
        }
        return result;
    }
};
```

# end
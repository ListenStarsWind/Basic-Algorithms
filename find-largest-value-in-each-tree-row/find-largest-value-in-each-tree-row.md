# [find-largest-value-in-each-tree-row](https://leetcode.cn/problems/find-largest-value-in-each-tree-row)

![image-20250313163339931](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250313163340092.png)

## overview

题目已经说的很明白了, 就是找出各层的最大值, 以数组形式返回.

## solution

直接层序遍历直接找.

## code

```cpp
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        vector<int> result;
        if(root == nullptr) return result;

        vector<TreeNode*> each_row;
        each_row.emplace_back(root);
        while(!each_row.empty())
        {
            int max_ = INT_MIN;
            vector<TreeNode*> temp_row;
            for(auto node : each_row)
            {
                if(node->left) temp_row.emplace_back(node->left);
                if(node->right) temp_row.emplace_back(node->right);
                max_ = max(max_, node->val);
            }
            result.emplace_back(max_);
            each_row = move(temp_row);
        }
        return result;
    }
};
```

# end
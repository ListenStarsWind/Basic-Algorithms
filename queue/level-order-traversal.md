# [level-order-traversal](https://leetcode.cn/problems/n-ary-tree-level-order-traversal)

![image-20250310195039947](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250310195040094.png)

## overview

给你一个N叉树, 请你以二位数组的形式返回它的层序遍历.

## solution

层序遍历有着固定的模版, 它们都是借助于队列完成的. 先把头结点放入队列中, 然后每次读值时都把当前节点的子节点再放入队列中即可.   需要注意的是, 因为它用的是二维数组, 是要有分层的, 所以我们每次在正式处理队列中的节点时, 都要统计一下当前队列的元素数目, 这就是当前层的节点数, 将这个数目作为计数器, 进行对应层的循环.

## code

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> result;
        if(root == nullptr)
            return result;

        queue<Node*> q;
        q.emplace(root);
        while(!q.empty())
        {
            int size = q.size();
            vector<int> v;
            for(int i = 0; i < size; ++i)
            {
                Node* curr = q.front();
                for(Node* child : curr->children)
                {
                    if(child != nullptr)
                    {
                        q.emplace(child);
                    }
                }
                q.pop();
                v.emplace_back(curr->val);
            }
            result.emplace_back(std::move(v));
        }
        return result;
    }
};
```

# end
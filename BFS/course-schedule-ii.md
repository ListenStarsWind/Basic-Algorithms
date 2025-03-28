# [course-schedule-ii](https://leetcode.cn/problems/course-schedule-ii)

![image-20250328100315044](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250328100315279.png)

## overview

本题与上一道题, 课程表一完全一致, 唯一的区别就是它要存一下序列, 最后要返回的

## solution

略

## code

```cpp
class Solution {
    public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        unordered_map<int, vector<int>> edges;
        vector<int> in(numCourses);

        for(const auto& v : prerequisites)
        {
            int a = v[0], b = v[1];
            edges[b].emplace_back(a);
            ++in[a];
        }

        queue<int> q;
        for(int i = 0; i < numCourses; ++i)
        {
            if(in[i] == 0)
                q.emplace(i);
        }

        vector<int> result;
        while(!q.empty())
        {
            int k = q.front(); q.pop();
            result.emplace_back(k);
            for(int e : edges[k])
            {
                --in[e];
                if(in[e] == 0)
                    q.emplace(e);
            }
        }

        if(result.size() == numCourses)
            return result;
        else
            return vector<int>();
    }
};
```

# end
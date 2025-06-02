/*
有两棵无向树，分别有n和m个树节点。
两棵树中的节点编号分别为[0,n-1]和[0,m-1]中的整数。
给两个二维整数edges1和edges2，长度分别为n-1和m-1，
其中edges1[i]=[ai,bi]表示第一棵树中节点ai和bi之间有一条边，
edges2[i]=[ui,vi]表示第二棵树中节点ui和vi之间有一条边。
同时给一个整数k。
如果节点u和节点v之间路径的边数小于等于k，那么我们称节点u是节点v的目标节点。
注意，一个节点一定是它自己的目标节点。
请返回一个长度为n的整数数组answer，
answer[i]表示将第一棵树中的一个节点与第二棵树中的一个节点连接一条边后，
第一棵树中节点i的目标节点数目的最大值。
注意，每个查询相互独立。意味着进行下一次查询之前，需要先把刚添加的边给删掉。

示例1：
输入：edges1 = [[0,1],[0,2],[2,3],[2,4]],
     edges2 = [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]], k = 2
输出：[9,7,9,8,8]
解释：对于i = 0，连接第一棵树中的节点0和第二棵树中的节点0。
     对于i = 1，连接第一棵树中的节点1和第二棵树中的节点0。
     对于i = 2，连接第一棵树中的节点2和第二棵树中的节点4。
     对于i = 3，连接第一棵树中的节点3和第二棵树中的节点4。
     对于i = 4，连接第一棵树中的节点4和第二棵树中的节点4。

示例2：
输入：edges1 = [[0,1],[0,2],[0,3],[0,4]],
     edges2 = [[0,1],[1,2],[2,3]], k = 1
输出：[6,3,3,3,3]
解释：对于每个i，连接第一棵树中的节点i和第二棵树中的任意一个节点。


提示：
2 <= n, m <= 1000
edges1.length == n - 1
edges2.length == m - 1
edges1[i].length == edges2[i].length == 2
edges1[i] = [ai, bi]
0 <= ai, bi < n
edges2[i] = [ui, vi]
0 <= ui, vi < m
输入保证edges1和edges2都表示合法的树。
0 <= k <= 1000
*/

// 脑筋急转弯+暴力枚举
class Solution {
  vector<vector<int>> buildTree(vector<vector<int>>& edges) {
    vector<vector<int>> g(edges.size() + 1);
    for (auto& e : edges) {
      int x = e[0], y = e[1];
      g[x].push_back(y);
      g[y].push_back(x);
    }
    return g;
  }

  int dfs(int x, int fa, int d, vector<vector<int>>& g, int k) {
    if (d > k) {
      return 0;
    }
    int cnt = 1;
    for (int y : g[x]) {
      if (y != fa) {
        cnt += dfs(y, x, d + 1, g, k);
      }
    }
    return cnt;
  }

 public:
  vector<int> maxTargetNodes(vector<vector<int>>& edges1,
                             vector<vector<int>>& edges2, int k) {
    int max2 = 0;
    if (k > 0) {
      auto g = buildTree(edges2);
      for (int i = 0; i < edges2.size() + 1; i++) {
        max2 = max(max2, dfs(i, -1, 0, g, k - 1));  // 注意这里传的是k-1
      }
    }

    auto g = buildTree(edges1);
    vector<int> ans(edges1.size() + 1);
    for (int i = 0; i < ans.size(); i++) {
      ans[i] = dfs(i, -1, 0, g, k) + max2;
    }
    return ans;
  }
};
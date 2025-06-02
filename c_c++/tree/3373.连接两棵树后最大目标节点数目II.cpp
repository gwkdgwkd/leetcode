/*
有两棵无向树，分别有n和m个树节点。两棵树中的节点编号分别为[0,n-1]和[0,m-1]中的整数。
给你两个二维整数edges1和edges2，长度分别为n-1和m-1，
其中edges1[i]=[ai,bi]表示第一棵树中节点ai和bi之间有一条边，
edges2[i]=[ui,vi]表示第二棵树中节点ui和vi之间有一条边。
如果节点u和节点v之间路径的边数是偶数，那么我们称节点u是节点v的目标节点。
注意，一个节点一定是它自己的目标节点。
请返回一个长度为n的整数数组answer，
answer[i]表示将第一棵树中的一个节点与第二棵树中的一个节点连接一条边后，
第一棵树中节点i的目标节点数目的最大值。
注意，每个查询相互独立。意味着进行下一次查询之前，需要先把刚添加的边给删掉。

示例1：
输入：edges1 = [[0,1],[0,2],[2,3],[2,4]],
     edges2 = [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]]
输出：[8,7,7,8,8]
解释：对于i = 0，连接第一棵树中的节点0和第二棵树中的节点0。
     对于i = 1，连接第一棵树中的节点1和第二棵树中的节点4。
     对于i = 2，连接第一棵树中的节点2和第二棵树中的节点7。
     对于i = 3，连接第一棵树中的节点3和第二棵树中的节点0。
     对于i = 4，连接第一棵树中的节点4和第二棵树中的节点4。

示例2：
输入：edges1 = [[0,1],[0,2],[0,3],[0,4]], edges2 = [[0,1],[1,2],[2,3]]
输出：[3,6,6,6,6]
解释：对于每个i，连接第一棵树中的节点i和第二棵树中的任意一个节点。


提示：
2 <= n, m <= 105
edges1.length == n - 1
edges2.length == m - 1
edges1[i].length == edges2[i].length == 2
edges1[i] = [ai, bi]
0 <= ai, bi < n
edges2[i] = [ui, vi]
0 <= ui, vi < m
输入保证edges1和edges2都表示合法的树。
*/

class Solution {
 public:
  vector<int> maxTargetNodes(vector<vector<int>>& edges1,
                             vector<vector<int>>& edges2) {
    auto count = [](vector<vector<int>>& edges) {
      vector<vector<int>> g(edges.size() + 1);
      for (auto& e : edges) {
        int x = e[0], y = e[1];
        g[x].push_back(y);
        g[y].push_back(x);
      }

      array<int, 2> cnt{};
      auto dfs = [&](this auto&& dfs, int x, int fa, int d) -> void {
        cnt[d]++;
        for (int y : g[x]) {
          if (y != fa) {
            dfs(y, x, d ^ 1);
          }
        }
      };
      dfs(0, -1, 0);
      return pair(g, cnt);
    };

    auto [_, cnt2] = count(edges2);
    int max2 = max(cnt2[0], cnt2[1]);

    auto [g, cnt1] = count(edges1);
    vector<int> ans(g.size(), max2);
    auto dfs = [&](this auto&& dfs, int x, int fa, int d) -> void {
      ans[x] += cnt1[d];
      for (int y : g[x]) {
        if (y != fa) {
          dfs(y, x, d ^ 1);
        }
      }
    };
    dfs(0, -1, 0);
    return ans;
  }
};
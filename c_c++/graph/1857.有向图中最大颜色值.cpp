/*
给一个有向图，它含有n个节点和m条边。节点编号从0到n-1。
给一个字符串colors，其中colors[i]是小写英文字母，表示图中第i个节点的颜色（下标从0开始）。
同时给一个二维数组edges，其中edges[j]=[aj,bj]表示从节点aj到节点bj有一条有向边。
图中一条有效路径是一个点序列x1->x2->x3->...->xk，对于所有1<=i<k，
从xi到xi+1在图中有一条有向边。路径的颜色值是路径中出现次数最多颜色的节点数目。
请返回给定图中有效路径里面的最大颜色值。如果图中含有环，请返回-1。

示例1：
输入：colors = "abaca", edges = [[0,1],[0,2],[2,3],[3,4]]
输出：3
解释：路径0 -> 2 -> 3 -> 4含有3个颜色为"a"的节点（上图中的红色节点）。

示例2：
输入：colors = "a", edges = [[0,0]]
输出：-1
解释：从0到0有一个环。


提示：
n == colors.length
m == edges.length
1 <= n <= 10^5
0 <= m <= 10^5
colors只含有小写英文字母。
0 <= aj, bj < n
*/

// 拓扑排序 + 刷表法
class Solution {
 public:
  int largestPathValue(string colors, vector<vector<int>>& edges) {
    int n = colors.size();
    vector<vector<int>> g(n);
    vector<int> deg(n);
    for (auto& e : edges) {
      int x = e[0], y = e[1];
      if (x == y) {  // 自环
        return -1;
      }

      g[x].push_back(y);
      deg[y]++;
    }

    vector<int> q;
    for (int i = 0; i < n; i++) {
      if (deg[i] == 0) {
        q.push_back(i);  // 入度为0的点入队
      }
    }

    int ans = 0;
    vector<array<int, 26>> f(n);
    for (int i = 0; i < q.size(); i++) {  // 注意q.size()会变大
      int x = q[i];  // x的所有转移来源都计算完毕，也都更新到f[x]中
      int ch = colors[x] - 'a';
      f[x][ch]++;
      ans = max(ans, f[x][ch]);
      for (int y : g[x]) {
        for (int j = 0; j < 26; j++) {
          f[y][j] = max(f[y][j], f[x][j]);  // 刷表法，更新邻居的最大值
        }

        if (--deg[y] == 0) {
          q.push_back(y);
        }
      }
    }

    return q.size() < n ? -1 : ans;
  }
};

// 记忆化搜索 + 三色标记法
class Solution {
 public:
  int largestPathValue(string colors, vector<vector<int>>& edges) {
    int n = colors.size();
    vector<vector<int>> g(n);
    for (auto& e : edges) {
      int x = e[0], y = e[1];
      if (x == y) {  // 自环
        return -1;
      }
      g[x].push_back(y);
    }

    vector<vector<int>> memo(n);
    auto dfs = [&](this auto&& dfs, int x) -> vector<int> {
      if (!memo[x].empty()) {  // x计算中或者计算过
        return memo[x];        // 如果是空vector，表示有环
      }

      memo[x] = {0};  // 表示计算中
      vector<int> res(26);
      for (int y : g[x]) {
        auto cy = dfs(y);
        if (cy.size() <= 1) {  // 有环
          return cy;
        }

        for (int i = 0; i < 26; i++) {
          res[i] = max(res[i], cy[i]);
        }
      }
      res[colors[x] - 'a']++;
      return memo[x] = res;  // 记忆化，同时也表示x计算完毕
    };

    int ans = 0;
    for (int x = 0; x < n; x++) {
      auto res = dfs(x);
      if (res.size() <= 1) {  // 有环
        return -1;
      }
      ans = max(ans, res[colors[x] - 'a']);
    }

    return ans;
  }
};

// 拓扑排序 + 动态规划
class Solution {
 public:
  int largestPathValue(string colors, vector<vector<int>>& edges) {
    int n = colors.size();
    // 邻接表
    vector<vector<int>> g(n);
    // 节点的入度统计，用于找出拓扑排序中最开始的节点
    vector<int> indeg(n);
    for (auto&& edge : edges) {
      ++indeg[edge[1]];
      g[edge[0]].push_back(edge[1]);
    }

    // 记录拓扑排序过程中遇到的节点个数
    // 如果最终found的值不为n，说明图中存在环
    int found = 0;
    vector<array<int, 26>> f(n);
    queue<int> q;
    for (int i = 0; i < n; ++i) {
      if (!indeg[i]) {
        q.push(i);
      }
    }

    while (!q.empty()) {
      ++found;
      int u = q.front();
      q.pop();
      // 将节点u对应的颜色增加1
      ++f[u][colors[u] - 'a'];
      // 枚举u的后继节点v
      for (int v : g[u]) {
        --indeg[v];
        // 将f(v,c)更新为其与f(u,c)的较大值
        for (int c = 0; c < 26; ++c) {
          f[v][c] = max(f[v][c], f[u][c]);
        }
        if (!indeg[v]) {
          q.push(v);
        }
      }
    }

    if (found != n) {
      return -1;
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
      ans = max(ans, *max_element(f[i].begin(), f[i].end()));
    }
    return ans;
  }
};

/*
给一棵n个节点的无向树，节点编号为1到n。
给你一个整数n和一个长度为n-1的二维整数数组edges，
其中edges[i]=[ui,vi]表示节点ui和vi在树中有一条边。
请返回树中的合法路径数目。
如果在节点a到节点b之间恰好有一个节点的编号是质数，那么我们称路径(a,b)是合法的。
注意：
路径(a, b)指的是一条从节点a开始到节点b结束的一个节点序列，
序列中的节点互不相同，且相邻节点之间在树上有一条边。
路径(a, b)和路径(b, a)视为同一条路径，且只计入答案一次。

示例1：
输入：n = 5, edges = [[1,2],[1,3],[2,4],[2,5]]
输出：4
解释：恰好有一个质数编号的节点路径有：
     (1,2)因为路径1到2只包含一个质数2。
     (1,3)因为路径1到3只包含一个质数3。
     (1,4)因为路径1到4只包含一个质数2。
     (2,4)因为路径2到4只包含一个质数2。
     只有4条合法路径。

示例2：
输入：n = 6, edges = [[1,2],[1,3],[2,4],[3,5],[3,6]]
输出：6
解释：恰好有一个质数编号的节点路径有：
     (1,2)因为路径1到2只包含一个质数2。
     (1,3)因为路径1到3只包含一个质数3。
     (1,4)因为路径1到4只包含一个质数2。
     (1,6)因为路径1到6只包含一个质数3。
     (2,4)因为路径2到4只包含一个质数2。
     (3,6)因为路径3到6只包含一个质数3。
     只有6条合法路径。


提示：
1 <= n <= 10^5
edges.length == n - 1
edges[i].length == 2
1 <= ui, vi <= n
输入保证edges形成一棵合法的树。
*/

const int MX = 1e5;
bool np[MX + 1];  // 质数=false 非质数=true
int init = []() {
  np[1] = true;
  for (int i = 2; i * i <= MX; i++) {
    if (!np[i]) {
      for (int j = i * i; j <= MX; j += i) {
        np[j] = true;
      }
    }
  }

  return 0;
}();

class Solution {
 public:
  long long countPaths(int n, vector<vector<int>> &edges) {
    vector<vector<int>> g(n + 1);

    for (auto &e : edges) {
      int x = e[0], y = e[1];
      g[x].push_back(y);
      g[y].push_back(x);
    }

    vector<int> size(n + 1);
    vector<int> nodes;
    function<void(int, int)> dfs = [&](int x, int fa) {
      nodes.push_back(x);
      for (int y : g[x]) {
        if (y != fa && np[y]) {
          dfs(y, x);
        }
      }
    };

    long long ans = 0;
    for (int x = 1; x <= n; x++) {
      if (np[x]) continue;  // 跳过非质数
      int sum = 0;
      for (int y : g[x]) {  // 质数 x 把这棵树分成了若干个连通块
        if (!np[y]) continue;
        if (size[y] == 0) {  // 尚未计算过
          nodes.clear();
          dfs(y, -1);  // 遍历y
                       // 所在连通块，在不经过质数的前提下，统计有多少个非质数

          for (int z : nodes) {
            size[z] = nodes.size();
          }
        }

        // 这size[y]个非质数与之前遍历到的sum个非质数，两两之间的路径只包含质数
        ans += (long long)size[y] * sum;
        sum += size[y];
      }

      ans += sum;  // 从x出发的路径
    }

    return ans;
  }
};
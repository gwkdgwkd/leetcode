/*
给一棵无根带权树，树中总共有n个节点，分别表示n个服务器，服务器从0到n-1编号。
同时给你一个数组edges，其中edges[i]=[ai,bi,weighti]表示节点ai和bi之间有一条双向边，
边的权值为weighti。再给你一个整数signalSpeed。
如果两台服务器a和b是通过服务器c可连接的，则：
a < b ，a != c且b != c。
从c到a的距离是可以被signalSpeed整除的。
从c到b的距离是可以被signalSpeed整除的。
从c到b的路径与从c到a的路径没有任何公共边。
请返回一个长度为n的整数数组count，其中count[i]表示通过服务器i可连接的服务器对的数目。

示例1：
输入：edges = [[0,1,1],[1,2,5],[2,3,13],[3,4,9],[4,5,2]], signalSpeed = 1
输出：[0,4,6,6,4,0]
解释：由于signalSpeed等于1，count[c]等于所有从c开始且没有公共边的路径对数目。
     在输入图中，count[c]等于服务器c左边服务器数目乘以右边服务器数目。

示例2：
输入：edges = [[0,6,3],[6,5,3],[0,3,1],[3,2,7],[3,1,6],[3,4,2]], signalSpeed = 3
输出：[2,0,0,0,0,0,2]
解释：通过服务器0，有2个可连接服务器对(4,5)和(4,6)。
     通过服务器6，有2个可连接服务器对(4,5)和(0,5)。
     所有服务器对都必须通过服务器0或6才可连接，所以其他服务器对应的可连接服务器对数目都为0。


提示：
2 <= n <= 1000
edges.length == n - 1
edges[i].length == 3
0 <= ai, bi < n
edges[i] = [ai, bi, weighti]
1 <= weighti <= 10^6
1 <= signalSpeed <= 10^6
输入保证edges构成一棵合法的树。
*/

class Solution {
 public:
  vector<int> countPairsOfConnectableServers(vector<vector<int>> &edges,
                                             int signalSpeed) {
    int n = edges.size() + 1;
    vector<vector<pair<int, int>>> g(n);
    for (auto &e : edges) {
      int x = e[0], y = e[1], wt = e[2];
      g[x].push_back({y, wt});
      g[y].push_back({x, wt});
    }

    function<int(int, int, int)> dfs = [&](int x, int fa, int sum) -> int {
      int cnt = sum % signalSpeed == 0;
      for (auto &[y, wt] : g[x]) {
        if (y != fa) {
          cnt += dfs(y, x, sum + wt);
        }
      }
      return cnt;
    };

    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
      if (g[i].size() == 1) {
        continue;
      }
      int sum = 0;
      for (auto &[y, wt] : g[i]) {
        int cnt = dfs(y, i, wt);
        ans[i] += cnt * sum;
        sum += cnt;
      }
    }
    return ans;
  }
};
/*
给两个整数n和threshold，同时给你一个n个节点的有向带权图，节点编号为0到n-1。
这个图用二维整数数组edges表示，
其中edges[i]=[Ai,Bi,Wi]表示节点Ai到节点Bi之间有一条边权为Wi的有向边。
需要从这个图中删除一些边（也可能不删除任何边），使得这个图满足以下条件：
所有其他节点都可以到达节点0。
图中剩余边的最大边权值尽可能小。
每个节点都至多有threshold条出去的边。
请返回删除必要的边后，最大边权的最小值为多少。如果无法满足所有的条件，请你返回-1。

示例1：
输入：n = 5, edges = [[1,0,1],[2,0,2],[3,0,1],[4,3,1],[2,1,1]],
     threshold = 2
输出：1
解释：删除边2->0。剩余边中的最大值为1。

示例 2：
输入：n = 5, edges = [[0,1,1],[0,2,2],[0,3,1],[0,4,1],[1,2,1],[1,4,1]],
     threshold = 1
输出：-1 解释：无法从节点2到节点0。

示例3：
输入：n = 5, edges = [[1,2,1],[1,3,3],[1,4,5],[2,3,2],[3,4,2],[4,0,1]],
     threshold = 1
输出：2
解释：删除边1->3和1->4。剩余边中的最大值为2。

示例4：
输入：n = 5, edges = [[1,2,1],[1,3,3],[1,4,5],[2,3,2],[4,0,1]], threshold = 1
输出：-1


提示：
2 <= n <= 10^5
1 <= threshold <= n - 1
1 <= edges.length <= min(10^5, n * (n - 1) / 2).
edges[i].length == 3
0 <= Ai, Bi < n
Ai != Bi
1 <= Wi <= 10^6
一对节点之间可能会有多条边，但它们的权值互不相同。
*/

// 二分答案 + DFS
class Solution {
 public:
  int minMaxWeight(int n, vector<vector<int>>& edges, int) {
    if (edges.size() < n - 1) {
      return -1;
    }

    vector<vector<pair<int, int>>> g(n);
    int max_w = 0;
    for (auto& e : edges) {
      int x = e[0], y = e[1], w = e[2];
      g[y].emplace_back(x, w);
      max_w = max(max_w, w);
    }

    vector<int> vis(n);
    auto check = [&](int upper) -> bool {
      int left = n;
      auto dfs = [&](this auto&& dfs, int x) -> void {
        vis[x] = upper;  // 避免每次二分重新创建vis数组
        left--;
        for (auto& [y, w] : g[x]) {
          if (w <= upper && vis[y] != upper) {
            dfs(y);
          }
        }
      };
      dfs(0);
      return left == 0;
    };

    // int left = 0, right = max_w + 1;
    // while (left + 1 < right) {
    //     int mid = left + (right - left) / 2;
    //     (check(mid) ? right : left) = mid;
    // }
    // return right > max_w ? -1 : right;
    int left = 1, right = max_w;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (check(mid)) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    return left > max_w ? -1 : left;
  }
};

// Dijkstra
class Solution {
 public:
  int minMaxWeight(int n, vector<vector<int>>& edges, int) {
    if (edges.size() < n - 1) {
      return -1;
    }

    vector<vector<pair<int, int>>> g(n);
    for (auto& e : edges) {
      int x = e[0], y = e[1], w = e[2];
      g[y].emplace_back(x, w);
    }

    vector<int> dis(n, INT_MAX);
    dis[0] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, 0);  // (路径最大边权, 节点编号)
    while (!pq.empty()) {
      auto [d, x] = pq.top();
      pq.pop();
      if (d > dis[x]) {
        continue;
      }
      for (auto& [y, w] : g[x]) {
        int new_d = max(d, w);
        if (new_d < dis[y]) {
          dis[y] = new_d;
          pq.emplace(new_d, y);
        }
      }
    }

    int ans = ranges::max(dis);
    return ans == INT_MAX ? -1 : ans;
  }
};

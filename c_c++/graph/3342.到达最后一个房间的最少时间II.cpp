/*
有一个地窖，地窖中有n x m个房间，它们呈网格状排布。
给一个大小为n x m的二维数组moveTime，
其中moveTime[i][j]表示在这个时刻以后才可以开始往这个房间移动。
在时刻t = 0时从房间(0, 0)出发，每次可以移动到相邻的一个房间。
在相邻房间之间移动需要的时间为：
第一次花费1秒，第二次花费2秒，第三次花费1秒，第四次花费2秒……如此往复。
请返回到达房间(n - 1, m - 1)所需要的最少时间。
如果两个房间有一条公共边（可以是水平的也可以是竖直的），那么称这两个房间是相邻的。

示例1：
输入：moveTime = [[0,4],[4,4]]
输出：7
解释：需要花费的最少时间为7秒。
     在时刻t == 4，从房间(0, 0)移动到房间(1, 0)，花费1秒。
     在时刻t == 5，从房间(1, 0)移动到房间(1, 1)，花费2秒。

示例2：
输入：moveTime = [[0,0,0,0],[0,0,0,0]]
输出：6
解释：需要花费的最少时间为6秒。
     在时刻t == 0，从房间(0, 0)移动到房间(1, 0)，花费1秒。
     在时刻t == 1，从房间(1, 0)移动到房间(1, 1)，花费2秒。
     在时刻t == 3，从房间(1, 1)移动到房间(1, 2)，花费1秒。
     在时刻t == 4，从房间(1, 2)移动到房间(1, 3)，花费2秒。

示 3：
输入：moveTime = [[0,1],[1,2]]
输出：4


提示：
2 <= n == moveTime.length <= 750
2 <= m == moveTime[i].length <= 750
0 <= moveTime[i][j] <= 10^9
*/

// Dijkstra最短路径
class Solution {
  static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

 public:
  int minTimeToReach(vector<vector<int>>& moveTime) {
    int n = moveTime.size(), m = moveTime[0].size();
    vector<vector<int>> dis(n, vector<int>(m, INT_MAX));
    dis[0][0] = 0;
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>,
                   greater<>>
        pq;
    pq.emplace(0, 0, 0);
    while (true) {
      auto [d, i, j] = pq.top();
      pq.pop();
      if (i == n - 1 && j == m - 1) {
        return d;
      }
      if (d > dis[i][j]) {
        continue;
      }
      int time = (i + j) % 2 + 1;
      for (auto& q : dirs) {
        int x = i + q[0], y = j + q[1];
        if (0 <= x && x < n && 0 <= y && y < m) {
          int new_dis = max(d, moveTime[x][y]) + time;
          if (new_dis < dis[x][y]) {
            dis[x][y] = new_dis;
            pq.emplace(new_dis, x, y);
          }
        }
      }
    }
  }
};
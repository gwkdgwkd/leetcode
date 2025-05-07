/*
有一个地窖，地窖中有nxm个房间，它们呈网格状排布。
给一个大小为nxm的二维数组moveTime，其中moveTime[i][j]表示在这个时刻以后才可以开始往这个房间移动。
在时刻t=0时从房间(0,0)出发，每次可以移动到相邻的一个房间。在相邻房间之间移动需要的时间为1秒。
请返回到达房间(n-1,m-1)所需要的最少时间。
如果两个房间有一条公共边（可以是水平的也可以是竖直的），那么我们称这两个房间是相邻的。

示例1：
输入：moveTime = [[0,4],[4,4]]
输出：6
解释：需要花费的最少时间为6秒。
     在时刻t == 4，从房间(0, 0)移动到房间(1, 0)，花费1秒。
     在时刻t == 5，从房间(1, 0)移动到房间(1, 1)，花费1秒。

示例2：
输入：moveTime = [[0,0,0],[0,0,0]]
输出：3
解释：需要花费的最少时间为3秒。
     在时刻t == 0，从房间(0, 0)移动到房间(1, 0)，花费1秒。
     在时刻t == 1，从房间(1, 0)移动到房间(1, 1)，花费1秒。
     在时刻t == 2，从房间(1, 1)移动到房间(1, 2)，花费1秒。

示例3：
输入：moveTime = [[0,1],[1,2]]
输出：3


提示：
2 <= n == moveTime.length <= 50
2 <= m == moveTime[i].length <= 50
0 <= moveTime[i][j] <= 10^9
*/

// dfs
class Solution {
 public:
  const int dx[4] = {1, 0, -1, 0};
  const int dy[4] = {0, 1, 0, -1};
  int m, n;
  int mintime = INT_MAX;
  int dfs(vector<vector<int>>& moveTime, int x, int y, int currenttime,
          vector<vector<int>>& memo) {
    if (x == m - 1 && y == n - 1) {
      return currenttime;
    }
    if (memo[x][y] != -1 && memo[x][y] <= currenttime) {
      return INT_MAX;
    }
    memo[x][y] = currenttime;
    for (int k = 0; k < 4; ++k) {
      int r = x + dx[k];
      int c = y + dy[k];
      if (r >= 0 && r < m && c >= 0 && c < n) {
        int newtime = max(currenttime, moveTime[r][c]) + 1;
        mintime = min(mintime, dfs(moveTime, r, c, newtime, memo));
      }
    }
    return mintime;
  }

  int minTimeToReach(vector<vector<int>>& moveTime) {
    m = moveTime.size();
    n = moveTime[0].size();
    vector<vector<int>> memo(m, vector<int>(n, -1));

    int ans = dfs(moveTime, 0, 0, 0, memo);
    return ans;
  }
};

// BFS
class Solution {
  struct Node {
    int x, y, t;
    Node() { x = y = t = 0; }
    Node(int _x, int _y, int _t) : x(_x), y(_y), t(_t) {}
    Node(const Node& node) {
      x = node.x;
      y = node.y;
      t = node.t;
    }

    bool operator>(const Node& node) const { return t > node.t; }

    bool operator<(const Node& node) const { return t < node.t; }
  };

 public:
  int dx[4] = {0, 0, 1, -1};
  int dy[4] = {1, -1, 0, 0};

  int minTimeToReach(vector<vector<int>>& moveTime) {
    int m = moveTime.size(), n = moveTime[0].size();
    priority_queue<Node, vector<Node>, greater<Node>> q;
    q.push(Node(0, 0, 0));

    int ret = 0;
    vector<vector<int>> memo(m, vector<int>(n, 0x3f3f3f3f));
    memo[0][0] = 0;
    while (!q.empty()) {
      Node node = q.top();
      q.pop();
      // 最快情况下，也到不了， 剪枝
      if (node.t + m - node.x + n - node.y - 2 >= memo[m - 1][n - 1]) continue;

      for (int k = 0; k < 4; k++) {
        int x = node.x + dx[k], y = node.y + dy[k];
        if (x >= 0 && y >= 0 && x < m && y < n && memo[x][y] > node.t + 1) {
          if (node.t + 1 <= moveTime[x][y])
            memo[x][y] = moveTime[x][y] + 1;
          else
            memo[x][y] = node.t + 1;
          q.push(Node(x, y, memo[x][y]));
        }
      }
    }

    return memo[m - 1][n - 1];
  }
};

// Dijkstra最短路径
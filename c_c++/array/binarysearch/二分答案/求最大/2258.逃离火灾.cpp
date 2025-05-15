/*
给一个下标从0开始大小为m x n的二维整数数组grid，它表示一个网格图。
每个格子为下面3个值之一：
0表示草地。
1表示着火的格子。
2表示一座墙，跟火都不能通过这个格子。
一开始在最左上角的格子(0,0)，想要到达最右下角的安全屋格子(m-1,n-1)。
每一分钟，可以移动到相邻的草地格子。每次你移动之后，着火的格子会扩散到所有不是墙的相邻格子。
请返回在初始位置可以停留的最多分钟数，且停留完这段时间后你还能安全到达安全屋。
如果无法实现，请返回-1。如果不管在初始位置停留多久，你总是能到达安全屋，请返回10^9。
注意，如果到达安全屋后，火马上到了安全屋，这视为能够安全到达安全屋。
如果两个格子有共同边，那么它们为相邻格子。

示例1：
输入：grid = [[0,2,0,0,0,0,0],
             [0,0,0,2,2,1,0],
             [0,2,0,0,1,2,0],
             [0,0,2,2,2,0,2],
             [0,0,0,0,0,0,0]]
输出：3
解释：上图展示了在初始位置停留3分钟后的情形。仍然可以安全到达安全屋。
     停留超过3分钟会无法安全到达安全屋。

示例2：
输入：grid = [[0,0,0,0],
             [0,1,2,0],
             [0,2,0,0]]
输出：-1
解释：上图展示了你马上开始朝安全屋移动的情形。
     火会蔓延到你可以移动的所有格子，所以无法安全到达安全屋。所以返回-1。

示例3：
输入：grid = [[0,0,0],
             [2,2,0],
             [1,2,0]]
输出：1000000000
解释：上图展示了初始网格图。
     注意，由于火被墙围了起来，所以无论如何你都能安全到达安全屋。所以返回10^9。


提示：
m == grid.length
n == grid[i].length
2 <= m, n <= 300
4 <= m * n <= 2 * 10^4
grid[i][j]是0，1或者2。
grid[0][0] == grid[m - 1][n - 1] == 0
*/

class Solution {
  const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  // 返回能否在初始位置停留t分钟，并安全到达安全屋
  bool check(vector<vector<int>> &grid, int t) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> on_fire(m, vector<int>(n));
    vector<pair<int, int>> f;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == 1) {
          on_fire[i][j] = true;  // 标记着火的位置
          f.emplace_back(i, j);
        }
      }
    }

    // 火的BFS
    auto spread_fire = [&]() {
      vector<pair<int, int>> nf;
      for (auto &[i, j] : f) {
        for (auto &[dx, dy] : dirs) {  // 枚举上下左右四个方向
          int x = i + dx, y = j + dy;
          if (0 <= x && x < m && 0 <= y && y < n && !on_fire[x][y] &&
              grid[x][y] == 0) {
            on_fire[x][y] = true;  // 标记着火的位置
            nf.emplace_back(x, y);
          }
        }
      }
      f = move(nf);
    };

    while (t-- && !f.empty()) {  // 如果火无法扩散就提前退出
      spread_fire();             // 火扩散
    }

    if (on_fire[0][0]) {
      return false;  // 起点着火，寄
    }

    // 人的BFS
    vector<vector<int>> vis(m, vector<int>(n));
    vis[0][0] = true;
    vector<pair<int, int>> q{{0, 0}};
    while (!q.empty()) {
      vector<pair<int, int>> nq;
      for (auto &[i, j] : q) {
        if (on_fire[i][j]) continue;  // 人走到这个位置后，火也扩散到了这个位置
        for (auto &[dx, dy] : dirs) {  // 枚举上下左右四个方向
          int x = i + dx, y = j + dy;
          if (0 <= x && x < m && 0 <= y && y < n && !on_fire[x][y] &&
              !vis[x][y] && grid[x][y] == 0) {
            if (x == m - 1 && y == n - 1) {
              return true;  // 我们安全了暂时。
            }

            vis[x][y] = true;  // 避免反复访问同一个位置
            nq.emplace_back(x, y);
          }
        }
      }

      q = move(nq);
      spread_fire();  // 火扩散
    }

    return false;  // 人被火烧到，或者没有可以到达安全屋的路
  }

 public:
  int maximumMinutes(vector<vector<int>> &grid) {
    int m = grid.size(), n = grid[0].size();

    int left = -1, right = m * n + 1;
    while (left + 1 < right) {
      int mid = (left + right) / 2;
      (check(grid, mid) ? left : right) = mid;
    }

    return left < m * n ? left : 1'000'000'000;
  }
};

// 直接计算
class Solution {
  const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

 public:
  int maximumMinutes(vector<vector<int>> &grid) {
    int m = grid.size(), n = grid[0].size();
    // 返回三个数，分别表示到达安全屋/安全屋左边/安全屋上边的最短时间
    auto bfs = [&](vector<pair<int, int>> &q) -> tuple<int, int, int> {
      vector<vector<int>> time(m, vector<int>(n, -1));  // -1 表示未访问
      for (auto &[i, j] : q) {
        time[i][j] = 0;
      }
      for (int t = 1; !q.empty(); t++) {  // 每次循环向外扩展一圈
        vector<pair<int, int>> nq;
        for (auto &[i, j] : q) {
          for (auto &[dx, dy] : dirs) {  // 枚举上下左右四个方向
            int x = i + dx, y = j + dy;
            if (0 <= x && x < m && 0 <= y && y < n && grid[x][y] == 0 &&
                time[x][y] < 0) {
              time[x][y] = t;
              nq.emplace_back(x, y);
            }
          }
        }
        q = move(nq);
      }
      return {time[m - 1][n - 1], time[m - 1][n - 2], time[m - 2][n - 1]};
    };

    vector<pair<int, int>> q = {{0, 0}};
    auto [man_to_house_time, m1, m2] = bfs(q);
    if (man_to_house_time < 0) {  // 人无法到安全屋
      return -1;
    }

    vector<pair<int, int>> fire_pos;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == 1) {
          fire_pos.emplace_back(i, j);
        }
      }
    }

    auto [fire_to_house_time, f1, f2] = bfs(fire_pos);  // 多个着火点同时跑 BFS
    if (fire_to_house_time < 0) {                       // 火无法到安全屋
      return 1'000'000'000;
    }

    int d = fire_to_house_time - man_to_house_time;
    if (d < 0) {  // 火比人先到安全屋
      return -1;
    }

    if (m1 != -1 && m1 + d < f1 ||  // 安全屋左边相邻格子，人比火先到
        m2 != -1 && m2 + d < f2) {  // 安全屋上边相邻格子，人比火先到
      return d;                     // 图中第一种情况
    }
    return d - 1;  // 图中第二种情况
  }
};
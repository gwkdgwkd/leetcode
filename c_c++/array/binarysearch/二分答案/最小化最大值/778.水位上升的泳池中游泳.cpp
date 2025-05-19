/*
在一个nxn的整数矩阵grid中，每一个方格的值grid[i][j]表示位置(i,j)的平台高度。
当开始下雨时，在时间为t时，水池中的水位为t。
可以从一个平台游向四周相邻的任意一个平台，但是前提是此时水位必须同时淹没这两个平台。
假定你可以瞬间移动无限距离，也就是默认在方格内部游动是不耗时的。
当然，在游泳的时候你必须待在坐标方格里面。
从坐标方格的左上平台(0，0)出发。返回到达坐标方格的右下平台(n-1,n-1)所需的最少时间。

示例1:
输入：grid = [[0,2],
             [1,3]]
输出：3
解释：时间为0时，位于坐标方格的位置为(0,0)。
     此时不能游向任意方向，因为四个相邻方向平台的高度都大于当前时间为0时的水位。
     等时间到达3时，才可以游向平台(1,1)。
     因为此时的水位是3，坐标方格中的平台没有比水位3更高的，所以可以游向坐标方格中的任意位置

示例2:
输入：grid = [[0,1,2,3,4],
             [24,23,22,21,5],
             [12,13,14,15,16],
             [11,17,18,19,20],
             [10,9,8,7,6]]
输出：16
解释：最终的路线用加粗进行了标记。
     我们必须等到时间为16，此时才能保证平台(0,0)和(4,4)是连通的


提示:
n == grid.length
n == grid[i].length
1 <= n <= 50
0 <= grid[i][j] < n^2
grid[i][j]中每个值均无重复
*/

// 二分查找
class Solution {
 public:
  bool check(vector<vector<int>>& grid, int threshold) {
    if (grid[0][0] > threshold) {
      return false;
    }
    int n = grid.size();
    vector<vector<int>> visited(n, vector<int>(n, 0));
    visited[0][0] = 1;
    queue<pair<int, int>> q;
    q.push(make_pair(0, 0));

    vector<pair<int, int>> directions{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    while (!q.empty()) {
      auto [i, j] = q.front();
      q.pop();

      for (const auto [di, dj] : directions) {
        int ni = i + di, nj = j + dj;
        if (ni >= 0 && ni < n && nj >= 0 && nj < n) {
          if (visited[ni][nj] == 0 && grid[ni][nj] <= threshold) {
            q.push(make_pair(ni, nj));
            visited[ni][nj] = 1;
          }
        }
      }
    }
    return visited[n - 1][n - 1] == 1;
  }

  int swimInWater(vector<vector<int>>& grid) {
    int n = grid.size();
    int left = 0, right = n * n - 1;
    while (left < right) {
      int mid = (left + right) / 2;
      if (check(grid, mid)) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }
    return left;
  }
};

// 二分查找
class Solution {
 public:
  vector<vector<int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  int swimInWater(vector<vector<int>>& grid) {
    int n = grid.size();
    auto check = [&](int t) -> bool {
      if (grid[0][0] > t) return false;  // 初始节点不满足，直接返回
      queue<vector<int>> q;
      vector<vector<int>> vis(n, vector<int>(n, 0));
      q.push({0, 0});
      vis[0][0] = 1;
      while (!q.empty()) {
        vector<int> cur = q.front();
        q.pop();
        for (auto& dir : dirs) {
          int x = cur[0] + dir[0], y = cur[1] + dir[1];
          if (x >= 0 && x < n && y >= 0 && y < n && grid[x][y] <= t &&
              !vis[x][y]) {
            q.push({x, y});
            vis[x][y] = 1;
          }
        }
      }
      return vis[n - 1][n - 1] == 1;
    };
    // 开区间二分
    int left = -1, right = n * n;
    while (left + 1 < right) {
      int mid = left + (right - left) / 2;
      // t越小，越不满足，因此check为true时，往左侧区间搜索：
      (check(mid) ? right : left) = mid;
    }
    return right;
  }
};

// 堆（优先队列）

// 并查集
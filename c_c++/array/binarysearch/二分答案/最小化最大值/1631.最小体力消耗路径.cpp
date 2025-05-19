/*
准备参加一场远足活动。给一个二维rowsxcolumns的地图heights，
其中heights[row][col]表示格子(row,col)的高度。
一开始在最左上角的格子(0,0)，且希望去最右下角的格子(rows-1,columns-1)（下标从0开始）。
每次可以往上，下，左，右四个方向之一移动，想要找到耗费体力最小的一条路径。
一条路径耗费的体力值是路径上相邻格子之间高度差绝对值的最大值决定的。
请返回从左上角走到右下角的最小体力消耗值。

示例1：
输入：heights = [[1,2,2],
                [3,8,2],
                [5,3,5]]
输出：2
解释：路径[1,3,5,3,5]连续格子的差值绝对值最大为2。
这条路径比路径[1,2,2,2,5]更优，因为另一条路径差值最大值为3。

示例2：
输入：heights = [[1,2,3],
                [3,8,4],
                [5,3,5]]
输出：1
解释：路径[1,2,3,4,5]的相邻格子差值绝对值最大为1，比路径[1,3,5,3,5]更优。

示例3：
输入：heights = [[1,2,1,1,1],
                [1,2,1,2,1],
                [1,2,1,2,1],
                [1,2,1,2,1],
                [1,1,1,2,1]]
输出：0
解释：上图所示路径不需要消耗任何体力。


提示：
rows == heights.length
columns == heights[i].length
1 <= rows, columns <= 100
1 <= heights[i][j] <= 106
*/

class Solution {
  static constexpr int dx[4] = {0, 1, 0, -1};
  static constexpr int dy[4] = {1, 0, -1, 0};

 public:
  int minimumEffortPath(vector<vector<int>>& heights) {
    int n = heights.size();
    int m = heights[0].size();
    auto check = [&](int k) -> bool {  // 不写->bool会崩溃，什么原因
      vector<vector<bool>> vis(n, vector<bool>(m));
      vis[0][0] = true;
      vector<pair<int, int>> q = {{0, 0}};
      while (!q.empty()) {
        pair<int, int> cur = q.back();
        q.pop_back();
        int x = cur.first;
        int y = cur.second;
        for (int i = 0; i < 4; ++i) {
          int nx = x + dx[i];
          int ny = y + dy[i];
          if (0 <= nx && nx < n && 0 <= ny && ny < m && !vis[nx][ny] &&
              abs(heights[x][y] - heights[nx][ny]) <= k) {
            vis[nx][ny] = true;
            q.push_back({nx, ny});
          }
        }
      }
      return vis[n - 1][m - 1];
    };

    int left = 0;
    int right = 1000000;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (check(mid)) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    return left;
  }
};

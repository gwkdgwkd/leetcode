/*
给一个下标从0开始、大小为nxn的二维矩阵grid，其中(r,c)表示：
如果grid[r][c] = 1，则表示一个存在小偷的单元格
如果grid[r][c] = 0，则表示一个空单元格
最开始位于单元格(0, 0)。
在一步移动中，可以移动到矩阵中的任一相邻单元格，包括存在小偷的单元格。
矩阵中路径的安全系数定义为：
从路径中任一单元格到矩阵中任一小偷所在单元格的最小曼哈顿距离。
返回所有通向单元格(n-1, n-1)的路径中的 最大安全系数。
单元格(r, c)的某个相邻单元格，
是指在矩阵中存在的(r,c+1)、(r,c-1)、(r+1,c)和(r-1,c) 之一。
两个单元格(a, b)和(x, y)之间的曼哈顿距离等于| a - x |+| b - y |，
其中|val|表示val的绝对值。

示例1：
输入：grid = [[1,0,0],[0,0,0],[0,0,1]]
输出：0
解释：从(0,0)到(n-1,n-1)的每条路径都经过存在小偷的单元格(0,0)和(n-1,n-1)。

示例2：
输入：grid = [[0,0,1],[0,0,0],[0,0,0]]
输出：2
解释：上图所示路径的安全系数为2：
     该路径上距离小偷所在单元格（02）最近的单元格是（0，0）。
     它们之间的曼哈顿距离为|0 - 0| + |0 - 2| = 2。
     可以证明，不存在安全系数更高的其他路径。

示例3：
输入：grid = [[0,0,0,1],[0,0,0,0],[0,0,0,0],[1,0,0,0]]
输出：2
解释：上图所示路径的安全系数为2：
     该路径上距离小偷所在单元格（0，3）最近的单元格是（1，2）。
     它们之间的曼哈顿距离为| 0 - 1 | + | 3 - 2 | = 2。
     该路径上距离小偷所在单元格（3，0）最近的单元格是（3，2）。
     它们之间的曼哈顿距离为| 3 - 3 | + | 0 - 2 | = 2。
     可以证明，不存在安全系数更高的其他路径。


提示：
1 <= grid.length == n <= 400
grid[i].length == n
grid[i][j]为0或1
grid 至少存在一个小偷
*/

// 多源BFS + 倒序枚举答案 + 并查集
class Solution {
  static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

 public:
  int maximumSafenessFactor(vector<vector<int>> &grid) {
    int n = grid.size();
    vector<pair<int, int>> q;
    vector<vector<int>> dis(n, vector<int>(n, -1));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j]) {
          q.emplace_back(i, j);
          dis[i][j] = 0;
        }
      }
    }

    vector<vector<pair<int, int>>> groups = {q};
    while (!q.empty()) {  // 多源BFS
      vector<pair<int, int>> nq;
      for (auto &[i, j] : q) {
        for (auto &d : dirs) {
          int x = i + d[0], y = j + d[1];
          if (0 <= x && x < n && 0 <= y && y < n && dis[x][y] < 0) {
            nq.emplace_back(x, y);
            dis[x][y] = groups.size();
          }
        }
      }

      groups.push_back(nq);  // 相同dis分组记录
      q = move(nq);
    }

    // 并查集模板
    vector<int> fa(n * n);
    iota(fa.begin(), fa.end(), 0);
    function<int(int)> find = [&](int x) -> int {
      return fa[x] == x ? x : fa[x] = find(fa[x]);
    };

    for (int ans = (int)groups.size() - 2; ans > 0; ans--) {
      for (auto &[i, j] : groups[ans]) {
        for (auto &d : dirs) {
          int x = i + d[0], y = j + d[1];
          if (0 <= x && x < n && 0 <= y && y < n && dis[x][y] >= dis[i][j])
            fa[find(x * n + y)] = find(i * n + j);
        }
      }

      if (find(0) == find(n * n - 1))  // 写这里判断更快些
        return ans;
    }

    return 0;
  }
};

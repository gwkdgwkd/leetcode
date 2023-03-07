/*
给你一个大小为mxn的二进制矩阵grid，岛屿是由一些相邻的1(代表土地)构成的组合，
这里的相邻要求两个1必须在水平或者竖直的四个方向上相邻。
可以假设grid的四个边缘都被0（代表水）包围着，岛屿的面积是岛上值为1的单元格的数目。
计算并返回grid中最大的岛屿面积，如果没有岛屿，则返回面积为0。

示例1：
输入：grid =
[
  [0,0,1,0,0,0,0,1,0,0,0,0,0],
  [0,0,0,0,0,0,0,1,1,1,0,0,0],
  [0,1,1,0,1,0,0,0,0,0,0,0,0],
  [0,1,0,0,1,1,0,0,1,0,1,0,0],
  [0,1,0,0,1,1,0,0,1,1,1,0,0],
  [0,0,0,0,0,0,0,0,0,0,1,0,0],
  [0,0,0,0,0,0,0,1,1,1,0,0,0],
  [0,0,0,0,0,0,0,1,1,0,0,0,0]
]
输出：6
解释：答案不应该是11，因为岛屿只能包含水平或垂直这四个方向上的1。

示例2：
输入：grid = [[0,0,0,0,0,0,0,0]]
输出：0

提示：
m == grid.length
n == grid[i].length
1 <= m, n <= 50
grid[i][j]为0或1
*/

// DFS
int dfs(int** grid, int gridSize, int* gridColSize, int row, int col) {
  // 越界处理
  if (row < 0 || row >= gridSize || col < 0 || col >= gridColSize[0] ||
      grid[row][col] == 0)
    return 0;
  // 每次计算后清零
  grid[row][col] = 0;
  // dfs处理
  return 1 + dfs(grid, gridSize, gridColSize, row + 1, col) +
         dfs(grid, gridSize, gridColSize, row - 1, col) +
         dfs(grid, gridSize, gridColSize, row, col + 1) +
         dfs(grid, gridSize, gridColSize, row, col - 1);
}

int maxAreaOfIsland(int** grid, int gridSize, int* gridColSize) {
  int area = 0;
  int max = 0;
  // 遍历二维数组
  for (int i = 0; i < gridSize; i++) {
    for (int j = 0; j < gridColSize[0]; j++) {
      area = dfs(grid, gridSize, gridColSize, i, j);
      max = max > area ? max : area;
    }
  }
  return max;
}

// DFS
class Solution {
  int m;
  int n;
  int maxLand = 0;
  int dfs(vector<vector<int>>& grid, int x, int y) {
    if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == 0) {
      return 0;
    }
    grid[x][y] = 0;
    return 1 + dfs(grid, x - 1, y) + dfs(grid, x + 1, y) + dfs(grid, x, y - 1) +
           dfs(grid, x, y + 1);
  }

 public:
  int maxAreaOfIsland(vector<vector<int>>& grid) {
    m = grid.size();
    n = grid[0].size();
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        maxLand = max(maxLand, dfs(grid, i, j));
      }
    }

    return maxLand;
  }
};

// BFS
#define f first
#define s second
const int dx[] = {0, -1, 0, 1};
const int dy[] = {1, 0, -1, 0};
typedef pair<int, int> PII;
class Solution {
 public:
  int maxAreaOfIsland(vector<vector<int>>& grid) {
    int ans = 0;
    int n = grid.size();
    int m = grid[0].size();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        if (grid[i][j] == 1) {
          int cnt = 0;
          grid[i][j] = 0;
          cnt++;
          queue<PII> q;
          q.push({i, j});
          while (q.size()) {
            PII t = q.front();
            q.pop();
            for (int i = 0; i < 4; ++i) {
              int a = t.f + dx[i];
              int b = t.s + dy[i];
              if (a >= 0 && a < n && b >= 0 && b < m && grid[a][b] == 1) {
                grid[a][b] = 0;
                cnt++;
                q.push({a, b});
              }
            }
          }
          ans = max(ans, cnt);
        }
      }
    return ans;
  }
};
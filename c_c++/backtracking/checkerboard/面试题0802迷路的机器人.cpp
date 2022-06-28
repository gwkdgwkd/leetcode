/*
设想有个机器人坐在一个网格的左上角，网格r行c列。
机器人只能向下或向右移动，但不能走到一些被禁止的网格（有障碍物）。
设计一种算法，寻找机器人从左上角移动到右下角的路径。
网格中的障碍物和空位置分别用1和0来表示。
返回一条可行的路径，路径由经过的网格的行号和列号组成。
左上角为0行0列。如果没有可行的路径，返回空数组。

示例1:
输入:
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
输出: [[0,0],[0,1],[0,2],[1,2],[2,2]]
解释:
输入中标粗的位置即为输出表示的路径，即
0行0列（左上角） -> 0行1列 -> 0行2列 -> 1行2列 -> 2行2列（右下角）

说明：r和c的值均不超过100。
*/

void backTrace(int** obstacleGrid, int rowSize, int colSize, int row, int col,
               int** ret, int* returnSize, bool* arrived, int depth,
               bool visited[][100]) {
  if (row >= rowSize || col >= colSize || obstacleGrid[row][col] == 1 ||
      *arrived || visited[row][col])
    return;

  // add this grid to ret
  visited[row][col] = 1;
  ret[depth][0] = row;
  ret[depth][1] = col;

  if (row == (rowSize - 1) && col == (colSize - 1)) {
    *arrived = 1;
    *returnSize = depth + 1;
  } else {
    backTrace(obstacleGrid, rowSize, colSize, row, col + 1, ret, returnSize,
              arrived, depth + 1, visited);
    backTrace(obstacleGrid, rowSize, colSize, row + 1, col, ret, returnSize,
              arrived, depth + 1, visited);
  }
}
int** pathWithObstacles(int** obstacleGrid, int obstacleGridSize,
                        int* obstacleGridColSize, int* returnSize,
                        int** returnColumnSizes) {
  *returnSize = 0;

  int** ret = malloc(sizeof(int*) * 200);

  for (int i = 0; i < 200; i++) ret[i] = malloc(sizeof(int) * 2);

  bool arrived = 0;

  bool visited[100][100];
  for (int i = 0; i < obstacleGridSize; i++)
    memset(visited[i], 0, sizeof(bool) * (*obstacleGridColSize));

  backTrace(obstacleGrid, obstacleGridSize, *obstacleGridColSize, 0, 0, ret,
            returnSize, &arrived, 0, visited);

  if (arrived) {
    *returnColumnSizes = malloc(sizeof(int) * (*returnSize));

    for (int i = 0; i < *returnSize; i++) (*returnColumnSizes)[i] = 2;
  } else
    *returnSize = 0;

  return ret;
}

class Solution {
  vector<vector<int>> res;
  vector<vector<bool>> used;
  bool arrived;
  int dir[2][2] = {{0, 1}, {1, 0}};

 public:
  void dfs(vector<vector<int>>& obstacleGrid, int row, int col) {
    if (arrived) return;

    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();
    if (row == m - 1 && col == n - 1) {
      arrived = true;
      return;
    }
    for (int d = 0; d < 2 && !arrived; ++d) {
      int newRow = row + dir[d][0];
      int newCol = col + dir[d][1];
      if (newRow >= 0 && newCol >= 0 && newRow < m && newCol < n) {
        if (!used[newRow][newCol] && !obstacleGrid[newRow][newCol]) {
          used[newRow][newCol] = true;
          res.push_back({newRow, newCol});
          dfs(obstacleGrid, newRow, newCol);
          if (!arrived) {
            // 如果前后左右都能走，那么回溯的时候visited要置成false
            // visited[newRow][newCol] = false;
            res.pop_back();
          }
        }
      }
    }
  }
  vector<vector<int>> pathWithObstacles(vector<vector<int>>& obstacleGrid) {
    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();
    if (obstacleGrid[0][0] || obstacleGrid[m - 1][n - 1]) {
      return res;
    }
    arrived = false;
    used.assign(m, vector<bool>(n, false));

    used[0][0] = true;
    res.push_back({0, 0});
    dfs(obstacleGrid, 0, 0);
    if (!arrived) {
      res.resize(0);
    }
    return res;
  }
};
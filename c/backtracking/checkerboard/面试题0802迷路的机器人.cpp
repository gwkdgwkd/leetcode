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
  vector<vector<int>> ans;
  int size;
  bool arrived;

 public:
  void dfs(vector<vector<int>>& obstacleGrid, int row, int col, int index,
           vector<vector<int>>& used) {
    if (row >= obstacleGrid.size() || col >= obstacleGrid[row].size() ||
        arrived || obstacleGrid[row][col] || used[row][col]) {
      return;
    }

    used[row][col] = 1;
    ans[index][0] = row;
    ans[index][1] = col;

    if (row == obstacleGrid.size() - 1 && col == obstacleGrid[row].size() - 1) {
      arrived = true;
      size = index + 1;
    } else {
      dfs(obstacleGrid, row + 1, col, index + 1, used);
      dfs(obstacleGrid, row, col + 1, index + 1, used);
    }
  }
  vector<vector<int>> pathWithObstacles(vector<vector<int>>& obstacleGrid) {
    vector<vector<int>> used;
    for (int i = 0; i < obstacleGrid.size(); ++i) {
      used.emplace_back(vector(obstacleGrid[i].size(), 0));
    }

    arrived = false;
    int len = obstacleGrid.size() + obstacleGrid[0].size();
    ans.resize(len);
    for (int i = 0; i < len; ++i) {
      ans[i].resize(2);
    }
    size = 0;
    dfs(obstacleGrid, 0, 0, 0, used);
    if (arrived == false) {
      ans.clear();
    }
    ans.resize(size);
    return ans;
  }
};
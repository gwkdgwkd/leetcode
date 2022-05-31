/*
给定一个m x n整数矩阵matrix，找出其中最长递增路径的长度。
对于每个单元格，你可以往上，下，左，右四个方向移动。
你不能在对角线方向上移动或移动到边界外（即不允许环绕）。

示例1：
输入：matrix = [[9,9,4],[6,6,8],[2,1,1]]
输出：4
解释：最长递增路径为[1, 2, 6, 9]。

示例2：
输入：matrix = [[3,4,5],[3,2,6],[2,2,1]]
输出：4
解释：最长递增路径是[3, 4, 5, 6]。注意不允许在对角线方向上移动。

示例3：
输入：matrix = [[1]]
输出：1

提示：
m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
0 <= matrix[i][j] <= 2^31 - 1
*/

// 剑指OfferII112最长递增路径

// 记忆化深度优先搜索：
// 将矩阵看成一个有向图，每个单元格对应图中的一个节点，如果相邻的两个单元格的值不相等，
// 则在相邻的两个单元格之间存在一条从较小值指向较大值的有向边。问题转化成在有向图中寻找最长路径。
// 深度优先搜索是非常直观的方法。
// 从一个单元格开始进行深度优先搜索，即可找到从该单元格开始的最长递增路径。
// 对每个单元格分别进行深度优先搜索之后，即可得到矩阵中的最长递增路径的长度。
// 但是如果使用朴素深度优先搜索，时间复杂度是指数级，会超出时间限制，因此必须加以优化。
// 朴素深度优先搜索的时间复杂度过高的原因是进行了大量的重复计算，
// 同一个单元格会被访问多次，每次访问都要重新计算。
// 由于同一个单元格对应的最长递增路径的长度是固定不变的，因此可以使用记忆化的方法进行优化。
// 用矩阵memo作为缓存矩阵，已经计算过的单元格的结果存储到缓存矩阵中。
// 使用记忆化深度优先搜索，当访问到一个单元格(i,j)时，如果memo[i][j]≠0，
// 说明该单元格的结果已经计算过，则直接从缓存中读取结果，如果memo[i][j]=0，
// 说明该单元格的结果尚未被计算过，则进行搜索，并将计算得到的结果存入缓存中。
// 遍历完矩阵中的所有单元格之后，即可得到矩阵中的最长递增路径的长度。
// 时间复杂度：O(mn)
// 空间复杂度：O(mn)
const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int rows, columns;
int dfs(int** matrix, int row, int column, int** memo) {
  if (memo[row][column] != 0) {
    return memo[row][column];
  }
  ++memo[row][column];
  for (int i = 0; i < 4; ++i) {
    int newRow = row + dirs[i][0], newColumn = column + dirs[i][1];
    if (newRow >= 0 && newRow < rows && newColumn >= 0 && newColumn < columns &&
        matrix[newRow][newColumn] > matrix[row][column]) {
      memo[row][column] =
          fmax(memo[row][column], dfs(matrix, newRow, newColumn, memo) + 1);
    }
  }
  return memo[row][column];
}
int longestIncreasingPath(int** matrix, int matrixSize, int* matrixColSize) {
  if (matrixSize == 0 || matrixColSize[0] == 0) {
    return 0;
  }
  rows = matrixSize;
  columns = matrixColSize[0];

  int** memo = (int**)malloc(sizeof(int*) * rows);
  for (int i = 0; i < rows; i++) {
    memo[i] = (int*)malloc(sizeof(int) * columns);
    memset(memo[i], 0, sizeof(int) * columns);
  }
  int ans = 0;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      ans = fmax(ans, dfs(matrix, i, j, memo));
    }
  }
  free(memo);
  return ans;
}

// 拓扑排序
// 时间复杂度：O(mn)
// 空间复杂度：O(mn)
const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int rows, columns;
typedef struct point {
  int x, y;
} point;
int longestIncreasingPath(int** matrix, int matrixSize, int* matrixColSize) {
  if (matrixSize == 0 || matrixColSize[0] == 0) {
    return 0;
  }
  rows = matrixSize;
  columns = matrixColSize[0];

  int** outdegrees = (int**)malloc(sizeof(int*) * rows);
  for (int i = 0; i < rows; i++) {
    outdegrees[i] = (int*)malloc(sizeof(int) * columns);
    memset(outdegrees[i], 0, sizeof(int) * columns);
  }
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      for (int k = 0; k < 4; ++k) {
        int newRow = i + dirs[k][0], newColumn = j + dirs[k][1];
        if (newRow >= 0 && newRow < rows && newColumn >= 0 &&
            newColumn < columns && matrix[newRow][newColumn] > matrix[i][j]) {
          ++outdegrees[i][j];
        }
      }
    }
  }

  point* q = (point*)malloc(sizeof(point) * rows * columns);
  int l = 0, r = 0;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      if (outdegrees[i][j] == 0) {
        q[r++] = (point){i, j};
      }
    }
  }
  int ans = 0;
  while (l < r) {
    ++ans;
    int size = r - l;
    for (int i = 0; i < size; ++i) {
      point cell = q[l++];
      int row = cell.x, column = cell.y;
      for (int k = 0; k < 4; ++k) {
        int newRow = row + dirs[k][0], newColumn = column + dirs[k][1];
        if (newRow >= 0 && newRow < rows && newColumn >= 0 &&
            newColumn < columns &&
            matrix[newRow][newColumn] < matrix[row][column]) {
          --outdegrees[newRow][newColumn];
          if (outdegrees[newRow][newColumn] == 0) {
            q[r++] = (point){newRow, newColumn};
          }
        }
      }
    }
  }
  return ans;
}

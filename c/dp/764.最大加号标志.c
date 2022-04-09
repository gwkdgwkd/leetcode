/*
在一个n x n的矩阵grid中，除了在数组mines中给出的元素为0，其他每个元素都为1。
mines[i] = [xi, yi]表示grid[xi][yi] == 0
返回grid中包含1的最大的轴对齐加号标志的阶数。如果未找到加号标志，则返回0。
一个k阶由1组成的“轴对称”加号标志具有中心网格grid[r][c] == 1，
以及4个从中心向上、向下、向左、向右延伸，长度为k-1，由1组成的臂。
注意，只有加号标志的所有网格要求为1，别的网格可能为0也可能为1。

示例1：
输入: n = 5, mines = [[4, 2]]
输出: 2
解释: 在上面的网格中，最大加号标志的阶只能是2。一个标志已在图中标出。

示例2：
输入: n = 1, mines = [[0, 0]]
输出: 0
解释: 没有加号标志，返回0。

提示：
1 <= n <= 500
1 <= mines.length <= 5000
0 <= xi, yi < n
每一对(xi, yi)都不重复​​​​​​​
*/

// 动态规划
#define MAX_GRID_SIZE 500
#define MIN(a, b) (((a) > (b)) ? (b) : (a))
#define MIN_FOUR(a, b, c, d) MIN(MIN(a, b), MIN(c, d))
typedef struct tagGridNode {
  int flag;
  int up;
  int down;
  int left;
  int right;
} GRID_NODE;

int orderOfLargestPlusSign(int N, int** mines, int minesSize,
                           int* minesColSize) {
  GRID_NODE grid[MAX_GRID_SIZE][MAX_GRID_SIZE] = {0};
  int i, j;
  int stage = 0;
  int curStage = 0;
  GRID_NODE* PNode = NULL;

  if (mines == NULL || minesSize == 0) {
    return (N + 1) / 2;
  }

  for (i = 0; i < minesSize; i++) {
    grid[mines[i][0]][mines[i][1]].flag = 1;
  }

  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      PNode = &grid[i][j];
      if (PNode->flag == 0) {
        PNode->left = 1;
        PNode->up = 1;
        if (j > 0) {
          PNode->left += grid[i][j - 1].left;
        }

        if (i > 0) {
          PNode->up += grid[i - 1][j].up;
        }
      }
    }
  }

  for (i = N - 1; i >= 0; i--) {
    for (j = N - 1; j >= 0; j--) {
      PNode = &grid[i][j];
      if (PNode->flag == 0) {
        PNode->right = 1;
        PNode->down = 1;
        if (i < N - 1) {
          PNode->down += grid[i + 1][j].down;
        }

        if (j < N - 1) {
          PNode->right += grid[i][j + 1].right;
        }

        curStage = MIN_FOUR(PNode->left, PNode->right, PNode->up, PNode->down);
        if (curStage > stage) {
          stage = curStage;
        }
      }
    }
  }

  return stage;
}

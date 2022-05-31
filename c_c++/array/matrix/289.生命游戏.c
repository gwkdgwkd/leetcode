/*
生命游戏，简称为生命，是英国数学家约翰·何顿·康威在1970年发明的细胞自动机。
给定一个包含m × n个格子的面板，每一个格子都可以看成是一个细胞。
每个细胞都具有一个初始状态：1即为活细胞（live），或0即为死细胞（dead）。
每个细胞与其八个相邻位置（水平，垂直，对角线）的细胞都遵循以下四条生存定律：
1.如果活细胞周围八个位置的活细胞数少于两个，则该位置活细胞死亡；
2.如果活细胞周围八个位置有两个或三个活细胞，则该位置活细胞仍然存活；
3.如果活细胞周围八个位置有超过三个活细胞，则该位置活细胞死亡；
4.如果死细胞周围正好有三个活细胞，则该位置死细胞复活；
下一个状态是通过将上述规则同时应用于当前状态下的每个细胞所形成的，其中细胞的出生和死亡是同时发生的。
给你m x n网格面板board的当前状态，返回下一个状态。

示例1：
输入：board = [[0,1,0],
              [0,0,1],
              [1,1,1],
              [0,0,0]]
输出：[[0,0,0],
      [1,0,1],
      [0,1,1],
      [0,1,0]]

示例2：
输入：board = [[1,1],[1,0]]
输出：[[1,1],[1,1]]

提示：
m == board.length
n == board[i].length
1 <= m, n <= 25
board[i][j]为0或1

进阶：
你可以使用原地算法解决本题吗？
请注意，面板上所有格子需要同时被更新：你不能先更新某些格子，然后使用它们的更新后的值再更新其他格子。
本题中，我们使用二维数组来表示面板。
原则上，面板是无限的，但当活细胞侵占了面板边界时会造成问题。你将如何解决这些问题？
*/

// 复制原数组进行模拟
void gameOfLife(int** board, int boardSize, int* boardColSize) {
  int neighbors[3] = {0, 1, -1};

  int rows = boardSize;
  int cols = boardColSize[0];

  int copyBoard[rows][cols];
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      copyBoard[row][col] = board[row][col];
    }
  }

  // 遍历面板每一个格子里的细胞
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      // 对于每一个细胞统计其八个相邻位置里的活细胞数量
      int liveNeighbors = 0;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          if (!(neighbors[i] == 0 && neighbors[j] == 0)) {
            int r = (row + neighbors[i]);
            int c = (col + neighbors[j]);
            // 查看相邻的细胞是否是活细胞
            if ((r < rows && r >= 0) && (c < cols && c >= 0) &&
                (copyBoard[r][c] == 1)) {
              liveNeighbors += 1;
            }
          }
        }
      }

      // 规则1或规则3
      if ((copyBoard[row][col] == 1) &&
          (liveNeighbors < 2 || liveNeighbors > 3)) {
        board[row][col] = 0;
      }
      // 规则4
      if (copyBoard[row][col] == 0 && liveNeighbors == 3) {
        board[row][col] = 1;
      }
    }
  }
}

void gameOfLife(int** board, int boardSize, int* boardColSize) {
  int neighbors[3] = {0, 1, -1};

  int rows = boardSize;
  int cols = boardColSize[0];

  // 遍历面板每一个格子里的细胞
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      // 对于每一个细胞统计其八个相邻位置里的活细胞数量
      int liveNeighbors = 0;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          if (!(neighbors[i] == 0 && neighbors[j] == 0)) {
            // 相邻位置的坐标
            int r = (row + neighbors[i]);
            int c = (col + neighbors[j]);

            // 查看相邻的细胞是否是活细胞
            if ((r < rows && r >= 0) && (c < cols && c >= 0) &&
                (abs(board[r][c]) == 1)) {
              liveNeighbors += 1;
            }
          }
        }
      }

      // 规则1或规则3
      if ((board[row][col] == 1) && (liveNeighbors < 2 || liveNeighbors > 3)) {
        board[row][col] = -1;  // -1代表这个细胞过去是活的现在死了
      }
      // 规则4
      if (board[row][col] == 0 && liveNeighbors == 3) {
        board[row][col] = 2;  // 2代表这个细胞过去是死的现在活了
      }
    }
  }

  // 遍历board得到一次更新后的状态
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (board[row][col] > 0) {
        board[row][col] = 1;
      } else {
        board[row][col] = 0;
      }
    }
  }
}
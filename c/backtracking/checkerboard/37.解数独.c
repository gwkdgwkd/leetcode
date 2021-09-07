/*
 * @lc app=leetcode.cn id=37 lang=c
 *
 * [37] 解数独
 */

// @lc code=start

// N皇后问题是因为每⼀⾏每⼀列只放⼀个皇后，只需要⼀层for循环遍历⼀⾏，递归来来遍历列，然后⼀⾏⼀列确定皇后的唯⼀位置。
// 本题中棋盘的每⼀个位置都要放⼀个数字，并检查数字是否合法，解数独的树形结构要⽐N皇后更宽更深。

int isValid(int row, int col, char val, char** board) {
  for (int i = 0; i < 9; i++) {  // 判断⾏⾥是否重复
    if (board[row][i] == val) {
      return 0;
    }
  }
  for (int j = 0; j < 9; j++) {  // 判断列⾥是否重复
    if (board[j][col] == val) {
      return 0;
    }
  }
  int startRow = (row / 3) * 3;
  int startCol = (col / 3) * 3;
  for (int i = startRow; i < startRow + 3; i++) {  // 判断9⽅格⾥是否重复
    for (int j = startCol; j < startCol + 3; j++) {
      if (board[i][j] == val) {
        return 0;
      }
    }
  }
  return 1;
}
int backtracking(char** board, int boardSize, int* boardColSize) {
  // 题递归不⽤终⽌条件，解数独是要遍历整个树形结构寻找可能的叶⼦节点就⽴刻返回。不⽤终⽌条件会不会死循环？
  // 递归的下⼀层的棋盘⼀定⽐上⼀层的棋盘多⼀个数，等数填满了棋盘⾃然就终⽌（填满当然好了，说明找到结果了），所以不需要终⽌条件！

  // ⼀个for循环遍历棋盘的⾏，⼀个for循环遍历棋盘的列，⼀⾏⼀列确定下来之后，递归遍历这个位置放9个数字的可能性！
  for (int i = 0; i < boardSize; i++) {        // 遍历⾏
    for (int j = 0; j < *boardColSize; j++) {  // 遍历列
      if (board[i][j] != '.') {
        continue;
      }
      for (char k = '1'; k <= '9'; k++) {  // (i, j) 这个位置放k是否合适
        if (isValid(i, j, k, board)) {
          board[i][j] = k;  // 放置k
          if (backtracking(board, boardSize, boardColSize)) {
            return 1;  // 如果找到合适⼀组⽴刻返回
          }
          board[i][j] = '.';  // 回溯，撤销k
        }
      }

      // 为什么没有终⽌条件也不会永远填不满棋盘⽽⽆限递归下去？
      // 如果⼀⾏⼀列确定下来了，这⾥尝试了9个数都不⾏，说明这个棋盘找不到解决数独问题的解！那么会直接返回。
      return 0;  // 9个数都试完了，都不⾏，那么就返回false
    }
  }

  // 因为解数独找到⼀个符合的条件（就在树的叶⼦节点上）⽴刻就返回，相当于找从根节点到叶⼦节点⼀条唯⼀路径，所以需要使⽤bool返回值
  return 1;  // 遍历完没有返回false，说明找到了合适棋盘位置了
}
void solveSudoku(char** board, int boardSize, int* boardColSize) {
  backtracking(board, boardSize, boardColSize);
}
// @lc code=end

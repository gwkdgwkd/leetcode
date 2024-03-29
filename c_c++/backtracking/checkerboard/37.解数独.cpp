/*
编写一个程序，通过填充空格来解决数独问题。
数独的解法需 遵循如下规则：
数字1-9在每一行只能出现一次。
数字1-9在每一列只能出现一次。
数字1-9在每一个以粗实线分隔的3x3宫内只能出现一次。
数独部分空格内已填入了数字，空白格用'.'表示。

示例1：
输入：board = [["5","3",".",".","7",".",".",".","."],
              ["6",".",".","1","9","5",".",".","."],
              [".","9","8",".",".",".",".","6","."],
              ["8",".",".",".","6",".",".",".","3"],
              ["4",".",".","8",".","3",".",".","1"],
              ["7",".",".",".","2",".",".",".","6"],
              [".","6",".",".",".",".","2","8","."],
              [".",".",".","4","1","9",".",".","5"],
              [".",".",".",".","8",".",".","7","9"]]
输出：[["5","3","4","6","7","8","9","1","2"],
      ["6","7","2","1","9","5","3","4","8"],
      ["1","9","8","3","4","2","5","6","7"],
      ["8","5","9","7","6","1","4","2","3"],
      ["4","2","6","8","5","3","7","9","1"],
      ["7","1","3","9","2","4","8","5","6"],
      ["9","6","1","5","3","7","2","8","4"],
      ["2","8","7","4","1","9","6","3","5"],
      ["3","4","5","2","8","6","1","7","9"]]
解释：输入的数独如上图所示，唯一有效的解决方案如下所示：

提示：
board.length == 9
board[i].length == 9
board[i][j]是一位数字或者'.'
题目数据保证输入数独仅有一个解
*/

// N皇后问题是因为每⼀⾏每⼀列只放⼀个皇后，只需要⼀层for循环遍历⼀⾏，
// 递归来来遍历列，然后⼀⾏⼀列确定皇后的唯⼀位置。
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
  // 题递归不⽤终⽌条件，解数独是要遍历整个树形结构寻找可能的叶⼦节点就⽴刻返回。
  // 不⽤终⽌条件会不会死循环？
  // 递归的下⼀层的棋盘⼀定⽐上⼀层的棋盘多⼀个数，
  // 等数填满了棋盘⾃然就终⽌（填满当然好了，说明找到结果了），所以不需要终⽌条件！

  // ⼀个for循环遍历棋盘的⾏，⼀个for循环遍历棋盘的列，
  // ⼀⾏⼀列确定下来之后，递归遍历这个位置放9个数字的可能性！
  for (int i = 0; i < boardSize; i++) {        // 遍历⾏
    for (int j = 0; j < *boardColSize; j++) {  // 遍历列
      if (board[i][j] != '.') {
        continue;
      }
      for (char k = '1'; k <= '9'; k++) {  // (i,j)这个位置放k是否合适
        if (isValid(i, j, k, board)) {
          board[i][j] = k;  // 放置k
          if (backtracking(board, boardSize, boardColSize)) {
            return 1;  // 如果找到合适⼀组⽴刻返回
          }
          board[i][j] = '.';  // 回溯，撤销k
        }
      }

      // 为什么没有终⽌条件也不会永远填不满棋盘⽽⽆限递归下去？
      // 如果⼀⾏⼀列确定下来了，这⾥尝试了9个数都不⾏，
      // 说明这个棋盘找不到解决数独问题的解！那么会直接返回。
      return 0;  // 9个数都试完了，都不⾏，那么就返回false
    }
  }

  // 因为解数独找到⼀个符合的条件（就在树的叶⼦节点上）⽴刻就返回，
  // 相当于找从根节点到叶⼦节点⼀条唯⼀路径，所以需要使⽤bool返回值
  return 1;  // 遍历完没有返回false，说明找到了合适棋盘位置了
}
void solveSudoku(char** board, int boardSize, int* boardColSize) {
  backtracking(board, boardSize, boardColSize);
}

class Solution {
 public:
  bool isValid(vector<vector<char>>& board, char val, int row, int col) {
    for (int i = 0; i < 9; ++i) {
      if (board[i][col] == val) {
        return false;
      }
    }

    for (int j = 0; j < 9; ++j) {
      if (board[row][j] == val) {
        return false;
      }
    }

    int newrow = (row / 3) * 3;
    int newcol = (col / 3) * 3;
    for (int i = newrow; i < newrow + 3; ++i) {
      for (int j = newcol; j < newcol + 3; ++j) {
        if (board[i][j] == val) {
          return false;
        }
      }
    }

    return true;
  }

  bool backtracking(vector<vector<char>>& board) {
    for (int i = 0; i < board.size(); ++i) {
      for (int j = 0; j < board[i].size(); ++j) {
        if (board[i][j] != '.') {
          continue;
        }
        for (char k = '1'; k <= '9'; ++k) {
          if (isValid(board, k, i, j)) {
            board[i][j] = k;
            if (backtracking(board)) {
              return true;
            }
            board[i][j] = '.';
          }
        }
        return false;
      }
    }

    return true;
  }

  void solveSudoku(vector<vector<char>>& board) { backtracking(board); }
};

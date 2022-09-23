/*
请你判断一个9x9的数独是否有效。
只需要根据以下规则，验证已经填入的数字是否有效即可。
数字1-9在每一行只能出现一次。
数字1-9在每一列只能出现一次。
数字1-9在每一个以粗实线分隔的3x3宫内只能出现一次。

注意：
一个有效的数独（部分已被填充）不一定是可解的。
只需要根据以上规则，验证已经填入的数字是否有效即可。
空白格用'.'表示。

示例1：
输入：board =
[["5","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
输出：true

示例2：
输入：board =
[["8","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
输出：false
解释：除了第一行的第一个数字从5改为8以外，空格内其他数字均与示例1相同。
     但由于位于左上角的3x3宫内有两个8存在，因此这个数独是无效的。

提示：
board.length == 9
board[i].length == 9
board[i][j]是一位数字（1-9）或者'.'
*/

bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
  int row = boardSize;
  int col = *boardColSize;
  int rows[row][9];
  int cols[col][9];
  int box[3][3][9];
  memset(rows, 0, sizeof(rows));
  memset(cols, 0, sizeof(cols));
  memset(box, 0, sizeof(box));
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (board[i][j] != '.') {
        int index = board[i][j] - '0' - 1;
        rows[i][index]++;
        cols[j][index]++;
        box[i / 3][j / 3][index]++;
        if (rows[i][index] > 1 || cols[j][index] > 1 ||
            box[i / 3][j / 3][index] > 1) {
          return false;
        }
      }
    }
  }

  return true;
}

class Solution {
 public:
  bool isValidSudoku(vector<vector<char>>& board) {
    int rows[9][9];
    int columns[9][9];
    int subboxes[3][3][9];
    memset(rows, 0, sizeof(rows));
    memset(columns, 0, sizeof(columns));
    memset(subboxes, 0, sizeof(subboxes));

    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        char c = board[i][j];
        if (c != '.') {
          int index = c - '0' - 1;
          rows[i][index]++;
          columns[j][index]++;
          subboxes[i / 3][j / 3][index]++;
          if (rows[i][index] > 1 || columns[j][index] > 1 ||
              subboxes[i / 3][j / 3][index] > 1) {
            return false;
          }
        }
      }
    }
    return true;
  }
};
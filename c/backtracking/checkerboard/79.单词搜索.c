/*
给定一个m x n二维字符网格board和一个字符串单词word。
如果word存在于网格中，返回true；否则，返回false。
单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
同一个单元格内的字母不允许被重复使用。

示例1：
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
输出：true

示例2：
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
输出：true

示例3：
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
输出：false

提示：
m == board.length
n = board[i].length
1 <= m, n <= 6
1 <= word.length <= 15
board和word仅由大小写英文字母组成

进阶：你可以使用搜索剪枝的技术来优化解决方案，使其在board更大的情况下可以更快解决问题？
*/

int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
bool check(char** board, int boardSize, int boardColSize, int** visited, int i,
           int j, char* s, int sSize, int k) {
  if (board[i][j] != s[k]) {
    return false;
  } else if (k == sSize - 1) {
    return true;
  }
  visited[i][j] = true;
  bool result = false;
  for (int sel = 0; sel < 4; sel++) {
    int newi = i + directions[sel][0], newj = j + directions[sel][1];
    if (newi >= 0 && newi < boardSize && newj >= 0 && newj < boardColSize) {
      if (!visited[newi][newj]) {
        bool flag = check(board, boardSize, boardColSize, visited, newi, newj,
                          s, sSize, k + 1);
        if (flag) {
          result = true;
          break;
        }
      }
    }
  }
  visited[i][j] = false;
  return result;
}
bool exist(char** board, int boardSize, int* boardColSize, char* word) {
  int** visited = malloc(sizeof(int*) * boardSize);
  for (int i = 0; i < boardSize; i++) {
    visited[i] = malloc(sizeof(int) * boardColSize[0]);
    memset(visited[i], 0, sizeof(int) * boardColSize[0]);
  }
  int wordSize = strlen(word);
  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardColSize[0]; j++) {
      bool flag = check(board, boardSize, boardColSize[0], visited, i, j, word,
                        wordSize, 0);
      if (flag) {
        return true;
      }
    }
  }
  return false;
}
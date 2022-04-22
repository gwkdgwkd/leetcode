/*
给定一个m x n二维字符网格board和一个字符串单词word。
如果word存在于网格中，返回true；否则，返回false。
单词必须按照字母顺序，通过相邻的单元格内的字母构成，
其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
同一个单元格内的字母不允许被重复使用。

示例1：
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
输出：true

示例2：
输入：board = [["a","b"],["c","d"]], word = "abcd"
输出：false

提示：
1 <= board.length <= 200
1 <= board[i].length <= 200
board和word仅由大小写英文字母组成

注意：本题与79题相同
*/

int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
bool check(char** board, int m, int n, int** visited, int i, int j, char* str,
           int len, int index) {
  if (board[i][j] != str[index]) {
    return false;
  }
  if (index == len - 1) {
    return true;
  }

  visited[i][j] = true;
  bool ret = false;
  for (int k = 0; k < 4; ++k) {
    int newi = i + directions[k][0];
    int newj = j + directions[k][1];
    if (newi >= 0 && newi < m && newj >= 0 && newj < n) {
      if (visited[newi][newj] == false) {
        if (check(board, m, n, visited, newi, newj, str, len, index + 1)) {
          ret = true;
          break;
        }
      }
    }
  }

  visited[i][j] = false;
  return ret;
}
bool exist(char** board, int boardSize, int* boardColSize, char* word) {
  int m = boardSize;
  int n = *boardColSize;

  int** visited = malloc(sizeof(int*) * m);
  for (int i = 0; i < m; i++) {
    visited[i] = malloc(sizeof(int) * n);
    memset(visited[i], 0, sizeof(int) * n);
  }

  int len = strlen(word);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (check(board, m, n, visited, i, j, word, len, 0)) {
        return true;
      }
    }
  }

  return false;
}
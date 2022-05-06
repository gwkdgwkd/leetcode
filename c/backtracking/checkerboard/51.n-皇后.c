/*
n皇后问题研究的是如何将n个皇后放置在n×n的棋盘上，并且使皇后彼此之间不能相互攻击。
给你一个整数n，返回所有不同的n皇后问题的解决方案。
每一种解法包含一个不同的n皇后问题的棋子放置方案，该方案中'Q'和'.'分别代表了皇后和空位。

示例1：
输入：n = 4
输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
解释：4皇后问题存在两个不同的解法。

示例2：
输入：n = 1
输出：[["Q"]]

提示：1 <= n <= 9
*/

// 面试题0812八皇后

// n皇后问题是回溯算法解决的经典问题
char ***result;
int resultSize;
char **path;
int pathSize;
int isValid(int n, int row, int col) {
  // 为什么没有在同⾏进⾏检查呢？
  // 因为在单层搜索的过程中，每⼀层递归，只会选for循环（也就是同⼀⾏）⾥的⼀个元素，所以不⽤去重了。

  // 检查列
  for (int i = 0; i < row; i++) {  // 这是⼀个剪枝
    if (*(*(path + i) + col) == 'Q') {
      return 0;
    }
  }
  // 检查45度⻆是否有皇后
  for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
    if (path[i][j] == 'Q') {
      return 0;
    }
  }
  // 检查135度⻆是否有皇后
  for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
    if (path[i][j] == 'Q') {
      return 0;
    }
  }

  return 1;
}
void backtracking(int n, int startIndex, int **returnColumnSizes) {
  // 只要搜索到了树的叶⼦节点，说明就找到了皇后们的合理位置了
  if (startIndex == n) {
    result[resultSize] = (char **)malloc(sizeof(char *) * pathSize);
    for (int i = 0; i < pathSize; ++i) {
      result[resultSize][i] = (char *)malloc(sizeof(char) * (n + 1));
      memcpy(result[resultSize][i], path[i], n + 1);
    }
    resultSize++;
    return;
  }
  // 每⼀层⾥for循环的i控制棋盘的列，⼀⾏⼀列，确定了放置皇后的位置。
  // 每次都是要从新的⼀⾏的起始位置开始搜，所以都是从0开始。
  for (int i = 0; i < n; ++i) {
    if (isValid(n, startIndex, i)) {
      path[pathSize++][i] = 'Q';
      backtracking(n, startIndex + 1, returnColumnSizes);
      path[--pathSize][i] = '.';
    }
  }
}
char ***solveNQueens(int n, int *returnSize, int **returnColumnSizes) {
  result = (char ***)malloc(sizeof(char **) * 501);
  path = (char **)malloc(sizeof(char *) * n);
  for (int i = 0; i < n; ++i) {
    path[i] = (char *)malloc(sizeof(char) * (n + 1));
    memset(path[i], 0, sizeof(char) * (n + 1));
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      path[i][j] = '.';
    }
  }

  resultSize = pathSize = 0;
  // 递归深度控制棋盘的⾏
  backtracking(n, 0, returnColumnSizes);
  *returnSize = resultSize;
  *returnColumnSizes = (int *)malloc(sizeof(int) * resultSize);
  for (int i = 0; i < resultSize; ++i) {
    (*returnColumnSizes)[i] = n;
  }

  return result;
}

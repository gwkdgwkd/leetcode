/*
 * @lc app=leetcode.cn id=131 lang=c
 *
 * [131] 分割回文串
 */

// @lc code=start

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
// 回溯算法
char ***result;
int resultSize;
char **path;
int pathSize;
int isPalindrome(const char *str, int start, int end) {
  // 可以不写，但是如果写了，效率会高些
  // if (end == start) {
  //   return 1;
  // }

  // 双指针法，判断是否为回文
  for (int i = start, j = end; i < j; ++i, --j) {
    if (str[i] != str[j]) {
      return 0;
    }
  }

  return 1;
}
void backtracking(char *s, int len, int startIndex, int **returnColumnSizes) {
  if (startIndex == len) {
    result[resultSize] = (char **)malloc(sizeof(char *) * len);
    for (int i = 0; i < len; ++i) {
      result[resultSize][i] = (char *)malloc(sizeof(char) * len + 1);
    }
    // printf("%d:",pathSize);
    for (int i = 0; i < pathSize; ++i) {
      memcpy(result[resultSize][i], path[i], strlen(path[i]) + 1);
      // printf("%s|",result[resultSize][i]);
    }
    // printf("\n");
    (*returnColumnSizes)[resultSize] = pathSize;
    resultSize++;
    return;
  }
  for (int i = startIndex; i < len; ++i) {
    // printf("%*c[%d,%d]",startIndex + 1,' ',startIndex,i);
    if (isPalindrome(s, startIndex, i)) {
      memcpy(path[pathSize], s + startIndex, i - startIndex + 1);
      path[pathSize++][i - startIndex + 1] = 0;
      // printf(":(%d)%s\n",pathSize - 1,path[pathSize - 1]);
      backtracking(s, len, i + 1, returnColumnSizes);
      pathSize--;
    } else {
      // printf("\n");
    }
  }

  // "aab"
  //  [0,0]:(0)a
  //   [1,1]:(1)a
  //    [2,2]:(2)b
  // 3:a|a|b|
  //   [1,2]
  //  [0,1]:(0)aa
  //    [2,2]:(1)b
  // 2:aa|b|
  //  [0,2]

  return;
}
// 切割问题类似组合问题
char ***partition(char *s, int *returnSize, int **returnColumnSizes) {
  int len = strlen(s);
  int retMaxLen = len * (1 << len);  // 求组合的最大个数？
  result = (char ***)malloc(sizeof(char **) * retMaxLen);
  // printf("%d\n",len);
  path = (char **)malloc(sizeof(char *) * len);
  for (int i = 0; i < len; ++i) {
    path[i] = (char *)malloc(sizeof(char) * len + 1);
  }
  resultSize = pathSize = 0;
  *returnColumnSizes = (int *)malloc(sizeof(int) * retMaxLen);

  backtracking(s, len, 0, returnColumnSizes);
  *returnSize = resultSize;
  return result;
}
// @lc code=end

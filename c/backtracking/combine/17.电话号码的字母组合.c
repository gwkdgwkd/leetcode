/*
 * @lc app=leetcode.cn id=17 lang=c
 *
 * [17] 电话号码的字母组合
 */

// @lc code=start

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

// 回溯算法
char *map[10] = {
    "",      // 0
    "",      // 1
    "abc",   // 2
    "def",   // 3
    "ghi",   // 4
    "jkl",   // 5
    "mno",   // 6
    "pqrs",  // 7
    "tuv",   // 8
    "wxyz",  // 9
};
char **result;
int resultSize;
char *path;
int pathSize;
void backtracking(char *digits, int index) {
  if (pathSize == strlen(digits)) {
    result[resultSize] = (char *)malloc(sizeof(char) * pathSize + 1);
    for (int i = 0; i < pathSize; ++i) {
      result[resultSize][i] = path[i];
    }
    result[resultSize][pathSize] = 0;
    resultSize++;

    return;
  }

  int len = strlen(map[digits[index] - '0']);
  for (int i = 0; i < len; ++i) {
    path[pathSize++] = map[digits[index] - '0'][i];
    // printf("%*c\n", pathSize * 2, map[digits[index] - '0'][i]);
    backtracking(digits, index + 1);
    pathSize--;
  }

  return;
}
char **letterCombinations(char *digits, int *returnSize) {
  int len = strlen(digits);
  if (0 == len) {
    *returnSize = 0;
    return;
  }
  int max = 1;
  for (int i = 0; i < len; ++i) {
    max *= 4;
  }
  result = (char **)malloc(sizeof(char *) * max);
  path = (char *)malloc(sizeof(char) * len);
  resultSize = pathSize = 0;
  backtracking(digits, 0);
  *returnSize = resultSize;
  return result;
}
// @lc code=end

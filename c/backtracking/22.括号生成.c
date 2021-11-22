// 回溯算法
// 翻译：现在有2n个位置，每个位置可以放置字符(或者)，组成的所有括号组合中，有多少个是合法的？
// 有关括号问题，你只要记住两个个性质，思路就很容易想出来：
// 1、一个「合法」括号组合的左括号数量一定等于右括号数量，这个显而易见。
// 2、对于一个「合法」的括号字符串组合p，必然对于任何0 <= i < len(p)都有：子串p[0..i]中左括号的数量都大于或等于右括号的数量。
char **res;
int resSize;
char *path;
int pathSize;
void backtrack(int left, int right) {
  if (right < 0 || left < 0 || right < left) {
    return;
  }

  if (right == 0 && left == 0) {
    res[resSize] = (char *)malloc(sizeof(char) * (pathSize + 1));
    memcpy(res[resSize], path, pathSize);
    res[resSize++][pathSize] = 0;
    return;
  }

  path[pathSize++] = '(';
  backtrack(left - 1, right);
  pathSize--;

  path[pathSize++] = ')';
  backtrack(left, right - 1);
  pathSize--;
}
char **generateParenthesis(int n, int *returnSize) {
  res = (char **)malloc(sizeof(char *) * 10000);
  path = (char *)malloc(sizeof(char) * 2 * n);

  resSize = pathSize = 0;
  backtrack(n, n);

  *returnSize = resSize;
  return res;
}
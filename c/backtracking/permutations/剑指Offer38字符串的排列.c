/*
输入一个字符串，打印出该字符串中字符的所有排列。
你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。

示例:
输入：s = "abc"
输出：["abc","acb","bac","bca","cab","cba"]

限制：1 <= s 的长度 <= 8
*/

void backtrack(char** rec, int* recSize, int* vis, char* s, int i, int n,
               char* perm) {
  if (i == n) {
    char* tmp = malloc(sizeof(char) * (n + 1));
    strcpy(tmp, perm);
    rec[(*recSize)++] = tmp;
    return;
  }
  for (int j = 0; j < n; j++) {
    if (vis[j] || (j > 0 && !vis[j - 1] && s[j - 1] == s[j])) {
      continue;
    }
    vis[j] = true;
    perm[i] = s[j];
    backtrack(rec, recSize, vis, s, i + 1, n, perm);
    vis[j] = false;
  }
}
int cmp(char* a, char* b) { return *a - *b; }
char** permutation(char* s, int* returnSize) {
  int n = strlen(s);
  int recMaxSize = 1;
  for (int i = 2; i <= n; i++) {
    recMaxSize *= i;
  }
  char** rec = malloc(sizeof(char*) * recMaxSize);
  *returnSize = 0;
  int vis[n];
  memset(vis, 0, sizeof(vis));
  char perm[n + 1];
  perm[n] = '\0';
  qsort(s, n, sizeof(char), cmp);
  backtrack(rec, returnSize, vis, s, 0, n, perm);
  return rec;
}
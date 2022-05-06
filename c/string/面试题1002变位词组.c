/*
编写一种方法，对字符串数组进行排序，将所有变位词组合在一起。变位词是指字母相同，但排列不同的字符串。
注意：本题相对原题稍作修改

示例:
输入: ["eat", "tea", "tan", "ate", "nat", "bat"],
输出:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]

说明：
所有输入均为小写字母。
不考虑答案输出的顺序。
*/

int strcmp0(char *a, char *b) {
  int len = strlen(a);
  int i;
  int c1['z' - 'a' + 1] = {0};
  int c2['z' - 'a' + 1] = {0};

  for (i = 0; i < len; i++) {
    c1[a[i] - 'a']++;
    c2[b[i] - 'a']++;
  }

  for (i = 0; i < 26; i++) {
    if (c1[i] != c2[i]) {
      return c1[i] - c2[i];
    }
  }
  return 0;
}
int cmp(const void *a0, const void *b0) {
  char *a = *(char **)a0;
  char *b = *(char **)b0;

  if (strlen(a) != strlen(b)) {
    return strlen(a) - strlen(b);
  }
  return strcmp0(a, b);
}
char ***groupAnagrams(char **strs, int strsSize, int *returnSize,
                      int **returnColumnSizes) {
  int i, j = 0, k, tmp = 1;
  char *ct[strsSize];
  char ***res = malloc(strsSize * sizeof(char *));

  *returnColumnSizes = malloc(strsSize * sizeof(int));

  // 排序，确保每个字母个数相同的字符串相邻
  qsort(strs, strsSize, sizeof(char *), cmp);

  for (i = 0; i < strsSize; i++) {
    if (i + 1 < strsSize && cmp(&strs[i], &strs[i + 1]) == 0) {
      tmp++;
    } else {
      res[j] = malloc(tmp * sizeof(char *));
      for (k = 0; k < tmp; k++) {
        res[j][k] = strs[i - k];
      }
      (*returnColumnSizes)[j] = tmp;
      tmp = 1;
      j++;
    }
  }
  *returnSize = j;
  return res;
}
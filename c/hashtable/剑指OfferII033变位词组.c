/*
给定一个字符串数组strs，将变位词组合在一起。可以按任意顺序返回结果列表。
注意：若两个字符串中每个字符出现的次数都相同，则称它们互为变位词。

示例1:
输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
输出: [["bat"],["nat","tan"],["ate","eat","tea"]]

示例2:
输入: strs = [""]
输出: [[""]]

示例3:
输入: strs = ["a"]
输出: [["a"]]

提示：
1 <= strs.length <= 10^4
0 <= strs[i].length <= 100
strs[i]仅包含小写字母

注意：本题与49题相同
*/

int cmp(const void *a, const void *b) { return *(char *)a - *(char *)b; }
char ***groupAnagrams(char **strs, int strsSize, int *returnSize,
                      int **returnColumnSizes) {
  // 储存对str的各个子字符串排序的字符数组
  char **tmp = (char **)calloc(strsSize, sizeof(char *));
  for (int i = 0; i < strsSize; i++) {
    char *string = strs[i];
    int length = strlen(string);
    tmp[i] = (char *)calloc(101, sizeof(char));
    memcpy(tmp[i], string, length);
    qsort(tmp[i], length, sizeof(char), cmp);
  }
#ifdef DEBUG
  printf("排序后的字符串：\n");
  for (int i = 0; i < strsSize; i++) {
    printf("%s\n", tmp[i]);
  }
#endif
  char ***res = (char ***)calloc(strsSize, sizeof(char **));
  *returnSize = 0;
  *returnColumnSizes = (int *)calloc(strsSize, sizeof(int));
  for (int i = 0; i < strsSize; i++) {
    unsigned long length = strlen(tmp[i]);
    int n = (*returnColumnSizes)[*returnSize];
    res[*returnSize] = (char **)calloc(101, sizeof(char *));
    res[*returnSize][n] = (char *)calloc(101, sizeof(char));
    if (*returnSize == 0) {
      memcpy(res[0][0], strs[0], length + 1);
#ifdef DEBUG
      printf("res[%d][%d]:%s\n", 0, 0, res[0][0]);
#endif
      (*returnColumnSizes)[0] += 1;
      (*returnSize)++;
      continue;
    }
    int index = 0;
    while (index < i) {
      int equl = strcmp(tmp[index], tmp[i]);
      if (equl == 0) {
        int k;
        for (k = 0; k < (*returnSize); k++) {
          int ans = strcmp(res[k][0], strs[index]);
          if (ans == 0) break;
        }
        int m = (*returnColumnSizes)[k];
        if (res[k][m] == NULL) res[k][m] = (char *)calloc(101, sizeof(char));
        memcpy(res[k][m], strs[i], length + 1);
#ifdef DEBUG
        printf("res[%d][%d]:%s\n", k, m, res[k][m]);
#endif
        (*returnColumnSizes)[k]++;
        break;
      }
      index++;
    }
    if (index == i) {
      (*returnColumnSizes)[*returnSize] = 0;
      int m = (*returnColumnSizes)[*returnSize];
      if (res[*returnSize][m] == NULL)
        res[*returnSize][m] = (char *)calloc(101, sizeof(char));
      memcpy(res[*returnSize][0], strs[i], length + 1);
#ifdef DEBUG
      printf("res[%d][%d]:%s\n", *returnSize, m, res[*returnSize][0]);
#endif
      (*returnColumnSizes)[*returnSize]++;
      (*returnSize)++;
    }
  }
  return res;
}
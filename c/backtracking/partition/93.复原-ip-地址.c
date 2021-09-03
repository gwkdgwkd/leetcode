/*
 * @lc app=leetcode.cn id=93 lang=c
 *
 * [93] 复原 IP 地址
 */

// @lc code=start

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

char **result;
int resultSize;
char *path;
int pathIndex;
int pathSize;
int isValid(const char *str, int start, int end) {
  if (end < start) {
    return 0;
  }
  if (str[start] == '0' && start != end) {
    return 0;
  }

  int num = 0;
  for (int i = start; i <= end; i++) {
    if (str[i] > '9' || str[i] < '0') {  // 遇到⾮数字字符不合法
      return 0;
    }
    num = num * 10 + (str[i] - '0');
    if (num > 255) {  // 如果⼤于255了不合法
      return 0;
    }
  }

  return 1;
}
void backtracking(char *s, int len, int startIndex) {
  if (pathSize == 3) {
    if (isValid(s, startIndex, len - 1)) {
      // printf("%s[%d %d]\n",path,startIndex,strlen(path));
      result[resultSize] = (char *)malloc(sizeof(char) * 16);
      strcpy(result[resultSize], path);
      // printf("%s\n",result[resultSize]);
      strcpy(result[resultSize] + strlen(path), s + startIndex);
      // printf("%s\n",result[resultSize]);
      resultSize++;
    }
    return;
  }

  int tmp = pathIndex;
  for (int i = startIndex; i < len; ++i) {
    if (isValid(s, startIndex, i)) {
      memcpy(path + pathIndex, s + startIndex, i - startIndex + 1);
      pathIndex += i - startIndex + 1;
      path[pathIndex++] = '.';
      path[pathIndex] = 0;
      // printf("%s\n",path);
      pathSize++;
      backtracking(s, len, i + 1);
      pathSize--;
      pathIndex = tmp;
    } else {
      break;
    }
  }

  // "25525511135"
  // 2.
  // 2.5.
  // 2.5.5.
  // 2.5.52.
  // 2.55.
  // 2.55.2.
  // 2.55.25.
  // 2.55.255.
  // 25.
  // 25.5.
  // 25.5.2.
  // 25.5.25.
  // 25.5.255.
  // 25.52.
  // 25.52.5.
  // 25.52.55.
  // 255.
  // 255.2.
  // 255.2.5.
  // 255.2.55.
  // 255.25.
  // 255.25.5.
  // 255.25.51.
  // 255.255.
  // 255.255.1.
  // 255.255.11.
  // 255.255.11.135
  // 255.255.111.
  // 255.255.111.35

  return;
}
char **restoreIpAddresses(char *s, int *returnSize) {
  int len = strlen(s);
  if (len > 12) {
    *returnSize = 0;
    return NULL;
  }
  int maxResultSize = len * (1 << len);
  // printf("%d %d\n", len, maxResultSize);
  result = (char **)malloc(sizeof(char *) * maxResultSize);
  path = (char *)malloc(sizeof(char) * 16);
  resultSize = pathSize = pathIndex = 0;
  backtracking(s, len, 0);
  *returnSize = resultSize;
  return result;
}

// @lc code=end

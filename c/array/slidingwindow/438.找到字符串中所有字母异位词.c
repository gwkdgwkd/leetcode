// 滑动窗口+哈希
int *findAnagrams(char *s, char *p, int *returnSize) {
  int lens = strlen(s);
  int lenp = strlen(p);
  int count = lenp;
  int hash[26] = {0};

  int *tmp = (int *)malloc(sizeof(int) * lens);
  *returnSize = 0;

  for (int i = 0; i < lenp; ++i) {
    hash[p[i] - 'a']++;  // 统计串t中各元素的哈希值
  }

  int start = 0, end = 0;
  while (end < lens) {  // 右指针从串s头移动到串s尾
    // 串s中当前元素在串t中出现过时，其值大于0，串s中当前元素的哈希值减1
    if (hash[s[end] - 'a']-- > 0) {
      count--;
    }
    end++;  // 右指针向右移动

    while (count == 0) {               // 出现匹配的子串
      if (end - start == lenp) {       // 当前子串与串t匹配
        tmp[(*returnSize)++] = start;  // 更新匹配数组的值
      }

      // 串s当前start的哈希值加1
      if (++hash[s[start] - 'a'] > 0) {
        // 若大于0，则表示左指针start移动后的子串不符合条件
        // 若小于等于0，则表示左指针start移动后的字串还能符合条件
        count++;
      }
      start++;  // 左指针向右移动
    }
  }

  if (*returnSize != 0) {  // 找到了最小匹配字串
    int *res = (int *)malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < *returnSize; ++i) {
      res[i] = tmp[i];
    }
    free(tmp);
    return res;
  } else {
    return tmp;
  }
}

// 采用26个字母的hash运算法+移动窗口，时间复杂度O(n)
int *findAnagrams(char *s, char *p, int *returnSize) {
  *returnSize = 0;
  int len_s = strlen(s);
  int len_p = strlen(p);
  if (len_s < len_p) return NULL;

  int i, j, len = len_s - len_p + 1;
  int hash[26] = {0};
  for (i = 0; i < len_p; ++i) {
    hash[p[i] - 'a']++;
    hash[s[i] - 'a']--;
  }
  int *res = (int *)malloc(len * sizeof(int));
  memset(res, 0, len * sizeof(int));
  char *s2 = s + len_p;
  for (i = 0; i < len; ++i) {
    for (j = 0; j < 26; ++j)
      if (hash[j]) break;
    if (j >= 26) res[(*returnSize)++] = i;
    hash[*s++ - 'a']++;
    if (*s2) hash[*s2++ - 'a']--;
  }
  return res;
}

// 滑动窗口
int *findAnagrams(char *s, char *p, int *returnSize) {
  int ls = strlen(s);
  int lp = strlen(p);
  int lenp = lp;
  int hash[26] = {0};
  int left = 0;
  int right = 0;
  for (int i = 0; i < lp; ++i) {
    hash[p[i] - 'a']++;
  }

  int *res = (int *)malloc(sizeof(int) * ls);
  *returnSize = 0;
  while (right < ls) {
    if (hash[s[right] - 'a']-- > 0) {
      lp--;
    }
    right++;
    while (0 == lp) {
      if (right - left == lenp) {
        res[(*returnSize)++] = left;
      }
      hash[s[left] - 'a']++;
      if (hash[s[left] - 'a'] > 0) {
        lp++;
      }
      left++;
    }
  }

  return res;
}
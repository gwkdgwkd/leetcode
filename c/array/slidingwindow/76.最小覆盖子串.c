/*
 * @lc app=leetcode.cn id=76 lang=c
 *
 * [76] 最小覆盖子串
 */

// @lc code=start

// 滑动窗口问题思想：
// 如果不满足条件，右边界向前推移，寻找解
// 如果满足条件，右边界停止更新，左边界向前推移，寻找最优解，并存储最优解；
// 条件指的是有效字符数和每个字符的个数都对应上；
#define MAX_NUM 128
char* minWindow(char* s, char* t) {
  int left = 0;
  int right = 0;
  int need[MAX_NUM] = {0};
  int window[MAX_NUM] = {0};
  int valid = 0;
  int cur = 0;
  int start = 0;
  int len = INT_MAX;
  for (int i = 0; i < strlen(t); i++) {
    if (need[t[i]] == 0) {
      valid++;
    }
    need[t[i]]++;
  }

  while (right < strlen(s)) {
    if (need[s[right]] > 0) {
      window[s[right]]++;
      if (need[s[right]] == window[s[right]]) {
        cur++;
      }
    }
    right++;
    // 停止更新窗口
    while (cur == valid) {
      if (right - left < len) {
        start = left;
        len = right - left;
      }
      char a = s[left];
      if (need[a] > 0) {
        window[a]--;
        if (need[a] > window[a]) {
          cur--;
        }
      }
      left++;
    }
  }

  if (len == INT_MAX) {
    return "";
  } else {
    *(s + start + len) = '\0';
    return s + start;
  }
}

// 哈希+滑动窗口
#define LEN 125
char* minWindow(char* s, char* t) {
  int hash[LEN] = {0};                    /* 定义哈希表 */
  int start = 0, end = 0;                 /* 左右指针 */
  int slen = strlen(s), tlen = strlen(t); /* 两串的长度 */
  int minstart = 0, minlen = INT_MAX;     /* 最小匹配串起点与长度 */

  for (int i = 0; t[i]; i++) {
    hash[t[i]]++; /* 再统计串t中各元素的哈希值 */
  }

  while (end < slen) { /* 右指针从串s头移动到串s尾 */
    // 若s串有t串的字母，则对应的哈希表减一，tlen也减一
    /* 这里无论hash[s[end]]是否大于0，都要将哈希值减一
         * 若T中有2个A，S中出现了3个连续的A，虽然前两个A都使得tlen--了
         * 但是第三个A没有使得tlen--，这样在后面缩小左边界的时候遇到三个连续的A时
         * 虽然A在t中出现过，但是这时A的哈希值未大于0，所以就不会使得tlen++了
         * 这样就能避免左边界还未收缩完，就收缩右边界的情况
         * 若s = [A A A C B D E C C A]；t = [AABC]
         * 第1次满足条件：这时tlen为0，ABC的哈希值为-1、0、0，保存minStart = start, minLen = end-start;
         * [ A A A C B D E C C A ]
         *   s         e 
         * 第1次移动左边界、第2次满足条件：移动之后tlen为0，ABC的哈希值为0、0、0，保存minStart = start, minLen = end-start;
         * [ A A A C B D E C C A ]
         *     s       e 
         * 第2次移动左边界：移动之后tlen为1，ABC的哈希值为1、0、0，不满足条件了，需要移动右边界了
         * [ A A A C B D E C C A ]
         *       s     e 
         * 第3次满足条件：这时tlen为0，ABC的哈希值为0、0、-2
         * [ A A A C B D E C C A ]
         *       s               e 
         * 第3次移动左边界：移动之后tlen为1，ABC的哈希值为1、0、-2，但是end >= sLen了，循环结束
         * [ A A A C B D E C C A ]
         *         s             e 
         */
    if (hash[s[end]]-- > 0) { /* 串s中当前元素在串t中出现过 */
      tlen--;                 /* tlen-- */
    }
    //hash[s[end]]--; /* 串s中当前元素的哈希值减1 */
    end++; /* 右指针向右移动 */

    while (tlen == 0) {           /* 出现匹配的子串 */
      if (end - start < minlen) { /* 更新最小匹配串的起点和长度 */
        minstart = start;
        minlen = end - start;
      }
      /* 串s当前start的哈希值加1：
             * 若大于0，则表示左指针start移动后的字串不符合条件 
             * 若小于等于0，则表示左指针start移动后的字串还能符合条件
             */
      hash[s[start]]++;
      if (hash[s[start]] > 0) {
        tlen++;
      }
      start++;
    }
  }

  if (minlen != INT_MAX) { /* 找到了最小匹配字串 */
    char* t = (char*)malloc(sizeof(char) * (minlen + 1));
    *t = '\0';
    /* char *strncat(char *dest, const char *src, size_t n)
         * 该函数返回一个指向最终的目标字符串dest的指针。
         * dest -- 指向目标数组，该数组包含了一个C字符串，且足够容纳追加后的字符串，包括额外的空字符。
         * src -- 要追加的字符串。
         * n -- 要追加的最大字符数。
         * 例如：https://www.runoob.com/cprogramming/c-function-strncat.html
         * strcpy(src,  "This is source");
         * strcpy(dest, "This is destination");
         * strncat(dest, src, 15);
         * printf("最终的目标字符串： |%s|", dest); 
         * 最终的目标字符串： |This is destinationThis is source|
         */
    strncat(t, s + minstart, minlen);
    return t;
  }

  return ""; /* 未找到最小匹配子串，返回""即可 */
}

// @lc code=end

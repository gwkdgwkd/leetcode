/*
给你一个字符串s、一个字符串t。返回s中涵盖t所有字符的最小子串。
如果s中不存在涵盖t所有字符的子串，则返回空字符串""。

注意：
对于t中重复字符，我们寻找的子字符串中该字符数量必须不少于t中该字符数量。
如果s中存在这样的子串，我们保证它是唯一的答案。

示例1：
输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"

示例2：
输入：s = "a", t = "a"
输出："a"

示例3:
输入: s = "a", t = "aa"
输出: ""
解释: t中两个字符'a'均应包含在s的子串中，
因此没有符合条件的子字符串，返回空字符串。

提示：
1 <= s.length, t.length <= 10^5
s和t由英文字母组成

进阶：你能设计一个在o(n)时间内解决此问题的算法吗？
*/

// 剑指OfferII017含有所有字符的最短字符串

// 滑动窗口问题思想：
// 如果不满足条件，右边界向前推移，寻找解
// 如果满足条件，右边界停止更新，左边界向前推移，寻找最优解，并存储最优解；
// 条件指的是有效字符数和每个字符的个数都对应上；
#define MAX 128
char* minWindow(char* s, char* t) {
  int lens = strlen(s);
  int lent = strlen(t);

  int hash[MAX] = {0};
  for (int i = 0; i < lent; ++i) {
    hash[t[i]]++;
  }

  int left = 0;
  int right = 0;
  int start = 0;
  int minlen = INT_MAX;
  while (right < lens) {
    if (hash[s[right++]]-- > 0) {
      --lent;
    }
    while (lent == 0) {
      if (right - left < minlen) {
        start = left;
        minlen = right - left;
      }
      if (++hash[s[left++]] > 0) {
        ++lent;
      }
    }
  }

  if (minlen == INT_MAX) {
    return "";
  }
  s[start + minlen] = 0;
  return s + start;
}

// 哈希+滑动窗口
#define LEN 128
char* minWindow(char* s, char* t) {
  int hash[LEN] = {0};                     // 定义哈希表
  int start = 0, end = 0;                  // 左右指针
  int slen = strlen(s), tlen = strlen(t);  // 两串的长度
  int minstart = 0, minlen = INT_MAX;      // 最小匹配串起点与长度

  for (int i = 0; t[i]; i++) {
    hash[t[i]]++;  // 再统计串t中各元素的哈希值
  }

  while (end < slen) {  // 右指针从串s头移动到串s尾
    // 若s串有t串的字母，则对应的哈希表减一，tlen也减一
    // 这里无论hash[s[end]]是否大于0，都要将哈希值减一
    // 若T中有2个A，S中出现了3个连续的A，虽然前两个A都使得tlen--了
    // 但是第三个A没有使得tlen--，这样在后面缩小左边界的时候遇到三个连续的A时
    // 虽然A在t中出现过，但是这时A的哈希值未大于0，所以就不会使得tlen++了
    // 这样就能避免左边界还未收缩完，就收缩右边界的情况
    // 若s = [A A A C B D E C C A]；t = [AABC]
    // 第1次满足条件：这时tlen为0，ABC的哈希值为-1、0、0，保存minStart = start,
    // minLen = end-start; [ A A A C B D E C C A ]
    //   s         e
    // 第1次移动左边界、第2次满足条件：移动之后tlen为0，ABC的哈希值为0、0、0，
    // 保存minStart = start, minLen = end-start;
    // [ A A A C B D E C C A ]
    //     s       e
    // 第2次移动左边界：移动之后tlen为1，ABC的哈希值为1、0、0，不满足条件了，需要移动右边界了
    // [ A A A C B D E C C A ]
    //       s     e
    // 第3次满足条件：这时tlen为0，ABC的哈希值为0、0、-2
    // [ A A A C B D E C C A ]
    //       s               e
    // 第3次移动左边界：移动之后tlen为1，ABC的哈希值为1、0、-2，但是end >=
    // sLen了，循环结束 [ A A A C B D E C C A ]
    //         s             e
    if (hash[s[end]]-- > 0) {  // 串s中当前元素在串t中出现过
      tlen--;                  // tlen--
    }
    end++;  // 右指针向右移动

    while (tlen == 0) {            // 出现匹配的子串
      if (end - start < minlen) {  // 更新最小匹配串的起点和长度
        minstart = start;
        minlen = end - start;
      }
      // 串s当前start的哈希值加1：
      // 若大于0，则表示左指针start移动后的字串不符合条件
      // 若小于等于0，则表示左指针start移动后的字串还能符合条件
      if (++hash[s[start]] > 0) {
        tlen++;
      }
      start++;
    }
  }

  if (minlen != INT_MAX) {  // 找到了最小匹配字串
    char* t = (char*)malloc(sizeof(char) * (minlen + 1));
    *t = '\0';
    // char *strncat(char *dest, const char *src, size_t n)
    // 该函数返回一个指向最终的目标字符串dest的指针。
    // dest --
    // 指向目标数组，该数组包含了一个C字符串，且足够容纳追加后的字符串，包括额外的空字符。
    // src -- 要追加的字符串。
    // n -- 要追加的最大字符数。
    // 例如：https://www.runoob.com/cprogramming/c-function-strncat.html
    // strcpy(src,  "This is source");
    // strcpy(dest, "This is destination");
    // strncat(dest, src, 15);
    // printf("最终的目标字符串： |%s|", dest);
    // 最终的目标字符串： |This is destinationThis is source|
    strncat(t, s + minstart, minlen);
    return t;
  }

  return "";  // 未找到最小匹配子串，返回""即可
}

class Solution {
 public:
  string minWindow(string s, string t) {
    int lens = s.size();
    int lent = t.size();

    int hash[128] = {0};
    for (char c : t) {
      hash[c]++;
    }

    int left = 0;
    int right = 0;
    int minlen = INT_MAX;
    int minstart = left;
    while (right < lens) {
      if (hash[s[right]]-- > 0) {
        --lent;
      }
      ++right;
      while (lent == 0) {
        if (right - left < minlen) {
          minlen = right - left;
          minstart = left;
        }

        if (++hash[s[left]] > 0) {
          ++lent;
        }
        ++left;
      }
    }

    string res = "";
    if (minlen != INT_MAX) {
      res = string(s.begin() + minstart, s.begin() + minstart + minlen);
    }

    return res;
  }
};
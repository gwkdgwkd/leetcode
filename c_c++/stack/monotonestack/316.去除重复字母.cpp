/*
给一个字符串s，请去除字符串中重复的字母，使得每个字母只出现一次。
需保证返回结果的字典序最小，要求不能打乱其他字符的相对位置。

示例1：
输入：s = "bcabc"
输出："abc"

示例2：
输入：s = "cbacdcbc"
输出："acdb"

提示：
1 <= s.length <= 10^4
s由小写英文字母组成
*/

// 1081.不同字符的最小子序列

// 单调栈
char *removeDuplicateLetters(char *s) {
  if (s == NULL || strlen(s) == 0) {
    return "";
  }
  if (strlen(s) == 1) {
    return s;
  }
  int len = (int)strlen(s);
  char recode[26] = {0};  // 注意，这里需要初始化为0
  for (int i = 0; i < len; i++) {
    recode[s[i] - 'a']++;
  }

  char *stack = (char *)malloc(sizeof(char) * (len + 1));
  int top = -1;

  int isExist;
  for (int i = 0; i < len; i++) {
    isExist = 0;
    for (int j = 0; j <= top; j++) {
      if (s[i] == stack[j]) {
        isExist = 1;
        break;
      }
    }

    if (isExist) {
      recode[s[i] - 'a']--;
    } else {
      while (top > -1 && stack[top] > s[i] && recode[stack[top] - 'a'] > 1) {
        // 如果栈顶字符比当前大，并且后边还会出现
        recode[stack[top] - 'a']--;
        top--;  // 出栈
      }
      stack[++top] = s[i];  // 入栈
    }
  }
  stack[++top] = '\0';
  return stack;
}

class Solution {
 public:
  string removeDuplicateLetters(string s) {
    int len = s.size();
    unordered_map<char, int> um1;
    for (int i = 0; i < len; ++i) {
      um1[s[i]]++;
    }

    string stk;
    unordered_map<char, bool> um2;
    for (int i = 0; i < len; ++i) {
      if (um2[s[i]]) {
        um1[s[i]]--;
      } else {
        while (!stk.empty() && stk.back() > s[i] && um1[stk.back()] > 1) {
          um1[stk.back()]--;
          um2[stk.back()] = false;
          stk.pop_back();
        }
        stk.push_back(s[i]);
        um2[s[i]] = true;
      }
    }

    return stk;
  }
};
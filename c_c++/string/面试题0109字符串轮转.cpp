/*
字符串轮转。
给定两个字符串s1和s2，请编写代码检查s2是否为s1旋转而成。
比如，waterbottle是erbottlewat旋转后的字符串。

示例1：
输入：s1 = "waterbottle", s2 = "erbottlewat"
输出：True

示例2：
输入：s1 = "aa", s2 = "aba"
输出：False

提示：字符串长度在[0，100000]范围内。

说明：你能只调用一次检查子串的方法吗？
*/

// 模拟
bool isFlipedString(char* s1, char* s2) {
  int m = strlen(s1), n = strlen(s2);
  if (m != n) {
    return false;
  }
  if (n == 0) {
    return true;
  }
  for (int i = 0; i < n; i++) {
    bool flag = true;
    for (int j = 0; j < n; j++) {
      if (s1[(i + j) % n] != s2[j]) {
        flag = false;
        break;
      }
    }
    if (flag) {
      return true;
    }
  }
  return false;
}

class Solution {
 public:
  bool isFlipedString(string s1, string s2) {
    int m = s1.size(), n = s2.size();
    if (m != n) {
      return false;
    }
    if (n == 0) {
      return true;
    }
    for (int i = 0; i < n; i++) {
      bool flag = true;
      for (int j = 0; j < n; j++) {
        if (s1[(i + j) % n] != s2[j]) {
          flag = false;
          break;
        }
      }
      if (flag) {
        return true;
      }
    }
    return false;
  }
};

// 搜索子字符串
bool isFlipedString(char* s1, char* s2) {
  int m = strlen(s1), n = strlen(s2);
  if (m != n) {
    return false;
  }
  char* str = (char*)malloc(sizeof(char) * (m + n + 1));
  sprintf(str, "%s%s", s2, s2);
  return strstr(str, s1) != NULL;
}

class Solution {
 public:
  bool isFlipedString(string s1, string s2) {
    return s1.size() == s2.size() && (s1 + s1).find(s2) != string::npos;
  }
};
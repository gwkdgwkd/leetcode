/*
给你一个由若干括号和字母组成的字符串s，删除最小数量的无效括号，
使得输入的字符串有效，返回所有可能的结果，答案可以按任意顺序返回。

示例1：
输入：s = "()())()"
输出：["(())()","()()()"]

示例2：
输入：s = "(a)())()"
输出：["(a())()","(a)()()"]

示例3：
输入：s = ")("
输出：[""]

提示：
1 <= s.length <= 25
s由小写英文字母以及括号'('和')'组成
s中至多含20个括号
*/

int gResultSize = 0;
char **gResult;
bool IsValid(char *s) {
  int cnt = 0;
  char *p = s;
  while (*p != '\0') {
    if (*p == '(') {
      cnt++;
    } else if (*p == ')') {
      cnt--;
    }
    if (cnt < 0) {
      return false;
    }
    p++;
  }
  return cnt == 0;
}

void removeInvalidParentheses2(char *s, int sLen, int start, int leftCnt,
                               int rightCnt) {
  if (start > sLen) {
    return;
  }
  // printf("enter:%s :%d:%d:%d\n", s, start, leftCnt, rightCnt);
  if (leftCnt == 0 && rightCnt == 0) {
    // printf("wait:%s\n", s);
    if (IsValid(s)) {
      gResult[gResultSize] = malloc(sizeof(char) * sLen + 1);
      strcpy(gResult[gResultSize], s);
      gResultSize++;
      // printf("%s\n", s);
    }
    return;
  }
  char subStr[sLen];
  for (int i = start; i < sLen; ++i) {
    if (i > start && s[i] == s[i - 1]) {
      continue;
    }
    if (s[i] == '(' && leftCnt > 0) {
      memcpy(subStr, s, i);
      subStr[i] = '\0';
      strcat(subStr, s + i + 1);
      removeInvalidParentheses2(subStr, sLen - 1, i, leftCnt - 1, rightCnt);
    } else if (s[i] == ')' && rightCnt > 0) {
      memcpy(subStr, s, i);
      subStr[i] = '\0';
      strcat(subStr, s + i + 1);
      // printf("subStr-->%s\n", subStr);
      removeInvalidParentheses2(subStr, sLen - 1, i, leftCnt, rightCnt - 1);
    }
  }
}
#define MAX_RESULT_LEN 10000
char **removeInvalidParentheses(char *s, int *returnSize) {
  int leftCnt = 0;
  int rightCnt = 0;
  for (int i = 0; i < strlen(s); ++i) {
    if (s[i] == '(') {
      leftCnt++;
    } else if (s[i] == ')') {
      if (leftCnt == 0) {
        rightCnt++;
      } else {
        leftCnt--;
      }
    }
  }
  char **ans = malloc(sizeof(char *) * MAX_RESULT_LEN);
  memset(ans, 0, sizeof(char *) * MAX_RESULT_LEN);
  gResult = ans;
  gResultSize = 0;
  removeInvalidParentheses2(s, strlen(s), 0, leftCnt, rightCnt);
  // printf("%d\n", gResultSize);
  if (gResultSize == 0) {
    gResult[0] = "";
    gResultSize = 1;
  }
  *returnSize = gResultSize;

  return ans;
}

class Solution {
  vector<string> result;
  inline bool check(const string &s) {
    int cnt = 0;
    for (const auto &c : s) {
      if (c == '(') {
        ++cnt;
      } else if (c == ')') {
        if (--cnt < 0) {
          return false;
        }
      }
    }
    return cnt == 0;
  }
  void dfs(string s, int start, int lremove, int rremove) {
    if (lremove == 0 && rremove == 0) {
      if (check(s)) {
        result.emplace_back(s);
      }
      return;
    }

    for (int i = start; i < s.size(); ++i) {
      if (i != start && s[i] == s[i - 1]) {
        continue;
      }
      if (lremove + rremove > s.size() - i) {
        return;
      }
      if (lremove > 0 && s[i] == '(') {
        dfs(s.substr(0, i) + s.substr(i + 1), i, lremove - 1, rremove);
      }
      if (rremove > 0 && s[i] == ')') {
        dfs(s.substr(0, i) + s.substr(i + 1), i, lremove, rremove - 1);
      }
    }
  }

 public:
  vector<string> removeInvalidParentheses(string s) {
    int left = 0;
    int right = 0;

    for (const auto &c : s) {
      if (c == '(') {
        ++left;
      } else if (c == ')') {
        if (left == 0) {
          ++right;
        } else {
          --left;
        }
      }
    }

    dfs(s, 0, left, right);

    return result;
  }
};
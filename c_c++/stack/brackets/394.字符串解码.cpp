/*
给定一个经过编码的字符串，返回它解码后的字符串。
编码规则为：k[encoded_string]，表示其中方括号内部的encoded_string正好重复k次。
注意k保证为正整数，可以认为输入字符串总是有效的；
输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。
可以认为原始数据不包含数字，所有的数字只表示重复的次数k，不会出现像3a或2[4]的输入。

示例1：
输入：s = "3[a]2[bc]"
输出："aaabcbc"

示例2：
输入：s = "3[a2[c]]"
输出："accaccacc"

示例3：
输入：s = "2[abc]3[cd]ef"
输出："abcabccdcdcdef"

示例4：
输入：s = "abc3[cd]xyz"
输出："abccdcdcdxyz"

提示：
1 <= s.length <= 30
s由小写英文字母、数字和方括号'[]'组成
s保证是一个有效的输入。
可能出现括号嵌套的情况。
s中所有整数的取值范围为[1，300]
*/

#include <ctype.h>
#include <string.h>

#include <cstdio>
#include <cstdlib>

#define MAX 2000
char *stack;
int idx;
void pop() { --idx; }
char top() { return stack[idx - 1]; }
void push(char c) { stack[idx++] = c; }
bool empty() { return idx == 0; }
char *decodeString(char *s) {
  stack = (char *)malloc(MAX * sizeof(char));
  memset(stack, 0, MAX * sizeof(char));
  idx = 0;

  char temp[20];
  int index1 = 0;
  int len = strlen(s);
  int nums[400];
  int index2 = 0;

  int i = 0;
  while (i < len) {
    if (s[i] == '[') {  // 入栈
      push(s[i++]);
    } else if (s[i] >= '0' && s[i] <= '9') {  // 获取数字
      nums[index2] = 0;
      while (i < len && s[i] >= '0' && s[i] <= '9') {
        nums[index2] = nums[index2] * 10 + s[i] - '0';
        ++i;
      }
      ++index2;
    } else if (s[i] == ']') {  // 出栈，把重复的结果入栈
      while (top() != '[') {
        temp[index1++] = top();
        pop();
      }
      pop();
      int num = nums[--index2];
      for (int j = 0; j < num; ++j) {
        for (int k = index1 - 1; k >= 0; --k) {
          push(temp[k]);
        }
      }
      index1 = 0;
      ++i;
    } else {  // 字母入栈
      push(s[i++]);
    }
  }
  stack[idx] = 0;

  return stack;
}

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

class Solution {  // 不好理解
 public:
  string getDigits(string &s, size_t &ptr) {
    string ret = "";
    while (isdigit(s[ptr])) {
      ret.push_back(s[ptr++]);
    }
    return ret;
  }
  string getString(vector<string> &v) {
    string ret;
    for (const auto &s : v) {
      ret += s;
    }
    return ret;
  }

  string decodeString(string s) {
    vector<string> stk;
    size_t ptr = 0;

    while (ptr < s.size()) {
      char cur = s[ptr];
      if (isdigit(cur)) {
        // 获取一个数字并进栈：
        string digits = getDigits(s, ptr);
        stk.push_back(digits);
      } else if (isalpha(cur) || cur == '[') {
        // 获取一个字母并进栈：
        stk.push_back(string(1, s[ptr++]));
      } else {
        ++ptr;
        vector<string> sub;
        while (stk.back() != "[") {
          sub.push_back(stk.back());
          stk.pop_back();
        }
        reverse(sub.begin(), sub.end());
        // 左括号出栈：
        stk.pop_back();
        // 此时栈顶为当前sub对应的字符串应该出现的次数：
        int repTime = stoi(stk.back());
        stk.pop_back();
        string t, o = getString(sub);
        // 构造字符串：
        while (repTime--) t += o;
        // 将构造好的字符串入栈：
        stk.push_back(t);
      }
    }

    return getString(stk);
  }
};

class Solution {
 public:
  string decodeString(string s) {
    string res = "";
    stack<int> nums;
    stack<string> strs;
    int num = 0;
    int len = s.size();
    for (int i = 0; i < len; ++i) {
      if (s[i] >= '0' && s[i] <= '9') {
        num = num * 10 + s[i] - '0';
      } else if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) {
        res = res + s[i];
      } else if (s[i] == '[') {  // 将[前的数字压入nums栈内，字符串压入strs栈内
        nums.push(num);
        num = 0;
        strs.push(res);
        res = "";
      } else {  //遇到]时，操作与之相配的[之间的字符，使用分配律
        int times = nums.top();
        nums.pop();
        for (int j = 0; j < times; ++j) {
          strs.top() += res;
        }
        // 之后若还是字母，就会直接加到res之后，因为它们是同一级的运算；
        // 若是左括号，res会被压入strs栈，作为上一层的运算。
        res = strs.top();
        strs.pop();
      }
    }
    return res;
  }
};

// 递归
#define STR_LEN 2000
char *decodeStringCore(char *s, char **e) {
  char *ret = (char *)malloc(sizeof(char) * STR_LEN);
  char *buf, *end = NULL;
  int count = 0, idx = 0;

  while (*s != '\0') {
    if (isalpha(*s)) {
      ret[idx++] = *s;
    } else if (isdigit(*s)) {
      count = 10 * count + *s - '0';
    } else if (*s == '[') {
      buf = decodeStringCore(s + 1, &end);
      while (count) {
        strcpy(ret + idx, buf);
        idx += strlen(buf);
        count--;
      }
      s = end;
    } else if (*s == ']') {
      *e = s;
      ret[idx] = '\0';
      return ret;
    }
    s++;
  }
  ret[idx] = '\0';
  return ret;
}
char *decodeString1(char *s) {
  char *end = NULL;
  return decodeStringCore(s, &end);
}

int main() {
  char *ret = decodeString("3[a]2[bc]");
  printf("%s\n", ret);  // aaabcbc
  ret = decodeString("3[a2[c]]");
  printf("%s\n", ret);  // accaccacc
  ret = decodeString("1[1[p]1[1[j]]]");
  printf("%s\n", ret);  // pj

  ret = decodeString1("3[a]2[bc]");
  printf("%s\n", ret);  // aaabcbc
  ret = decodeString1("3[a2[c]]");
  printf("%s\n", ret);  // accaccacc
  ret = decodeString1("1[1[p]1[1[j]]]");
  printf("%s\n", ret);  // pj
}
/*
实现myAtoi(string s)函数，将字符串转换成一个32位有符号整数（类似atoi函数）。
函数myAtoi(string s)的算法如下：
读入字符串并丢弃无用的前导空格，检查下一个字符为正还是负号，读取该字符（如果有）。
确定最终结果是负数还是正数，如果两者都不存在，则假定结果为正。
读入下一个字符，直到到达下一个非数字字符或到达输入的结尾，字符串的其余部分将被忽略。
将前面步骤读入的这些数字转换为整数（即，"123"->123，"0032"->32）。
如果没有读入数字，则整数为0。必要时更改符号（从步骤2开始）。
如果整数数超过32位有符号整数范围[−2^31,2^31-1]，需要截断这个整数，
使其保持在这个范围内。具体来说，小于-2^31的整数应该被固定为-2^31，
大于2^31-1的整数应该被固定为2^31-1，返回整数作为最终结果。

注意：
本题中的空白字符只包括空格字符' '。
除前导空格或数字后的其余字符串外，请勿忽略任何其他字符。

示例1：
输入：s = "42"
输出：42
解释：加粗的字符串为已经读入的字符，插入符号是当前读取的字符。
第1步："42"（当前没有读入字符，因为没有前导空格）
         ^
第2步："42"（当前没有读入字符，因为这里不存在'-'或者'+'）
         ^
第3步："42"（读入"42"）
           ^
解析得到整数42。
由于"42"在范围[-2^31, 2^31 - 1] 内，最终结果为42。

示例2：
输入：s = "   -42"
输出：-42
解释：
第1步："   -42"（读入前导空格，但忽视掉）
            ^
第2步："   -42"（读入'-' 字符，所以结果应该是负数）
             ^
第3步："   -42"（读入"42"）
               ^
解析得到整数-42。
由于"-42"在范围 [-2^31, 2^31-1]内，最终结果为-42。

示例3：
输入：s = "4193 with words"
输出：4193
解释：
第1步："4193 with words"（当前没有读入字符，因为没有前导空格）
         ^
第2步："4193 with words"（当前没有读入字符，因为这里不存在'-'或者'+'）
         ^
第3步："4193 with words"（读入"4193"；下一个字符不是数字，所以读入停止）
             ^
解析得到整数4193。
由于"4193"在范围[-2^31, 2^31-1]内，最终结果为4193。

提示：
0 <= s.length <= 200
s由英文字母（大写和小写）、数字（0-9）、' '、'+'、'-'和'.'组成
*/

// 剑指Offer67把字符串转换成整数

int myAtoi(char* s) {
  int len = strlen(s), index = 0;
  while (index < len && s[index] == ' ') {
    index++;
  }
  if (index == len) {
    return 0;
  }
  int neg = 1;
  if (s[index] == '-') {
    neg = -1;
    index++;
  } else if (s[index] == '+') {
    index++;
  }
  long long ans = 0;
  while (index < len && isdigit(s[index])) {
    int num = s[index] - '0';
    ans = ans * 10 + num;
    index++;
    if (ans > INT_MAX) break;
  }
  ans *= neg;
  if (ans > 0 && ans > INT_MAX) return INT_MAX;
  if (ans < 0 && ans < INT_MIN) return INT_MIN;

  return ans;
}

class Solution {
 public:
  int myAtoi(string s) {
    int res = 0;
    int flag = 1;  // 正负号
    int cur = 0;   // 当前位置

    while (cur < s.size() && ' ' == s[cur]) {
      ++cur;
    }

    if (cur < s.size() && '+' == s[cur]) {
      ++cur;
    } else if (cur < s.size() && '-' == s[cur]) {
      flag = -1;
      ++cur;
    }

    // isdigit保证了只获取最开始连续的数字，而且也保证了，后续不会获取到字符：
    while (cur < s.size() && isdigit(s[cur])) {
      int num = s[cur] - '0';

      // 核心代码，判断是否溢出：
      if (res > INT_MAX / 10 || (res == INT_MAX / 10 && num > INT_MAX % 10)) {
        return 1 == flag ? INT_MAX : INT_MIN;
      }

      res = res * 10 + num;
      ++cur;
    }

    return 1 == flag ? res : -res;  // 判断flag的正负性
  }
};

// 状态机
class Automaton {
  string state = "start";
  unordered_map<string, vector<string>> table = {
      {"start", {"start", "signed", "in_number", "end"}},
      {"signed", {"end", "end", "in_number", "end"}},
      {"in_number", {"end", "end", "in_number", "end"}},
      {"end", {"end", "end", "end", "end"}}};

  int get_col(char c) {
    if (isspace(c)) return 0;
    if (c == '+' or c == '-') return 1;
    if (isdigit(c)) return 2;
    return 3;
  }

 public:
  int sign = 1;
  long long ans = 0;

  void get(char c) {
    state = table[state][get_col(c)];
    if (state == "in_number") {
      ans = ans * 10 + c - '0';
      ans = sign == 1 ? min(ans, (long long)INT_MAX)
                      : min(ans, -(long long)INT_MIN);
    } else if (state == "signed")
      sign = c == '+' ? 1 : -1;
  }
};
class Solution {
 public:
  int myAtoi(string str) {
    Automaton automaton;
    for (char c : str) automaton.get(c);
    return automaton.sign * automaton.ans;
  }
};
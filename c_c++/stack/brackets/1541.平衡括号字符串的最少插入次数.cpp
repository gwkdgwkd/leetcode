/*
"())"，"())(())))"和"(())())))"是平衡的，")()"，"()))"和"(()))"是不平衡的。
可以在任意位置插入字符'('和')'使字符串平衡，请你返回让s平衡的最少插入次数。

示例1：
输入：s = "(()))"
输出：1
解释：第二个左括号有与之匹配的两个右括号，
     但是第一个左括号只有一个右括号。
     需要在字符串结尾额外增加一个')'，
     使字符串变成平衡字符串"(())))"。

示例2：
输入：s = "())"
输出：0
解释：字符串已经平衡了。

示例3：
输入：s = "))())("
输出：3
解释：添加'('去匹配最开头的'))'，然后添加'))'去匹配最后一个'('。

示例4：
输入：s = "(((((("
输出：12
解释：添加12个')'得到平衡字符串。

示例5：
输入：s = ")))))))"
输出：5
解释：在开头添加4个'('并在结尾添加1个')'，字符串变成平衡字符串"(((())))))))"。

提示：
1 <= s.length <= 10^5
s只包含'('和')'。
*/

int minInsertions(char* s) {
  int res = 0;   // 插入的括号的个数
  int need = 0;  // 需要的右括号的个数

  int len = strlen(s);
  for (int i = 0; i < len; i++) {
    if (s[i] == '(') {
      need += 2;
      if (need % 2 == 1) {
        res++;
        need--;
      }
    }

    if (s[i] == ')') {
      if (need == 0) {
        res++;
        need = 1;
      } else {
        need--;
      }
    }
  }

  return res + need;
}

class Solution {
 public:
  int minInsertions(string s) {
    int n = s.size();

    int left = 0;
    int right = 0;

    for (int i = 0; i < n; ++i) {
      if (s[i] == '(') {
        right += 2;
        if (right % 2) {
          ++left;
          --right;
        }
      }

      if (s[i] == ')') {
        if (right == 0) {
          ++left;
          ++right;
        } else {
          --right;
        }
      }
    }

    return left + right;
  }
};

// 贪心 + 模拟栈
class Solution {
 public:
  int minInsertions(string s) {
    int n = s.size();
    int left = 0;   // 左括号剩余数量
    int right = 0;  // 右括号剩余数量
    for (int i = 0; i < n; ++i) {
      if (s[i] == '(') {  // 遇到左括号，计数直接增加
        ++left;
      } else {  // 遇到右括号
        if (i + 1 < n && s[i + 1] == ')') {
          ++i;  // 1
        } else {
          ++right;  // 2
        }

        if (left > 0) {
          --left;  // 3
        } else {
          ++right;  // 4
        }
      }
    }

    return left * 2 + right;  // 每个左括号需要2个右括号消除
  }
};
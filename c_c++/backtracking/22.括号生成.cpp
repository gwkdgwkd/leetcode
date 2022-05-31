/*
数字n代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且有效的括号组合。

示例1：
输入：n = 3
输出：["((()))","(()())","(())()","()(())","()()()"]

示例2：
输入：n = 1
输出：["()"]

提示：1 <= n <= 8
*/

// 剑指OfferII085生成匹配的括号
// 面试题0809括号

// 回溯算法
// 翻译：现在有2n个位置，每个位置可以放置字符(或者)，组成的所有括号组合中，有多少个是合法的？
// 有关括号问题，你只要记住两个个性质，思路就很容易想出来：
// 1.一个合法括号组合的左括号数量一定等于右括号数量，这个显而易见。
// 2.对于一个合法的括号字符串组合p，必然对于任何0 <= i < len(p)都有：
//   子串p[0..i]中左括号的数量都大于或等于右括号的数量。
char **res;
int resSize;
char *path;
int pathSize;
void backtrack(int left, int right) {
  if (right < 0 || left < 0 || right < left) {
    return;
  }

  if (right == 0 && left == 0) {
    res[resSize] = (char *)malloc(sizeof(char) * (pathSize + 1));
    memcpy(res[resSize], path, pathSize);
    res[resSize++][pathSize] = 0;
    return;
  }

  path[pathSize++] = '(';
  backtrack(left - 1, right);
  pathSize--;

  path[pathSize++] = ')';
  backtrack(left, right - 1);
  pathSize--;
}
char **generateParenthesis(int n, int *returnSize) {
  res = (char **)malloc(sizeof(char *) * 10000);
  path = (char *)malloc(sizeof(char) * 2 * n);

  resSize = pathSize = 0;
  backtrack(n, n);

  *returnSize = resSize;
  return res;
}

class Solution {
  vector<string> ans;
  string path;

 public:
  void backtracking(int left, int right) {
    if (right < 0 || left < 0 || right < left) {
      return;
    }

    if (right == 0 && left == 0) {
      ans.emplace_back(path);
      return;
    }
    path.push_back('(');
    backtracking(left - 1, right);
    path.pop_back();

    path.push_back(')');
    backtracking(left, right - 1);
    path.pop_back();
  }
  vector<string> generateParenthesis(int n) {
    backtracking(n, n);
    return ans;
  }
};
/*
给一个字符串s，字符串的能量定义为：只包含一种字符的最长非空子字符串的长度。
请返回字符串s的能量。

示例1：
输入：s = "leetcode"
输出：2
解释：子字符串"ee"长度为2，只包含字符'e'。

示例2：
输入：s = "abbcccddddeeeeedcba"
输出：5
解释：子字符串"eeeee"长度为5，只包含字符'e'。


提示：
1 <= s.length <= 500
s只包含小写英文字母。
*/

// 一次遍历
class Solution {
 public:
  int maxPower(string s) {
    int n = s.size();
    int ans = 1;
    int cnt = 1;
    for (int i = 1; i < n; ++i) {
      if (s[i] == s[i - 1]) {
        ++cnt;
        ans = max(ans, cnt);
      } else {
        cnt = 1;
      }
    }
    return ans;
  }
};

// 分组循环，按照题目要求，数组会被分割成若干组，每一组的判断/处理逻辑是相同的。
class Solution {
 public:
  int maxPower(string s) {
    int n = s.size();
    int ans = 0;

    for (int i = 0; i < n; ++i) {
      // 外层循环负责遍历组之前的准备工作（记录开始位置），
      // 和遍历组之后的统计工作（更新答案最大值）：
      int count = 1;
      for (int j = i + 1; j < n; ++j) {
        // 内层循环负责遍历组，找出这一组最远在哪结束：
        if (s[j] == s[i]) {
          ++count;
        } else {
          break;
        }
      }
      ans = max(ans, count);
    }
    return ans;
  }
};
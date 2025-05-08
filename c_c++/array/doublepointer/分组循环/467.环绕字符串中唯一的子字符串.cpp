/*
定义字符串base为一个"abcdefghijklmnopqrstuvwxyz"无限环绕的字符串，
所以base看起来是这样的：
"...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd....".
给一个字符串s，请统计并返回s中有多少不同非空子串也在base中出现。

示例1：
输入：s = "a"
输出：1
解释：字符串s的子字符串"a"在base中出现。

示例2：
输入：s = "cac"
输出：2
解释：字符串s有两个子字符串("a","c")在base中出现。

示例3：
输入：s = "zab"
输出：6
解释：字符串s有六个子字符串("z","a","b","za","ab","zab")在base中出现。


提示：
1 <= s.length <= 10^5
s由小写英文字母组成
*/

// 动态规划
class Solution {
 public:
  int findSubstringInWraproundString(string p) {
    vector<int> dp(26);
    int k = 0;
    for (int i = 0; i < p.length(); ++i) {
      if (i && (p[i] - p[i - 1] + 26) % 26 == 1) {  // 字符之差为1或-25
        ++k;
      } else {
        k = 1;
      }
      dp[p[i] - 'a'] = max(dp[p[i] - 'a'], k);
    }
    return accumulate(dp.begin(), dp.end(), 0);
  }
};

// 分组循环

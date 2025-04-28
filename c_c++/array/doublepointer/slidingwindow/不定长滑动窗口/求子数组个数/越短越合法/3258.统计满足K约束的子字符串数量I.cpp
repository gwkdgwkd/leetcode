/*
给一个二进制字符串s和一个整数k。
如果一个二进制字符串满足以下任一条件，则认为该字符串满足k约束：
字符串中0的数量最多为k。
字符串中1的数量最多为k。
返回一个整数，表示s的所有满足k约束的的数量。

示例1：
输入：s = "10101", k = 1
输出：12
解释：s的所有子字符串中，除了"1010"、"10101"和"0101"外，
     其余子字符串都满足k约束。

示例2：
输入：s = "1010101", k = 2
输出：25
解释：s的所有子字符串中，除了长度大于5的子字符串外，其余子字符串都满足k约束。

示例3：
输入：s = "11111", k = 1
输出：15
解释：s的所有子字符串都满足k约束。


提示：
1 <= s.length <= 50
1 <= k <= s.length
s[i]是'0'或'1'。
*/

class Solution {
 public:
  int countKConstraintSubstrings(string s, int k) {
    int n = s.size();
    int ans = 0;
    int left = 0;
    int right = 0;
    int cnt[2]{};

    while (right < n) {
      cnt[s[right++] - '0']++;
      while (cnt[0] > k && cnt[1] > k) {
        cnt[s[left++] - '0']--;
      }
      ans += right - left;
    }
    return ans;
  }
};
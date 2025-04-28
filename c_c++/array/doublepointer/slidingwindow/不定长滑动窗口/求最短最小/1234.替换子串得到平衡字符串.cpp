/*
有一个只含有'Q', 'W', 'E', 'R'四种字符，且长度为n的字符串。
假如在该字符串中，这四个字符都恰好出现n/4次，那么它就是一个平衡字符串。
给一个这样的字符串s，请通过替换一个子串的方式，使原字符串s变成一个平衡字符串。
可以用和待替换子串长度相同的任何其他字符串来完成替换。
请返回待替换子串的最小可能长度。
如果原字符串自身就是一个平衡字符串，则返回0。

示例1：
输入：s = "QWER"
输出：0
解释：s已经是平衡的了。

示例2：
输入：s = "QQWE"
输出：1
解释：需要把一个'Q'替换成'R'，这样得到的"RQWE"(或"QRWE")是平衡的。

示例3：
输入：s = "QQQW"
输出：2
解释：可以把前面的"QQ"替换成"ER"。

示例4：
输入：s = "QQQQ"
输出：3
解释：可以替换后3个'Q'，使s = "QWER"。


提示：
1 <= s.length <= 10^5
s.length是4的倍数
s中只含有'Q','W','E','R'四种字符
*/

/*
根据题意，如果在待替换子串之外的任意字符的出现次数超过m=4n​，
那么无论怎么替换，都无法使这个字符在整个字符串中的出现次数为m。
反过来说，如果在待替换子串之外的任意字符的出现次数都不超过m，
那么可以通过替换，使s为平衡字符串，即每个字符的出现次数均为m。

对于本题，设子串的左右端点为left和right，枚举right，
如果子串外的任意字符的出现次数都不超过m，
则说明从left到right的这段子串可以是待替换子串，
用其长度right−left+1更新答案的最小值，并向右移动left，缩小子串长度。
*/
class Solution {
 public:
  int balancedString(string s) {
    int cnt['X']{};
    for (char c : s) {
      cnt[c]++;
    }
    int n = s.size();
    int m = n / 4;
    if (cnt['Q'] == m && cnt['W'] == m && cnt['E'] == m && cnt['R'] == m) {
      return 0;
    }

    int ans = n;
    int left = 0;
    int right = 0;
    while (right < n) {
      cnt[s[right++]]--;
      while (cnt['Q'] <= m && cnt['W'] <= m && cnt['E'] <= m && cnt['R'] <= m) {
        ans = min(ans, right - left);
        cnt[s[left++]]++;
      }
    }
    return ans;
  }
};

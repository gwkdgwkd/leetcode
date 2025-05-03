/*
给一个字符串s，它只包含三种字符a, b和c。
请返回a，b和c都至少出现过一次的子字符串数目。

示例1：
输入：s = "abcabc"
输出：10
解释：包含a，b和c各至少一次的子字符串为"abc", "abca", "abcab", "abcabc",
     "bca", "bcab", "bcabc", "cab", "cabc"和"abc"(相同字符串算多次)。

示例2：
输入：s = "aaacb"
输出：3
解释：包含a，b和c各至少一次的子字符串为"aaacb", "aacb"和"acb"。

示例3：
输入：s = "abc"
输出：1


提示：
3 <= s.length <= 5 x 10^4
s只包含字符a，b 和 c。
*/

class Solution {
 public:
  int numberOfSubstrings(string s) {
    int n = s.size();
    int cnt[3]{};
    int right = 0;
    int left = 0;
    int ans = 0;
    while (right < n) {
      cnt[s[right++] - 'a']++;
      /*
      一般要写ans += left。
      内层循环结束后，[left,right]这个子数组是不满足题目要求的，
      但在退出循环之前的最后一轮循环，[left−1,right]是满足题目要求的。
      由于子数组越长，越能满足题目要求，所以除了[left−1,right]，
      还有[left−2,right],[left−3,right],…,[0,right]都是满足要求的。
      也就是说，当右端点固定在right时，
      左端点在0,1,2,…,left−1的所有子数组都是满足要求的，这一共有left个。
      */
      while (cnt[0] && cnt[1] && cnt[2]) {
        cnt[s[left++] - 'a']--;
      }
      ans += left;
    }
    return ans;
  }
};
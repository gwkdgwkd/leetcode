/*
给字符串s和整数k。
请返回字符串s中长度为k的单个子字符串中可能包含的最大元音字母数。
英文中的元音字母为（a, e, i, o, u）。

示例1：
输入：s = "abciiidef", k = 3
输出：3
解释：子字符串"i"包含3个元音字母。

示例2：
输入：s = "aeiou", k = 2
输出：2
解释：任意长度为2的子字符串都包含2个元音字母。

示例3：
输入：s = "leetcode", k = 3
输出：2
解释："lee"、"eet"和"ode"都包含2个元音字母。

示例4：
输入：s = "rhythms", k = 4
输出：0
解释：字符串s中不含任何元音字母。

示例5：
输入：s = "tryhard", k = 4
输出：1


提示：
1 <= s.length <= 10^5
s由小写英文字母组成
1 <= k <= s.length
*/

/*
要计算所有长度恰好为k的子串中，最多可以包含多少个元音字母。
暴力枚举所有子串？时间复杂度是O(nk)，太慢了。能否O(1)计算子串的元音个数？
这是可以做到的，对于字符串abci，假如已经计算出了子串abc的元音个数，那么从子串abc到子串bci，
只需要考虑移除（离开窗口）的字母a是不是元音，以及添加（进入窗口）的字母i是不是元音即可，
因为中间的字母b和c都在这两个子串中。
*/

// 定长滑窗套路：入-更新-出，这三步适用于所有定长滑窗题目。
class Solution {
  // 时间复杂度：O(n)，其中n是s的长度。
  // 空间复杂度：O(1)，仅用到若干额外变量。
 public:
  int maxVowels(string s, int k) {
    int ans = 0;
    int cnt = 0;
    for (int i = 0; i < s.size(); ++i) {
      // 1.入，下标为i的元素进入窗口，更新相关统计量，如果i<k−1则重复第一步：
      if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' ||
          s[i] == 'u') {
        ++cnt;
      }
      if (i < k - 1) {
        continue;
      }

      // 2.更新，更新答案，一般是更新最大值/最小值：
      ans = max(ans, cnt);

      // 3.出，下标为i−k+1的元素离开窗口，更新相关统计量：
      char left = s[i - k + 1];
      if (left == 'a' || left == 'e' || left == 'i' || left == 'o' ||
          left == 'u') {
        --cnt;
      }
    }
    return ans;
  }
};

// 官方题解
class Solution {
  // 时间复杂度：O(∣s∣)，其中∣s∣是字符串s的长度。
  // 首先需要O(k)的时间求出前k个字母组成的子串包含的元音字母个数，
  // 在这之后还有O(∣s∣−k)个子串，每个子串包含的元音字母个数可以在O(1)的时间计算出，
  // 因此总时间复杂度为O(∣s∣)。
  // 空间复杂度：O(1)。
 public:
  bool isVowel(char ch) {
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
  }

  int maxVowels(string s, int k) {
    int n = s.size();
    int vowel_count = 0;
    for (int i = 0; i < k; ++i) {
      vowel_count += isVowel(s[i]);
    }
    int ans = vowel_count;
    for (int i = k; i < n; ++i) {
      vowel_count += isVowel(s[i]) - isVowel(s[i - k]);
      ans = max(ans, vowel_count);
    }
    return ans;
  }
};
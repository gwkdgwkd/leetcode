/*
给两个字符串word1和word2。
如果一个字符串重新排列后，word2是重排字符串的，那么我们称字符串x是合法的。
请你返回word1中合法的数目。
注意，这个问题中的内存限制比其他题目要小，所以必须实现一个线性复杂度的解法。

示例1：
输入：word1 = "bcca", word2 = "abc"
输出：1
解释：唯一合法的子字符串是"bcca"，可以重新排列得到"abcc"，"abc"是它的前缀。

示例2：
输入：word1 = "abcabc", word2 = "abc"
输出：10
解释：除了长度为1和2的所有子字符串都是合法的。

示例3：
输入：word1 = "abcabc", word2 = "aaabc"
输出：0


提示：
1 <= word1.length <= 106
1 <= word2.length <= 104
word1和word2都只包含小写英文字母。
*/

// 本题是[76.最小覆盖子串]的求个数版本
class Solution {
 public:
  long long validSubstringCount(string word1, string word2) {
    int n1 = word1.size();
    int n2 = word2.size();
    int hash[26]{};

    for (char c : word2) {
      hash[c - 'a']++;
    }

    int left = 0;
    int right = 0;
    long long ans = 0;

    while (right < n1) {
      if (hash[word1[right++] - 'a']-- > 0) {
        --n2;
      }
      while (n2 == 0) {
        if (++hash[word1[left++] - 'a'] > 0) {
          ++n2;
        }
      }
      ans += left;
    }
    return ans;
  }
};
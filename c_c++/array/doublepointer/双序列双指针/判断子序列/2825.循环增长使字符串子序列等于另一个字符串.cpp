/*
给一个下标从0开始的字符串str1和str2。
一次操作中，选择str1中的若干下标。
对于选中的每一个下标i，将str1[i]循环递增，变成下一个字符。
也就是说'a'变成'b'，'b'变成'c'，以此类推，'z'变成'a'。
如果执行以上操作至多一次，可以让str2成为str1的子序列，请返回true，否则返回false。
注意：一个字符串的子序列指的是从原字符串中删除一些（可以一个字符也不删）字符后，
剩下字符按照原本先后顺序组成的新字符串。

示例1：
输入：str1 = "abc", str2 = "ad"
输出：true
解释：选择str1中的下标2。
     将str1[2]循环递增，得到'd'。
     因此，str1变成"abd"且str2现在是一个子序列。所以返回true。

示例2：
输入：str1 = "zc", str2 = "ad"
输出：true
解释：选择str1中的下标0和1。
     将str1[0]循环递增得到'a'。
     将str1[1]循环递增得到'd'。
     因此，str1变成"ad"且str2现在是一个子序列。所以返回true。

示例3：
输入：str1 = "ab", str2 = "d"
输出：false
解释：这个例子中，没法在执行一次操作的前提下，将str2变为str1的子序列。
     所以返回false。


提示：
1 <= str1.length <= 10^5
1 <= str2.length <= 10^5
str1和str2只包含小写英文字母。
*/

class Solution {
 public:
  bool canMakeSubsequence(string str1, string str2) {
    int n1 = str1.size();
    int n2 = str2.size();
    if (n1 < n2) {
      return false;
    }
    int i = 0;
    int j = 0;
    while (i < n1) {
      if (str1[i] == str2[j] || str2[j] - str1[i] == 1 ||
          str1[i] - str2[j] == 25) {
        ++j;
      }
      ++i;
    }
    return !(n2 - j);
  }
};
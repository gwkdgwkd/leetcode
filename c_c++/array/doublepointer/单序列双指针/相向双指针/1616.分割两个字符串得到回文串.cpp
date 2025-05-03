/*
给两个字符串a和b，它们长度相同。
请选择一个下标，将两个字符串都在相同的下标分割开。
由a可以得到两个字符串：aprefix和asuffix，满足a = aprefix + asuffix，
同理，由b可以得到两个字符串bprefix和bsuffix，满足b = bprefix + bsuffix。
请你判断aprefix + bsuffix或者bprefix + asuffix能否构成回文串。
当将一个字符串s分割成sprefix和ssuffix时，ssuffix或者sprefix可以为空。
比方说，s = "abc"那么"" + "abc"，"a" + "bc"，"ab" + "c"和"abc" +""都是合法分割。
如果能构成回文字符串，那么请返回true，否则返回false。
注意，x+y表示连接字符串x和y。

示例1：
输入：a = "x", b = "y"
输出：true
解释：如果a或者b是回文串，那么答案一定为true，因为你可以如下分割：
     aprefix = "", asuffix = "x"
     bprefix = "", bsuffix = "y"
     那么aprefix + bsuffix = "" + "y" = "y"是回文串。

示例2：
输入：a = "xbdef", b = "xecab"
输出：false

示例3：
输入：a = "ulacfd", b = "jizalu"
输出：true
解释：在下标为3处分割：
     aprefix = "ula", asuffix = "cfd"
     bprefix = "jiz", bsuffix = "alu"
     那么aprefix + bsuffix = "ula" + "alu" = "ulaalu"是回文串。


提示：
1 <= a.length, b.length <= 10^5
a.length == b.length
a和b都只包含小写英文字母
*/

class Solution {
  bool isPalindrome(const string& s, int l, int r) {
    while (l < r && s[l] == s[r]) {
      ++l;
      --r;
    }
    return l >= r;
  }
  bool check(const string& s1, const string& s2) {
    int left = 0;
    int right = s2.size() - 1;
    while (left < right && s1[left] == s2[right]) {
      ++left;
      --right;
    }
    return isPalindrome(s1, left, right) || isPalindrome(s2, left, right);
  }

 public:
  bool checkPalindromeFormation(string a, string b) {
    return check(a, b) || check(b, a);
  }
};
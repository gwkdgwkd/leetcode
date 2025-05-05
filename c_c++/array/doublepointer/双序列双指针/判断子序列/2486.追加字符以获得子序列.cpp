/*
给两个仅由小写英文字母组成的字符串s和t。
现在需要通过向s末尾追加字符的方式使t变成s的一个子序列，返回需要追加的最少字符数。
子序列是一个可以由其他字符串删除部分（或不删除）字符但不改变剩下字符顺序得到的字符串。

示例1：
输入：s = "coaching", t = "coding"
输出：4
解释：向s末尾追加字符串"ding"，s = "coachingding" 。
     现在，t是s("coachingding")的一个子序列。
     可以证明向s末尾追加任何3个字符都无法使t成为s的一个子序列。

示例2：
输入：s = "abcde", t = "a"
输出：0
解释：t已经是s("abcde")的一个子序列。

示例3：
输入：s = "z", t = "abcde"
输出：5
解释：向s末尾追加字符串"abcde"，s = "zabcde"。
     现在，t是s("zabcde")的一个子序列。
     可以证明向s末尾追加任何4个字符都无法使t成为s的一个子序列。

提示：
1 <= s.length, t.length <= 10^5
s和t仅由小写英文字母组成
*/

// 双指针
class Solution {
 public:
  int appendCharacters(string s, string t) {
    int sn = s.size();
    int tn = t.size();
    int i = 0;
    int j = 0;

    while (i < sn) {
      if (s[i] == t[j]) {
        ++j;
      }
      ++i;
    }

    return tn - j;
  }
};
/*
给一个字符串word和一个整数numFriends。
Alice正在为她的numFriends位朋友组织一个游戏。游戏分为多个回合，在每一回合中：
word被分割成numFriends个非空字符串，且该分割方式与之前的任意回合所采用的都不完全相同。
所有分割出的字符串都会被放入一个盒子中。
在所有回合结束后，找出盒子中字典序最大的字符串。

示例1：
输入：word = "dbca", numFriends = 2
输出："dbc"
解释：所有可能的分割方式为：
    "d"和"bca"。
    "db"和"ca"。
    "dbc"和"a"。

示例2：
输入：word = "gggg", numFriends = 4
输出："g"
解释：唯一可能的分割方式为："g","g","g",和"g"。


提示:
1 <= word.length <= 5 * 10^3
word 仅由小写英文字母组成。
1 <= numFriends <= word.length
*/

// 枚举子串左端点
class Solution {
  // 时间复杂度：O(n(n−k))，其中n是s的长度。
  // 空间复杂度：O(n−k)或O(1)。Go的切片不会发生拷贝，只需要O(1)额外空间。
 public:
  string answerString(string word, int numFriends) {
    if (numFriends == 1) {
      return word;
    }

    int n = word.size();
    string ans;
    for (int i = 0; i < n; ++i) {
      ans = max(ans, word.substr(i, n - max(numFriends - 1, i)));
    }
    return ans;
  }
};

// 计算字典序最大的后缀（双指针）
class Solution {
  // 时间复杂度：O(n)，其中n是s的长度。
  // 空间复杂度：O(1)。返回值不计入。
 public:
  string answerString(string s, int k) {
    // 如何计算字典序最大的后缀，见[1163.按字典序排在最后的子串]
    if (k == 1) {
      return s;
    }
    int n = s.size();
    int i = 0, j = 1;
    while (j < n) {
      int k = 0;
      while (j + k < n && s[i + k] == s[j + k]) {
        k++;
      }
      if (j + k < n && s[i + k] < s[j + k]) {
        int t = i;
        i = j;
        j = max(j + 1, t + k + 1);
      } else {
        j += k + 1;
      }
    }
    return s.substr(i, n - max(k - 1, i));
  }
};

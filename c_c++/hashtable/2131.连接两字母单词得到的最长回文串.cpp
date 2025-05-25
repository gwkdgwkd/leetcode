/*
给一个字符串数组words。words中每个元素都是一个包含两个小写英文字母的单词。
请从words中选择一些元素并按任意顺序连接它们，并得到一个 尽可能长的回文串。
每个元素至多只能使用一次。
请返回你能得到的最长回文串的长度。如果没办法得到任何一个回文串，请返回0。
回文串指的是从前往后和从后往前读一样的字符串。

示例1：
输入：words = ["lc","cl","gg"]
输出：6
解释：一个最长的回文串为"lc" + "gg" + "cl" = "lcggcl"，长度为6。
     "clgglc"是另一个可以得到的最长回文串。

示例2：
输入：words = ["ab","ty","yt","lc","cl","ab"]
输出：8
解释：最长回文串是"ty" + "lc" + "cl" + "yt" = "tylcclyt"，长度为8。
     "lcyttycl"是另一个可以得到的最长回文串。

示例3：
输入：words = ["cc","ll","xx"]
输出：2
解释：最长回文串是"cc"，长度为2。"ll"是另一个可以得到的最长回文串。"xx"也是。


提示：
1 <= words.length <= 10^5
words[i].length == 2
words[i]仅包含小写英文字母。
*/

class Solution {
 public:
  int longestPalindrome(vector<string>& words) {
    unordered_map<string, int> cnt;
    int n = words.size();
    int ans = 0;
    for (const string& s : words) {
      if (s[0] == s[1]) {
        if (cnt.find(s) != cnt.end()) {
          ans += 4;
          cnt.erase(s);
        } else {
          cnt[s]++;
        }
      } else if (s[0] != s[1]) {
        string tmp{s[1], s[0]};
        if (cnt.find(tmp) != cnt.end()) {
          ans += 4;
          if (--cnt[tmp] == 0) {
            cnt.erase(tmp);
          }
        } else {
          cnt[s]++;
        }
      }
    }
    for (auto it = cnt.begin(); it != cnt.end(); it++) {
      if (it->first[0] == it->first[1] && it->second == 1) {
        ans += 2;
        break;
      }
    }
    return ans;
  }
};

// 分类讨论
class Solution {
 public:
  int longestPalindrome(vector<string>& words) {
    int cnt[26][26]{};
    for (auto& w : words) {
      cnt[w[0] - 'a'][w[1] - 'a']++;
    }

    int ans = 0, odd = 0;
    for (int i = 0; i < 26; i++) {
      int c = cnt[i][i];
      ans += c - c % 2;  // 保证结果是偶数，也可以写成c&~1
      odd |= c % 2;      // 存在出现奇数次的cnt[i][i]
      for (int j = i + 1; j < 26; j++) {
        ans += min(cnt[i][j], cnt[j][i]) * 2;
      }
    }
    return (ans + odd) * 2;  // 上面统计的是字符串个数，乘以2就是长度
  }
};
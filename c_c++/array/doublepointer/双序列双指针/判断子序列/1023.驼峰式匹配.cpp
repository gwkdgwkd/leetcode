/*
给一个字符串数组queries，和一个表示模式的字符串pattern，请返回一个布尔数组answer。
只有在待查项queries[i]与模式串pattern匹配时，answer[i]才为true，否则为false。
如果可以将小写字母插入模式串pattern得到待查询项queries[i]，
那么待查询项与给定模式串匹配。
可以在模式串中的任何位置插入字符，也可以选择不插入任何字符。

示例1：
输入：queries=["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"],
     pattern = "FB"
输出：[true,false,true,true,false]
解释："FooBar"可以这样生成："F" + "oo" + "B" + "ar"
     "FootBall"可以这样生成："F" + "oot" + "B" + "all"
     "FrameBuffer"可以这样生成："F" + "rame" + "B" + "uffer"

示例2：
输入：queries=["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"],
     pattern = "FoBa"
输出：[true,false,true,false,false]
解释："FooBar"可以这样生成：
     "Fo" +"o" + "Ba" + "r"
     "FootBall"可以这样生成："Fo" + "ot" + "Ba" + "ll"

示例3：
输入：queries=["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"],
     pattern ="FoBaT"
输出：[false,true,false,false,false]
解释："FooBarTest"可以这样生成："Fo" + "o" + "Ba" + "r" + "T" + "est"


提示：
1 <= pattern.length, queries.length <= 100
1 <= queries[i].length <= 100
queries[i]和pattern由英文字母组成
*/

class Solution {
 public:
  vector<bool> camelMatch(vector<string>& queries, string pattern) {
    int n = queries.size();
    int m = pattern.size();
    vector<bool> ans(n, true);
    for (int i = 0; i < n; ++i) {
      int j = 0;
      for (char c : queries[i]) {
        if (j < m && pattern[j] == c) {
          ++j;
        } else if (isupper(c)) {
          ans[i] = false;
          break;
        }
      }
      if (j < m) {
        ans[i] = false;
      }
    }
    return ans;
  }
};
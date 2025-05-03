/*
的初始能量为power，初始分数为0，只有一包令牌以整数数组tokens给出。
其中tokens[i]是第i个令牌的值（下标从0开始）。
的目标是通过有策略地使用这些令牌以最大化总分数。
在一次行动中，可以用两种方式中的一种来使用一个未被使用的令牌（但不是对同一个令牌使用两种方式）：
朝上：如果当前至少有tokens[i]点能量，可以使用令牌i，失去tokens[i]点能量，并得到1分。
朝下：如果当前至少有1分，可以使用令牌i，获得tokens[i]点能量，并失去1分。
在使用任意数量的令牌后，返回我们可以得到的最大分数。

示例1：
输入：tokens = [100], power = 50
输出：0
解释：因为你的初始分数为0，无法使令牌朝下。
     也不能使令牌朝上因为你的能量（50）比tokens[0]少（100）。

示例2：
输入：tokens = [200,100], power = 150
输出：1
解释：使令牌1正面朝上，能量变为50，分数变为1。
     不必使用令牌0，因为你无法使用它来提高分数。可得到的最大分数是1。

示例3：
输入：tokens = [100,200,300,400], power = 200
输出：2
解释：按下面顺序使用令牌可以得到2分：
     1.令牌0(100)正面朝上，能量变为100，分数变为1
     2.令牌3(400)正面朝下，能量变为500，分数变为0
     3.令牌1(200)正面朝上，能量变为300，分数变为1
     4.令牌2(300)正面朝上，能量变为0，分数变为2
     可得的最大分数是2。


提示：
0 <= tokens.length <= 1000
0 <= tokens[i], power < 10^4
*/

class Solution {
 public:
  int bagOfTokensScore(vector<int>& tokens, int power) {
    int n = tokens.size();
    sort(tokens.begin(), tokens.end());
    int ans = 0;
    int left = 0, right = n - 1;
    for (int i = 0; i < n; i++) {
      if (power >= tokens[left]) {
        ans += 1;
        power -= tokens[left];
        left++;
      } else if (ans > 0 && i < n - 1) {
        power += tokens[right];
        ans--;
        right--;
      } else {
        break;
      }
    }
    return ans;
  }
};

class Solution {
 public:
  int bagOfTokensScore(vector<int>& tokens, int power) {
    if (tokens.empty()) return 0;
    sort(tokens.begin(), tokens.end());
    if (power < tokens[0]) return 0;
    int n = tokens.size();
    int left = 0;
    int right = n - 1;
    int score = 0;
    int res = 0;
    while (left <= right) {
      if (power < tokens[left]) {
        if (score <= 0) return res;
        power += tokens[right];
        --score;
        --right;
      } else {
        power -= tokens[left];
        ++score;
        ++left;
        res = max(res, score);
      }
    }
    return res;
  }
};
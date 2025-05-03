/*
n张多米诺骨牌排成一行，将每张多米诺骨牌垂直竖立。
在开始时，同时把一些多米诺骨牌向左或向右推。
每过一秒，倒向左边的多米诺骨牌会推动其左侧相邻的多米诺骨牌。
同样地，倒向右边的多米诺骨牌也会推动竖立在其右侧的相邻多米诺骨牌。
如果一张垂直竖立的多米诺骨牌的两侧同时有多米诺骨牌倒下时，由于受力平衡，该骨牌仍然保持不变。
就这个问题而言，
会认为一张正在倒下的多米诺骨牌不会对其它正在倒下或已经倒下的多米诺骨牌施加额外的力。
给你一个字符串dominoes表示这一行多米诺骨牌的初始状态，其中：
dominoes[i] = 'L'，表示第i张多米诺骨牌被推向左侧，
dominoes[i] = 'R'，表示第i张多米诺骨牌被推向右侧，
dominoes[i] = '.'，表示没有推动第i张多米诺骨牌。
返回表示最终状态的字符串。

示例1：
输入：dominoes = "RR.L"
输出："RR.L"
解释：第一张多米诺骨牌没有给第二张施加额外的力。

示例2：
输入：dominoes = ".L.R...LR..L.."
输出："LL.RR.LLRRLL.."


提示：
n == dominoes.length
1 <= n <= 10^5
dominoes[i]为'L'、'R'或'.'
*/

/*
根据题意，有四种情况：
L...L：中间的点全部变成L。
R...R：中间的点全部变成R。
R...L：前一半的点全部变成R，后一半的点全部变成L，如果有奇数个点，则正中间的点不变。
L...R：不变。
*/

class Solution {
  // 时间复杂度：O(n)，n是dominoes的长度。每个点至多被修改一次，总的循环次数是O(n)。
  // 空间复杂度：O(n)或O(1)，取决于实现。
 public:
  string pushDominoes(string dominoes) {
    // 为方便处理开头和结尾的点，可以在字符串前后各加一个哨兵：
    string s = "L" + dominoes + "R";
    int n = s.size();
    int pre = 0;  // 初表示上一个L或R的位置
    for (int i = 1; i < n; ++i) {
      if (s[i] == '.') {
        continue;  // 如果s[i]是点，跳过
      }
      if (s[i] == s[pre]) {
        // 如果s[i]=s[pre]，pre到i是L...L或者R...R，全部变成s[i]：
        fill(s.begin() + pre + 1, s.begin() + i, s[i]);
      } else if (s[i] == 'L') {
        // 如果s[i]=L，说明从pre到i是R...L，
        // 把前一半的点全部变成R，后一半的点全部变成L。
        // 这可以兼容奇数个点和偶数个点的情况：
        fill(s.begin() + pre + 1, s.begin() + (pre + i + 1) / 2, 'R');
        fill(s.begin() + (pre + i) / 2 + 1, s.begin() + i, 'L');
      }
      // else分支，从pre到i是L...R，保持不变

      pre = i;  // 记录pre=i，继续循环
    }
    return s.substr(1, n - 2);
  }
};

// 原地修改
class Solution {
 public:
  string pushDominoes(string s) {
    int n = s.size();
    int pre = -1;  // 上一个 L 或 R 的位置
    for (int i = 0; i <= n; i++) {
      char ch = i < n ? s[i] : 'R';
      if (ch == '.') {
        continue;
      }
      if (ch == (pre < 0 ? 'L' : s[pre])) {            // L...L或R...R
        fill(s.begin() + pre + 1, s.begin() + i, ch);  // 全变成s[i]
      } else if (ch == 'L') {                          // R...L
        fill(s.begin() + pre + 1, s.begin() + (pre + i + 1) / 2, 'R');
        fill(s.begin() + (pre + i) / 2 + 1, s.begin() + i, 'L');
      }
      pre = i;
    }

    return s;
  }
};
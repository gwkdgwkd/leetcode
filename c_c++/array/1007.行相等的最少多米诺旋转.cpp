/*
在一排多米诺骨牌中，tops[i]和bottoms[i]分别代表第i个多米诺骨牌的上半部分和下半部分。
一个多米诺是两个从1到6的数字同列平铺形成的，该平铺的每一半上都有一个数字。
可以旋转第i张多米诺，使得tops[i]和bottoms[i]的值交换。
返回能使tops中所有值或者bottoms中所有值都相同的最小旋转次数。
如果无法做到，返回-1。

示例1：
输入：tops = [2,1,2,4,2,2], bottoms = [5,2,6,2,3,2]
输出：2
解释：旋转第二个和第四个多米诺骨牌，可以使上面一行中的每个值都等于2。

示例2：
输入：tops = [3,5,1,2,3], bottoms = [3,6,3,3,4]
输出：-1
解释：在这种情况下，不可能旋转多米诺牌使一行的值相等。


提示：
2 <= tops.length <= 2 * 10^4
bottoms.length == tops.length
1 <= tops[i], bottoms[i] <= 6
*/

class Solution {
 public:
  int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
    int n = tops.size();
    auto check = [&n](int k, vector<int>& t, vector<int>& b) -> int {
      int cnt = 0;
      for (int i = 0; i < n; ++i) {
        if (t[i] == k) {
          continue;
        }
        if (b[i] == k) {
          ++cnt;
        } else {
          return INT_MAX;
        }
      }
      return cnt;
    };

    int ans = INT_MAX;
    for (int i = 1; i <= 6; ++i) {
      int cnt = check(i, tops, bottoms);
      ans = min(ans, cnt);
    }
    for (int i = 1; i <= 6; ++i) {
      int cnt = check(i, bottoms, tops);
      ans = min(ans, cnt);
    }

    return ans == INT_MAX ? -1 : ans;
  }
};

class Solution {
 public:
  int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
    auto min_rot = [&](int target) -> int {
      int to_top = 0, to_bottom = 0;
      for (int i = 0; i < tops.size(); i++) {
        int x = tops[i], y = bottoms[i];
        if (x != target && y != target) {
          return INT_MAX;
        }
        if (x != target) {
          to_top++;  // 把y旋转到上半
        } else if (y != target) {
          to_bottom++;  // 把x旋转到下半
        }
      }
      return min(to_top, to_bottom);
    };

    // 目标是让第一排或者第二排的所有数都相同，这个所有必然包含第一个骨牌中的数。
    // 所以要么都变成tops[0]，要么都变成bottoms[0]，计算这两种情况，取最小值：
    int ans = min(min_rot(tops[0]), min_rot(bottoms[0]));
    return ans == INT_MAX ? -1 : ans;
  }
};

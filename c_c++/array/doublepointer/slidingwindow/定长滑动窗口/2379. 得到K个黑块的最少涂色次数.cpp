/*
给一个长度为n下标从0开始的字符串blocks，blocks[i]要么是'W'要么是'B'，
表示第i块的颜色。字符'W'和'B'分别表示白色和黑色。
给一个整数k，表示想要连续黑色块的数目。
每一次操作中，可以选择一个白色块将它涂成黑色块。
请返回至少出现一次连续k个黑色块的最少操作次数。

示例1：
输入：blocks = "WBBWWBBWBW", k = 7
输出：3
解释：一种得到7个连续黑色块的方法是把第0，3和4个块涂成黑色。
     得到blocks = "BBBBBBBWBW"。
     可以证明无法用少于3次操作得到7个连续的黑块。
     所以我们返回3。

示例2：
输入：blocks = "WBWBBBW", k = 2
输出：0
解释：不需要任何操作，因为已经有2个连续的黑块。
     所以我们返回0。


提示：
n == blocks.length
1 <= n <= 100
blocks[i]要么是'W'，要么是'B'。
1 <= k <= n
*/

class Solution {
  // 时间复杂度：O(n)，其中n为字符串blocks的长度。
  // 空间复杂度：O(1)，仅使用常量空间。
 public:
  int minimumRecolors(string blocks, int k) {
    int n = blocks.size();
    int ans = n + 1;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
      if (blocks[i] == 'W') {
        ++cnt;
      }
      if (i < k - 1) {
        continue;
      }
      ans = min(ans, cnt);
      if (blocks[i + 1 - k] == 'W') {
        --cnt;
      }
    }
    return ans;
  }
};
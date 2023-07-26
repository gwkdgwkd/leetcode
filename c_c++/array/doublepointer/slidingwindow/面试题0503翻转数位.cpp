/*
给定一个32位整数num，你可以将一个数位从0变为1。
请编写一个程序，找出你能够获得的最长的一串1的长度。

示例1：
输入：num = 1775(11011101111)
输出：8

示例2：
输入：num = 7(0111)
输出：4
*/

int reverseBits(int num) {
  int right = 0, max = 0, current_max = 0, i;
  for (i = 0; i < 32; i++) {
    if (((unsigned int)1 << i) & num) {
      right++;
      current_max++;
    } else {
      current_max = right + 1;
      right = 0;
    }
    if (current_max > max) max = current_max;
  }
  return max;
}

// 滑动窗口
class Solution {
 public:
  int reverseBits(int num) {
    bitset<32> b(num);
    int left = 0;
    int right = 0;

    int cnt = 0;
    int ans = 0;
    while (right < 32) {
      if (b[right++] == 0) {
        ++cnt;
      }

      while (left < right && cnt > 1) {
        if (b[left++] == 0) {
          --cnt;
        }
      }

      ans = max(ans, right - left);
    }

    return ans;
  }
};
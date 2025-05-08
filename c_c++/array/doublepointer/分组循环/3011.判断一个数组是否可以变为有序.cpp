/*
给一个下标从0开始且全是正整数的数组nums。
一次操作中，如果两个相邻元素在二进制下的数目相同，那么你可以将这两个元素交换。
可以执行这个操作任意次（也可以0次）。
如果可以使数组变为非降序，请返回true，否则返回false。

示例1：

输入：nums = [8,4,2,30,15]
输出：true
解释：先观察每个元素的二进制表示。
     2，4和8分别都只有一个数位为1，分别为"10"，"100"和"1000"。
     15和30分别有4个数位为1："1111"和"11110"。
     我们可以通过4个操作使数组非降序：
     交换nums[0]和nums[1]。8和4分别只有1个数位为1。数组变为[4,8,2,30,15]。
     交换nums[1]和nums[2]。8和2分别只有1个数位为1。数组变为[4,2,8,30,15]。
     交换nums[0]和nums[1]。4和2分别只有1个数位为1。数组变为[2,4,8,30,15]。
     交换nums[3]和nums[4]。30和15分别有4个数位为1，数组变为[2,4,8,15,30]。
     数组变成有序的，所以我们返回true。
     注意我们还可以通过其他的操作序列使数组变得有序。

示例2：
输入：nums = [1,2,3,4,5]
输出：true
解释：数组已经是非降序的，所以我们返回true。

示例3：
输入：nums = [3,16,8,4,2]
输出：false
解释：无法通过操作使数组变为非降序。


提示：
1 <= nums.length <= 100
1 <= nums[i] <= 28
*/

class Solution {
  int count(int num) {
    int c = 0;
    while (num) {
      num = num & (num - 1);
      ++c;
    }
    return c;
  }

 public:
  bool canSortArray(vector<int>& nums) {
    int lastCnt = 0;
    int lastCroupMax = 0;
    int curGroupMax = 0;
    for (int num : nums) {
      int curCnt = count(num);  // 可以使用__builtin_popcount
      if (curCnt == lastCnt) {
        curGroupMax = max(curGroupMax, num);
      } else {
        lastCnt = curCnt;
        lastCroupMax = curGroupMax;
        curGroupMax = num;
      }
      if (num < lastCroupMax) {
        return false;
      }
    }
    return true;
  }
};
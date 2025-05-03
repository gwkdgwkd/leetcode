/*
给一个整数数组arr，请删除一个子数组（可以为空），使得arr中剩下的元素是非递减的。
一个子数组指的是原数组中连续的一个子序列。
请返回满足题目要求的最短子数组的长度。

示例1：
输入：arr = [1,2,3,10,4,2,3,5]
输出：3
解释：需要删除的最短子数组是[10,4,2]，长度为3。
     剩余元素形成非递减数组 [1,2,3,3,5]。
     另一个正确的解为删除子数组[3,10,4]。

示例2：
输入：arr = [5,4,3,2,1]
输出：4
解释：由于数组是严格递减的，我们只能保留一个元素。
     所以我们需要删除长度为4的子数组，要么删除[5,4,3,2]，要么删除[4,3,2,1]。

示例3：
输入：arr = [1,2,3]
输出：0
解释：数组已经是非递减的了，我们不需要删除任何元素。

示例4：
输入：arr = [1]
输出：0


提示：
1 <= arr.length <= 10^5
0 <= arr[i] <= 10^9
*/

// 枚举左端点，移动右端点
class Solution {
 public:
  int findLengthOfShortestSubarray(vector<int>& arr) {
    int n = arr.size();
    int right = n - 1;
    while (right && arr[right - 1] <= arr[right]) {
      --right;
    }
    if (0 == right) {
      return 0;  // arr已经是非递减数组
    }

    // 此时arr[right-1] > arr[right]
    int ans = right;  // 删除0到right-1

    // 为什么枚举一个新的left时，right不会往左移？
    // 或者说，是否需要再次枚举之前枚举过的arr[right]？
    // 在向右移动时，由于arr[left]和arr[right]都是非递减的，
    // 所以right 左侧之前枚举过的元素必然小于arr[left]，无需再次枚举。
    // 这也是本题可以使用同向双指针（不定长滑动窗口）的前提。

    // 枚举left，增大right直到arr[left]≤arr[right]，此时更新子数组长度的最小值
    for (int left = 0; left == 0 || arr[left - 1] <= arr[left]; ++left) {
      while (right < n && arr[right] < arr[left]) {
        ++right;
      }

      // 此时arr[left] <= arr[right]，从left+1到right-1可以删除：
      ans = min(ans, right - left - 1);
    }
    return ans;
  }
};

// 枚举右端点，移动左端点
class Solution {
 public:
  int findLengthOfShortestSubarray(vector<int>& arr) {
    int n = arr.size(), right = n - 1;
    while (right && arr[right - 1] <= arr[right]) --right;
    if (right == 0) return 0;  // arr已经是非递减数组
    // 此时arr[right-1] > arr[right]
    int ans = right;              // 删除0到right-1
    for (int left = 0;; ++right)  // 枚举right
      while (right == n || arr[left] <= arr[right]) {
        // 中间left+1到right-1可以删除
        ans = min(ans, right - left - 1);
        if (arr[left] > arr[left + 1]) return ans;
        ++left;
      }
  }
};
/*
已知存在一个按非降序排列的整数数组nums，数组中的值不必互不相同。
在传递给函数之前，nums在预先未知的某个下标k（0<=k<nums.length）上进行了旋转，
使数组变为[nums[k],nums[k+1],...,nums[n-1],nums[0],nums[1],...,nums[k-1]]
例如，[0,1,2,4,4,4,5,6,6,7]在下标5处经旋转后可能变为[4,5,6,6,7,0,1,2,4,4]。

给旋转后的数组nums和一个整数target，请你编写一个函数来判断给定的目标值是否存在于数组中。
如果nums中存在这个目标值target，则返回true，否则返回false。
必须尽可能减少整个操作步骤。

示例1：
输入：nums = [2,5,6,0,0,1,2], target = 0
输出：true

示例2：
输入：nums = [2,5,6,0,0,1,2], target = 3
输出：false

提示：
1 <= nums.length <= 5000
-10^4 <= nums[i] <= 10^4
题目数据保证nums在预先未知的某个下标上进行了旋转
-10^4 <= target <= 10^4

进阶：
这是搜索旋转排序数组的延伸题目，本题中的nums可能包含重复元素。
这会影响到程序的时间复杂度吗？会有怎样的影响，为什么？
*/

class Solution {
 public:
  bool search(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] == target) {
        return true;
      }

      if (nums[mid] > nums[right]) {
        // 右侧无序,先判断是否在左侧有序部分：
        if (nums[left] <= target && target < nums[mid]) {
          right = mid - 1;
        } else {
          left = mid + 1;
        }
      } else if (nums[mid] < nums[right]) {
        // 左侧无序,先判度是否在右侧有序部分：
        if (nums[mid] < target && target <= nums[right]) {
          left = mid + 1;
        } else {
          right = mid - 1;
        }
      } else {
        // 此时无法确定在哪一侧,但我们知道right肯定不是,那么缩小范围即可：
        --right;
      }
    }

    return nums[left] == target ? true : false;
  }
};
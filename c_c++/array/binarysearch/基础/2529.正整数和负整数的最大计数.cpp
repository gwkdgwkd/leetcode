/*
给一个按非递减顺序排列的数组nums，返回正整数数目和负整数数目中的最大值。
换句话讲，如果nums中正整数的数目是pos，而负整数的数目是neg，返回pos和neg二者中的最大值。
注意：0既不是正整数也不是负整数。

示例1：
输入：nums = [-2,-1,-1,1,2,3]
输出：3
解释：共有3个正整数和3个负整数。计数得到的最大值是3。

示例2：
输入：nums = [-3,-2,-1,0,0,1,2]
输出：3
解释：共有2个正整数和3个负整数。计数得到的最大值是3。

示例3：
输入：nums = [5,20,66,1314]
输出：4
解释：共有4个正整数和0个负整数。计数得到的最大值是4。


提示：
1 <= nums.length <= 2000
-2000 <= nums[i] <= 2000
nums按非递减顺序排列。

进阶：可以设计并实现时间复杂度为O(log(n))的算法解决此问题吗？
*/

// 遍历
class Solution {
 public:
  int maximumCount(vector<int> &nums) {
    int neg = 0, pos = 0;
    for (int x : nums) {
      if (x < 0) {
        neg++;
      } else if (x > 0) {
        pos++;
      }
    }
    return max(neg, pos);
  }
};

class Solution {
 public:
  int maximumCount(vector<int> &nums) {
    int neg = lower_bound(nums.begin(), nums.end(), 0) - nums.begin();
    int pos = nums.end() - upper_bound(nums.begin(), nums.end(), 0);
    return max(neg, pos);
  }
};

// 参考[34.在排序数组中查找元素的第一个和最后一个位置]
class Solution {
  int lower_bound(vector<int> &nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] < target) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    return left;
  }

 public:
  int maximumCount(vector<int> &nums) {
    int neg = lower_bound(nums, 0);
    int pos = nums.size() - lower_bound(nums, 1);
    return max(neg, pos);
  }
};
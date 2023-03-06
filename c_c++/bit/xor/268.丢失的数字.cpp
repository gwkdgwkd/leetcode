/*
给定一个包含[0,n]中n个数的数组nums，找出[0,n]这个范围内没有出现在数组中的那个数。

示例1：
输入：nums = [3,0,1]
输出：2
解释：n = 3，因为有3个数字，所以所有的数字都在范围[0,3]内。
     2是丢失的数字，因为它没有出现在nums中。

示例2：
输入：nums = [0,1]
输出：2
解释：n = 2，因为有2个数字，所以所有的数字都在范围[0,2]内。
     2是丢失的数字，因为它没有出现在nums中。

示例3：
输入：nums = [9,6,4,2,3,5,7,0,1]
输出：8
解释：n = 9，因为有9个数字，所以所有的数字都在范围[0,9]内。
     8是丢失的数字，因为它没有出现在nums中。

示例4：
输入：nums = [0]
输出：1
解释：n =1，因为有1个数字，所以所有的数字都在范围[0,1]内。
     1是丢失的数字，因为它没有出现在nums中。

提示：
n == nums.length
1 <= n <= 10^4
0 <= nums[i] <= n
nums中的所有数字都独一无二

进阶：你能否实现线性时间复杂度、仅使用额外常数空间的算法解决此问题?
*/

// 面试题1704消失的数字

// 排序解法的时间复杂度是O(NlogN)，
// HashSet的解法时间复杂度是O(N)，但是还需要O(N)的空间复杂度存储HashSet。

// 位运算
// 时间复杂度：O(N)
// 空间复杂度：O(1)
int missingNumber(int* nums, int numsSize) {
  int ans = 0;
  for (int i = 0; i < numsSize; ++i) {
    ans ^= (i ^ nums[i]);
  }
  ans ^= numsSize;
  return ans;
}

class Solution {
 public:
  int missingNumber(vector<int>& nums) {
    int n = nums.size();
    int ans = n;
    for (int i = 0; i < n; ++i) {
      ans ^= i;
      ans ^= nums[i];
    }

    return ans;
  }
};

// 等差公式求和
int missingNumber(int* nums, int numsSize) {
  // 公式：(首项 + 末项) * 项数 / 2
  int expect = (0 + numsSize) * (numsSize + 1) / 2;  // 考虑过整型溢出

  int sum = 0;
  for (int i = 0; i < numsSize; ++i) sum += nums[i];
  return expect - sum;
}

// 边增加边减
int missingNumber(int* nums, int numsSize) {
  int n = numsSize;
  int res = 0;
  res += n - 0;
  for (int i = 0; i < n; i++) res += i - nums[i];
  return res;
}

// 剑指Offer53-II.0～n-1中缺失的数字
// 一个长度为n-1的递增排序数组中的所有数字都是唯一的，并且每个数字都在范围0～n-1之内。
// 在范围0～n-1内的n个数字中有且只有一个数字不在该数组中，请找出这个数字。

// 数组无序，就不能用这种方法，但上面的三种方法都可以
int missingNumber(int* nums, int numsSize) {
  for (int i = 0; i < numsSize; ++i) {
    if (nums[i] != i) {
      return i;
    }
  }

  return numsSize;
}
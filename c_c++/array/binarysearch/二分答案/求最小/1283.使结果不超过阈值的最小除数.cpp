/*
给一个整数数组nums和一个正整数threshold，需要选择一个正整数作为除数，
然后将数组里每个数都除以它，并对除法结果求和。
请找出能够使上述结果小于等于阈值threshold的除数中最小的那个。
每个数除以除数后都向上取整，比方说7/3 = 3， 10/2 = 5。
题目保证一定有解。

示例1：
输入：nums = [1,2,5,9], threshold = 6
输出：5
解释：如果除数为1，我们可以得到和为17（1+2+5+9）。
     如果除数为4，我们可以得到和为7(1+1+2+3) 。
     如果除数为5，和为5(1+1+1+2)。

示例2：
输入：nums = [2,3,5,7,11], threshold = 11
输出：3

示例3：
输入：nums = [19], threshold = 5
输出：4


提示：
1 <= nums.length <= 5 * 10^4
1 <= nums[i] <= 10^6
nums.length <= threshold <= 10^6
*/

class Solution {
 public:
  int smallestDivisor(vector<int>& nums, int threshold) {
    auto check = [&nums, &threshold](int d) {
      int sum = 0;
      for (int num : nums) {
        if (num % d) {
          sum += num / d + 1;
        } else {
          sum += num / d;
        }
      }
      return sum <= threshold;
    };

    int left = 1;
    int right = *max_element(nums.begin(), nums.end());
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (check(mid)) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }

    return left;
  }
};

class Solution {
 public:
  int smallestDivisor(vector<int>& nums, int threshold) {
    int l = 1, r = *max_element(nums.begin(), nums.end());
    int ans = -1;
    while (l <= r) {
      int mid = (l + r) / 2;
      int total = 0;
      for (int num : nums) {
        total += (num - 1) / mid + 1;
      }
      if (total <= threshold) {
        ans = mid;
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    return ans;
  }
};

/* 二分答案求最小
题目求什么，就二分什么。

如何把二分答案与数组上的二分查找联系起来？
假设范围是[2,3,4,5]，相当于在一个虚拟数组：[check(2),check(3),check(4),check(5)]中，
二分找第一个（或最后一个）值为true的check(i)。
这同样可以用红蓝染色法思考。

有些题目，明明m可以是答案，但却不在初始二分区间中。
比如闭区间二分初始化right=m−1（或者开区间right=m），这不会算错吗？
不会算错。想一想，如果二分的while循环每次更新的都是left，那么最终答案是什么？
正好就是m。一般地，如果一开始就能确定m一定可以满足题目要求，那么m是不需要在二分区间中的。
换句话说，二分区间是尚未确定是否满足题目要求的数的范围。
那些在区间外面的数，都是已确定的满足（不满足）题目要求的数。

什么是循环不变量？
想一想，对于求最小的题目，开区间二分的写法，为什么最终返回的是right，而不是别的数？
在初始化（循环之前）、循环中、循环结束后，
都时时刻刻保证check(right) == true和check(left) == false，这就叫循环不变量。
根据循环不变量，循环结束时left + 1 == right，
那么right就是最小的满足要求的数（因为再−1就不满足要求了），所以答案是right。

部分题目可以优化二分边界，减少二分次数，从而减少代码运行时间。
对于初次接触二分答案的同学，无需强求自己写出最优的代码，设定一个比较大的二分上界也是可以的。
*/
class Solution {
 public:
  int smallestDivisor(vector<int>& nums, int threshold) {
    auto check = [&](int m) -> bool {
      int sum = 0;
      for (int x : nums) {
        sum += (x + m - 1) / m;
        if (sum > threshold) {  // 提前退出循环
          return false;
        }
      }
      return true;
    };

    int left = 0, right = ranges::max(nums);  // 开区间
    while (left + 1 < right) {
      int mid = left + (right - left) / 2;
      (check(mid) ? right : left) = mid;
    }
    return right;
  }
};

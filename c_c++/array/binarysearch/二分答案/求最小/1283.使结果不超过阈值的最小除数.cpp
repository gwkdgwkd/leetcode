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
求最小和二分查找求排序数组中某元素的第一个位置是类似的，
按照红蓝染色法，左边是不满足要求的（红色），右边则是满足要求的（蓝色）。
求最大的题目则相反，左边是满足要求的（蓝色），右边是不满足要求的（红色）。
这会导致二分写法和上面的求最小有一些区别。

以开区间二分为例：
求最小：check(mid)==true时更新right=mid，反之更新left=mid，最后返回right。
求最大：check(mid)==true时更新left=mid，反之更新right=mid，最后返回left。
对于开区间写法，简单来说check(mid)==true时更新的是谁，最后就返回谁。
相比其他二分写法，开区间写法不需要思考加一减一等细节，个人推荐使用开区间写二分。
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

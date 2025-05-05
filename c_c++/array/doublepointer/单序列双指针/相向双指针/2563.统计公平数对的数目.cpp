/*
给一个下标从0 开始、长度为n的整数数组nums，
和两个整数lower和upper，返回公平数对的数目。
如果(i, j)数对满足以下情况，则认为它是一个公平数对：
0 <= i < j < n，且lower <= nums[i] + nums[j] <= upper

示例1：
输入：nums = [0,1,7,4,4,5], lower = 3, upper = 6
输出：6
解释：共计6个公平数对：(0,3)、(0,4)、(0,5)、(1,3)、(1,4)和(1,5)。

示例2：
输入：nums = [1,7,9,2,5], lower = 11, upper = 11
输出：1
解释：只有单个公平数对：(2,3)。


提示：
1 <= nums.length <= 10^5
nums.length == n
-10^9 <= nums[i] <= 10^9
-10^9 <= lower <= upper <= 10^9
*/

/* 两次相向双指针
可以枚举左边的i，统计右边有多少个合法的j。
枚举i，计算满足j>i且nums[j]≤upper−nums[i]的j的个数，记作count(upper)。
枚举i，计算满足j>i且nums[j]<lower−nums[i]，
也就是nums[j]≤lower−1−nums[i]的j的个数，记作count(lower−1)。
答案就是count(upper)−count(lower−1)。

怎么计算count(upper)？
初始化j=n−1。枚举i，如果nums[j]>upper−nums[i]，就减小j，
直到j=i或者nums[j]≤upper−nums[i]为止。
如果j=i，那么继续循环也无法满足j>i的要求，直接退出循环。

由于数组是有序的，如果nums[i]+nums[j]≤upper，
那么对于更小的j，也同样满足这个不等式。
所以[i+1,j]范围内的下标都可以是j，这有j−i个，加入答案。
*/
class Solution {
  // 时间复杂度：O(nlogn)，其中n为nums的长度，瓶颈在排序上。
  // 空间复杂度：O(1)，忽略排序的栈开销。
 public:
  long long countFairPairs(vector<int>& nums, int lower, int upper) {
    ranges::sort(nums);
    auto count = [&](int upper) {
      long long res = 0;
      int j = nums.size() - 1;
      for (int i = 0; i < nums.size(); i++) {
        while (j > i && nums[j] > upper - nums[i]) {
          j--;
        }
        if (j == i) {
          break;
        }
        res += j - i;
      }
      return res;
    };
    return count(upper) - count(lower - 1);
  }
};

// 两次相向双指针
class Solution {
  // 时间复杂度：O(nlogn)，其中n为nums的长度，瓶颈在排序上。
  // 空间复杂度：O(1)，忽略排序的栈开销。
 public:
  long long countFairPairs(vector<int>& nums, int lower, int upper) {
    sort(nums.begin(), nums.end());
    auto count = [&nums](int upper) {
      long long ans = 0;
      int left = 0;
      int right = nums.size() - 1;
      while (left < right) {
        if (nums[left] + nums[right] <= upper) {
          // 如果nums[left]+nums[right]≤upper，那么对于更小的right，也同样满足不等式。
          // 所以[left+1,right]范围内的下标j都可以和i配对，这有right−left个，
          // 加入答案，然后把left加一：
          ans += right - left;
          ++left;
        } else {
          // 如果nums[left]+nums[right]>upper，那么对于更大的left，也同样不满足题目要求。
          // 所以[left,right−1]范围内的下标i都无法与j配对，直接把right减一：
          --right;
        }
      }
      return ans;
    };

    return count(upper) - count(lower - 1);
  }
};

/* 二分查找
排序后，枚举右边的nums[j]，
那么左边的nums[i]需要满足0≤i<j以及lower−nums[j]≤nums[i]≤upper−nums[j]
计算≤upper−nums[j]的元素个数，减去<lower−nums[j]的元素个数，
即为满足上式的元素个数。

由于nums是有序的，可以在[0,j−1]中二分查找：
1.找到>upper−nums[j]的第一个数，设其下标为r，
  那么下标在[0,r−1]中的数都是≤upper−nums[j]的，这有r个。
  如果[0,j−1]中没有找到这样的数，那么二分结果为j。
  这意味着[0,j−1]中的数都是≤upper−nums[j]的，这有j个。
2.找到≥lower−nums[j]的第一个数，设其下标为l，
  那么下标在[0,l−1]中的数都是<lower−nums[j]的，这有l个。
  如果[0,j−1]中没有找到这样的数，那么二分结果为j。
  这意味着[0,j−1]中的数都是<lower−nums[j]的，这有j个。
3.满足lower−nums[j]≤nums[i]≤upper−nums[j]的nums[i]的个数为r−l，加入答案。
*/
class Solution {
  // 时间复杂度：O(nlogn)，其中n为 nums的长度。
  // 空间复杂度：O(1)，忽略排序的栈开销。
 public:
  long long countFairPairs(vector<int>& nums, int lower, int upper) {
    ranges::sort(nums);
    long long ans = 0;
    for (int j = 0; j < nums.size(); j++) {
      // 注意要在[0, j-1]中二分，因为题目要求两个下标i < j：
      auto r = upper_bound(nums.begin(), nums.begin() + j, upper - nums[j]);
      auto l = lower_bound(nums.begin(), nums.begin() + j, lower - nums[j]);
      ans += r - l;
    }

    return ans;
  }
};

// 相向三指针
class Solution {
  // 时间复杂度：O(nlogn)，其中n为nums的长度，瓶颈在排序上。
  // 空间复杂度：O(1)，忽略排序的栈开销。
 public:
  long long countFairPairs(vector<int>& nums, int lower, int upper) {
    ranges::sort(nums);
    long long ans = 0;
    int l = nums.size(), r = l;
    for (int j = 0; j < nums.size(); j++) {
      while (r && nums[r - 1] > upper - nums[j]) {
        r--;
      }
      while (l && nums[l - 1] >= lower - nums[j]) {
        l--;
      }
      ans += min(r, j) - min(l, j);
    }

    return ans;
  }
};

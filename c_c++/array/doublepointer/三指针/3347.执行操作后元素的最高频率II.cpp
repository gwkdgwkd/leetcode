/*
给一个整数数组nums和两个整数k和numOperations。
必须对nums执行操作numOperations次。每次操作中，可以：
选择一个下标i，它在之前的操作中没有被选择过。
将nums[i]增加范围[-k, k]中的一个整数。
在执行完所有操作以后，请返回nums中出现频率最高元素的出现次数。
一个元素x的频率指的是它在数组中出现的次数。

示例1：
输入：nums = [1,4,5], k = 1, numOperations = 2
输出：2
解释：通过以下操作得到最高频率2：
     将nums[1]增加0，nums变为[1, 4, 5]。
     将nums[2]增加-1，nums变为[1, 4, 4]。

示例2：
输入：nums = [5,11,20,20], k = 5, numOperations = 1
输出：2
解释：通过以下操作得到最高频率2：将nums[1]增加0。


提示：
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
0 <= k <= 10^9
0 <= numOperations <= nums.length
*/

/* 差分
设x=nums[i]。
x可以变成[x−k,x+k]中的整数。注意对于同一个nums[i]至多操作一次。
反过来想，对于一个整数y，有多少个数可以变成y？
这可以用差分计算，也就是把[x−k,x+k]中的每个整数的出现次数都加一。
最后计算差分的前缀和，就得到了有sumD个数可以变成y。
如果y不在nums中，那么y的最大频率为min(sumD,numOperations)。
如果y在nums中，且出现了cnt次，那么有sumD−cnt个其他元素（不等于y的数）可以变成y，
但这不能超过numOperations，所以有min(sumD−cnt,numOperations)个其他元素可以变成y，
再加上y自身出现的次数cnt，得到y的最大频率为：
cnt+min(sumD−cnt,numOperations)=min(sumD,cnt+numOperations)
注意上式兼容y不在nums中的情况，此时cnt=0。

为什么代码只考虑在diff中的数字？
比如x在diff中，x+1不在diff中，那么x+1的sumD和x的是一样的，无需重复计算。
此外，要想算出比min(sumD,cnt+numOperations)更大的数，要么sumD变大，要么cnt变大。
变大时的x必然在diff中。
*/
class Solution {
  // 时间复杂度：O(nlogn)，其中n是nums的长度。
  // 空间复杂度：O(n)。
 public:
  int maxFrequency(vector<int>& nums, int k, int numOperations) {
    unordered_map<int, int> cnt;
    map<int, int> diff;
    for (int x : nums) {
      cnt[x]++;
      diff[x];        // 把x插入diff，以保证下面能遍历到x
      diff[x - k]++;  // 把[x-k, x+k]中的每个整数的出现次数都加一
      diff[x + k + 1]--;
    }

    int ans = 0, sum_d = 0;
    for (auto& [x, d] : diff) {
      sum_d += d;
      ans = max(ans, min(sum_d, cnt[x] + numOperations));
    }
    return ans;
  }
};

/* 同向三指针 + 滑动窗口
把nums从小到大排序，方法一中的cnt[x]也可以用同向三指针/滑动窗口计算。
如果x在nums中，用同向三指针计算。
如果x不在nums中，用滑动窗口计算。

同向三指针
遍历排序后的nums，设x=nums[i]。计算元素值在[x−k,x+k]中的元素个数。
遍历的同时，维护左指针left，它是最小的满足nums[left]≥x−k的下标。
遍历的同时，维护右指针right，它是最小的满足nums[right]>x+k的下标。
如果不存在，则right=n。
那么方法一中的sumD就是right−left。

滑动窗口
枚举x=nums[right]作为被修改的最大元素。计算元素值在[x−2k,x]中的元素个数。
设nums[left]是被修改的最小元素，那么需要满足nums[right]−nums[left]≤2k，
那么可以把right−left+1个数都变成一样的。
注意上式不能超过numOperations。

如果同向三指针计算完毕后，发现答案已经≥numOperations，那么无需计算滑动窗口。
*/
class Solution {
 public:
  int maxFrequency(vector<int>& nums, int k, int numOperations) {
    ranges::sort(nums);

    int n = nums.size();
    int ans = 0, cnt = 0, left = 0, right = 0;
    for (int i = 0; i < n; i++) {
      int x = nums[i];
      cnt++;
      // 循环直到连续相同段的末尾，这样可以统计出x的出现次数
      if (i < n - 1 && x == nums[i + 1]) {
        continue;
      }
      while (nums[left] < x - k) {
        left++;
      }
      while (right < n && nums[right] <= x + k) {
        right++;
      }
      ans = max(ans, min(right - left, cnt + numOperations));
      cnt = 0;
    }

    if (ans >= numOperations) {
      return ans;
    }

    left = 0;
    for (int right = 0; right < n; right++) {
      int x = nums[right];
      while (nums[left] < x - k * 2) {
        left++;
      }
      ans = max(ans, right - left + 1);
    }
    return min(ans, numOperations);  // 最后和numOperations取最小值
  }
};

// 把两个for循环合起来
class Solution {
 public:
  int maxFrequency(vector<int>& nums, int k, int numOperations) {
    ranges::sort(nums);

    int n = nums.size();
    int ans = 0, cnt = 0, left = 0, right = 0, left2 = 0;
    for (int i = 0; i < n; i++) {
      int x = nums[i];
      while (nums[left2] < x - k * 2) {
        left2++;
      }
      ans = max(ans, min(i - left2 + 1, numOperations));

      cnt++;
      // 循环直到连续相同段的末尾，这样可以统计出x的出现次数
      if (i < n - 1 && x == nums[i + 1]) {
        continue;
      }
      while (nums[left] < x - k) {
        left++;
      }
      while (right < n && nums[right] <= x + k) {
        right++;
      }
      ans = max(ans, min(right - left, cnt + numOperations));
      cnt = 0;
    }

    return ans;
  }
};
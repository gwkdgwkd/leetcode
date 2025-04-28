/*
给一个下标从0开始的整数数组nums。
nums的一个子数组如果满足以下条件，那么它是不间断的：
i，i + 1 ，...，j表示子数组中的下标。
对于所有满足i <= i1, i2 <= j的下标对，
都有0 <= |nums[i1] - nums[i2]| <= 2。
请返回不间断子数组的总数目。
子数组是一个数组中一段连续非空的元素序列。

示例1：
输入：nums = [5,4,2,4]
输出：8
解释：大小为1的不间断子数组：[5], [4], [2], [4]。
     大小为 2 的不间断子数组：[5,4], [4,2], [2,4]。
     大小为 3 的不间断子数组：[4,2,4]。
     没有大小为4的不间断子数组。
     不间断子数组的总数目为4 + 3 + 1 = 8。
     除了这些以外，没有别的不间断子数组。

示例2：
输入：nums = [1,2,3]
输出：6
解释：大小为1的不间断子数组：[1],[2],[3]。
     大小为2的不间断子数组：[1,2],[2,3]。
     大小为3的不间断子数组：[1,2,3]。
     不间断子数组的总数目为3 + 2 + 1 = 6。


提示：
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
*/

/*
在遍历数组的同时，维护窗口内的元素及其出现次数。
由于绝对差至多为2，所以用有序集合或者哈希表维护都行。
由于至多维护3个数，无论用有序集合还是哈希表，添加、删除和查询最值都是O(1)的。
如果窗口内的最大值与最小值的差大于2，就不断移动左端点left，减少窗口内的数字。
内层循环结束后，[left,right]这个子数组是满足题目要求的。
由于子数组越短，越能满足题目要求，所以除了[left,right]，
还有 [left+1,right],[left+2,right],…,[right,right]都是满足要求的。
也就是说，当右端点固定在right时，
左端点在left,left+1,left+2,…,right的所有子数组都是满足要求的，
这一共有right−left+1个，加入答案。
*/

// 滑动窗口+有序集合/哈希表
class Solution {
 public:
  long long continuousSubarrays(vector<int>& nums) {
    long long ans = 0;
    multiset<int> ms;
    int left = 0;
    int right = 0;
    int n = nums.size();
    while (right < n) {
      ms.insert(nums[right++]);
      while (*ms.rbegin() - *ms.begin() > 2) {
        ms.erase(ms.find(nums[left++]));
      }
      ans += right - left;
    }
    return ans;
  }
};
class Solution {
 public:
  long long continuousSubarrays(vector<int>& nums) {
    long long ans = 0;
    map<int, int> cnt;
    int left = 0;
    for (int right = 0; right < nums.size(); right++) {
      cnt[nums[right]]++;
      while (cnt.rbegin()->first - cnt.begin()->first > 2) {
        int y = nums[left];
        if (--cnt[y] == 0) {
          cnt.erase(y);
        }
        left++;
      }
      ans += right - left + 1;
    }
    return ans;
  }
};

// 滑动窗口+单调队列
class Solution {
 public:
  long long continuousSubarrays(vector<int>& nums) {
    deque<int> min_q, max_q;
    long long ans = 0;
    int left = 0;

    for (int right = 0; right < nums.size(); right++) {
      int x = nums[right];
      while (!min_q.empty() && x <= nums[min_q.back()]) {
        min_q.pop_back();
      }
      min_q.push_back(right);
      while (!max_q.empty() && x >= nums[max_q.back()]) {
        max_q.pop_back();
      }
      max_q.push_back(right);
      while (nums[max_q.front()] - nums[min_q.front()] > 2) {
        left++;
        if (min_q.front() < left) {
          min_q.pop_front();
        }
        if (max_q.front() < left) {
          max_q.pop_front();
        }
      }
      ans += right - left + 1;
    }
    return ans;
  }
};

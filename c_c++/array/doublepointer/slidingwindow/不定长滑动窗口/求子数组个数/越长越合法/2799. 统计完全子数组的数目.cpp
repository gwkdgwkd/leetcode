/*
给一个由正整数组成的数组nums。
如果数组中的某个子数组满足下述条件，则称之为完全子数组：
子数组中不同元素的数目等于整个数组不同元素的数目。
返回数组中完全子数组的数目。
子数组是数组中的一个连续非空序列。



示例1：
输入：nums = [1,3,1,2,2]
输出：4
解释：完全子数组有：[1,3,1,2]、[1,3,1,2,2]、[3,1,2]和[3,1,2,2]。

示例2：
输入：nums = [5,5,5,5]
输出：10
解释：数组仅由整数5组成，所以任意子数组都满足完全子数组的条件，子数组的总数为10。


提示：
1 <= nums.length <= 1000
1 <= nums[i] <= 2000
*/

/*
由于子数组越长，包含的元素越多，越能满足题目要求；
反之，子数组越短，包含的元素越少，越不能满足题目要求。
有这种性质的题目，可以用滑动窗口解决。
枚举子数组的右端点right，同时用一个哈希表cnt维护子数组内每个元素的出现次数。
如果nums[right]加入哈希表后，发现哈希表的大小等于k，
说明子数组满足要求，移动子数组的左端点left，把nums[left]的出现次数减一。
如果nums[left]的出现次数变成0，则从cnt中去掉，表示子数组内少了一种元素。
内层循环结束后，[left,right]这个子数组是不满足题目要求的，
但在退出循环之前的最后一轮循环，[left−1,right]是满足题目要求的（哈希表的大小等于k）。
由于子数组越长，越能满足题目要求，所以除了[left−1,right]，
还有[left−2,right],[left−3,right],…,[0,right]都是满足要求的。
即，当右端点固定在right时，左端点在0,1,2,…,left−1的所有子数组都满足要求，一共有left个。
*/

class Solution {
  // 时间复杂度：O(n)，其中n为nums的长度，虽然写了个二重循环，
  // 但是内层循环中对left加一的总执行次数不会超过n次，所以总的时间复杂度为O(n)。
  // 空间复杂度：O(k)，其中k是nums中的不同元素个数，这不会超过n。
 public:
  int countCompleteSubarrays(vector<int>& nums) {
    unordered_set<int> s(nums.begin(), nums.end());
    int c = s.size();

    unordered_map<int, int> cnt;
    int count = 0;
    int left = 0;
    for (int num : nums) {
      cnt[num]++;
      while (cnt.size() == c) {
        int l = nums[left];
        if (--cnt[l] == 0) {
          cnt.erase(l);
        }
        ++left;
      }
      count += left;
    }

    return count;
  }
};
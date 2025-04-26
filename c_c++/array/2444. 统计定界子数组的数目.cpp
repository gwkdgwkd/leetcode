/*
给一个整数数组nums和两个整数minK以及maxK。
nums的定界子数组是满足下述条件的一个子数组：
子数组中的最小值等于minK。
子数组中的最大值等于maxK。
返回定界子数组的数目。
子数组是数组中的一个连续部分。

示例1：
输入：nums = [1,3,5,2,7,5], minK = 1, maxK = 5
输出：2
解释：定界子数组是[1,3,5]和[1,3,5,2]。

示例2：
输入：nums = [1,1,1,1], minK = 1, maxK = 1
输出：10
解释：nums的每个子数组都是一个定界子数组，共有10个子数组。


提示：
2 <= nums.length <= 10^5
1 <= nums[i], minK, maxK <= 10^6
*/

/*
从特殊到一般，首先考虑一个简单的情况，nums的所有元素都在[minK,maxK]范围内。
在这种情况下，问题相当于：同时包含minK和maxK的子数组的个数。
核心思路：枚举子数组的右端点，统计有多少个合法的左端点。

遍历nums，记录minK最近出现的位置min_i，以及maxK最近出现的位置max_i，
当遍历到nums[i]时，如果minK和maxK都遇到过，则左端点在[0,min(minI,maxI)]中的子数组，
包含minK和maxK，最小值一定是minK，最大值一定是maxK。
以i为右端点的合法子数组的个数为0到min(min_i,max_i)个元素，即min(min_i,max_i)+1。

回到原问题，由于子数组不能包含在[minK,maxK]范围之外的元素，
需要额外记录在[minK,maxK]范围之外的最近元素位置，记作not_i，
则左端点在[not_i+1,min(min_i,max_i)]中的子数组都是合法的。
所以以i为右端点的合法子数组的个数为min(min_i,max_i)−(not_i+1)+1，
即min(min_i,max_i)-not_i。​
*/

class Solution {
  // 时间复杂度：O(n)，其中n为nums的长度。
  // 空间复杂度：O(1)。
 public:
  long long countSubarrays(vector<int>& nums, int minK, int maxK) {
    long long ans = 0;
    // 可以初始化min_i=max_i=not_i​=−1，兼容没有找到相应元素的情况：
    int min_i = -1;
    int max_i = -1;
    int not_i = -1;
    for (int i = 0; i < nums.size(); ++i) {
      int x = nums[i];
      if (x == minK) {
        min_i = i;
      }
      if (x == maxK) {
        max_i = i;
      }
      if (x < minK || x > maxK) {
        not_i = i;
      }

      // 如果min(min_i,max_i)−not_i​<0，则表示在not_i右侧minK和maxK没有同时出现，
      // 此时以i为右端点的合法子数组的个数为0，所以加到答案中的是：
      ans += max(min(min_i, max_i) - not_i, 0);
    }

    return ans;
  }
};

// 相似题目：795.区间子数组个数
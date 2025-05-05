/*
给一个下标从0开始、严格递增的整数数组nums和一个正整数diff。
如果满足下述全部条件，则三元组(i, j, k)就是一个等差三元组：
i < j < k，
nums[j] - nums[i] == diff且nums[k] - nums[j] == diff
返回不同等差三元组的数目。

示例1：
输入：nums = [0,1,4,6,7,10], diff = 3
输出：2
解释：(1, 2, 4)是等差三元组：7 - 4 == 3且4 - 1 == 3。
     (2, 4, 5)是等差三元组：10 - 7 == 3且7 - 4 == 3。

示例2：
输入：nums = [4,5,6,7,8,9], diff = 2
输出：2
解释：(0, 2, 4)是等差三元组：8 - 6 == 2 且 6 - 4 == 2。
     (1, 3, 5)是等差三元组：9 - 7 == 2 且 7 - 5 == 2。


提示：
3 <= nums.length <= 200
0 <= nums[i] <= 200
1 <= diff <= 50
nums严格递增
*/

// 哈希表
class Solution {
  // 时间复杂度：O(n)，其中n为nums的长度。
  // 空间复杂度：O(n)。
 public:
  int arithmeticTriplets(vector<int>& nums, int diff) {
    int ans = 0;
    unordered_set<int> us(nums.begin(), nums.end());
    for (int x : nums) {
      if (us.count(x - diff) && us.count(x + diff)) {
        ++ans;
      }
    }

    return ans;
  }
};

// 优化
class Solution {
 public:
  int arithmeticTriplets(vector<int>& nums, int diff) {
    // 等差三元组也可以用nums[k]表示：(nums[k]−2*diff,nums[k]−diff,nums[k])
    // 所以还可以一边查询哈希表中是否有nums[k]−2*diff和nums[k]−diff，
    // 一边把nums[k]插入哈希表，从而做到一次遍历。
    int ans = 0;
    unordered_set<int> s;
    for (int x : nums) {
      if (s.count(x - diff) && s.count(x - diff * 2)) ++ans;
      s.insert(x);
    }

    return ans;
  }
};

/* 三指针
由于nums是严格递增的，遍历k时，i和j只增不减，因此可以用类似同向双指针的做法来移动指针：
1.枚举x=nums[k]；
2.移动j直到nums[j]+diff≥x；
3.如果nums[j]+diff=x，则移动i直到nums[i]+2*diff≥x；
4.如果nums[i]+2*diff=x，则找到了一对等差三元组。

注意下面代码在循环时没有判断j<k和i<j，因为一旦j=k，
nums[j]+diff≥x必然成立，所以j<k无需判断，i也同理。
*/
class Solution {
 public:
  int arithmeticTriplets(vector<int>& nums, int diff) {
    int ans = 0, i = 0, j = 1;
    for (int x : nums) {  // x = nums[k]
      while (nums[j] + diff < x) {
        ++j;
      }
      if (nums[j] + diff > x) {
        continue;
      }
      while (nums[i] + diff * 2 < x) {
        ++i;
      }
      if (nums[i] + diff * 2 == x) {
        ++ans;
      }
    }

    return ans;
  }
};
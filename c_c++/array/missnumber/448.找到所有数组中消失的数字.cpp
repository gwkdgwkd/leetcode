/*
给你一个含n个整数的数组nums，其中nums[i]在区间[1,n]内。
请你找出所有在[1,n]范围内但没有出现在nums中的数字，并以数组的形式返回结果。

示例1：
输入：nums = [4,3,2,7,8,2,3,1]
输出：[5,6]

示例2：
输入：nums = [1,1]
输出：[2]

提示：
n == nums.length
1 <= n <= 10^5
1 <= nums[i] <= n

进阶：你能在不使用额外空间且时间复杂度为O(n)的情况下解决这个问题吗？
你可以假定返回的数组不算在额外空间内。
*/

// 参考41的置换方法
int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize) {
  for (int i = 0; i < numsSize; ++i) {
    while (nums[i] > 0 && nums[i] <= numsSize && nums[nums[i] - 1] != nums[i]) {
      int t = nums[nums[i] - 1];  // 注意顺序
      nums[nums[i] - 1] = nums[i];
      nums[i] = t;
    }
  }

  *returnSize = 0;
  int* result = (int*)malloc(sizeof(int) * numsSize);
  for (int i = 0; i < numsSize; ++i) {
    if (nums[i] != i + 1) {
      result[(*returnSize)++] = i + 1;
    }
  }

  return result;
}

class Solution {
 public:
  vector<int> findDisappearedNumbers(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
      while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
        swap(nums[nums[i] - 1], nums[i]);
      }
    }

    vector<int> res;
    for (int i = 0; i < n; ++i) {
      if (nums[i] != i + 1) {
        res.emplace_back(i + 1);
      }
    }

    return res;
  }
};

// 原地修改
class Solution {
 public:
  vector<int> findDisappearedNumbers(vector<int>& nums) {
    int n = nums.size();

    // 遍历nums，每遇到一个数x，就让nums[x−1]增加n。
    // 由于nums中所有数均在[1,n]中，增加以后，这些数必然大于n。
    for (auto& num : nums) {
      // 遍历到某个位置时，可能已经被增加过，因此需要对n取模来还原出它本来的值：
      int x = (num - 1) % n;
      nums[x] += n;
    }

    vector<int> ret;
    // 最后遍历nums，若nums[i]未大于n，就说明没有遇到过数i+1：
    for (int i = 0; i < n; i++) {
      if (nums[i] <= n) {
        ret.push_back(i + 1);
      }
    }
    return ret;
  }
};
/*
给你一个由n个整数组成的数组nums，和一个目标值target。
请你找出并返回满足下述全部条件且不重复的四元组
[nums[a],nums[b],nums[c],nums[d]]：0 <= a, b, c, d < n
a、b、c和d互不相同
nums[a] + nums[b] + nums[c] + nums[d] == target
你可以按任意顺序返回答案。

示例1：
输入：nums = [1,0,-1,0,-2,2], target = 0
输出：[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

示例2：
输入：nums = [2,2,2,2,2], target = 8
输出：[[2,2,2,2]]

提示：
1 <= nums.length <= 200
-10^9 <= nums[i] <= 10^9
-10^9 <= target <= 10^9
*/

// 四数之和的双指针解法是两层for循环nums[k]+nums[i]为确定值，
// 依然是循环内有left和right下表作为双指针，
// 找出nums[k]+nums[i]+nums[left]+nums[right]==target的情况。
// 对于15.三数之和双指针法就是将原本暴力O(n^3)的解法，降为O(n^2)的解法，
// 四数之和的双指针解法就是将原本暴力O(n^4)的解法，降为O(n^3)的解法。
int comp(const void* a, const void* b) { return *(int*)a - *(int*)b; }
int** fourSum(int* nums, int numsSize, int target, int* returnSize,
              int** returnColumnSizes) {
  int** quadruplets = malloc(sizeof(int*) * 1001);
  *returnSize = 0;
  *returnColumnSizes = malloc(sizeof(int) * 1001);
  if (numsSize < 4) {
    return quadruplets;
  }
  qsort(nums, numsSize, sizeof(int), comp);
  int length = numsSize;
  for (int i = 0; i < length - 3; i++) {
    if (i > 0 && nums[i] == nums[i - 1]) {
      continue;
    }
    if ((long)nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) {
      break;
    }
    if ((long)nums[i] + nums[length - 3] + nums[length - 2] + nums[length - 1] <
        target) {
      continue;
    }
    for (int j = i + 1; j < length - 2; j++) {
      if (j > i + 1 && nums[j] == nums[j - 1]) {
        continue;
      }
      if ((long)nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target) {
        break;
      }
      if ((long)nums[i] + nums[j] + nums[length - 2] + nums[length - 1] <
          target) {
        continue;
      }
      int left = j + 1, right = length - 1;
      while (left < right) {
        int sum = nums[i] + nums[j] + nums[left] + nums[right];
        if (sum == target) {
          int* tmp = malloc(sizeof(int) * 4);
          tmp[0] = nums[i], tmp[1] = nums[j], tmp[2] = nums[left],
          tmp[3] = nums[right];
          (*returnColumnSizes)[(*returnSize)] = 4;
          quadruplets[(*returnSize)++] = tmp;
          while (left < right && nums[left] == nums[left + 1]) {
            left++;
          }
          left++;
          while (left < right && nums[right] == nums[right - 1]) {
            right--;
          }
          right--;
        } else if (sum < target) {
          left++;
        } else {
          right--;
        }
      }
    }
  }
  return quadruplets;
}

class Solution {
 public:
  vector<vector<int>> fourSum(vector<int>& nums, int target) {
    vector<vector<int>> quadruplets;
    if (nums.size() < 4) {
      return quadruplets;
    }
    sort(nums.begin(), nums.end());
    int length = nums.size();
    for (int i = 0; i < length - 3; i++) {
      if (i > 0 && nums[i] == nums[i - 1]) {
        continue;
      }
      if ((long)nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) {
        break;
      }
      if ((long)nums[i] + nums[length - 3] + nums[length - 2] +
              nums[length - 1] <
          target) {
        continue;
      }
      for (int j = i + 1; j < length - 2; j++) {
        if (j > i + 1 && nums[j] == nums[j - 1]) {
          continue;
        }
        if ((long)nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target) {
          break;
        }
        if ((long)nums[i] + nums[j] + nums[length - 2] + nums[length - 1] <
            target) {
          continue;
        }
        int left = j + 1, right = length - 1;
        while (left < right) {
          int sum = nums[i] + nums[j] + nums[left] + nums[right];
          if (sum == target) {
            quadruplets.push_back({nums[i], nums[j], nums[left], nums[right]});
            while (left < right && nums[left] == nums[left + 1]) {
              left++;
            }
            left++;
            while (left < right && nums[right] == nums[right - 1]) {
              right--;
            }
            right--;
          } else if (sum < target) {
            left++;
          } else {
            right--;
          }
        }
      }
    }
    return quadruplets;
  }
};
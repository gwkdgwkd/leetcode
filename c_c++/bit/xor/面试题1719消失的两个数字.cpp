/*
给定一个数组，包含从1到N所有的整数，但其中缺了两个数字。
能在O(N)时间内只用O(1)的空间找到它们吗？以任意顺序返回这两个数字均可。

示例1:
输入: [1]
输出: [2,3]

示例2:
输入: [2,3]
输出: [1,4]

提示：nums.length <= 30000
*/

// 位运算
int* missingTwo(int* nums, int numsSize, int* returnSize) {
  int xor = 0;
  for (int i = 0; i < numsSize; ++i) {
    xor ^= ((i + 1) ^ nums[i]);
  }
  xor ^= numsSize + 1;
  xor ^= numsSize + 2;

  int* res = (int*)malloc(sizeof(int) * 2);
  memset(res, 0, sizeof(int) * 2);
  *returnSize = 2;

  int mask = xor&(-xor);  // 取最低位的1
  for (int i = 0; i <= numsSize + 1; ++i) {
    if (i < numsSize) {
      if ((nums[i] & mask) == mask) {
        res[0] ^= nums[i];
      } else {
        res[1] ^= nums[i];
      }
    }
    if (((i + 1) & mask) == mask) {
      res[0] ^= (i + 1);
    } else {
      res[1] ^= (i + 1);
    }
  }

  return res;
}

int* missingTwo(int* nums, int numsSize, int* returnSize) {
  *returnSize = 0;
  int* res = malloc(sizeof(int) * 2);
  int* temp = calloc(numsSize + 3, sizeof(int));
  for (int i = 0; i < numsSize; i++) {
    temp[nums[i]]++;
  }
  for (int i = 1; i < numsSize + 3; i++) {
    if (temp[i] == 0) res[(*returnSize)++] = i;
  }
  return res;
}

int* missingTwo(int* nums, int numsSize, int* returnSize) {
  *returnSize = 2;
  int* res = malloc(sizeof(int) * 2);
  int sum = 0, two_sum = (1 + numsSize + 2) * (numsSize + 2) / 2;
  for (int i = 0; i < numsSize; i++) {
    sum += nums[i];
  }
  two_sum = two_sum - sum;
  int ave = two_sum / 2;
  int low_sum = 0, high_sum = 0;
  for (int i = 0; i < numsSize; i++) {
    if (nums[i] <= ave)
      low_sum += nums[i];
    else
      high_sum += nums[i];
  }
  res[0] = (1 + ave) * ave / 2 - low_sum;
  res[1] = two_sum - res[0];
  return res;
}

class Solution {
 public:
  vector<int> missingTwo(vector<int>& nums) {
    int n = nums.size();

    int sum = (n + 1) ^ (n + 2);
    for (int i = 0; i < n; ++i) {
      sum ^= i + 1;
      sum ^= nums[i];
    }

    int mask = sum & -sum;
    vector<int> ans(2);
    auto tmp = [&ans, &mask](int num) {
      if ((num & mask) == mask) {
        ans[0] ^= num;
      } else {
        ans[1] ^= num;
      }
    };
    tmp(n + 1);
    tmp(n + 2);
    for (int i = 0; i < n; ++i) {
      tmp(i + 1);
      tmp(nums[i]);
    }

    return ans;
  }
};
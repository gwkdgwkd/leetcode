/*
集合s包含从1到n的整数，不幸的是，因为数据错误，
导致集合里面某一个数字复制了成了集合里面的另外一个数字的值，
导致集合丢失了一个数字并且有一个数字重复。
给定一个数组nums代表了集合S发生错误后的结果。
请你找出重复出现的整数，再找到丢失的整数，将它们以数组的形式返回。

示例1：
输入：nums = [1,2,2,4]
输出：[2,3]

示例2：
输入：nums = [1,1]
输出：[1,2]

提示：
2 <= nums.length <= 10^4
1 <= nums[i] <= 10^4
*/

int* findErrorNums(int* nums, int numsSize, int* returnSize) {
  int* res = (int*)malloc(sizeof(int) * 2);
  *returnSize = 2;
  int dup = -1;
  for (int i = 0; i < numsSize; i++) {
    int index = abs(nums[i]) - 1;  // 索引应该从0开始
    if (nums[index] < 0)
      dup = abs(nums[i]);
    else
      nums[index] *= -1;
  }
  res[0] = dup;

  int missing = -1;
  for (int i = 0; i < numsSize; i++)
    if (nums[i] > 0) missing = i + 1;  // 将索引转换成元素
  res[1] = missing;

  return res;
}

// 位运算
int* findErrorNums(int* nums, int numsSize, int* returnSize) {
  int* res = (int*)malloc(sizeof(int) * 2);
  *returnSize = 2;

  int n = numsSize;
  int xorVal = 0;
  // 1.经过下面两个循环体后，xorVal保存重复整数与丢失整数的异或运算结果
  for (int i = 1; i <= n; i++) {
    xorVal ^= i;
  }
  for (int i = 0; i < n; ++i) {
    xorVal ^= nums[i];
  }
  // 2.确定mask的值，为分组做准备
  int mask = 1;
  while ((xorVal & mask) == 0) {
    mask <<= 1;
  }
  // 3.进行分组之间的异或运算，求出两个目标整数的值
  int a = 0, b = 0;
  for (int i = 1; i <= n; i++) {
    if ((i & mask) == 0) {
      a ^= i;
    } else {
      b ^= i;
    }
  }
  for (int i = 0; i < n; ++i) {
    if ((nums[i] & mask) == 0) {
      a ^= nums[i];
    } else {
      b ^= nums[i];
    }
  }
  // 4.区分出重复整数和丢失整数
  int count = 0;
  for (int i = 0; i < n; ++i) {
    if (nums[i] == a) {
      count++;
    }
  }
  if (count == 2) {
    res[0] = a;
    res[1] = b;
    return res;
  }
  res[0] = b;
  res[1] = a;
  return res;
}

class Solution {
 public:
  vector<int> findErrorNums(vector<int>& nums) {
    int n = nums.size();
    int sum = 0;
    for (int i = 0; i < n; ++i) {
      sum ^= i + 1;
      sum ^= nums[i];
    }

    int mask = sum & -sum;
    vector<int> ans(2);
    for (int i = 0; i < n; ++i) {
      if (((i + 1) & mask) == mask) {
        ans[0] ^= (i + 1);
      } else {
        ans[1] ^= (i + 1);
      }
      if ((nums[i] & mask) == mask) {
        ans[0] ^= nums[i];
      } else {
        ans[1] ^= nums[i];
      }
    }

    int count = 0;
    for (int num : nums) {
      if (num == ans[0]) {
        ++count;
      }
    }

    if (count == 0) {
      swap(ans[0], ans[1]);
    }

    return ans;
  }
};
/*
给一个循环数组nums，返回nums中每个元素的下一个更大元素。
数字x的下一个更大的元素是按数组遍历顺序，
这个数字之后的第一个比它更大的数，
这意味着你应该循环地搜索它的下一个更大的数。
如果不存在，则输出-1。

示例1：
输入：nums = [1,2,1]
输出：[2,-1,2]
解释：第一个1的下一个更大的数是2；
     数字2找不到下一个更大的数；
     第二个1的下一个最大的数需要循环搜索，结果也是2。

示例2：
输入：nums = [1,2,3,4,3]
输出：[2,3,4,-1,4]

提示：
1 <= nums.length <= 10^4
-10^9 <= nums[i] <= 10^9
*/

// 对于找最近一个比当前值大/小的问题，都可以使用单调栈来解决。
// 单调栈就是在栈的基础上维护一个栈内元素单调。

// 单调栈
int* nextGreaterElements(int* nums, int numsSize, int* returnSize) {
  *returnSize = numsSize;
  int* result = (int*)malloc(sizeof(int) * numsSize);
  for (int i = 0; i < numsSize; ++i) {
    result[i] = -1;
  }
  int stack[numsSize * 2];
  int top = 0;

  // nums：[1,2,1]
  for (int i = 0; i < numsSize * 2 - 1; ++i) {
    int index = i % numsSize;
    // printf("i[%d] index [%d] : \n", i, index);
    while (top > 0 && nums[stack[top - 1]] < nums[index]) {
      // printf("result[%d] = %d\n", stack[top - 1], nums[index]);
      result[stack[top - 1]] = nums[index];
      --top;
    }
    stack[top++] = index;

    // for (int i = 0; i < top; ++i) {
    //   printf("%d(%d) ", stack[i], nums[stack[i]]);
    // }
    // printf("\n");
  }

  // i[0] index [0] :
  // 0(1)
  // i[1] index [1] :
  // result[0] = 2
  // 1(2)
  // i[2] index [2] :
  // 1(2) 2(1)
  // i[3] index [0] :
  // 1(2) 2(1) 0(1)
  // i[4] index [1] :
  // result[0] = 2
  // result[2] = 2
  // 1(2) 1(2)

  return result;
}

class Solution {
 public:
  vector<int> nextGreaterElements(vector<int>& nums) {
    int len = nums.size();

    stack<int> stk;
    vector<int> ans(len, -1);

    for (int i = 0; i < len * 2 - 1; ++i) {
      int index = i % len;
      while (!stk.empty() && nums[stk.top()] < nums[index]) {
        ans[stk.top()] = nums[index];
        stk.pop();
      }
      stk.push(index);
    }
    return ans;
  }
};

// 单调栈模板[496,503,739]
int* nextGreaterElements(int* nums, int numsSize, int* returnSize) {
  if (numsSize <= 0) {
    return NULL;
  }

  int* res = (int*)malloc(numsSize * sizeof(int));
  int stack[numsSize * 2];
  int top = 0;

  // 倒着往栈里放
  for (int i = numsSize * 2 - 1; i >= 0; i--) {
    while (top > 0 && nums[i % numsSize] >= stack[top - 1]) {
      top--;  // 出栈
    }

    res[i % numsSize] = top > 0 ? stack[top - 1] : -1;
    stack[top++] = nums[i % numsSize];  // 入栈
  }

  *returnSize = numsSize;
  return res;
}
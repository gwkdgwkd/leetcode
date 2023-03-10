/*
给定一个整数数组temperatures，表示每天的温度，返回一个数组answer，
其中answer[i]是指在第i天之后，才会有更高的温度。
如果气温在这之后都不会升高，请在该位置用0来代替。

示例1：
输入：temperatures = [73,74,75,71,69,72,76,73]
输出：[1,1,4,2,1,1,0,0]

示例2：
输入：temperatures = [30,40,50,60]
输出：[1,1,1,0]

示例3：
输入：temperatures = [30,60,90]
输出：[1,1,0]

提示：
1 <= temperatures.length <= 10^5
30 <= temperatures[i] <= 100
*/

// 剑指OfferII038每日温度

// 暴力法，超时
int* dailyTemperatures(int* temperatures, int temperaturesSize,
                       int* returnSize) {
  int* res = (int*)malloc(sizeof(int) * temperaturesSize);
  memset(res, 0, sizeof(int) * temperaturesSize);
  *returnSize = 0;

  for (int i = 0; i < temperaturesSize; ++i) {
    for (int j = i + 1; j < temperaturesSize; ++j) {
      if (temperatures[j] > temperatures[i]) {
        res[(*returnSize)++] = j - i;
        break;
      }
      if (j == temperaturesSize - 1) {
        res[(*returnSize)++] = 0;
      }
    }
  }
  res[(*returnSize)++] = 0;

  return res;
}

// 单调栈
int* dailyTemperatures(int* temperatures, int temperaturesSize,
                       int* returnSize) {
  *returnSize = temperaturesSize;
  int* result = (int*)malloc(sizeof(int) * temperaturesSize);
  memset(result, 0, sizeof(int) * temperaturesSize);

  int stack[temperaturesSize];
  int top = 0;

  for (int i = 0; i < temperaturesSize; ++i) {
    while (top > 0 && temperatures[stack[top - 1]] < temperatures[i]) {
      result[stack[top - 1]] = i - stack[top - 1];
      --top;
    }
    stack[top++] = i;
  }

  return result;
}

class Solution {
 public:
  vector<int> dailyTemperatures(vector<int>& temperatures) {
    int len = temperatures.size();
    stack<int> stk;
    vector<int> ans(len, 0);
    for (int i = 0; i < len; ++i) {
      while (!stk.empty() && temperatures[stk.top()] < temperatures[i]) {
        ans[stk.top()] = i - stk.top();
        stk.pop();
      }
      stk.push(i);
    }

    return ans;
  }
};

// 单调栈？就是栈里的元素保持升序或者降序。
// 通常是一维数组，要寻找任一个元素的右边或者左边第一个比自己大或者小的元素的位置，
// 此时就要想到可以用单调栈了，时间复杂度为O(n)，单调栈的本质是空间换时间，
// 遍历时需要用一个栈来记录右边第一个比当前元素大的元素，优点是只需要遍历一次。
#define STACKSIZE 30000
int stackIndex;
int stack[STACKSIZE];
int top() { return stack[stackIndex - 1]; }
void pop() { stackIndex--; }
void push(int c) { stack[stackIndex++] = c; }
bool empty() { return stackIndex == 0; }
int* dailyTemperatures(int* temperatures, int temperaturesSize,
                       int* returnSize) {
  // 维护一个存储下标的单调栈，从栈底到栈顶的下标对应的温度列表中的温度依次递减。
  // 如果一个下标在单调栈里，则表示尚未找到下一次温度更高的下标。
  // 正向遍历温度列表，对于温度列表中的每个元素temperatures[i]，如果栈为空，则直接将i进栈，
  // 如果栈不为空，则比较栈顶元素prevIndex对应的温度temperatures[prevIndex]，
  // 和当前温度temperatures[i]，如果temperatures[i]>temperatures[prevIndex]，
  // 则将prevIndex移除，并将prevIndex对应的等待天数赋为i-prevIndex，
  // 重复上述操作直到栈为空或者栈顶元素对应的温度小于等于当前温度，然后将i进栈。
  // 为什么可以在弹栈的时候更新ans[prevIndex]呢？
  // 因为在这种情况下，即将进栈的i对应的temperatures[i]，
  // 一定是temperatures[prevIndex]右边第一个比它大的元素，
  // 试想如果prevIndex和i有比它大的元素，假设下标为j，
  // 那么prevIndex一定会在下标j的那一轮被弹掉。
  // 由于单调栈满足从栈底到栈顶元素对应的温度递减，
  // 因此每次有元素进栈时，会将温度更低的元素全部移除，
  // 并更新出栈元素对应的等待天数，这样可以确保等待天数一定是最小的。

  int* res = (int*)malloc(sizeof(int) * temperaturesSize);
  memset(res, 0, sizeof(int) * temperaturesSize);
  *returnSize = temperaturesSize;

  stackIndex = 0;
  memset(stack, 0, sizeof(stack));
  push(0);

  for (int i = 1; i < temperaturesSize; ++i) {
    if (temperatures[i] < temperatures[top()]) {
      // 情况一，当前元素temperatures[i]小于栈顶元素的情况
      push(i);

    } else if (temperatures[i] == temperatures[top()]) {
      // 情况二，当前元素temperatures[i]等于栈顶元素的情况
      push(i);

    } else {
      // 情况三，当前元素temperatures[i]大于栈顶元素的情况
      while (!empty() && temperatures[i] > temperatures[top()]) {
        // 找到一个比栈顶大的元素，那么该元素是栈顶右边第一个比栈顶大的元素
        res[top()] = i - top();
        pop();
      }
      push(i);
    }

    // 循环可以简写为下面格式（三种情况统一起来）：
    // for (int i = 1; i < temperaturesSize; ++i) {
    //   while (!empty() && temperatures[i] > temperatures[top()]) {
    //     res[top()] = i - top();
    //     pop();
    //   }
    //   push(i);
    // }
  }

  return res;
}

// 单调栈模板[496,503,739]
int* dailyTemperatures(int* temperatures, int temperaturesSize,
                       int* returnSize) {
  if (temperaturesSize <= 0) {
    return NULL;
  }

  // 保存索引
  int* res = (int*)malloc(temperaturesSize * sizeof(int));

  int stack[temperaturesSize];
  int top = 0;

  // 倒着往栈里放
  for (int i = temperaturesSize - 1; i >= 0; i--) {
    while (top > 0 && temperatures[i] >= temperatures[stack[top - 1]]) {
      top--;  // 出栈
    }

    res[i] = top > 0 ? stack[top - 1] - i : 0;
    stack[top++] = i;  // 把i入栈
  }

  *returnSize = temperaturesSize;
  return res;
}
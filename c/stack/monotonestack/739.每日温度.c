/*
给定一个整数数组temperatures，表示每天的温度，返回一个数组answer，
其中answer[i]是指在第i天之后，才会有更高的温度。
如果气温在这之后都不会升高，请在该位置用0来代替。

示例1:
输入: temperatures = [73,74,75,71,69,72,76,73]
输出: [1,1,4,2,1,1,0,0]

示例2:
输入: temperatures = [30,40,50,60]
输出: [1,1,1,0]

示例3:
输入: temperatures = [30,60,90]
输出: [1,1,0]

提示：
1 <= temperatures.length <= 105
30 <= temperatures[i] <= 100
*/

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

// 单调栈？就是栈里的元素保持升序或者降序。
// 通常是一维数组，要寻找任一个元素的右边或者左边第一个比自己大或者小的元素的位置，此时我们就要想到可以用单调栈了。
// 时间复杂度为O(n)。
// 单调栈的本质是空间换时间，因为在遍历的过程中需要用一个栈来记录右边第一个比当前元素的元素，优点是只需要遍历一次。
#define STACKSIZE 30000
int stackIndex;
int stack[STACKSIZE];
int top() { return stack[stackIndex - 1]; }
void pop() { stackIndex--; }
void push(int c) { stack[stackIndex++] = c; }
bool empty() { return stackIndex == 0; }
int* dailyTemperatures(int* temperatures, int temperaturesSize,
                       int* returnSize) {
  int* res = (int*)malloc(sizeof(int) * temperaturesSize);
  memset(res, 0, sizeof(int) * temperaturesSize);
  *returnSize = temperaturesSize;

  stackIndex = 0;
  memset(stack, 0, sizeof(stack));
  push(0);
  // printf("temperatures[0]:%d, 0\n", temperatures[0]);
  for (int i = 1; i < temperaturesSize; ++i) {
    // printf("temperatures[%d]:%d, ", i, temperatures[i]);
    if (temperatures[i] < temperatures[top()]) {
      // 情况一，当前遍历的元素temperatures[i]小于栈顶元素temperatures[st.top()]的情况
      // printf("%d < %d(%d), push(%d)\n", temperatures[i], temperatures[top()],
      // top(), i);
      push(i);

    } else if (temperatures[i] == temperatures[top()]) {
      // 情况二，当前遍历的元素temperatures[i]等于栈顶元素temperatures[st.top()]的情况
      // printf("%d == %d(%d), push(%d)\n", temperatures[i],
      // temperatures[top()], top(), i);
      push(i);

    } else {
      // 情况三，当前遍历的元素temperatures[i]大于栈顶元素temperatures[st.top()]的情况
      // printf("%d > %d(%d), push(%d)\n", temperatures[i], temperatures[top()],
      // top(), i);
      while (!empty() && temperatures[i] > temperatures[top()]) {
        res[top()] = i - top();
        // printf("    res[%d] : %d(%d-%d)\n", top(), i - top(), i, top());
        pop();
      }
      push(i);
    }
    // printf("[ ");
    // for (int j = 0; j < stackIndex; ++j) {
    //   printf("%d(%d) ", stack[j], temperatures[stack[j]]);
    // }
    // printf("]\n");

    // 循环可以简写为下面格式（三种情况统一起来）：
    // for (int i = 1; i < temperaturesSize; ++i) {
    //   while (!empty() && temperatures[i] > temperatures[top()]) {
    //     res[top()] = i - top();
    //     pop();
    //   }
    //   push(i);
    // }
  }

  // [73,74,75,71,69,72,76,73]
  // temperatures[0]:73, 0
  // temperatures[1]:74, 74 > 73(0), push(1)
  //     res[0] : 1(1-0)
  // [ 1(74) ]
  // temperatures[2]:75, 75 > 74(1), push(2)
  //     res[1] : 1(2-1)
  // [ 2(75) ]
  // temperatures[3]:71, 71 < 75(2), push(3)
  // [ 2(75) 3(71) ]
  // temperatures[4]:69, 69 < 71(3), push(4)
  // [ 2(75) 3(71) 4(69) ]
  // temperatures[5]:72, 72 > 69(4), push(5)
  //     res[4] : 1(5-4)
  //     res[3] : 2(5-3)
  // [ 2(75) 5(72) ]
  // temperatures[6]:76, 76 > 72(5), push(6)
  //     res[5] : 1(6-5)
  //     res[2] : 4(6-2)
  // [ 6(76) ]
  // temperatures[7]:73, 73 < 76(6), push(7)
  // [ 6(76) 7(73) ]

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
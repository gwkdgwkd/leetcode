/*
给你一个整数数组nums，有一个大小为k的滑动窗口从数组的最左侧移动到数组的最右侧。
你只可以看到在滑动窗口内的k个数字。滑动窗口每次只向右移动一位。
返回滑动窗口中的最大值。

示例1：
输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
输出：[3,3,5,5,6,7]
解释：
滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

示例2：
输入：nums = [1], k = 1
输出：[1]

提示：
1 <= nums.length <= 105
-104 <= nums[i] <= 104
1 <= k <= nums.length
*/

// 把从队首到队尾单调递减或递增的队列称之为单调队列。
// 1.用一个数组和一前一后两个指针（head，tail）来模拟双端队列，
//   而这个双端队列是用来存原来数组中符合条件的下标。
// 2.因为窗口的大小是k，因此，在遍历原数组时，满足q[head]<=
// i-k时，q的head就得出列，就是head++。
// 3.首先排除原队列中没用的尾巴tail，满足nums[q[tail-1]]<nums[i]时，原尾巴出列，就是tail--。
//   然后就是q[tail++] = i，入队。
// 时间复杂度：进队一次，出队一次，2N，就是O(N)
// 空间复杂度：O(N)，因为要建立与原数组等大的队列（数组）与答案数组
void print_q(int* q, int head, int tail, int index, int* nums) {
  printf("%d: %d %d [ ", index, head, tail);
  for (int i = head; i < tail; ++i) {
    printf("%d(%d) ", nums[q[i]], q[i]);
  }
  printf("],nums[q[%d]]: %d\n", head, nums[q[head]]);
}

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
  *returnSize = 0;
  int* result = (int*)malloc(sizeof(int) * (numsSize - k + 1));

  // 数组模拟双端队列，尾入队，头尾出队，保存数组中的下标
  int queue[numsSize];
  int head = 0, tail = 0;  // 头和尾指针
  for (int i = 0; i < numsSize; ++i) {
    // 窗口已经越过队列头指向的元素，从队列头出队
    while (head < tail && queue[head] <= i - k) {
      ++head;
    }
    // 新元素比队列尾的元素要大，为了维持单调递减，从队列尾把小于新元素的都出队
    while (head < tail && nums[queue[tail - 1]] <= nums[i]) {
      --tail;
    }
    queue[tail++] = i;  // 从队尾插入新元素
    // print_q(q, head, tail, i, nums);
    if (i >= k - 1) {  // 满足窗口大小时，队列头元素就是当前窗口最大的元素
      result[(*returnSize)++] = nums[queue[head]];
    }
  }

  // [1,3,-1,-3,5,3,8,11]
  // 3
  // 0: 0 1 [ 1(0) ],nums[q[0]]: 1
  // 1: 0 1 [ 3(1) ],nums[q[0]]: 3
  // 2: 0 2 [ 3(1) -1(2) ],nums[q[0]]: 3
  // 3: 0 3 [ 3(1) -1(2) -3(3) ],nums[q[0]]: 3
  // 4: 1 2 [ 5(4) ],nums[q[1]]: 5
  // 5: 1 3 [ 5(4) 3(5) ],nums[q[1]]: 5
  // 6: 1 2 [ 8(6) ],nums[q[1]]: 8
  // 7: 1 2 [ 11(7) ],nums[q[1]]: 11

  return result;
}

// 单调队列
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
  if (nums == NULL || returnSize == NULL) {
    return NULL;
  }
  int outLen = numsSize - k + 1;
  int* result = (int*)malloc(sizeof(int) * outLen);
  int* deque = (int*)malloc(sizeof(int) * numsSize);
  int start = 0;
  int end = 0;
  int i = 0, j = 0;
  while (i < numsSize) {
    // 若右边成员的值小于即将入队的值，就从右边依次出队
    while (start != end && nums[i] > nums[deque[end - 1]]) {
      end--;
    }
    // 从右边入队
    deque[end++] = i;
    // 已入队了K次，需要开始记录当前窗口最大值
    if (i >= k - 1) {
      result[i - k + 1] = nums[deque[start]];
      if (start != end && deque[start] <= i - k + 1) {
        // 最大值已出窗口，左边出队
        start++;
      }
    }
    i++;
  }
  free(deque);
  *returnSize = outLen;
  return result;
}

// 暴力法，超时
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
  *returnSize = 0;
  int* ans = malloc(sizeof(int) * numsSize);
  for (int i = 0; i <= numsSize - k; ++i) {
    int max = nums[i];
    for (int j = i + 1; j < i + k; ++j) {
      if (nums[j] > max) {
        max = nums[j];
      }
    }
    ans[(*returnSize)++] = max;
  }

  return ans;
}
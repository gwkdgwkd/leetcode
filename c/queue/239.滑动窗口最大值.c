
// 把从队首到队尾单调递减或递增的队列称之为单调队列。
// （1）用一个数组和一前一后两个指针（head，tail）来模拟双端队列，而这个双端队列是用来存原来数组中符合条件的下标
// （2）因为窗口的大小是k，因此，在遍历原数组时，满足q[head]<= i-k时，q的head就得出列，就是head++
// （3）首先排除原队列中没用的尾巴tail，满足nums[q[tail-1]]<nums[i]时，原尾巴出列，就是tail--。然后就是q[tail++] = i，入队
// 时间复杂度：进队一次，出队一次，2N，就是O(N）
// 空间复杂度：O(N)，因为要建立与原数组等大的队列（数组）与答案数组
void print_q(int* q, int head, int tail, int index, int* nums) {
  printf("%d: %d %d [ ", index, head, tail);
  for (int i = head; i < tail; ++i) {
    printf("%d(%d) ", nums[q[i]], q[i]);
  }
  printf("],nums[q[%d]]: %d\n", head, nums[q[head]]);
}
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
  int q[numsSize];
  // 数组模拟双端队列，存下标（代表时间）
  int head = 0, tail = 0;  // 数组q的一头一尾
  *returnSize = 0;
  int* ans = malloc(sizeof(int) * numsSize);
  for (int i = 0; i < numsSize; i++) {
    // 窗口扫过去了，队头就得出列了
    while (head < tail && q[head] <= i - k) {
      head++;
    }
    // 维护队列单调性 + 插入新的选项
    while (head < tail && nums[q[tail - 1]] <= nums[i]) {
      tail--;  // 不满足单调性，原来的尾部不要
    }
    q[tail++] = i;  // 插入新的选项
    // print_q(q, head, tail, i, nums);
    if (i >= k - 1) {
      ans[(*returnSize)++] = nums[q[head]];
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

  return ans;
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
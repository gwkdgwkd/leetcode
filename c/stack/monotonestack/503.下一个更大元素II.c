// 单调栈
int* nextGreaterElements(int* nums, int numsSize, int* returnSize) {
  // 要找比自己大的，所以比自己小的先留下来，一旦找到大的，自己离开，大的留下来继续找更大的；
  // 单调递增栈，栈顶小于等于栈顶下一位的入栈，大于的话则把前面小于他的赶走，他入栈；
  // 用栈记录数组下表，赶走的时候将对应下标的返回值记录为此大值；
  // 利用numsSize*2-1 进行两次便利，确保后面的元素能遍历到前面的数值高的数
  // 因为小的已经出去了，不会再被访问到，大的只是先从最上面开始访问，栈底都是更大的，所以减小便利次数
  // 这样已经走调的就不会再访问，两次便利这个数组后，每个数组一共只会被访问两次
  // 最开始默认为-1.如果没找到，此对应下标返回值一直保留在此不便
  *returnSize = numsSize;
  if (numsSize == 0) {
    return NULL;
  }
  int stack[2 * numsSize - 1];  // 建立一个栈来维护数组下标
  int* ret = malloc(sizeof(int) * numsSize);
  memset(ret, -1, sizeof(int) * numsSize);
  int top = 0;  // 栈顶进出栈表示
  for (int i = 0; i < numsSize * 2 - 1; i++) {
    // 因为要循环遍历，确保循环将所有小于目前nums[index]的栈中下表对应结果记录弹出
    int index = i % numsSize;
    while (top > 0 && nums[stack[top - 1]] < nums[index]) {
      // 找到对应返回结果下标位置，赋值此最近的比他的大数组元素
      ret[stack[top - 1]] = nums[index];
      top--;  // 将已经记录到结果的下表彻底弹出，不用考虑他了
    }
    // 把所有比他小的都弹出后，把他加入栈中下标，等待以后找他的对应返回值；
    stack[top++] = index;
  }
  return ret;
}

// 单调栈
int* nextGreaterElements(int* nums, int numsSize, int* returnSize) {
  int stack[numsSize * 2];
  int top = 0;

  int* res = (int*)malloc(sizeof(int) * numsSize);
  *returnSize = numsSize;
  for (int i = 0; i < numsSize; ++i) {
    res[i] = -1;
  }

  stack[top++] = 0;
  for (int i = 1; i < numsSize * 2; ++i) {
    while (top > 0 && nums[stack[top - 1]] < nums[i % numsSize]) {
      res[stack[top - 1]] = nums[i % numsSize];
      top--;
    }
    stack[top++] = i % numsSize;
  }

  return res;
}

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
// 暴力法
// 时间复杂度：O(n1*n2)
int* nextGreaterElement(int* nums1, int nums1Size, int* nums2, int nums2Size,
                        int* returnSize) {
  int i, j;
  int* res = (int*)malloc(sizeof(int) * nums1Size);

  for (i = 0; i < nums1Size; i++) {
    res[i] = -1;
    /* 在nums2中找到nums1[i] */
    for (j = 0; j < nums2Size; j++) {
      if (nums2[j] == nums1[i]) {
        break;
      }
    }
    /* 找到下一个更大的元素, 输出结果 */
    for (j = j + 1; j < nums2Size; j++) {
      if (nums2[j] > nums1[i]) {
        res[i] = nums2[j];
        break;
      }
    }
  }
  *returnSize = nums1Size;
  return res;
}

// 单调栈 + 哈希表
// 时间复杂度为O(n1+n2)
typedef struct {
  int num;
  int greater;
  UT_hash_handle hh;
} NumHash;
NumHash* g_head;
int* nextGreaterElement(int* nums1, int nums1Size, int* nums2, int nums2Size,
                        int* returnSize) {
  int i, j;
  int* res = (int*)malloc(sizeof(int) * nums1Size);
  int stack[nums2Size];
  int top = 0;
  NumHash* s = NULL;
  g_head = NULL;

  // 用单调栈求出nums2元素的下一个更大值, 并记录在hash表中
  for (i = nums2Size - 1; i >= 0; i--) {
    while (top != 0 && nums2[i] >= stack[top - 1]) {
      top--;
    }
    s = (NumHash*)malloc(sizeof(NumHash));
    s->num = nums2[i];
    s->greater = (top == 0) ? -1 : stack[top - 1];
    HASH_ADD_INT(g_head, num, s);
    stack[top++] = nums2[i];
  }

  // 遍历nums1元素, 在hash表中找到更大元素输出即可
  for (i = 0; i < nums1Size; i++) {
    HASH_FIND_INT(g_head, &nums1[i], s);
    res[i] = s->greater;
  }
  *returnSize = nums1Size;
  return res;
}
/*
输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。

示例1：
输入：head = [1,3,2]
输出：[2,3,1]

限制：0 <= 链表长度 <= 10000
*/

int* reversePrint(struct ListNode* head, int* returnSize) {
  int* res = (int*)malloc(sizeof(int) * 10000);
  *returnSize = 0;

  while (head) {
    res[(*returnSize)++] = head->val;
    head = head->next;
  }

  for (int left = 0, right = *returnSize - 1; left < right; ++left, --right) {
    int tmp = res[left];
    res[left] = res[right];
    res[right] = tmp;
  }

  return res;
}
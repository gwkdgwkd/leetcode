// 反转区间[a, b)的元素，注意是左闭右开
struct ListNode* reverse(struct ListNode* start, struct ListNode* end) {
  struct ListNode* pre = NULL;
  struct ListNode* cur = start;
  struct ListNode* next;

  while (cur != end) {
    next = cur->next;
    cur->next = pre;
    pre = cur;
    cur = next;
  }

  // 返回反转后的头结点
  return pre;
}
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
  if (!head) return head;

  struct ListNode* next_head = head;
  for (int i = 0; i < k; ++i) {
    // 不足k个，不需要反转，base case
    if (!next_head) return head;
    next_head = next_head->next;
  }

  // 区间[head, next_head)包含k个待反转元素
  struct ListNode* res = reverse(head, next_head);
  // 递归反转后续链表并连接起来
  head->next = reverseKGroup(next_head, k);

  return res;
}
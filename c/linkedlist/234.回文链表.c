struct ListNode* reverse(struct ListNode* head) {
  struct ListNode* cur = head;
  struct ListNode* pre = NULL;
  struct ListNode* temp;

  while (cur) {
    temp = cur->next;
    cur->next = pre;
    pre = cur;
    cur = temp;
  }

  return pre;
}
bool isPalindrome(struct ListNode* head) {
  struct ListNode* fast = head;
  struct ListNode* slow = head;

  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;
  }
  if (fast) {
    // fast不为空意味着元素个数为奇数，slow需要再走一步
    slow = slow->next;
  }

  fast = head;
  slow = reverse(slow);
  while (slow) {
    if (fast->val != slow->val) {
      return false;
    }
    fast = fast->next;
    slow = slow->next;
  }

  return true;
}
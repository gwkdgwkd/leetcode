// 双指针，与26题相同，只不过由数组变成了链表
struct ListNode* deleteDuplicates(struct ListNode* head) {
  if (!head) return head;
  struct ListNode* fast = head;
  struct ListNode* slow = head;
  while (fast) {
    if (fast->val != slow->val) {
      slow->next = fast;  // nums[slow] = nums[fast];
      slow = slow->next;  // slow++;
    }
    fast = fast->next;  // fast++
  }

  slow->next = NULL;  // 断开与后面重复元素的连接
  return head;
}
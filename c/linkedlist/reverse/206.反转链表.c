/*
 * @lc app=leetcode.cn id=206 lang=c
 *
 * [206] 反转链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

// 迭代
struct ListNode* reverseList(struct ListNode* head) {
  struct ListNode* cur = head;
  struct ListNode* pre = NULL;
  struct ListNode* temp;  // 保存cur的下一个节点

  while (cur) {
    temp = cur->next;  // 保存一下cur的下一个节点，因为接下来要改变cur->next
    cur->next = pre;  // 翻转操作
    pre = cur;        // 更新pre
    cur = temp;       // 更新cur
  }

  return pre;
}

// 递归
struct ListNode* reverse(struct ListNode* pre, struct ListNode* cur) {
  if (cur == NULL) return pre;
  struct ListNode* temp = cur->next;
  cur->next = pre;
  return reverse(cur, temp);
}
struct ListNode* reverseList(struct ListNode* head) {
  return reverse(NULL, head);
}

// 递归
struct ListNode* reverseList(struct ListNode* head) {
  if (head == NULL || head->next == NULL) return head;
  struct ListNode* last = reverseList(head->next);
  head->next->next = head;
  head->next = NULL;
  return last;
}
// @lc code=end

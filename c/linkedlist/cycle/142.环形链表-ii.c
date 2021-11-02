/*
 * @lc app=leetcode.cn id=142 lang=c
 *
 * [142] 环形链表 II
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
// 快慢指针
struct ListNode* detectCycle(struct ListNode* head) {
  struct ListNode* fast = head;
  struct ListNode* slow = head;
  while (fast != NULL && fast->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
    // 快慢指针相遇，此时从head和相遇点，同时查找直至相遇
    if (slow == fast) {
      // 当快慢指针相遇时，让其中任一个指针指向头节点，然后让它俩以相同速度前进，再次相遇时所在的节点位置就是环开始的位置。
      struct ListNode* index1 = fast;  // 从相遇节点也出发一个指针
      struct ListNode* index2 = head;  // 从头结点出发一个指针
      // 这两个指针每次只走一个节点， 那么当这两个指针相遇的时候就是环形入口的节点
      while (index1 != index2) {
        index1 = index1->next;
        index2 = index2->next;
      }
      return index2;  // 返回环的入口
    }
  }
  return NULL;
}
// @lc code=end

/*
给定一个链表的头节点head，请判断其是否为回文链表。
如果一个链表是回文，那么链表节点序列从前往后看和从后往前看是相同的。

示例1：
输入: head = [1,2,3,3,2,1]
输出: true

示例2：
输入: head = [1,2]
输出: false

提示：
链表L的长度范围为[1, 10^5]
0 <= node.val <= 9

进阶：能否用O(n)时间复杂度和O(1)空间复杂度解决此题？

注意：本题与234题相同
*/

struct ListNode* reverse(struct ListNode* head) {
  struct ListNode* left = NULL;
  struct ListNode* mid = head;
  struct ListNode* right;

  while (mid) {
    right = mid->next;
    mid->next = left;
    left = mid;
    mid = right;
  }

  return left;
}
bool isPalindrome(struct ListNode* head) {
  struct ListNode* slow = head;
  struct ListNode* fast = head;
  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;
  }

  if (fast) {
    slow = slow->next;
  }

  slow = reverse(slow);
  fast = head;

  while (slow) {
    if (fast->val != slow->val) {
      return false;
    }
    slow = slow->next;
    fast = fast->next;
  }

  return true;
}
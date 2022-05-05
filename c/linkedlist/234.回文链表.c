/*
给你一个单链表的头节点head，请你判断该链表是否为回文链表。如果是，返回true；否则，返回false。

示例1：
输入：head = [1,2,2,1]
输出：true

示例2：
输入：head = [1,2]
输出：false

提示：
链表中节点数目在范围[1,105]内
0 <= Node.val <= 9

进阶：你能否用O(n)时间复杂度和O(1)空间复杂度解决此题？
*/

// 面试题0206回文链表

struct ListNode {
  int val;
  struct ListNode* next;
};

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
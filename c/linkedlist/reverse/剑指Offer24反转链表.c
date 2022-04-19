/*
定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。

示例:
输入: 1->2->3->4->5->NULL
输出: 5->4->3->2->1->NULL

限制：0 <= 节点个数 <= 5000
注意：本题与206题相同
*/

struct ListNode* reverseList(struct ListNode* head) {
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
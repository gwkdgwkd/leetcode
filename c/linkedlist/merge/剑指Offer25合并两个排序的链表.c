/*
输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是递增排序的。

示例1：
输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4

限制：0 <= 链表长度 <= 1000

注意：本题与21题相同
*/

struct ListNode {
  int val;
  struct ListNode* next;
};
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
  struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
  dummy->next = NULL;
  struct ListNode* p = dummy;
  while (l1 && l2) {
    if (l1->val < l2->val) {
      p->next = l1;
      l1 = l1->next;
    } else {
      p->next = l2;
      l2 = l2->next;
    }
    p = p->next;
  }

  if (l1) {
    p->next = l1;
  }
  if (l2) {
    p->next = l2;
  }

  return dummy->next;
}
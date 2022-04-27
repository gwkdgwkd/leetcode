/*
给定一个单链表L的头节点head，单链表L表示为：
 L0 → L1 → … → Ln-1 → Ln 
请将其重新排列后变为：
L0 → Ln → L1 → Ln-1 → L2 → Ln-2 → …
不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

示例1:
输入: head = [1,2,3,4]
输出: [1,4,2,3]

示例2:
输入: head = [1,2,3,4,5]
输出: [1,5,2,4,3]

提示：
链表的长度范围为 [1, 5*10^4]
1 <= node.val <= 1000

注意：本题与143题相同
*/

struct ListNode {
  int val;
  struct ListNode* next;
};

struct ListNode* reverse(struct ListNode* root) {
  struct ListNode* left = NULL;
  struct ListNode* cur = root;
  struct ListNode* right;

  while (cur) {
    right = cur->next;
    cur->next = left;
    left = cur;
    cur = right;
  }

  return left;
}
void reorderList(struct ListNode* head) {
  if (head == NULL) {
    return head;
  }

  struct ListNode* slow = head;
  struct ListNode* fast = head;
  while (fast->next && fast->next->next) {
    fast = fast->next->next;
    slow = slow->next;
  }
  struct ListNode* tmp = slow->next;
  slow->next = NULL;

  struct ListNode* l1 = head;
  struct ListNode* l2 = reverse(tmp);

  while (l1 && l2) {
    struct ListNode* tmp1 = l1->next;
    struct ListNode* tmp2 = l2->next;
    l1->next = l2;
    l1 = tmp1;
    l2->next = l1;
    l2 = tmp2;
  }

  return head;
}
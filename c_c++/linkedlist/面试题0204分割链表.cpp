/*
给你一个链表的头节点head和一个特定值x，请对链表进行分隔，
使得所有小于x的节点都出现在大于或等于x的节点之前。
不需要保留每个分区中各节点的初始相对位置。

示例1：
输入：head = [1,4,3,2,5,2], x = 3
输出：[1,2,2,4,3,5]

示例2：
输入：head = [2,1], x = 2
输出：[1,2]

提示：
链表中节点的数目在范围[0, 200]内
-100 <= Node.val <= 100
-200 <= x <= 200
*/

struct ListNode {
  int val;
  struct ListNode* next;
};

struct ListNode* partition(struct ListNode* head, int x) {
  struct ListNode dummy1;
  struct ListNode* h1 = &dummy1;
  struct ListNode dummy2;
  struct ListNode* h2 = &dummy2;
  while (head) {
    if (head->val < x) {
      h1->next = head;
      h1 = h1->next;
    } else {
      h2->next = head;
      h2 = h2->next;
    }
    head = head->next;
  }
  h2->next = NULL;
  h1->next = dummy2.next;

  return dummy1.next;
}

class Solution {
 public:
  ListNode* partition(ListNode* head, int x) {
    ListNode dummy1(0, head);
    ListNode* h1 = &dummy1;
    ListNode dummy2(0, head);
    ListNode* h2 = &dummy2;

    while (head) {
      if (head->val < x) {
        h1->next = head;
        h1 = h1->next;
      } else {
        h2->next = head;
        h2 = h2->next;
      }

      head = head->next;
    }

    h2->next = nullptr;
    h1->next = dummy2.next;

    return dummy1.next;
  }
};
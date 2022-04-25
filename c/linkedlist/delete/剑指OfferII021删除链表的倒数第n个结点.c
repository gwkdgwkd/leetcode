/*
给定一个链表，删除链表的倒数第n个结点，并且返回链表的头结点。

示例1：
输入：head = [1,2,3,4,5], n = 2
输出：[1,2,3,5]

示例2：
输入：head = [1], n = 1
输出：[]

示例3：
输入：head = [1,2], n = 1
输出：[1]

提示：
链表中结点的数目为sz
1 <= sz <= 30
0 <= Node.val <= 100
1 <= n <= sz

进阶：能尝试使用一趟扫描实现吗？

注意：本题与19题相同
*/

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
  struct ListNode dummy;
  dummy.next = head;
  struct ListNode* slow = &dummy;
  struct ListNode* fast = &dummy;

  while (fast) {
    while (n-- >= 0) {
      fast = fast->next;
      continue;
    }
    if (fast) {
      fast = fast->next;
      slow = slow->next;
    }
  }

  struct ListNode* tmp = slow->next;
  slow->next = slow->next->next;
  free(tmp);
  tmp = NULL;

  return dummy.next;
}

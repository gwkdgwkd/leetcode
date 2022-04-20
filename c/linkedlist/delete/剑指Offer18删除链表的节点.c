/*
给定单向链表的头指针和一个要删除的节点的值，定义一个函数删除该节点。
返回删除后的链表的头节点。
注意：此题对比原题有改动

示例1:
输入: head = [4,5,1,9], val = 5
输出: [4,1,9]
解释:给定你链表中值为5的第二个节点，那么在调用了你的函数之后，该链表应变为4->1->9.

示例2:
输入: head = [4,5,1,9], val = 1
输出: [4,5,9]
解释:给定你链表中值为1的第三个节点，那么在调用了你的函数之后，该链表应变为4->5->9.

说明：
题目保证链表中节点的值互不相同
若使用C或C++语言，你不需要free或delete被删除的节点
*/

struct ListNode {
  int val;
  struct ListNode* next;
};

struct ListNode* deleteNode(struct ListNode* head, int val) {
  struct ListNode dummy;
  dummy.next = head;
  struct ListNode* l = &dummy;

  while (l->next) {
    if (l->next->val == val) {
      l->next = l->next->next;
      break;
    }
    l = l->next;
  }

  return dummy.next;
}
/*
 * @lc app=leetcode.cn id=19 lang=c
 *
 * [19] 删除链表的倒数第 N 个结点
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

// 双指针的经典应用，如果要删除倒数第n个节点，让fast移动n步，然后让fast和slow同时移动，直到fast指向链表末尾。删掉slow所指向的节点就可以了。
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
  // 使用虚拟头结点
  struct ListNode* dummyHead =
      (struct ListNode*)malloc(sizeof(struct ListNode));
  dummyHead->next = head;
  struct ListNode* fast = dummyHead;
  struct ListNode* slow = dummyHead;
  while (n-- && fast) {
    fast = fast->next;
  }
  // fast再提前走一步，因为需要让slow指向删除节点的上一个节点
  fast = fast->next;
  while (fast) {
    fast = fast->next;
    slow = slow->next;
  }
  struct ListNode* tmp = slow->next;
  slow->next = slow->next->next;
  free(tmp);
  tmp = NULL;

  return dummyHead->next;  // head不行，只有一个节点时，head不为NULL
}

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
  // 分别记录快指针，慢指针(要删除的节点)，以及慢指针前面的指针
  struct ListNode *fast, *slow, *f;
  f = fast = slow = head;
  int i = 1;
  if (!(head->next)) return NULL;

  // 快指针先走n个节点后，开始执行while,然快慢指针同时走，最后快指针走到尾部时，慢指针正好是倒数第n个
  while (i <= n) {
    fast = fast->next;
    i++;
  }
  while (fast) {
    fast = fast->next;
    slow = slow->next;
    if (fast) f = f->next;
  }

  // 当slow就是在头结点时
  if (slow == head)
    head = head->next;
  else
    f->next = slow->next;

  return head;
}
// @lc code=end

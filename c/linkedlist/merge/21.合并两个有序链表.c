/*
将两个升序链表合并为一个新的升序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。

示例1：
输入：l1 = [1,2,4], l2 = [1,3,4]
输出：[1,1,2,3,4,4]

示例2：
输入：l1 = [], l2 = []
输出：[]

示例3：
输入：l1 = [], l2 = [0]
输出：[0]

提示：
两个链表的节点数目范围是[0, 50]
-100 <= Node.val <= 100
l1和l2均按非递减顺序排列
*/

// 剑指Offer25合并两个排序的链表.c

struct ListNode {
  int val;
  struct ListNode* next;
};

// 使用局部变量作为虚拟表头
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
  struct ListNode head;
  struct ListNode* tail = &head;
  head.next = NULL;
  while (l1 && l2) {
    if (l1->val <= l2->val) {
      tail->next = l1;
      l1 = l1->next;
    } else {
      tail->next = l2;
      l2 = l2->next;
    }
    tail = tail->next;
  }
  tail->next = l1 ? l1 : l2;
  return head.next;
}

// 使用虚拟头节点
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
  struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
  dummy->next = NULL;
  struct ListNode* p = dummy;
  struct ListNode* p1 = l1;
  struct ListNode* p2 = l2;

  while (p1 && p2) {
    if (p1->val > p2->val) {
      p->next = p2;
      p2 = p2->next;
    } else {
      p->next = p1;
      p1 = p1->next;
    }
    p = p->next;
  }

  if (p1) {
    p->next = p1;
  }
  if (p2) {
    p->next = p2;
  }

  return dummy->next;
}

// 不使用虚拟头节点
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
  if (l1 == NULL) {
    return l2;
  }
  if (l2 == NULL) {
    return l1;
  }

  struct ListNode *newhead, *tail;
  if (l1->val <= l2->val) {
    newhead = l1;
    l1 = l1->next;
  } else {
    newhead = l2;
    l2 = l2->next;
  }
  tail = newhead;

  while (l1 && l2) {
    if (l1->val <= l2->val) {
      tail->next = l1;
      l1 = l1->next;
    } else {
      tail->next = l2;
      l2 = l2->next;
    }
    tail = tail->next;
  }

  if (!l1) {
    tail->next = l2;
  }
  if (!l2) {
    tail->next = l1;
  }

  return newhead;
}
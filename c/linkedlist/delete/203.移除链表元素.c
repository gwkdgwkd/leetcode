/*
 * @lc app=leetcode.cn id=203 lang=c
 *
 * [203] 移除链表元素
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

// 直接使用原来的链表来进行删除操作
struct ListNode* removeElements(struct ListNode* head, int val) {
  // 删除头节点
  while (head && head->val == val) {
    struct ListNode* tmp = head;
    head = head->next;
    free(tmp);
  }

  // 删除非头节点
  struct ListNode* cur = head;
  while (cur && cur->next) {
    if (cur->next->val == val) {
      struct ListNode* tmp = cur->next;
      cur->next = cur->next->next;
      free(tmp);
    } else {
      cur = cur->next;
    }
  }

  return head;
}

// 设置一个虚拟头结点在进行删除操作，以一种统一的逻辑来移除链表的节点
struct ListNode* removeElements(struct ListNode* head, int val) {
  struct ListNode* d = (struct ListNode*)malloc(sizeof(struct ListNode));
  d->next = head;
  struct ListNode* cur = d;

  while (cur->next) {
    if (cur->next->val == val) {
      struct ListNode* tmp = cur->next;
      cur->next = cur->next->next;
      free(tmp);
    } else {
      cur = cur->next;
    }
  }

  head = d->next;
  free(d);
  return head;
}

// 另一种写法，就是定义dummyHead的时候，不定义指针，而是定义实体，这样在程序结束的时候就自动释放内存了
struct ListNode* removeElements(struct ListNode* head, int val) {
  struct ListNode d;
  d.next = head;
  struct ListNode* cur = &d;

  while (cur->next) {
    if (cur->next->val == val) {
      struct ListNode* tmp = cur->next;
      cur->next = cur->next->next;
      free(tmp);
    } else {
      cur = cur->next;
    }
  }

  head = d.next;
  return head;
}

// @lc code=end

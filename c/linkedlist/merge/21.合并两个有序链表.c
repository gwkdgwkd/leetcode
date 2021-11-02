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
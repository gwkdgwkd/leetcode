struct ListNode *getIntersectionNode(struct ListNode *headA,
                                     struct ListNode *headB) {
  if (!headA || !headB) return NULL;
  struct ListNode *p = headA;
  struct ListNode *q = headB;

  while (p != q) {
    p = p ? p->next : headB;  // p走一步，如果走到A链表末尾，转到B链表
    q = q ? q->next : headA;  // q走一步，如果走到B链表末尾，转到A链表
  }

  return p;
}

struct ListNode *getIntersectionNode(struct ListNode *headA,
                                     struct ListNode *headB) {
  struct ListNode *curA = headA;
  struct ListNode *curB = headB;
  int countA = 0;
  int countB = 0;
  while (curA) {
    countA++;
    curA = curA->next;
  }
  while (curB) {
    countB++;
    curB = curB->next;
  }
  int diff = 0;
  struct ListNode *curL;
  struct ListNode *curS;
  if (countA >= countB) {
    diff = countA - countB;
    curL = headA;
    curS = headB;
  } else {
    diff = countB - countA;
    curL = headB;
    curS = headA;
  }
  while (diff--) {
    curL = curL->next;
  }
  while (curL) {
    if (curL == curS) {
      return curL;
    }
    curL = curL->next;
    curS = curS->next;
  }

  return NULL;
}
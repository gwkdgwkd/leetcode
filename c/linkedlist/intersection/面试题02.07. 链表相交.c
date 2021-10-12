/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
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
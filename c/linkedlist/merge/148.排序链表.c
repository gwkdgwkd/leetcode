/*
给你链表的头结点head，请将其按升序排列并返回排序后的链表。

示例1：
输入：head = [4,2,1,3]
输出：[1,2,3,4]

示例2：
输入：head = [-1,5,3,4,0]
输出：[-1,0,3,4,5]

示例3：
输入：head = []
输出：[]

提示：
链表中节点的数目在范围[0, 5 * 10^4]内
-10^5 <= Node.val <= 10^5

进阶：你可以在O(nlogn)时间复杂度和常数级空间复杂度下，对链表进行排序吗？
*/

struct ListNode {
  int val;
  struct ListNode* next;
};

// 自顶向下归并排序
// 时间复杂度：O(nlog⁡n)
// 空间复杂度：O(log⁡n)
struct ListNode* merge(struct ListNode* head1, struct ListNode* head2) {
  struct ListNode* dummyHead = malloc(sizeof(struct ListNode));
  dummyHead->val = 0;
  struct ListNode *temp = dummyHead, *temp1 = head1, *temp2 = head2;
  while (temp1 != NULL && temp2 != NULL) {
    if (temp1->val <= temp2->val) {
      temp->next = temp1;
      temp1 = temp1->next;
    } else {
      temp->next = temp2;
      temp2 = temp2->next;
    }
    temp = temp->next;
  }
  if (temp1 != NULL) {
    temp->next = temp1;
  } else if (temp2 != NULL) {
    temp->next = temp2;
  }
  return dummyHead->next;
}
struct ListNode* toSortList(struct ListNode* head, struct ListNode* tail) {
  if (head == NULL) {
    return head;
  }
  if (head->next == tail) {
    head->next = NULL;
    return head;
  }
  struct ListNode *slow = head, *fast = head;
  while (fast != tail) {
    slow = slow->next;
    fast = fast->next;
    if (fast != tail) {
      fast = fast->next;
    }
  }
  struct ListNode* mid = slow;
  return merge(toSortList(head, mid), toSortList(mid, tail));
}
struct ListNode* sortList(struct ListNode* head) {
  return toSortList(head, NULL);
}

// 自底向上归并排序
// 时间复杂度：O(nlog⁡n)
// 空间复杂度：O(1)
struct ListNode* merge(struct ListNode* head1, struct ListNode* head2) {
  struct ListNode* dummyHead = malloc(sizeof(struct ListNode));
  dummyHead->val = 0;
  struct ListNode *temp = dummyHead, *temp1 = head1, *temp2 = head2;
  while (temp1 != NULL && temp2 != NULL) {
    if (temp1->val <= temp2->val) {
      temp->next = temp1;
      temp1 = temp1->next;
    } else {
      temp->next = temp2;
      temp2 = temp2->next;
    }
    temp = temp->next;
  }
  if (temp1 != NULL) {
    temp->next = temp1;
  } else if (temp2 != NULL) {
    temp->next = temp2;
  }
  return dummyHead->next;
}
struct ListNode* sortList(struct ListNode* head) {
  if (head == NULL) {
    return head;
  }
  int length = 0;
  struct ListNode* node = head;
  while (node != NULL) {
    length++;
    node = node->next;
  }
  struct ListNode* dummyHead = malloc(sizeof(struct ListNode));
  dummyHead->next = head;
  for (int subLength = 1; subLength < length; subLength <<= 1) {
    struct ListNode *prev = dummyHead, *curr = dummyHead->next;
    while (curr != NULL) {
      struct ListNode* head1 = curr;
      for (int i = 1; i < subLength && curr->next != NULL; i++) {
        curr = curr->next;
      }
      struct ListNode* head2 = curr->next;
      curr->next = NULL;
      curr = head2;
      for (int i = 1; i < subLength && curr != NULL && curr->next != NULL;
           i++) {
        curr = curr->next;
      }
      struct ListNode* next = NULL;
      if (curr != NULL) {
        next = curr->next;
        curr->next = NULL;
      }
      struct ListNode* merged = merge(head1, head2);
      prev->next = merged;
      while (prev->next != NULL) {
        prev = prev->next;
      }
      curr = next;
    }
  }
  return dummyHead->next;
}

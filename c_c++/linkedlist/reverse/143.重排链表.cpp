/*
给定一个单链表L的头节点head，单链表L表示为：
L0 → L1 → … → Ln - 1 → Ln
请将其重新排列后变为：
L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

示例1：
输入：head = [1,2,3,4]
输出：[1,4,2,3]

示例2：
输入：head = [1,2,3,4,5]
输出：[1,5,2,4,3]

提示：
链表的长度范围为 [1, 5*10^4]
1 <= node.val <= 1000
*/

// 剑指OfferII026重排链表

struct ListNode {
  int val;
  struct ListNode* next;
};

// 线性表
void reorderList(struct ListNode* head) {
  if (head == NULL) {
    return;
  }
  struct ListNode* vec[40001];
  struct ListNode* node = head;
  int n = 0;
  while (node != NULL) {
    vec[n++] = node;
    node = node->next;
  }
  int i = 0, j = n - 1;
  while (i < j) {
    vec[i]->next = vec[j];
    i++;
    if (i == j) {
      break;
    }
    vec[j]->next = vec[i];
    j--;
  }
  vec[i]->next = NULL;
}

// 寻找链表中点 + 链表逆序 + 合并链表
struct ListNode* reverse(struct ListNode* root) {
  struct ListNode* left = NULL;
  struct ListNode* cur = root;
  struct ListNode* right;

  while (cur) {
    right = cur->next;
    cur->next = left;
    left = cur;
    cur = right;
  }

  return left;
}
void reorderList(struct ListNode* head) {
  if (head == NULL) {
    return head;
  }

  struct ListNode* slow = head;
  struct ListNode* fast = head;
  while (fast->next && fast->next->next) {
    fast = fast->next->next;
    slow = slow->next;
  }
  struct ListNode* tmp = slow->next;
  slow->next = NULL;

  struct ListNode* l1 = head;
  struct ListNode* l2 = reverse(tmp);

  while (l1 && l2) {
    struct ListNode* tmp1 = l1->next;
    struct ListNode* tmp2 = l2->next;
    l1->next = l2;
    l1 = tmp1;
    l2->next = l1;
    l2 = tmp2;
  }

  return head;
}

class Solution {
  ListNode* reverse(ListNode* head) {
    ListNode* left = nullptr;
    ListNode* curr = head;
    ListNode* right;
    while (curr) {
      right = curr->next;
      curr->next = left;
      left = curr;
      curr = right;
    }

    return left;
  }
  void merge(ListNode* head1, ListNode* head2) {
    ListNode* h1;
    ListNode* h2;
    while (head1 && head2) {
      h1 = head1->next;
      h2 = head2->next;

      head1->next = head2;
      head1 = h1;
      head2->next = head1;
      head2 = h2;
    }
  }

 public:
  void reorderList(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
      fast = fast->next->next;
      slow = slow->next;
    }

    ListNode* tmp = slow->next;
    slow->next = nullptr;
    ListNode* head2 = reverse(tmp);

    merge(head, head2);
  }
};
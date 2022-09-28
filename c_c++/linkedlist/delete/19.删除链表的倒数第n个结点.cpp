/*
给你一个链表，删除链表的倒数第n个结点，并且返回链表的头结点。

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

进阶：你能尝试使用一趟扫描实现吗？
*/

// 剑指OfferII021删除链表的倒数第n个结点

struct ListNode {
  int val;
  struct ListNode* next;
};

// 双指针的经典应用，如果要删除倒数第n个节点，让fast移动n步，
// 然后让fast和slow同时移动，直到fast指向链表末尾。
// 删掉slow所指向的节点就可以了。
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
  struct ListNode dummy;  // 使用虚拟头节点，统一逻辑
  dummy.next = head;
  struct ListNode* fast = &dummy;
  struct ListNode* slow = &dummy;

  while (fast) {
    // 等于0，让fast多走一步，最终slow停在删除节点之前：
    if (n-- >= 0) {
      fast = fast->next;
      continue;
    }
    if (fast) {
      fast = fast->next;
      slow = slow->next;
    }
  }

  struct ListNode* del = slow->next;  // 防止内存泄露
  slow->next = slow->next->next;
  free(del);
  del = NULL;

  // 不能返回head，只有一个节点时，head为NULL：
  return dummy.next;
}

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
  // 分别记录快指针，慢指针(要删除的节点)，以及慢指针前面的指针
  struct ListNode *fast, *slow, *f;
  f = fast = slow = head;
  int i = 1;
  if (!(head->next)) return NULL;

  // 快指针先走n个节点后，开始执行while，然快慢指针同时走，
  // 最后快指针走到尾部时，慢指针正好是倒数第n个：
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

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
  struct ListNode *fast, *slow;
  fast = slow = head;

  while (n-- > 0) {  // 快指针先前进n步
    fast = fast->next;
  }

  if (fast == NULL) {
    // 如果此时快指针走到头了，说明倒数第n个节点就是第一个节点：
    return head->next;
  }

  // 让慢指针和快指针同步向前：
  while (fast != NULL && fast->next != NULL) {
    fast = fast->next;
    slow = slow->next;
  }

  // slow.next就是倒数第n个节点的前一个节点，删除它：
  slow->next = slow->next->next;
  return head;
}

class Solution {
 public:
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy;
    dummy.next = head;
    ListNode* fast = &dummy;
    ListNode* slow = &dummy;

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
    ListNode* del = slow->next;
    slow->next = slow->next->next;
    delete (del);
    del = nullptr;

    return dummy.next;
  }
};

// 剑指Offer22链表中倒数第k个节点，输出该链表中倒数第k个节点
struct ListNode* getKthFromEnd(struct ListNode* head, int k) {
  struct ListNode* fast = head;
  struct ListNode* slow = head;

  while (k-- && fast) {
    fast = fast->next;
  }

  while (fast) {
    fast = fast->next;
    slow = slow->next;
  }

  return slow;
}

// 面试题0202返回倒数第k个节点，输出节点的值
int kthToLast(struct ListNode* head, int k) {
  struct ListNode* fast = head;
  struct ListNode* slow = head;

  while (k-- && fast) {
    fast = fast->next;
  }

  while (fast) {
    fast = fast->next;
    slow = slow->next;
  }

  return slow->val;
}
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

进阶：可以在O(nlogn)时间复杂度和常数级空间复杂度下，对链表进行排序吗？
*/

struct ListNode {
  int val;
  struct ListNode* next;
};

// 自顶向下归并排序
// 时间复杂度：O(nlog⁡n)
// 空间复杂度：O(log⁡n)，由于递归导致的
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

class Solution {
 public:
  // 21.合并两个有序链表：
  ListNode* merge(ListNode* list1, ListNode* list2) {
    ListNode dummy;
    ListNode* cur = &dummy;
    ListNode* l1 = list1;
    ListNode* l2 = list2;
    while (l1 && l2) {
      if (l1->val < l2->val) {
        cur->next = l1;
        l1 = l1->next;
      } else {
        cur->next = l2;
        l2 = l2->next;
      }
      cur = cur->next;
    }
    cur->next = l1 ? l1 : l2;
    return dummy.next;
  }
  ListNode* twoList(ListNode* start, ListNode* end) {
    if (start == nullptr) {
      return start;
    }
    if (start->next == end) {
      start->next = nullptr;
      return start;
    }
    ListNode* slow = start;
    ListNode* fast = start;
    while (fast != end && fast->next != end) {
      fast = fast->next->next;
      slow = slow->next;
    }

    ListNode* l = twoList(start, slow);  // slow此时就是mid
    ListNode* r = twoList(slow, end);
    return merge(l, r);
  }
  ListNode* sortList(ListNode* head) { return twoList(head, nullptr); }
};

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

class Solution {
 public:
  // 21.合并两个有序链表：
  ListNode* merge(ListNode* list1, ListNode* list2) {
    ListNode dummy;
    ListNode* cur = &dummy;
    ListNode* l1 = list1;
    ListNode* l2 = list2;
    while (l1 && l2) {
      if (l1->val < l2->val) {
        cur->next = l1;
        l1 = l1->next;
      } else {
        cur->next = l2;
        l2 = l2->next;
      }
      cur = cur->next;
    }
    cur->next = l1 ? l1 : l2;
    return dummy.next;
  }

  // 使用迭代，不用递归，所以空间复杂度为：O(1)
  ListNode* sortList(ListNode* head) {
    if (head == nullptr) {
      return head;
    }

    // 统计链表节点个数：
    ListNode* node = head;
    int n = 0;
    while (node) {
      node = node->next;
      ++n;
    }

    ListNode dummy(0, head);                 // 虚拟头节点
    for (int len = 1; len < n; len <<= 1) {  // 遍历子链表长度
      ListNode* prev = &dummy;
      ListNode* curr = dummy.next;
      while (curr) {
        // 找到长度为len的子链表1：
        ListNode* head1 = curr;
        for (int i = 1; i < len && curr->next; ++i) {
          curr = curr->next;
        }
        ListNode* head2 = curr->next;
        curr->next = nullptr;  // 子链表尾部为空
        curr = head2;
        // 找到长度为len的子链表2：
        for (int i = 1; i < len && curr && curr->next; ++i) {
          curr = curr->next;
        }
        ListNode* remain = nullptr;  // 标记子链表1和2后面的节点
        if (curr != nullptr) {
          remain = curr->next;
          curr->next = nullptr;
        }
        prev->next = merge(head1, head2);  // 排序子链表1和子链表2
        while (prev->next) {
          prev = prev->next;
        }
        curr = remain;  // curr指向没排序子链表，下次循环继续拆分排序
      }
    }

    return dummy.next;
  }
};

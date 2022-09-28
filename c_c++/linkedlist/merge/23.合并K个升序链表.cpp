/*
给你一个链表数组，每个链表都已经按升序排列。
请你将所有链表合并到一个升序链表中，返回合并后的链表。

示例1：
输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
[
  1->4->5,
  1->3->4,
  2->6
]
将它们合并到一个有序链表中得到。
1->1->2->3->4->4->5->6

示例2：
输入：lists = []
输出：[]

示例3：
输入：lists = [[]]
输出：[]

提示：
k == lists.length
0 <= k <= 10^4
0 <= lists[i].length <= 500
-10^4 <= lists[i][j] <= 10^4
lists[i]按升序排列
lists[i].length的总和不超过10^4
*/

// 剑指OfferII078合并排序链表

struct ListNode {
  int val;
  struct ListNode* next;
};

// 暴力法
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
  struct ListNode *head = NULL, *tail = NULL;
  int nums[10000] = {0};  // 创建数组用来保存链表数组的值
  int i = 0, j = 0, k = 0, min = 0, swap = 0;
  for (; i < listsSize; i++) {  // 保存链表数组的值
    while (lists[i]) {
      nums[k++] = lists[i]->val;
      lists[i] = lists[i]->next;
    }
  }
  for (i = 0; i < k; i++) {  // 简单选择排序
    min = i;
    for (j = i + 1; j < k; j++) {
      if (nums[j] < nums[min]) {
        min = j;
      }
    }
    if (min != i) {
      swap = nums[i];
      nums[i] = nums[min];
      nums[min] = swap;
    }
  }
  for (i = 0; i < k; i++) {  // 新链表
    if (!head) {
      struct ListNode* p = malloc(sizeof(struct ListNode));
      head = p;
      tail = p;
      p->val = nums[i];
      p->next = NULL;
    } else {
      struct ListNode* p = malloc(sizeof(struct ListNode));
      p->val = nums[i];
      p->next = NULL;
      tail->next = p;
      tail = p;
    }
  }
  return head;
}

// 逐一比较
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
  struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
  dummy->next = NULL;
  struct ListNode* p = dummy;

  while (1) {
    struct ListNode* min = NULL;
    int index = -1;
    int i;
    // 找到当前所以表头中最小的那个
    for (i = 0; i < listsSize; ++i) {
      if (lists[i] == NULL) {
        continue;
      }
      if (min == NULL) {
        // 找到第一个非空的表头，赋值
        min = lists[i];
        index = i;
      } else {
        // 如果找到更小的表头，更新
        if (min->val > lists[i]->val) {
          min = lists[i];
          index = i;
        }
      }
    }
    if (i == listsSize && min == NULL) {
      // 所有列表都为空，跳出循环
      break;
    }
    p->next = min;
    p = p->next;
    lists[index] = lists[index]->next;
  }

  return dummy->next;
}

// 逐一两两排序
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
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
  if (listsSize == 0) return NULL;
  struct ListNode *l1, *l2;
  l1 = lists[0];
  for (int i = 1; i < listsSize; ++i) {
    l2 = lists[i];
    l1 = mergeTwoLists(l1, l2);
  }

  return l1;
}

// 堆排序
void HeapBuild(struct ListNode** A, int len) {  // 建堆
  for (int i = len / 2 - 1; i >= 0; i--) {
    HeapAdjust(A, i, len);
  }
}
void HeapAdjust(struct ListNode** A, int k, int len) {  // 堆调整
  struct ListNode* swap = NULL;
  for (int i = 2 * k + 1; i < len; i = 2 * i + 1) {
    if (i + 1 < len && A[i + 1]->val < A[i]->val) {
      i++;
    }
    if (A[k]->val <= A[i]->val) {
      break;
    } else {
      swap = A[k];
      A[k] = A[i];
      A[i] = swap;
      k = i;
    }
  }
}
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
  struct ListNode** heap = malloc(listsSize * sizeof(struct ListNode));
  struct ListNode *head = malloc(sizeof(struct ListNode)), *tail = head;
  head->next = NULL;
  int i, j = 0, k = listsSize;
  for (i = 0; i < k; i++) {  // 去除空指针，建堆
    if (!lists[i]) {
      listsSize--;
    } else {
      heap[j++] = lists[i];
    }
  }
  while (listsSize) {
    HeapBuild(heap, listsSize);  // 反复调整为小顶堆
    tail->next = heap[0];
    tail = tail->next;
    if (heap[0]->next) {
      heap[0] = heap[0]->next;
    } else {  // heap[0]->next空，将堆最后一个链表放到堆顶
      listsSize--;
      heap[0] = heap[listsSize];
    }
  }
  return head->next;
}

// 归并排序，这个最快啊
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
struct ListNode* TwoLists(struct ListNode** lists, int l, int r) {  // 递归分治
  if (l == r) return lists[l];
  if (l > r) return NULL;
  int mid = l + (r - l) / 2;
  struct ListNode* l1 = TwoLists(lists, l, mid);
  struct ListNode* l2 = TwoLists(lists, mid + 1, r);
  return mergeTwoLists(l1, l2);
}
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
  if (!listsSize) return NULL;
  return TwoLists(lists, 0, listsSize - 1);
}

class Solution {
  // 21.合并两个有序链表：
  ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode dummy;
    ListNode* curr = &dummy;
    ListNode* l1 = list1;
    ListNode* l2 = list2;
    while (l1 && l2) {
      if (l1->val < l2->val) {
        curr->next = l1;
        l1 = l1->next;
      } else {
        curr->next = l2;
        l2 = l2->next;
      }
      curr = curr->next;
    }
    if (l1) {
      curr->next = l1;
    }
    if (l2) {
      curr->next = l2;
    }
    return dummy.next;
  }
  ListNode* TwoLists(vector<ListNode*>& lists, int left, int right) {
    if (left == right) {
      return lists[left];
    }
    if (left > right) {
      return nullptr;
    }

    int mid = left + (right - left) / 2;
    ListNode* l = TwoLists(lists, left, mid);
    ListNode* r = TwoLists(lists, mid + 1, right);
    return mergeTwoLists(l, r);
  }

 public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    return TwoLists(lists, 0, lists.size() - 1);
  }
};

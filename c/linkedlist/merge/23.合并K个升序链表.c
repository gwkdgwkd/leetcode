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

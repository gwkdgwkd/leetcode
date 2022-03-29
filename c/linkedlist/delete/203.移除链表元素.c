/*
给你一个链表的头节点head和一个整数val，请你删除链表中所有满足Node.val == val的节点，并返回新的头节点。

示例1：
输入：head = [1,2,6,3,4,5,6], val = 6
输出：[1,2,3,4,5]

示例2：
输入：head = [], val = 1
输出：[]

示例3：
输入：head = [7,7,7,7], val = 7
输出：[]

提示：
列表中的节点数目在范围[0, 104]内
1 <= Node.val <= 50
0 <= val <= 50
*/

struct ListNode {
  int val;
  struct ListNode* next;
};

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
  struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
  dummy->next = head;
  struct ListNode* cur = dummy;

  while (cur->next) {
    if (cur->next->val == val) {
      struct ListNode* tmp = cur->next;
      cur->next = cur->next->next;
      free(tmp);
    } else {
      cur = cur->next;
    }
  }

  head = dummy->next;
  free(dummy);
  return head;
}

// 另一种写法，就是定义dummyHead的时候，不定义指针，而是定义实体，这样在程序结束的时候就自动释放内存了
struct ListNode* removeElements(struct ListNode* head, int val) {
  struct ListNode dummy;
  dummy.next = head;
  struct ListNode* cur = &dummy;

  while (cur->next) {
    if (cur->next->val == val) {
      struct ListNode* tmp = cur->next;
      cur->next = cur->next->next;
      free(tmp);
      tmp = NULL;
    } else {
      cur = cur->next;
    }
  }

  return dummy.next;
}

// @lc code=end

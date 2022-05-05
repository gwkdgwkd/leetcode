/*
编写代码，移除未排序链表中的重复节点。保留最开始出现的节点。

示例1:
输入：[1, 2, 3, 3, 2, 1]
输出：[1, 2, 3]

示例2:
输入：[1, 1, 1, 1, 2]
输出：[1, 2]

提示：
链表长度在[0, 20000]范围内。
链表元素在[0, 20000]范围内。

进阶：如果不得使用临时缓冲区，该怎么解决？
*/

struct ListNode {
  int val;
  struct ListNode* next;
};

// 两遍循环
struct ListNode* removeDuplicateNodes(struct ListNode* head) {
  struct ListNode* h1 = head;
  while (h1) {
    struct ListNode* h2 = h1;
    while (h2->next) {
      if (h2->next->val == h1->val) {
        h2->next = h2->next->next;
      } else {
        h2 = h2->next;
      }
    }
    h1 = h1->next;
  }
  return head;
}
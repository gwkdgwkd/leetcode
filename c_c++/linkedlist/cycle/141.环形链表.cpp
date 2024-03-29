/*
给你一个链表的头节点head，判断链表中是否有环。
如果链表中有某个节点，可以通过连续跟踪next指针再次到达，则链表中存在环。
为了表示给定链表中的环，使用整数pos来表示链表尾连接到链表中的位置（从0开始）。
注意：pos不作为参数进行传递，仅仅是为了标识链表的实际情况。
如果链表中存在环，则返回true；否则，返回false。

示例1：
输入：head = [3,2,0,-4], pos = 1
输出：true
解释：链表中有一个环，其尾部连接到第二个节点。

示例2：
输入：head = [1,2], pos = 0
输出：true
解释：链表中有一个环，其尾部连接到第一个节点。

示例3：
输入：head = [1], pos = -1
输出：false
解释：链表中没有环。

提示：
链表中节点的数目范围是 [0, 10^4]
-10^5 <= Node.val <= 10^5
pos为-1或者链表中的一个 有效索引。

进阶：你能用O(1)内存解决此问题吗？
*/

struct ListNode {
  int val;
  struct ListNode *next;
};

// 快慢指针
bool hasCycle(struct ListNode *head) {
  struct ListNode *fast = head;
  struct ListNode *slow = head;

  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;
    if (fast == slow) {
      return true;
    }
  }

  return false;
}

class Solution {
 public:
  bool hasCycle(ListNode *head) {
    ListNode *fast = head;
    ListNode *slow = head;
    while (fast && fast->next) {
      fast = fast->next->next;
      slow = slow->next;
      if (fast == slow) {
        return true;
      }
    }

    return false;
  }
};
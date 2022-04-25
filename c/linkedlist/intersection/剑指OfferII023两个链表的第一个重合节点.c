/*
给定两个单链表的头节点headA和headB，请找出并返回两个单链表相交的起始节点。
如果两个链表没有交点，返回null。
题目数据 保证 整个链式结构中不存在环。
注意，函数返回结果后，链表必须保持其原始结构。

示例1：
输入：intersectVal= 8,listA= [4,1,8,4,5],listB= [5,0,1,8,4,5],skipA= 2,skipB= 3
输出：Reference of the node with value = 8
输入解释：相交节点的值为8（注意，如果两个列表相交则不能为 0）。
从各自的表头开始算起，链表A为[4,1,8,4,5]，链表B为[5,0,1,8,4,5]。
在A中，相交节点前有2个节点；在B中，相交节点前有3个节点。

示例2：
输入：intersectVal = 2,listA = [0,9,1,2,4],listB = [3,2,4],skipA = 3,skipB = 1
输出：Reference of the node with value = 2
输入解释：相交节点的值为2（注意，如果两个列表相交则不能为0）。
从各自的表头开始算起，链表A为[0,9,1,2,4]，链表B为[3,2,4]。
在A中，相交节点前有3个节点；在B中，相交节点前有1个节点。

示例3：
输入：intersectVal = 0,listA = [2,6,4],listB = [1,5],skipA = 3,skipB = 2
输出：null
输入解释：从各自的表头开始算起，链表A为[2,6,4]，链表B为[1,5]。
由于这两个链表不相交，所以intersectVal必须为0，而skipA和skipB可以是任意值。
解释：这两个链表不相交，因此返回null。

提示：
listA中节点数目为m
listB中节点数目为n
0 <= m, n <= 3 * 10^4
1 <= Node.val <= 10^5
0 <= skipA <= m
0 <= skipB <= n
如果listA和listB没有交点，intersectVal为0
如果listA和listB有交点，intersectVal == listA[skipA + 1] == listB[skipB + 1]

进阶：能否设计一个时间复杂度O(n) 、仅用O(1)内存的解决方案？

注意：本题与160题相同
*/

struct ListNode *getIntersectionNode(struct ListNode *headA,
                                     struct ListNode *headB) {
  if (headA == NULL || headB == NULL) return NULL;

  struct ListNode *la = headA;
  struct ListNode *lb = headB;

  while (la != lb) {
    la = la ? la->next : headB;
    lb = lb ? lb->next : headA;
  }

  return la;
}
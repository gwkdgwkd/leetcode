/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

int getDecimalValue(struct ListNode* head){
    unsigned int rstNum=0;
    while(head) {
        //rstNum = rstNum<<1;
        //rstNum ^= head->val;
        rstNum = (rstNum << 1) | (head->val);
        head = head->next;
    }
    return rstNum;
}

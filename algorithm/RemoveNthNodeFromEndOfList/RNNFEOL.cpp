/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode tempHead(0);
        tempHead.next = head;
        ListNode *removeFront = &tempHead,*nowUse = head;
        
        while(nowUse) {
            nowUse = nowUse->next;
            if(n) n--;
            else removeFront = removeFront->next;
        }
        removeFront->next = removeFront->next->next;
        head = tempHead.next;
        return head;
    }
};
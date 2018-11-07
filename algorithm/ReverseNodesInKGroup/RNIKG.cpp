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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode root(0);
        root.next = head;
        ListNode* use = &root;
        while(use) {
            ListNode* tail = use->next;
            for(int i = 0 ; i < k-1 ; i++) {
                if(tail) tail = tail->next;
            }
            if(!tail) return root.next;
            use = SubReverse(use,tail);
        }
        return root.next;
    }
private:
    ListNode* SubReverse(ListNode* head, ListNode* tail) {
        ListNode* use = head->next;
        ListNode* newhead = use;
        ListNode rList(0);
        rList.next = tail->next;
        while(rList.next!=tail) {
            ListNode* temp = use->next;
            use->next = rList.next;
            rList.next = use;
            use = temp;
            if(temp) temp = temp->next;
        }
        head->next = rList.next;
        return newhead;
    }
};
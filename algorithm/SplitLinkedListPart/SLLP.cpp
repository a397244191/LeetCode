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
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        int len = 0;
        ListNode* use = root;

        while(use != NULL) {
            len++;
            use = use->next;
        }
        vector<ListNode*> ans;
        ListNode* head = NULL;
        int eachPartN = len/k;
        int moreOneP = len%k;
        
        use = root;
        for(int i = 0 ; i < k ; i++){
            head = NULL;
            ListNode* go = NULL;
            if(i <moreOneP){
                head = go = new ListNode(use->val);
                use = use->next;
            }
            for(int j = 0 ; j < eachPartN ; j++){
                ListNode* now = new ListNode(use->val);
                if(go != NULL)
                    go->next = now;
                else head = now;
                go = now;
                use = use->next;
            }
            ans.push_back(head);
        }
        return ans;
    }
};